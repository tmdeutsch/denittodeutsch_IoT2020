// Messung der Temperatur durch Sensor
float getTemperature(DHT dht) {

  float t = dht.readTemperature();

  if (isnan(t)) {    
    Serial.println("Failed to read from Temperature sensor!");
    return 0;
  }
  else {
    Serial.println(t);
    return t;
  }
}

// Messung der Luftfeuchtigkeit durch Sensor
float getHumidity(DHT dht) {
  float h = dht.readHumidity();
  if (isnan(h)) {
    Serial.println("Failed to read from Humidity sensor!");
    return 0;
  }
  else {
    Serial.println(h);
    return h;
  }
}