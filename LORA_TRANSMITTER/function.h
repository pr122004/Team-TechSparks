#ifndef function_h
#define function_h


void dht11_data() {
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
}

void soil_sensor() {
  
  soilmoisture = (100.00 - ((analogRead(A0) / 1023.00) * 100.00));
}

void publish_data() {

  LoRa.beginPacket();
  LoRa.print(jsonBuffer);
  LoRa.endPacket();

  Serial.println(jsonBuffer);

}

void jason_string() {

  doc["humidity"] = humidity;
  doc["temperature"] = temperature;
  doc["soilmoisture"] = soilmoisture;
  serializeJson(doc, jsonBuffer);
}

void SETUP() {

  Serial.begin(115200);
  pinMode(pot, INPUT);
  dht.begin();
  while (!Serial)
    ;
  Serial.println("LoRa Sender");

  if (!LoRa.begin(433E6)) { 
    Serial.println("Starting LoRa failed!");
    while (1)
      ;
  }
}

#endif
