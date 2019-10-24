int portaLDR = A5; //Porta analógica utilizada pelo LDR  

void setup() {  
  Serial.begin(9600); 
}  
   
void loop() {  
  int estado = analogRead(portaLDR);  //Lê o valor fornecido pelo LDR  
  Serial.println(estado); 
}  
