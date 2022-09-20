#include <SoftwareSerial.h>
 
SoftwareSerial SIM900(2, 3);
String textForSMS;

int Buzzer= 8;  // the pin that the Buzzer is atteched to
int RedLED= 13;    // the pin that the Red LED is atteched to
int GreenLED = 12; // the pin that the Green LED is atteched to
int PIR= 5;     // the pin that the PIR sensor is atteched to
int val= 0;     
  
void setup() {
  randomSeed(analogRead(0));

pinMode(Buzzer, OUTPUT);
pinMode(RedLED, OUTPUT);
pinMode(GreenLED, OUTPUT);
pinMode(PIR, INPUT);

digitalWrite(Buzzer, LOW);
digitalWrite(RedLED, LOW);
digitalWrite(GreenLED, LOW);
delay(100);

Serial.begin(9600);
SIM900.begin(9600);
}

void loop() {
val = digitalRead(PIR); 

if(val == HIGH){
  Serial.println("Motion detected!"); 
textForSMS =  "\n Motion detected!!! \n Any Person in your Room  Plz Check It ";


  digitalWrite(RedLED, HIGH); 
  delay(10);
  digitalWrite(Buzzer, HIGH); 
  delay(10);
  digitalWrite(GreenLED, LOW);

sendSMS(textForSMS);
//Serial.println(textForSMS);
Serial.println("message sent.");
delay(100); 

MakeCall();
delay(100);
}

if(val == LOW){

  digitalWrite(RedLED, LOW);
  digitalWrite(Buzzer, LOW);
  digitalWrite(GreenLED, HIGH);
  delay(1000);
  Serial.println("Movement not Detected");
  
}
}

void sendSMS(String message){
SIM900.print("AT+CMGF=1\r");                     // AT command to send SMS message
delay(1000);
SIM900.println("AT + CMGS = \"+917569183893\"");  // recipient's mobile number, in international format
delay(1000);
SIM900.println(message);                         // message to send
SIM900.println((char)26);                        // End AT command with a ^Z, ASCII code 26
delay(1000);
SIM900.println();
// give module time to send SMS
}

void MakeCall()
{
  SIM900.println("ATD+917569183891;"); // ATDxxxxxxxxxx; -- watch out here for semicolon at the end!!
  SIM900.println("Calling  "); // print response over serial port
  delay(1000);
}

