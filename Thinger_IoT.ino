#include<SPI.h>
#include <ESP8266WiFi.h>
#include <ThingerESP8266.h>
#include<TinyGPS.h>
#include<SoftwareSerial.h>
#define USERNAME "XXXXXXXX"
#define DEVICE_ID "xxxxxxxx"
#define DEVICE_CREDENTIAL "xxxxxxxx"
float lat,lng;
SoftwareSerial gpsSerial(D1,D2); //tx,rx
TinyGPS gps;
String latitude_send,longitude_send;


#define SSID "your_SSID"
#define SSID_PASSWORD "SSID_PASSWORD"
ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

void setup() {
  Serial.begin(115200);
  Serial.print("Connecting to ");
  Serial.println(SSID);
  WiFi.begin(SSID,SSID_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  
  gpsSerial.begin(9600);
  Serial.println("GPS START");
  thing.add_wifi(SSID, SSID_PASSWORD);
  thing["location"] >> [](pson& out)
  {
    out["lat"] = lat;  //sync your latitude with thinger dashboard
    out["lon"] = lng; //sync your longitude with thinger dashboard
};
 
  
}

void loop() {
 while(gpsSerial.available())
  {
if(gps.encode(gpsSerial.read()))
{
gps.f_get_position(&lat,&lng); 

}
   }
    String latitude_send=String ((lat),6);
    String longitude_send=String((lng), 6);
   Serial.println("latitude:");
   Serial.println(latitude_send);
   Serial.println("longitude");
   Serial.println(longitude_send);
   thing.handle();
   }
