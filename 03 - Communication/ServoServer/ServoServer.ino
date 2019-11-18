#include <SPI.h>
#include <Ethernet.h>
#include <Servo.h>
 
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xE4 };                    
EthernetServer server(80);                             
 
String requisicao;

Servo myservo; 
int pos = 1; 
 
void setup()
{
    Ethernet.begin(mac); 
    server.begin();
    myservo.attach(7); 

    Serial.begin(9600);
    Serial.print("server is at ");
    Serial.println(Ethernet.localIP());

    requisicao = "";
}
 
void loop() {
  EthernetClient client = server.available();
  //Serial.println("Waiting...");
  if (client) { 
    boolean currentLineIsBlank = true;
    
    while (client.connected()) {
      
      if (client.available()) { 
        char c = client.read(); 
        requisicao += c;
        
        if (c == '\n' && currentLineIsBlank ) {     
          Serial.println(requisicao);
          
          Serial.println("Analisando requisicao...");
          if (requisicao.indexOf("GET /?graus=") != -1)  {
            String posStr = requisicao.substring(12, 15);
            pos = posStr.toInt();
            
            myservo.write(pos);   
            Serial.print("Setando posição do servo para: ");         
            Serial.println(pos);

            delay(15);  
          }
          
          enviaResposta(client, pos);  
          
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
    Serial.println("Client disconnected");
    Serial.println("");
    requisicao = ""; 
  }
}

void enviaResposta(EthernetClient client, int pos) {
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("O servo esta na posicao ");
  client.println(pos);
  client.println("<br><br>");
  client.println("<form>");
  client.println("<input required name=\"graus\" type=\"number\"/>"); 
  client.println("<input type=\"submit\" value=\"Enviar\">");
  client.println("</form>");
  client.println("</html>");
}
