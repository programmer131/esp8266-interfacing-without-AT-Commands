#include <ArduinoJson.h>
StaticJsonDocument<200> arduino_packet;
const int sensor=A0; // Assigning analog pin A5 to variable 'sensor'
float vout=0; //temporary variable to hold sensor reading
int temp=0;
const int buttonPin = 12;
int buttonState = 0;

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  arduino_packet["temperature"]=0;
  buttonState=digitalRead(buttonPin);
  arduino_packet["button_state"]=buttonState;
}

void loop() {
  vout=((analogRead(sensor)*500)/1023);
  if(temp!=(int)vout)
  {
    temp=(int)vout;
    arduino_packet["temperature"]=temp;
    serializeJson(arduino_packet, Serial);
    Serial.println();  
  }
  
  if(buttonState!=digitalRead(buttonPin))
  {
    buttonState=digitalRead(buttonPin);
    arduino_packet["button_state"]=buttonState;
    serializeJson(arduino_packet, Serial);//Serial.println((int)vout);
    Serial.println();
  }
  delay(1000); //Delay of 1 second 
}
