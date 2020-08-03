#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <FirebaseArduino.h>
#include <ArduinoJson.h>
 #include <ESP8266HTTPClient.h>
 
// Set these to run example.
#define FIREBASE_HOST "https://sih-final-45aee.firebaseio.com/Chennai/dispenser%201"
#define FIREBASE_AUTH "FVTY93w2qcjEcTniek4a2appEsc6SYA5MYwUpEq2"
#define WIFI_SSID "InfinityGems"
#define WIFI_PASSWORD "123456789"
 
String myString;
int mass = A0; // give the output of arduino here (mass);
int volume = constant; //
 
void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode(mass ,INPUT);
  pinMode(vol ,INPUT);
  // connect to wifi.
  pinMode(D0,OUTPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED)
    Serial.print(".");
    delay(500);
      }
  Serial.println();
  Serial.print("connected: ");
  Serial.print (" ");
  Serial.println (WIFI_SSID);
  Serial.print ("IP Address is:");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.setString("");
}
 
void loop()
{ 
//sdata = analogRead(vr);
//myString = String(sdata); 
//Serial.println(myString); // convert mass and vol to string
Firebase.pushString ("mass , vol", firebaseHumid); 
delay(1000);            
}
