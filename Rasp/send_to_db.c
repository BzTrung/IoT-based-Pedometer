#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h> // -lm
#include "unistd.h"
#include "string.h"
#include <stdlib.h>
#include "MPU6050.h"
#include "mqtt_pub_sub.h"

float A,threshold;
uint8_t sampling,flag;
uint16_t step;

float get_A_value(void)
{
    //uint16_t coef = 2046.0;
    uint16_t coef = 8192.0;
    float Ax = (float)read_value(Acc_X)/coef;
    float Ay = (float)read_value(Acc_Y)/coef;
    float Az = (float)read_value(Acc_Z)/coef;
    return sqrt(pow(Ax,2)+pow(Ay,2)+pow(Az,2));
}

PI_THREAD (myThread)
{
    mpu6050 = wiringPiI2CSetup(0x68);
    init_mpu6050(19,6,0x08,0x08,0x01);

    A=0;sampling=0; flag=1; step=0;
    threshold = 1.25;
    
    while(1)
    {
        A = get_A_value();
        if (A > threshold && flag == 0)
        {
            step++;
            flag = 1;
        }

        else if (A > threshold && flag == 1)
        {
        }

        else if (A < threshold && flag == 1)
        {
            flag = 0;
        }

        delay(100);
    }
    return 0;
	
}

int on_message(void *context, char *topicName, int topicLen, MQTTClient_message *message) {
    char* payload = message->payload;
    printf("Received message: %s\n", payload);
    threshold = atof(payload);
    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);
    return 1;
}

int main(int argc, char* argv[])
{
    piThreadCreate (myThread);

    MQTTClient client;
    MQTTClient_create(&client, ADDRESS, CLIENTID, MQTTCLIENT_PERSISTENCE_NONE, NULL);
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
	MQTTClient_setCallbacks(client, NULL, NULL, on_message, NULL);
    
    int rc;
    if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS) {
        printf("Failed to connect, return code %d\n", rc);
        exit(-1);
    }
    //listen for operation
    MQTTClient_subscribe(client, SUB_TOPIC, 0);
    while(1) {
        char msg [20];
        sprintf(msg,"{\"A\":%0.2f,\"step\":%lu}",A,step);
  
        publish(client, PUB_TOPIC, msg);
        delay(100);
        printf("threshold: %0.2f\n",threshold);
    }
    MQTTClient_disconnect(client, 1000);
    MQTTClient_destroy(&client);
    return rc;
    
}