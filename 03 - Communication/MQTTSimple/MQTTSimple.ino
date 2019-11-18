/*
 Basic MQTT example

 This sketch demonstrates the basic capabilities of the library.
 It connects to an MQTT server then:
  - publishes "hello world" to the topic "outTopic"
  - subscribes to the topic "inTopic", printing out any messages
    it receives. NB - it assumes the received payloads are strings not binary

 It will reconnect to the server if the connection is lost using a blocking
 reconnect function. See the 'mqtt_reconnect_nonblocking' example for how to
 achieve the same result without blocking the main loop.
 
*/

#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

//TODO Atualizar valores do MAC e IP do servidor MQTT
byte mac[]    = {0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED};
String server = "m14.cloudmqtt.com";
//IPAddress server(192, 168, 0, 101);
//int port = 1883;
int port = 12891;

String clientName = "arduinoClient01"; //TODO change it!!
String username = "vqlvmcfj";
String password = "Vzw6NIX4voxY";

//Aqui são tratadas as mensagens que são recebidas do servidor MQTT
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");

  String message = "";
  
  for (int i=0;i<length;i++) {
    message += (char)payload[i];
  }

  Serial.println(message);
}

EthernetClient ethClient;
PubSubClient client(ethClient);

void connectToMQTTBroker() {
    Serial.println("Aqui!");
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(clientName.c_str(), username.c_str(), password.c_str())) {
    //if (client.connect(clientName.c_str())) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println("trying again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
  
}

//Aqui acontecem as inscrições em tópicos
void subscribeToTopics() {

  client.subscribe("topicoEntrada");

}

void setup()
{
  Serial.begin(9600);
  Serial.println("A");
  Ethernet.begin(mac);
  delay(1500);
  Serial.println("B");

  client.setServer(server.c_str(), port);
  client.setCallback(callback);

  Serial.println("C");

  connectToMQTTBroker();
  subscribeToTopics();
  
}

void loop()
{
  if(!client.connected()) {
    connectToMQTTBroker();
    subscribeToTopics();
  }
  
  client.loop();
}
