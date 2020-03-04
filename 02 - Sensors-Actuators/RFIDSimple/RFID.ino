#include <SPI.h>
#include <MFRC522.h>

MFRC522 mfrc522(8, 9);
String uidTag, prevUidTag;
boolean firstTime = true;
unsigned long t0, t1;

void initRFID() {
  SPI.begin();          // Inicia  SPI bus
  mfrc522.PCD_Init();   // Inicia MFRC522  
  
  Serial.println("Aproxime o seu cartao do leitor...");
  Serial.println();
}

boolean verificaTag() {
  boolean newTag = false;
  boolean returnable;
  
  // Look for new cards
  if (!mfrc522.PICC_IsNewCardPresent()) 
  {
    return false;
  }
  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial()) 
  {
    return false;
  }
  uidTag = "";
  byte letra;
    
  for (byte i = 0; i < mfrc522.uid.size; i++) {
     uidTag.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : ""));
     uidTag.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  uidTag.toUpperCase();
  if(firstTime or !uidTag.equals(prevUidTag) or millis() - t0 > 100) {
    if(firstTime) {
      firstTime = false;
    }
    Serial.print("Nova TAG detectada: ");
    Serial.println(uidTag);
    prevUidTag = String(uidTag);

    returnable = true;
    
  }
  else {
    returnable = false;
  }
  t0 = millis();

  return returnable;
}

String getUidTag() {
  return uidTag;
}
