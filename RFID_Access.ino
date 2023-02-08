//Viral Science
//RFID
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

// Redefine the LED to RGB LED 

#define SS_PIN 10
#define RST_PIN 9
int redPin = 4;
int greenPin = 5;
int bluePin = 6;
#define BUZZER 2 //buzzer pin 
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
Servo myServo; //define servo name

void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  myServo.attach(3); //servo pin
  myServo.write(0); //servo start position
  pinMode(redPin,OUTPUT);//Defining the pin number , Defining it's OUTPUT or INPUT
  pinMode(greenPin,OUTPUT);//Defining the pin number , Defining it's OUTPUT or INPUT
  pinMode(bluePin,OUTPUT);//Defining the pin number , Defining it's OUTPUT or INPUT 
  noTone(BUZZER);
  Serial.println("Put your card to the reader...");
  Serial.println();

}
void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  //change here the UID of the card/cards that you want to give access
  if (content.substring(1) == "04 34 9E 02 70 71 80" || content.substring(1) == "50 0E 5A 1B" || content.substring(1) == "13 CB 63 A7") 
  {// change this part to RGB
    Serial.println("Authorized access");
    Serial.println();
    delay(500); //wait for 500ms
    setColor(0,255,0);//turn on the green led
    tone(BUZZER, 500);//turn on the buzzer on 500 frequency
    delay(300); // wait for 300ms
    noTone(BUZZER); // turn off buzzer
    myServo.write(180); //servo turn 180 degree
    delay(5000); // wait 5000ms
    myServo.write(0); // turn off servo
    setColor(0,0,0); // turn off green lite 
  }
 
 else   {
    Serial.println(" Access denied");
    setColor(255,0,0); // red led turn on 
    tone(BUZZER, 300);//turn on the buzzer on 300 frequency
    delay(1000);//wait 1000ms
    setColor(0,0,0);//turn off red lite 
    noTone(BUZZER);// turn off buzzer
  }
} 

void setColor(int redValue, int greenValue, int blueValue){
  analogWrite(redPin,redValue);
  analogWrite(greenPin,greenValue);
  analogWrite(bluePin,blueValue);
}
