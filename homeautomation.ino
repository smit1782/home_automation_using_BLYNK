#include <Blynk.h>
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include<WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>


/************************* Pin Definition *********************************/
#define DHTTYPE DHT11     // DHT 11
//#define DHTTYPE DHT22   // DHT 22, AM2302, AM2321
//#define DHTTYPE DHT21   // DHT 21, AM2301

//Relays for switching appliances
#define Relay1            23// GP23 pin for Hall light
#define Relay2            22// GP22 pin for TV

//DHT11 for reading temperature and humidity value
#define DHTPIN            12
#define proximityPIN      13
#define lightPIN          14
#define gasPIN            26
#define motionPIN         27

//buzzer to use it for alert
#define buzzer            36

int proximity;
int light;
int gas;
int motion;
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "VS2mjuY-x8rJPhqUD509jHmIXWJvzse-";

// Uncomment whatever type you're using!

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "ShardaVilla";
char pass[] = "6355551879";
// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, proximity);
  Blynk.virtualWrite(V2, gas);
  Blynk.virtualWrite(V3, motion);
  Blynk.virtualWrite(V4, light);
  
 }

void setup()
{
  // Debug console
  Serial.begin(115200);
  
  Serial.print("Connecting to ");

  Serial.println(ssid);

  WiFi.begin(ssid, pass);

  int wifi_ctr = 0;

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);

    Serial.print(".");

  }

  Serial.println("WiFi connected"); 
  Blynk.begin(auth, ssid, pass);

  dht.begin();
  pinMode(buzzer, OUTPUT);
  

}

void loop()
{
    
  // Now we can publish stuff!
  
  float t = dht.readTemperature();
  Serial.print("temperature=");Serial.print(t);
  Blynk.virtualWrite(V0, t);
  
  gas = analogRead(gasPIN);
  Serial.print("Gas - "); Serial.println(gas);
  Blynk.virtualWrite(V2, gas);

  motion = analogRead(motionPIN);
  if (motion > 512)
  {
    motion = 1;
    
  }
  else
  {
    motion = 0;
     
    
  }
  Blynk.virtualWrite(V3, motion);

  
  proximity = analogRead(proximityPIN);
  Serial.print("Proximity - "); Serial.println(proximity);
  if (proximity>512)
  {
    proximity = 1;
    digitalWrite(buzzer, HIGH);
    Blynk.email("Security check", "someone entered !");
  }
  else
  {
    proximity = 0;
    digitalWrite(buzzer, LOW); 
  }
  Blynk.virtualWrite(V1, proximity); 



  int raw_light = analogRead(lightPIN);
  light = map(raw_light, 100, 0, 0, 100);
  Serial.print("Light - "); Serial.println(light);
  Blynk.virtualWrite(V4, light);

  
  Blynk.run();
  timer.run();
    
}
