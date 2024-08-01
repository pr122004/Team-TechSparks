#ifndef variables_h
#define variables_h

#define DHTPIN 5  
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

int pot = A0;
float humidity = 0;
int soilmoisture = 0;
float temperature = 0;

StaticJsonDocument<1024> doc;
char jsonBuffer[1024];

#endif
