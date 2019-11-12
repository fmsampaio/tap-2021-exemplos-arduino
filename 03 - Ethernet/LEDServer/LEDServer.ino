#include <SPI.h>
#include <Ethernet.h>
 
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };               
EthernetServer server(80);                             
 
int pinoLED = 13;
int estadoLED;
 
void setup()
{
    Ethernet.begin(mac); 
    server.begin();                 
    pinMode(pinoLED,OUTPUT);

    Serial.begin(9600);
    Serial.print("server is at ");
    Serial.println(Ethernet.localIP());

    estadoLED = LOW;

    digitalWrite(pinoLED, estadoLED);
}
 
void loop() {
  EthernetClient client = server.available();
  //Serial.println("Waiting...");
  if (client) { 
    boolean currentLineIsBlank = true;
    String requisicao;

    while (client.connected()) {
      
      if (client.available()) { 
        char c = client.read(); 
        requisicao += c;
        
        if (c == '\n' && currentLineIsBlank ) {     
          Serial.print(requisicao);
          analisaRequisicao(requisicao);               
          enviaResposta(client);  
          break;
        }
        
        if (c == '\n') {
          currentLineIsBlank = true;
        } 
        else if (c != '\r') {
          currentLineIsBlank = false;
        }
      } 
    }
    
    delay(1);
    client.stop();  
    Serial.println("Client disonnected");
    Serial.println("");
    requisicao = ""; 
  }
}

void enviaResposta(EthernetClient client) {
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  
  client.print("Led pin is now: ");
  
  if(estadoLED == HIGH) {
    client.print("On");
  } else {
    client.print("Off");
  }
  client.println("<br><br>");
  client.println("<a href=\"/LED=ON\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/LED=OFF\"\"><button>Turn Off </button></a><br />");  
  client.println("</html>");
}

void analisaRequisicao(String requisicao) {
  if (requisicao.indexOf("/LED=ON") != -1)  {
    estadoLED = HIGH;
  }
  if (requisicao.indexOf("/LED=OFF") != -1)  {
    estadoLED = LOW;
  }
  
  digitalWrite(pinoLED, estadoLED);
}
