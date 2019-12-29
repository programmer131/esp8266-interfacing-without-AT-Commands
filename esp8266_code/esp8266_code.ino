#include <ESP8266WiFi.h>
#include <ArduinoJson.h>


#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

//int temperature;
//int button_state=0;
/************************* WiFi Access Point *********************************/

#define WLAN_SSID       "ssid"
#define WLAN_PASS       "wifi_password"

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "...."
#define AIO_KEY         "...."

/************ Global State (you don't need to change this!) ******************/

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;
// or... use WiFiFlientSecure for SSL
//WiFiClientSecure client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

/****************************** Feeds ***************************************/

Adafruit_MQTT_Publish buttonState = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/buttonState");
Adafruit_MQTT_Publish temperature = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/temperature");

/*************************** Sketch Code ************************************/

// Bug workaround for Arduino 1.6.6, it seems to need a function declaration
// for some reason (only affects ESP8266, likely an arduino-builder bug).
void MQTT_connect();
StaticJsonDocument<200> arduino_packet;
void serialEvent();
String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete


void setup() {
  Serial.begin(9600);
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  inputString.reserve(100);
}

uint32_t x=0;

void loop() {
  serialEvent();
  MQTT_connect();
  if (stringComplete) {
    DeserializationError error = deserializeJson(arduino_packet, inputString);
    if (!error){
      int button_state_value=arduino_packet["button_state"];
      int temperature_value=arduino_packet["temperature"];
      buttonState.publish(button_state_value);
      temperature.publish(temperature_value);
      Serial.println("Published buttons_state and temperature");
    }
    //Serial.println(inputString);
    inputString = "";
    stringComplete = false;
  }  
}

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  
  Serial.println("MQTT Connected..");

}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
      Serial.println("New String received");
    }
  }
}
