#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <ArduinoJson.h>

#define WIFI_SSID "your_wifi_ssid"
#define WIFI_PASSWORD "your_password"
#define FIREBASE_HOST "myapp1234.firebasetabase.app"
#define FIREBASE_AUTH "jfekfmdfmldmfvlmTksnfkcdmkfdfld"

float humidity = 0;
float temperature = 0;
int soilmoisture = 0;

String str = "";

StaticJsonDocument<1024> doc;

FirebaseData firebaseData;
FirebaseConfig firebaseConfig;
FirebaseAuth firebaseAuth;

void setup() {
  Serial.begin(115200);


  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Connected to WiFi");

  firebaseConfig.host = FIREBASE_HOST;
  firebaseConfig.signer.tokens.legacy_token = FIREBASE_AUTH;

  Firebase.begin(&firebaseConfig, &firebaseAuth);
  Firebase.reconnectWiFi(true);

  if (!Firebase.ready()) {
    Serial.println("Failed to connect to Firebase");
    while (true) {

      delay(1000);
      Serial.print(".");
    }
  } else {
    Serial.println("Connected to Firebase");
  }
}

void loop() {
  if (Serial.available()) {
    str = Serial.readStringUntil('\n');
    Serial.println("Received string: " + str);
    deserialization_string();


    if (Firebase.setFloat(firebaseData, "/temperature", temperature)) {

    } else {
      Serial.print("Failed to send temperature: ");
      Serial.println(firebaseData.errorReason());
    }

    if (Firebase.setFloat(firebaseData, "/humidity", humidity)) {
    } else {
      Serial.print("Failed to send humidity: ");
      Serial.println(firebaseData.errorReason());
    }

    if (Firebase.setInt(firebaseData, "/soil_moisture", soilmoisture)) {

    } else {
      Serial.print("Failed to send soil moisture: ");
      Serial.println(firebaseData.errorReason());
    }

  }


}

void deserialization_string() {
  DeserializationError error = deserializeJson(doc, str);

  if (!error) {
    humidity = doc["humidity"];
    temperature = doc["temperature"];
    soilmoisture = doc["soilmoisture"];
    soilmoisture = soilmoisture * 10.24;


    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" *C\t");
    Serial.print("Soil Moisture: ");
    Serial.println(soilmoisture);
    str = "";
  } else {
    Serial.print("Deserialization failed: ");
    Serial.println(error.c_str());
  }
}
