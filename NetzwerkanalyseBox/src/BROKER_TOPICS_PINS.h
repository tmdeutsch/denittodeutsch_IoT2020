#define LEDPIN 33
#define BUTTONPIN 26
#define DHTPIN 14
#define DHTTYPE DHT11
#define NUMBER_OF_STRING 6
#define MAX_STRING_SIZE 50

// MQTT Broker
const char *broker = "mqtt.eclipse.org";          //Adresse des Brokers

// Topics für MQTT Publish
const char *temp_topic = "thkoeln/IoT/wohnzimmer/temperature";  //Ein Topic
const char *hum_topic = "thkoeln/IoT/wohnzimmer/humidity";  //Ein Topic
const char *lati_topicMobile = "thkoeln/IoT/wohnzimmer/latitudeMobile";  //Ein Topic
const char *longi_topicMobile = "thkoeln/IoT/wohnzimmer/longitudeMobile";  //Ein Topic
const char *wifi_topicMobile = "thkoeln/IoT/wohnzimmer/wifiMobile";  //Ein Topic
const char *mobile_topicMobile = "thkoeln/IoT/wohnzimmer/mobileMobile";  //Ein Topic

const char *lati_topic = "thkoeln/IoT/wohnzimmer/latitude";  //Ein Topic
const char *longi_topic = "thkoeln/IoT/wohnzimmer/longitude";  //Ein Topic
const char *wifi_topic = "thkoeln/IoT/wohnzimmer/wifi";  //Ein Topic
const char *mobile_topic = "thkoeln/IoT/wohnzimmer/mobile";  //Ein Topic

char temperature[50];
char humidity[50];
char latitude[50];
char longitude[50];
char wifi[150];
char mobile[250];


int randomInt() {
  int r;
  return r = rand() % 6;
}

void startAllSensors(bool val)
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