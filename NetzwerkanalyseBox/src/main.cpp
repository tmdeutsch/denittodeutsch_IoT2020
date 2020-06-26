#include <Arduino.h>
#include <Wire.h>
#include <WiFi.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>
#include <PubSubClient.h>
#include "rgb_lcd.h"

#define PIN 33
#define PIN_BTN 26
#define DHTPIN 14
#define DHTTYPE    DHT11

DHT dht(DHTPIN, DHTTYPE);
rgb_lcd lcd;

const int colorR = 255;
const int colorG = 120;
const int colorB = 0;
const char* ssid = "R2DLan";
const char* password = "49761671295406304116";
const char *broker = "test.mosquitto.org";         //Adresse des Brokers
const char *topic = "thkoeln/IoT/wohnzimmer/whatever"; //Ein Topic

bool lampOn = true;
int buttonState = 0;
int savedState = 0;


WiFiClient espClient;
PubSubClient client(espClient);
char messages[50];


void setupWifi()
{
  Serial.print("\nConnecting to");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.println(WiFi.status());
  }
 
  Serial.print("\nConnected to");
  Serial.println(ssid);
}

/*** Connenct/Reconnect to MQTT Broker in Case of Connection loss ***/
void reconnect()
{
  while (!client.connected())
  {
    Serial.print("\nConencting to");
    Serial.println(broker);
    if (client.connect("ESP8266Client-")) //ClientName am Server, sollte unique sein
    {
      Serial.print("\nConnected to");
      Serial.println(broker);
      client.subscribe(topic);
    }
    else
    {
      Serial.print("\nTrying again...");
      delay(5000);
    }
  }
}

String getTemperature() {

  float t = dht.readTemperature();

  if (isnan(t)) {    
    Serial.println("Failed to read from Temperature sensor!");
    return "--";
  }
  else {
    Serial.println(t);
    return String(t);
  }
}

String getHumidity() {
  float h = dht.readHumidity();
  if (isnan(h)) {
    Serial.println("Failed to read from Humidity sensor!");
    return "--";
  }
  else {
    Serial.println(h);
    return String(h);
  }
}

/*** Funktion welche ausgeführt wird, wenn eine Nachricht auf einem abbonierten Topic ankommt ***/
void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Received messages: ");
  Serial.println(topic);
  for (int i = 0; i < length; i++)
  {
    Serial.printf("%c", (char)payload[i]); // Ausgabe der gesamten Nachricht
  }
 
  if ((char)payload[0] == '1')
  {
    lcd.println("Testfall 1");
    delay(500);
    lcd.clear();
  }
  else
  {
    lcd.println("Testfall 2");
    delay(500);
    lcd.clear();
  }
  Serial.println();
}

void setup() { 
  Serial.begin(9600);
  pinMode(PIN, OUTPUT);
  pinMode(PIN_BTN, INPUT);
  setupWifi();  
  client.setServer(broker, 1883);
  client.setCallback(callback);
  digitalWrite(PIN, HIGH);
  lcd.begin(16, 2);
  lcd.setRGB(colorR, colorG, colorB);
}

void loop() {

if(WiFi.status()==WL_CONNECTED){
     lcd.println("WLAN aktiv!");
     delay(500);
     lcd.clear();
  }

if (!client.connected())
  {
    reconnect();
  }
  client.loop();
  buttonState = digitalRead(PIN_BTN);
  if (buttonState == HIGH)
  {
    if (savedState != HIGH)
    {
      snprintf(messages, 75, "%i", !lampOn); // Bool/int zu String
      client.publish(topic, messages);       //Nachricht auf Topic publishen (geht auch direkt mit String)
    }
    savedState = HIGH;
  }
  else
  {
    savedState = LOW;
  }


  boolean pressed = digitalRead(PIN_BTN);  
  if(pressed == true){
  digitalWrite(PIN,HIGH);
  String temp  = getTemperature();
  lcd.println("Licht an.");
  lcd.println("Temp:" + temp);
  delay(1000);
  lcd.clear();
  digitalWrite(PIN,LOW);
  lcd.println("Lampe aus...");
  delay(1000);
  lcd.clear();
  }
}