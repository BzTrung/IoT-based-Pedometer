#include "MQTTClient.h"
/*
Broker: broker.emqx.io
TCP Port: 1883 
*/
#define ADDRESS     "ws://broker.emqx.io:8083"
#define CLIENTID    "pedometer"
#define SUB_TOPIC   "data/threshold"
#define PUB_TOPIC   "data/AnStep"
#define QOS         1

void publish(MQTTClient client, char* topic, char* payload) {
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    pubmsg.payload = payload;
    pubmsg.payloadlen = strlen(pubmsg.payload);
    pubmsg.qos = 1;
    pubmsg.retained = 0;
    MQTTClient_deliveryToken token;
    MQTTClient_publishMessage(client, topic, &pubmsg, &token);
    MQTTClient_waitForCompletion(client, token, 1000L);
    printf("Message '%s' with delivery token %d delivered\n", payload, token);
}

