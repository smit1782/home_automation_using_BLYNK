#define BLYNK_PRINT Serial

#include <WiFi.h>

#include <WiFiClient.h>

#include <BlynkSimpleEsp32.h>

int pin = 2;

// You should get Auth Token in the Blynk App.

// Go to the Project Settings (nut icon).

char auth[] = "VS2mjuY-x8rJPhqUD509jHmIXWJvzse-";

// Your WiFi credentials.

// Set password to "" for open networks.

char ssid[] = "ShardaVilla";

char pass[] = "6355551879";

void setup() { 

  pinMode(pin, OUTPUT);

  pinMode(pin, HIGH);

  Serial.begin(115200);

  delay(10);

  Serial.print("Connecting to ");

  Serial.println(ssid);

  WiFi.begin(ssid, pass);

  int wifi_ctr = 0;

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);

    Serial.print(".");

  }

  Serial.println("WiFi connected"); 

  Blynk.begin("VS2mjuY-x8rJPhqUD509jHmIXWJvzse-", ssid, pass);

}

void loop(){

    Blynk.run();

}
