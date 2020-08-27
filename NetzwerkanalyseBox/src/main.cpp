// Inkludieren von Bibliotheken & anderen "Helferdateien"
#include <Arduino.h>
#include <stdlib.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>
#include "rgb_lcd.h"
#include "WIFI_DATA.h"
#include "BROKER_TOPICS_PINS.h"
#include "SENSOR_FUNCTIONS.H" 

// DHT ist eine Bibliothek für Temperatur- / Feuchtigkeitssensoren der DHT-Serie. Klasse, die Status und Funktionen für DHT speichert
DHT dht(DHTPIN, DHTTYPE);

// LCD-Display Settings (Initialisierung & Farbe)
rgb_lcd lcd;
const int colorR = 100;
const int colorG = 150;
const int colorB = 250;

// Status des Buttons (gedrückt oder nicht)
int buttonState = 0;
int savedState = 0;

// WIFI & PubSub Client definieren 
WiFiClient espClient;
PubSubClient client(espClient);

// Connenct/Reconnect mit MQTT Broker, falls Verbindungsaufbau fehlschlägt oder die Verbindung verloren geht
void reconnect()
{
  while (!client.connected())
  {
    Serial.print("\nConencting to ");
    Serial.println(broker);
    if (client.connect("ESP8266ClientDeNittoDeutsch-"))       // Clientname am Server
    {
      Serial.print("\nConnected to ");
      Serial.println(broker);

      client.subscribe(longi_topicMobile);
      client.subscribe(lati_topicMobile);

      client.subscribe(wifi_topicMobile);
      client.subscribe(wifiType_topicMobile);
      client.subscribe(wifiState_topicMobile);

      client.subscribe(mobile_topicMobile);
      client.subscribe(mobileType_topicMobile);
      client.subscribe(mobileState_topicMobile);

    }
    else
    {
      Serial.print("\nTrying again...");
      delay(5000); 
    }
  }
}


 // Funktion welche ausgeführt wird, wenn eine Nachricht auf einem abbonierten Topic ankommt
void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.println("Received message:");

  if(topic[24] == longi_topicMobile[24]){
        for (int i = 0; i < length; i++)
        {
          
          Serial.printf("%c", (char)payload[i]);            // Ausgabe der gesamten Nachricht
          longitude[i] = (char)payload[i];
        } 
      Serial.println("");     
      client.publish(longi_topic, longitude);               // Nachricht auf Topic publishen
      lcd.setCursor(1, 0);                                  // Curser des LCD-Displays auf 1. Zeile setzen
      lcd.println("Detecting long..");                      // Ausgabe auf LCD-Display
      delay(1000);                                          // Verzögerung, damit LCD-Anzeige gelesen werden kann
      lcd.setCursor(0, 1);                                  // Curser des LCD-Displays auf 2. Zeile setzen
      lcd.println("PWM received it!");                      // Ausgabe auf LCD-Display
      delay(2000);                                          // Verzögerung, damit LCD-Anzeige gelesen werden kann
      lcd.clear();                                          // LCD-Display bereinigen
      
  }

  if(topic[23] == lati_topicMobile[23]){
        
        for (int i = 0; i < length; i++)
        {
          
          Serial.printf("%c", (char)payload[i]);            // Ausgabe der gesamten Nachricht
          latitude[i] = (char)payload[i];
        }
      Serial.println("");      
      client.publish(lati_topic, latitude);                 // Nachricht auf Topic publishen
      lcd.setCursor(1, 0);                                  // Curser des LCD-Displays auf 1. Zeile setzen
      lcd.println("Detecting lati..");                      // Ausgabe auf LCD-Display
      delay(1000);                                          // Verzögerung, damit LCD-Anzeige gelesen werden kann
      lcd.setCursor(0, 1);                                  // Curser des LCD-Displays auf 2. Zeile setzen
      lcd.println("PWM received it!");                      // Ausgabe auf LCD-Display
      delay(2000);                                          // Verzögerung, damit LCD-Anzeige gelesen werden kann
      lcd.clear();                                          // LCD-Display bereinigen
  }
     
  if(topic[23] == wifi_topicMobile[23]){
        for (int i = 0; i < length; i++)
        {
          
          Serial.printf("%c", (char)payload[i]);            // Ausgabe der gesamten Nachricht
          wifi[i] = (char)payload[i];
        } 
      Serial.println("");     
      client.publish(wifi_topic, wifi);                     // Nachricht auf Topic publishen
      lcd.setCursor(1, 0);                                  // Curser des LCD-Displays auf 1. Zeile setzen
      lcd.println("Detecting net...");                      // Ausgabe auf LCD-Display
      delay(1000);                                          // Verzögerung, damit LCD-Anzeige gelesen werden kann
      lcd.setCursor(0, 1);                                  // Curser des LCD-Displays auf 2. Zeile setzen
      lcd.println("PWM received it!");                      // Ausgabe auf LCD-Display
      delay(2000);                                          // Verzögerung, damit LCD-Anzeige gelesen werden kann
      lcd.clear();                                          // LCD-Display bereinigen
  }

  if(topic[28] == wifiType_topicMobile[28]){
        for (int i = 0; i < length; i++)
        {
          
          Serial.printf("%c", (char)payload[i]);            // Ausgabe der gesamten Nachricht
          wifiType[i] = (char)payload[i];
        } 
      Serial.println("");     
      client.publish(wifiType_topic, wifiType);             // Nachricht auf Topic publishen
      lcd.setCursor(1, 0);                                  // Curser des LCD-Displays auf 1. Zeile setzen
      lcd.println("Detect NetType...");                      // Ausgabe auf LCD-Display
      delay(1000);                                          // Verzögerung, damit LCD-Anzeige gelesen werden kann
      lcd.setCursor(0, 1);                                  // Curser des LCD-Displays auf 2. Zeile setzen
      lcd.println("PWM received it!");                      // Ausgabe auf LCD-Display
      delay(2000);                                          // Verzögerung, damit LCD-Anzeige gelesen werden kann
      lcd.clear();                                          // LCD-Display bereinigen
  }

  if(topic[29] == wifiState_topicMobile[29]){
        for (int i = 0; i < length; i++)
        {
          
          Serial.printf("%c", (char)payload[i]);            // Ausgabe der gesamten Nachricht
          wifiState[i] = (char)payload[i];
        } 
      Serial.println("");     
      client.publish(wifiState_topic, wifiState);             // Nachricht auf Topic publishen
      lcd.setCursor(1, 0);                                  // Curser des LCD-Displays auf 1. Zeile setzen
      lcd.println("Detect NetState..");                      // Ausgabe auf LCD-Display
      delay(1000);                                          // Verzögerung, damit LCD-Anzeige gelesen werden kann
      lcd.setCursor(0, 1);                                  // Curser des LCD-Displays auf 2. Zeile setzen
      lcd.println("PWM received it!");                      // Ausgabe auf LCD-Display
      delay(2000);                                          // Verzögerung, damit LCD-Anzeige gelesen werden kann
      lcd.clear();                                          // LCD-Display bereinigen
  }

  if(topic[24] == mobile_topicMobile[24]){
        for (int i = 0; i < length; i++)
        {
          
          Serial.printf("%c", (char)payload[i]);            // Ausgabe der gesamten Nachricht
          mobile[i] = (char)payload[i];
        }  
      Serial.println("");    
      client.publish(mobile_topic, mobile);                 // Nachricht auf Topic publishen
      lcd.setCursor(1, 0);                                  // Curser des LCD-Displays auf 1. Zeile setzen
      lcd.println("Detecting cell..");                      // Ausgabe auf LCD-Display
      delay(1000);                                          // Verzögerung, damit LCD-Anzeige gelesen werden kann
      lcd.setCursor(0, 1);                                  // Curser des LCD-Displays auf 2. Zeile setzen
      lcd.println("PWM received it!");                      // Ausgabe auf LCD-Display
      delay(2000);                                          // Verzögerung, damit LCD-Anzeige gelesen werden kann
      lcd.clear();                                          // LCD-Display bereinigen
  }  

  if(topic[29] == mobileType_topicMobile[29]){
        for (int i = 0; i < length; i++)
        {
          
          Serial.printf("%c", (char)payload[i]);            // Ausgabe der gesamten Nachricht
          mobileType[i] = (char)payload[i];
        }  
      Serial.println("");    
      client.publish(mobileType_topic, mobileType);         // Nachricht auf Topic publishen
      lcd.setCursor(1, 0);                                  // Curser des LCD-Displays auf 1. Zeile setzen
      lcd.println("Detect cellType.");                      // Ausgabe auf LCD-Display
      delay(1000);                                          // Verzögerung, damit LCD-Anzeige gelesen werden kann
      lcd.setCursor(0, 1);                                  // Curser des LCD-Displays auf 2. Zeile setzen
      lcd.println("PWM received it!");                      // Ausgabe auf LCD-Display
      delay(2000);                                          // Verzögerung, damit LCD-Anzeige gelesen werden kann
      lcd.clear();                                          // LCD-Display bereinigen
  }  

  if(topic[30] == mobileState_topicMobile[30]){
        for (int i = 0; i < length; i++)
        {
          
          Serial.printf("%c", (char)payload[i]);            // Ausgabe der gesamten Nachricht
          mobileState[i] = (char)payload[i];
        }  
      Serial.println("");    
      client.publish(mobileState_topic, mobileState);       // Nachricht auf Topic publishen
      lcd.setCursor(1, 0);                                  // Curser des LCD-Displays auf 1. Zeile setzen
      lcd.println("Detect cellState");                      // Ausgabe auf LCD-Display
      delay(1000);                                          // Verzögerung, damit LCD-Anzeige gelesen werden kann
      lcd.setCursor(0, 1);                                  // Curser des LCD-Displays auf 2. Zeile setzen
      lcd.println("PWM received it!");                      // Ausgabe auf LCD-Display
      delay(2000);                                          // Verzögerung, damit LCD-Anzeige gelesen werden kann
      lcd.clear();                                          // LCD-Display bereinigen
  } 



}

 void setup()
 {
  Serial.begin(9600);
  pinMode(LEDPIN, OUTPUT);                                  // PIN für LED
  pinMode(BUTTONPIN, INPUT);                                // PIN für Button
  setupWifi();                                              // ESP mit WLAN verbinden
  client.setServer(broker, 1883);                           // client mit Broker und Port verbinden
  client.setCallback(callback);
  digitalWrite(LEDPIN, HIGH);                               // LCD Screen

  // LCD aktivieren, Farben setzen, Beide Zeilen mit Begrüßung etc. befüllen
  lcd.begin(16, 2); 
  lcd.setRGB(colorR, colorG, colorB);
  lcd.setCursor(1, 0);
  lcd.println("PWM-Analysebox  ");
  lcd.setCursor(0, 1);
  lcd.println("Push Button pls.");
}



// ESP loop
void loop()
{
  if (!client.connected())                                  // Wenn keine Verbindung besteht, reconnect() zum erneuten Verbindungsaufbau aufrufen
  {
    reconnect();
  }
  client.loop();
  buttonState = digitalRead(BUTTONPIN);                     // aktuellen Button-Status (gedrückt oder nicht) abfragen
  if (buttonState == HIGH)                                  // Falls der Button gedrückt wurde...
  {
    if (savedState != HIGH)                                 // ...und der Status nicht vorher schon als "gedrückt" im savedState ist... 
    { 

      // Hier werden die Temperatur- und Luftfeuchtigkeit über den Sensor abgefragt, gepublished & Infos dazu auf dem LCD-Display ausgegeben
      lcd.clear();
      lcd.setCursor(1, 0);                                  // Curser des LCD-Displays auf 1. Zeile setzen
      lcd.println("Button pushed.  ");                      // Ausgabe auf LCD-Display
      delay(2000);                                          // Verzögerung, damit LCD-Anzeige gelesen werden kann
      sprintf(temperature, "%f", getTemperature(dht));      // die Temperatur wird für den publish umgewandelt
      client.publish(temp_topic, temperature);              // Nachricht auf Topic publishen
      lcd.setCursor(1, 0);                                  // Curser des LCD-Displays auf 1. Zeile setzen
      lcd.println("Detecting Temp..");                      // Ausgabe auf LCD-Display
      delay(3000);                                          // Verzögerung, damit LCD-Anzeige gelesen werden kann
      lcd.setCursor(0, 1);                                  // Curser des LCD-Displays auf 2. Zeile setzen
      lcd.println("PWM received it!");                      // Ausgabe auf LCD-Display
      delay(1000);                                          // Verzögerung, damit LCD-Anzeige gelesen werden kann
      lcd.clear();                                          // LCD-Display bereinigen

      sprintf(humidity, "%f", getHumidity(dht));            // die Luftfeuchtigkeit wird für den publish umgewandelt
      client.publish(hum_topic, humidity);                  //Nachricht auf Topic publishen
      lcd.setCursor(1, 0);                                  // Curser des LCD-Displays auf 1. Zeile setzen
      lcd.println("Detecting Humi..");                      // Ausgabe auf LCD-Display
      delay(3000);                                          // Verzögerung, damit LCD-Anzeige gelesen werden kann
      lcd.setCursor(0, 1);                                  // Curser des LCD-Displays auf 2. Zeile setzen
      lcd.println("PWM received it!");                      // Ausgabe auf LCD-Display
      delay(2000);                                          // Verzögerung, damit LCD-Anzeige gelesen werden kann
      lcd.clear();                                          // LCD-Display bereinigen
      lcd.setCursor(1, 0);                                  // Curser des LCD-Displays auf 1. Zeile setzen
      lcd.println("FINISHED!       ");                      // Ausgabe auf LCD-Display
      lcd.setCursor(0, 1);                                  // Curser des LCD-Displays auf 2. Zeile setzen
      lcd.println("Thank you! - PWM");                      // Ausgabe auf LCD-Display
    }
    savedState = HIGH;                                      // savedstate des Buttons auf "gedrückt" setzen
  }
  else
  {
    savedState = LOW;                                       // savedstate des Buttons auf "nicht gedrückt" setzen
  }
}