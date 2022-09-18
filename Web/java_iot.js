
//-----------------------------MQTT connection-------------------------//
var host = "broker.emqx.io";
var port = 8083;
var topic1 = "data/AnStep";
var topic2 = "data/threshold";

// Khoi tao ket noi Paho client
var client = new Paho.MQTT.Client(host, Number(port),"TTP"); // sua lai host; port
client.qos = 1;
client.retained = 0;
client.destinationName = topic1;

// Cac function nay se duoc goi khi co gi do xay ra(mat ket noi, nhan duoc du lieu)
client.onConnectionLost = onConnectionLost;
client.onMessageArrived = onMessageArrived;

// tien hanh ket noi voi client
client.connect({onSuccess:onConnect});

// called when the client connects
function onConnect() {
  // Once a connection has been made, make a subscription and send a message.
  console.log("onConnect to "+topic1);
  client.subscribe(topic1);  

}

// goi ham nay toi khi client duoc ket noi
function Connect() {  
    message = new Paho.MQTT.Message("Hello"); // gui tin nhan da ket noi duoc toi publisher
    message.destinationName = topic1;
    message.qos = 1;
    console.log(message);
    client.send(message);
  }

// ham duoc goi khi tin nhan gui duoc nhan
function onMessageArrived(message) {
    console.log("onMessageArrived:"+message.payloadString);
  }

  // goi ham nay khi mat ket noi voi client
function onConnectionLost(responseObject) {
    if (responseObject.errorCode !== 0) {
      console.log("onConnectionLost:"+responseObject.errorMessage);
    }

  }
// yeu cau nhan du lieu tu broker 
   function onMessageArrived(message) { 

    var data=message.payloadString;
    console.log(data); // coi data lay ve la dang gi ( array or structure)
    const convert=JSON.parse(data);
    document.getElementById('a_id').value=convert.A;
    document.getElementById('step_id').value=convert.step;

    $(document).ready(function(){
      //new
      $.post("addData_mpu.php",$('#form_mpu').serialize(),function(){/*alert("sent") */});
      });


 }
// Create mqtt client2
var client2 = new Paho.MQTT.Client(host, Number(port), "ttp2");

client2.destinationName = topic2;
client2.qos = 1;
client2.retained = true;

// set callback handlers
client2.onConnectionLost = onConnectionLost_2;
client2.onMessageArrived = onMessageArrived_2;

// connect the client
client2.connect({onSuccess:onConnect2});


// called when the client connects
function onConnect2() {
  // Once a connection has been made, make a subscription and send a message.
  console.log("onConnect to "+topic2);

}
function publish_client()
{
    var A_threshold =document.getElementById("set_threshold_id").value;
    message = new Paho.MQTT.Message(A_threshold);
    message.destinationName = topic2;
    message.qos = 1;
    console.log(message);
    client2.send(message);
    document.getElementById("threshold_id").value=A_threshold;
    alert('Success');
    

}

// called when the client loses its connection
function onConnectionLost_2(responseObject) {
  if (responseObject.errorCode !== 0) {
    console.log("onConnectionLost:"+responseObject.errorMessage);
  }
  
}
function onMessageArrived_2(message) {

    
  console.log("onMessageArrived from " + topic2 + ":" + message.payloadString);
}

 