//DECLARAÇÃO DAS FREQUÊNCIAS DAS NOTAS MÚSICAIS
  const float c = 261.63; //Do (Oitava 0)
  const float d = 293.66; //Re (Oitava 0)
  const float e = 329.63; //Mi (Oitava 0)
  const float f = 349.23; //Fa (Oitava 0)
  const float g = 392.00; //Sol (Oitava 0)
  const float gS = 415.30;  //Sol# (Oitava 0)
  const float a = 440.00; //La (Oitava 0)
  const float b = 466.16; //La# (Oitava 0)
  const float cH = 523.25;   //Do (Oitava 1)
  const float cSH = 554.37;  //Do# (Oitava 1)
  const float dH = 587.33; //Re (Oitava 1)
  const float dSH = 622.25; //Re# (Oitava 1)
  const float eH = 659.26; //Mi (Oitava 1)
  const float fH = 698.46; //Fa (Oitava 1)
  const float fSH = 739.99; //Fa# (Oitava 1)
  const float gH = 783.99;  //Sol (Oitava 1)
  const float gSH = 830.61; //Sol# (Oitava 1)
  const float aH = 880.00; //La (Oitava 1)
   
  const int pinoBuzzer = 8; //PINO DIGITAL UTILIZADO PELO BUZZER
 
  int contador = 0; //VARIÁVEL DO TIPO INTEIRA
 
  void setup(){
    pinMode(pinoBuzzer, OUTPUT); //DEFINE O PINO COMO SAÍDA
  }
   
  void loop(){ 
    primeraSecao(); //CHAMADA DE SONS DA PRIMEIRA SEÇÃO
   
    segundaSecao(); //CHAMADA DE SONS DA SEGUNDA SEÇÃO
   
    //VARIANTE 1
    tom(f, 250);  
    tom(gS, 500);  
    tom(f, 350);  
    tom(a, 125);
    tom(cH, 500);
    tom(a, 375);  
    tom(cH, 125);
    tom(eH, 650);
   
    delay(500); //INTEVALO DE 500 MILISSEGUNDOS
   
    segundaSecao(); //CHAMADA DE TONS DA SEGUNDA SEÇÃO
   
    //VARIANTE 2
    tom(f, 250);  
    tom(gS, 500);  
    tom(f, 375);  
    tom(cH, 125);
    tom(a, 500);  
    tom(f, 375);  
    tom(cH, 125);
    tom(a, 650);  
   
    delay(650); //INTEVALO DE 650 MILISSEGUNDOS
  }
  
  //FUNÇÃO RESPONSÁVEL POR EXECUTAR CADA TOM 
  void tom(int frequencia, int duracao){
    //EXECUTA O TOM CONFORME OS PARÂMETROS PASSADOS
    tone(pinoBuzzer, frequencia, duracao); 
   
    if(contador % 2 == 0){ //SE contador FOR UM NÚMERO PAR, FAZ
      delay(duracao); //INTERVALO DE ACORDO COM O VALOR DA VARIÁVEL
    }
    else //SENÃO, FAZ
    {
      delay(duracao); //INTERVALO DE ACORDO COM O VALOR DA VARIÁVEL
    }
    noTone(pinoBuzzer); //BUZZER PERMANECE DESLIGADO
    delay(50); //INTEVALO DE 50 MILISSEGUNDOS
    contador++; //INCREMENTADOR O CONTADOR
  }
  
  //FUNÇÃO DA PRIMEIRA SEÇÃO
  void primeraSecao(){
    tom(a, 500);
    tom(a, 500);    
    tom(a, 500);
    tom(f, 350);
    tom(cH, 150);  
    tom(a, 500);
    tom(f, 350);
    tom(cH, 150);
    tom(a, 650);
   
    delay(500); //INTEVALO DE 500 MILISSEGUNDOS
   
    tom(eH, 500);
    tom(eH, 500);
    tom(eH, 500);  
    tom(fH, 350);
    tom(cH, 150);
    tom(gS, 500);
    tom(f, 350);
    tom(cH, 150);
    tom(a, 650);
   
    delay(500); //INTEVALO DE 500 MILISSEGUNDOS
  }
  
  //FUNÇÃO DA SEGUNDA SEÇÃO  
  void segundaSecao(){
    tom(aH, 500);
    tom(a, 300);
    tom(a, 150);
    tom(aH, 500);
    tom(gSH, 325);
    tom(gH, 175);
    tom(fSH, 125);
    tom(fH, 125);    
    tom(fSH, 250);
   
    delay(325); //INTEVALO DE 325 MILISSEGUNDOS
   
    tom(a, 250);
    tom(dSH, 500);
    tom(dH, 325);  
    tom(cSH, 175);  
    tom(cH, 125);  
    tom(b, 125);  
    tom(cH, 250);  
   
    delay(350); //INTEVALO DE 350 MILISSEGUNDOS
  }