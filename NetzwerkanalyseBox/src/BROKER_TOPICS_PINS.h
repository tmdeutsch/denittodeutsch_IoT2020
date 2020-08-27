#define LEDPIN 33
#define BUTTONPIN 26
#define DHTPIN 14
#define DHTTYPE DHT11
#define NUMBER_OF_STRING 6
#define MAX_STRING_SIZE 50

// MQTT Broker
const char *broker = "mqtt.eclipse.org";          //Adresse des Brokers

// Topics für MQTT Subscribe
const char *longi_topicMobile = "thkoeln/IoT/MobileApp/longitude";  // Longitude Subscribe Topic
const char *lati_topicMobile = "thkoeln/IoT/MobileApp/latitude";  // Latitude Subscribe Topic

const char *wifi_topicMobile = "thkoeln/IoT./MobileApp/wifi";  // WIFI Subscribe Topic
const char *wifiType_topicMobile = "thkoeln/IoT../MobileApp/wifiType";  // WIFI-Type Subscribe Topic
const char *wifiState_topicMobile = "thkoeln/IoT.../MobileApp/wifiState";  // WIFI-State Subscribe Topic

const char *mobile_topicMobile = "thkoeln/IoT/MobileApp/Mobile";  // Mobile Subscribe Topic
const char *mobileType_topicMobile = "thkoeln/IoT./MobileApp/MobileType";  // Mobile-Type Subscribe Topic
const char *mobileState_topicMobile = "thkoeln/IoT../MobileApp/MobileState";  // Mobile-State Subscribe Topic


// Topics für MQTT Publish
const char *temp_topic = "thkoeln/IoT/mqtt/temperature";  // Temperature Subscribe Topic
const char *hum_topic = "thkoeln/IoT/mqtt/humidity";  // Humidity Subscribe Topic

const char *lati_topic = "thkoeln/IoT/mqtt/latitude";  // Latitude Publish Topic
const char *longi_topic = "thkoeln/IoT/mqtt/longitude";  // Longitude Publish Topic

const char *wifi_topic = "thkoeln/IoT/mqtt/wifi";  // WIFI Publish Topic
const char *wifiType_topic = "thkoeln/IoT/mqtt/wifiType"; // WIFI-Type Publish Topic
const char *wifiState_topic = "thkoeln/IoT/mqtt/wifiState"; // WIFI-State Publish Topic

const char *mobile_topic = "thkoeln/IoT/mqtt/mobile";  // Mobile Publish Topic
const char *mobileType_topic = "thkoeln/IoT/mqtt/MobileType";  // Mobile-Type Publish Topic
const char *mobileState_topic = "thkoeln/IoT/mqtt/MobileState";  // Mobile-State Publish Topic

// Char Arrays für Publish
char temperature[50]; // Temperature char Array for Publish
char humidity[50]; // Humidity char Array for Publish

char latitude[50]; // Latitude char Array for Publish
char longitude[50]; // Longitude char Array for Publish

char wifi[150]; // WIFI char Array for Publish
char wifiType[150]; // WIFI-Type char Array for Publish
char wifiState[150]; // WIFI-State char Array for Publish

char mobile[250]; // Mobile char Array for Publish
char mobileType[150]; // Mobile-Type char Array for Publish
char mobileState[150]; // Mobile-State char Array for Publish


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