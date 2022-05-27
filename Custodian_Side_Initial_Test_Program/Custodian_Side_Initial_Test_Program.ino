#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);

int YellowLED = A0;
int GreenLED = A1;

void setup() {
   //For Debug or Registration purposes
  Serial.begin(9600);
  //Serial.println("Put your card to the reader");
pinMode(GreenLED, OUTPUT);
pinMode(YellowLED, OUTPUT);
  SPI.begin();     
  mfrc522.PCD_Init();

}

void loop() {
  analogWrite(YellowLED,250);
  analogWrite(GreenLED,0);
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }

 //Remove "//" for debug or registering new cards
  //Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
    //Remove "//" for debug or registering new cards
     //Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     //Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
         mfrc522.PICC_HaltA();

  }
       
  //Serial.println();
  //Serial.print("Message : ");
   content.toUpperCase();
   String id = {content.substring(1)};

   String RFID = id;

    Serial.print(RFID);

 
  if (RFID != 0) //change here the UID of the card/cards that you want to give access
  {
    
    //Serial.println("Authorized access");
    //Serial.println();
    analogWrite(GreenLED,250);
    analogWrite(YellowLED,0);
    delay(200);
  }
  

}
