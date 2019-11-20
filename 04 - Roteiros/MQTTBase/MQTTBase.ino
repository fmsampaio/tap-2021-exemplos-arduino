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
#include <Ultrasonic.h>
#include "DHT.h"
#include <Servo.h>

unsigned long startMillis;  //some global variables available anywhere in the program
unsigned long currentMillis;
const unsigned long period = 1000;  //the value is a number of milliseconds

int pinLDR = A0;
Ultrasonic ultrassom(6, 5); 

byte mac[]    = {0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED}; //TODO modificar aqui!!
IPAddress server(192, 168, 2, 19);
int port = 1883;

String clientName = "arduinoClient01"; //TODO modificar aqui!!

#define DHTPIN A1
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

int pinPIR = 7;

Servo servo1, servo2;

//Aqui são tratadas as mensagens que são recebidas do servidor MQTT
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");

  String message = "";
  
  for (int i=0;i<length;i++) {
    message += (char)payload[i];
  }

  String topicStr = String(topic);
  if(topicStr.equals("servo1")) {
    int ang = message.toInt();
    servo1.write(ang);
  }
  if(topicStr.equals("servo2")) {
    int ang = message.toInt();
    servo2.write(ang);
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
    if (client.connect(clientName.c_str())) {
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
  client.subscribe("servo1");
  client.subscribe("servo2"); 
}

void publishLuminosity() {
    int lum = analogRead(A0);
    String lumStr = lum < 300 ? "Muito escuro" :
                    lum < 600 ? "Escuro" :
                    lum < 900 ? "Claro" :
                    "Muito claro";
    client.publish("luminosidade", lumStr.c_str());
}

void publishDistance() {
    long dist = ultrassom.Ranging(CM);
    String distStr = String(dist);
    client.publish("distancia", distStr.c_str());
}

void publishTempHum() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  // testa se retorno é valido, caso contrário algo está errado.
  if (isnan(t) || isnan(h)) 
  {
    Serial.println("Failed to read from DHT");
  } 
  else
  {
    String humStr = String(h);
    String tempStr = String(t);
    client.publish("temperatura", tempStr.c_str());
    client.publish("umidade", humStr.c_str());
    
  }
}

void setup()
{
  Serial.begin(9600);
  Ethernet.begin(mac);
  delay(1500);

  Serial.println("Interface ethernet iniciada...");

  client.setServer(server, port);
  client.setCallback(callback);

  connectToMQTTBroker();
  subscribeToTopics();

  startMillis = millis();  //initial start time

  dht.begin();
  pinMode(pinPIR, INPUT);
  servo1.attach(3);
  servo2.attach(9);
  
}

void publishPresence() {
  int presence = digitalRead(pinPIR);
  if(presence == HIGH) {
    client.publish("presenca", "Presença detectada!");
  }
  else {
    client.publish("presenca", "");
  }
}

void loop()
{
  if(!client.connected()) {
    connectToMQTTBroker();
    subscribeToTopics();
  }
  
  client.loop();
  
  currentMillis = millis();  
  if (currentMillis - startMillis >= period) {  
    publishLuminosity();
    publishDistance();
    publishTempHum();
    //publishPresence();



    startMillis = currentMillis;  
  }
}
