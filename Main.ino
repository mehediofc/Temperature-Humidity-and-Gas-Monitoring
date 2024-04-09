#define BLYNK_TEMPLATE_ID "TMPL63Sxdrpt_"
#define BLYNK_TEMPLATE_NAME "Temperature and Humidity"
#define BLYNK_AUTH_TOKEN "r6nIvLGKVmI15MCiZX2oWs926zvaghUF"
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>


char auth[] = BLYNK_AUTH_TOKEN; //Token Added 

char ssid[] = "Mehedi Hasan";  //My wifi name
char pass[] = "11223345";  //My wifi password

BlynkTimer timer;


#define DHTPIN 14 //I choose 14
#define DHTTYPE DHT11  

#define sensor 34  //monitoring gas and controling an alarm
#define buzzer 2

DHT dht(DHTPIN, DHTTYPE);


void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); 

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!"); //In case of failed to read from DHT sensor!
    return;
  }

    Blynk.virtualWrite(V0, t);
    Blynk.virtualWrite(V1, h);
    Serial.print("Temperature : ");
    Serial.print(t);
    Serial.print("    Humidity : ");
    Serial.println(h);					//I want to see value 
}

void GASLevel() {
  int value = analogRead(sensor);
  value = map(value, 0, 4095, 0, 100);

  if (value >= 50) {
    digitalWrite(buzzer, HIGH);
  } else {
    digitalWrite(buzzer, LOW);
  }

  Blynk.virtualWrite(V2, value);
  Serial.println(value);
}



void setup()
{   
  
  Serial.begin(115200);  // Because of IOT device 
  
  Blynk.begin(auth, ssid, pass);
  dht.begin();
  timer.setInterval(100L, sendSensor); // Syncing for each 100 milliseconds
  pinMode(buzzer, OUTPUT);
  delay(1000);
 }

void loop()
{
  Blynk.run();
  GASLevel();
  timer.run();
  delay(1000);
}