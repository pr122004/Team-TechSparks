#include <SPI.h>
#include <LoRa.h>
#include <ArduinoJson.h>
#include "variables.h"
#include "function.h"

void setup() {
    SETUP();
}

void loop() {
    data_receive();
    deserialization_string();
    send_string();
}
