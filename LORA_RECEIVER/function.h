#ifndef function_h
#define function_h

void SETUP() {
    Serial.begin(115200);
    pinMode(LED, OUTPUT);

    while (!Serial);
    Serial.println("LoRa Receiver");
    if (!LoRa.begin(433E6)) {  // or 915E6
        Serial.println("Starting LoRa failed!");
        while (1);
    }
}

void data_receive() {
    int packetSize = LoRa.parsePacket();
    if (packetSize) {
        inString = "";  // Clear the string at the start of new data
        // read packet
        while (LoRa.available()) {
            char inChar = (char)LoRa.read();
            inString += inChar;
        }
        Serial.println("Received: " + inString);
    }
}

void deserialization_string() {
    DeserializationError error = deserializeJson(doc, inString);

    if (!error) {
        humidity = doc["humidity"];
        temperature = doc["temperature"];
        soilmoisture = doc["soilmoisture"];

        Serial.print("Humidity: ");
        Serial.print(humidity);
        Serial.print(" %\tTemperature: ");
        Serial.print(temperature);
        Serial.print(" *C\tSoil Moisture: ");
        Serial.println(soilmoisture);
    } else {
        Serial.print("Deserialization failed: ");
        Serial.println(error.c_str());
    }

    delay(100);
}

void send_string() {
    Serial.println(inString);
    delay(1000);
    // inString = "";
}

#endif
