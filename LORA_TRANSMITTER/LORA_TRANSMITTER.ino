#include <SPI.h>
#include <LoRa.h>
#include <DHT.h>
#include <ArduinoJson.h>
#include "variables.h"
#include "function.h"


void setup() {
  SETUP();
}

void loop() {
  dht11_data();
  soil_sensor();
  jason_string();
  publish_data();
}
