#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>
#include "rgb_lcd.h"
 
const char *ssid = "";                        //Name des Netzwerks
const char *pass = "";          //Passwort des Netzwerks
const char *broker = "mqtt.eclipse.org";          //Adresse des Brokers
const char *topic = "thkoeln/IoT/wohnzimmer/ledlight";  //Ein Topic
 
#define LEDPIN 33
#define BUTTONPIN 26
#define DHTPIN 14
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
rgb_lcd lcd;
const int colorR = 112;
const int colorG = 100;
const int colorB = 238;
 
bool lampOn = true;
int buttonState = 0;
int savedState = 0;

WiFiClient espClient;
PubSubClient client(espClient);
char messages[50];

/*** Initales verbinden mit WLAN ***/
void setupWifi()
{
  Serial.print("\nConnecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, pass);
 
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
    Serial.print("\nConencting to ");
    Serial.println(broker);
    if (client.connect("ESP8266ClientDeNittoDeutsch-")) //ClientName am Server, sollte unique sein
    {
      Serial.print("\nConnected to ");
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

void changeLED(bool val)
{
  if (val == 1)
  {
    digitalWrite(LEDPIN, HIGH);
  }
  else
  {
    digitalWrite(LEDPIN, LOW);
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
    //lcd.println("Button gedrückt!");
    changeLED(true);
    lampOn = true;
    //delay(500);
    //lcd.clear();

  }
  else
  {
    //lcd.println("Button nicht gedrückt!");
    changeLED(false);
    lampOn = false;
    //delay(500);
    //lcd.clear();
  }
  Serial.println();
}
 
void setup()
{
  Serial.begin(9600);
  pinMode(LEDPIN, OUTPUT);
  pinMode(BUTTONPIN, INPUT);
  setupWifi();
  client.setServer(broker, 1883);
  client.setCallback(callback);
  digitalWrite(LEDPIN, HIGH);
  lcd.begin(16, 2);
  lcd.setRGB(colorR, colorG, colorB);
}
 
void loop()
{
  if (!client.connected())
  {
    reconnect();
  }
  client.loop();
  buttonState = digitalRead(BUTTONPIN);
  if (buttonState == HIGH)
  {
    if (savedState != HIGH)
    { 
      lcd.println("Button gedrückt!");
      delay(1000);
      lcd.clear();
      snprintf(messages, 75, "%i", !lampOn); // Bool/int zu String
      client.publish(topic, messages);       //Nachricht auf Topic publishen (geht auch direkt mit String)
    }
    savedState = HIGH;
  }
  else
  {
    savedState = LOW;
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

//  boolean pressed = digitalRead(PIN_BTN);  
//  if(pressed == true){
//  digitalWrite(PIN,HIGH);
//  String temp  = getTemperature();
//  lcd.println("Licht an.");
//  lcd.println("Temp:" + temp);
//  delay(1000);
//  lcd.clear();
//  digitalWrite(PIN,LOW);
//  lcd.println("Lampe aus...");
//  delay(1000);
//  lcd.clear();