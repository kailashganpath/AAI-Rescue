
#include <LiquidCrystal_I2C.h>
#include<TinyGPS.h>
#include <SoftwareSerial.h>
#include<Wire.h>
int ok;
int Humanhelp;
int Sensor;
float lat,lng;
float latitude=11.101265,longitude=76.966226;
SoftwareSerial mySerial(3,4);
TinyGPS gps;
SoftwareSerial gpsSerial(12,13);
String latitudee;
String longitudee;
LiquidCrystal_I2C lcd(0x27,16,2);

void setup()
{
 pinMode(lm1,OUTPUT);
   pinMode(lm2,OUTPUT);
   pinMode(rm1,OUTPUT);
   pinMode(rm2,OUTPUT);
   Serial.begin(115200);//set the serial communication rate
  
  mySerial.begin(9600);     
  gpsSerial.begin(9600);
  Wire.begin(9600);
    Serial.println("GPS Start");
  pinMode(5,INPUT);
  pinMode(6,INPUT);
  pinMode(11,INPUT);
  delay(100);
}

void loop()
{
  bluetooth();
  ok=digitalRead(5);
  Humanhelp=digitalRead(6);
  Sensor=digitalRead(6);
  while(gpsSerial.available())
  {
if(gps.encode(gpsSerial.read()))
{
gps.f_get_position(&lat,&lng); 

}
   }
   String latitudee=String((lat), 6);
   String longitudee=String((lng), 6);
   lcd.clear();
   lcd.print("latitude:");
   lcd.setCursor(0,1);
   lcd.print(lat);
   delay(1000);
    lcd.clear();
   lcd.print("longitude:");
   lcd.setCursor(0,1);
   lcd.print(lng);
  if(ok==1)
{
  mySerial.println("AT+CMGF=1");   
  delay(1000);  
  mySerial.println("AT+CMGS=\"+910000000000\"\r"); 
  delay(1000);
  mySerial.println("I am safe");
   delay(1000);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  Serial.println("safe message has been sended to rescue system");
  delay(3000);
  mySerial.println("AT+CMGS=\"+918778683086\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("I am safe");// The SMS text you want to send
   delay(1000);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  Serial.println("safe message has been sended to police station");
  delay(3000);
  mySerial.println("AT+CMGS=\"+918778683086\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("I am safe");// The SMS text you want to send
   delay(1000);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  Serial.println("safe message has been sended personal number");
  delay(3000);
}

if(Humanhelp==1)
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+910000000000\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("EMERGENCY");// The SMS text you want to send
  delay(100);
  mySerial.println("Latitude:");
  mySerial.println(latitudee);
  delay(1000);
  mySerial.println("\nLongitude:");
  mySerial.println(longitudee);
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  Serial.println("Alert has been sended to the rescue system");
  }

  
if(Sensor==1)
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+910000000000\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("Latitude:");
  mySerial.println(latitudee);
  delay(1000);
  mySerial.println("\nLongitude:");
  mySerial.println(longitudee);
  delay(1000);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  Serial.println("message has been sended to the rescue system");
  delay(6000);
  mySerial.println("AT+CMGS=\"+918778683086\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("Latitude:");
  mySerial.println(latitudee);
  delay(1000);
  mySerial.println("\nLongitude:");
  mySerial.println(longitudee);
  delay(1000);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  Serial.println("message has been sended to the police station system");
  delay(6000);
  mySerial.println("AT+CMGS=\"+918778683086\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("Latitude:");
  mySerial.println(latitudee);
  delay(1000);
  mySerial.println("\nLongitude:");
  mySerial.println(longitudee);
  delay(1000);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  Serial.println("message has been sended to the personal number");
  delay(5000);

}

}
void bluetooth()
{
while(Serial.available()== 0);//check whether arduino is recieving signal or not
   val = Serial.read() ;//reads the signal
 Serial.print(val);
  /*********For Forward motion*********/
if (val == 'F')
  {
    forward();
   }
    /*********For Backward Motion*********/
  else if(val == 'B')
  {
    
    backward();
  
  }
   /*********Right*********/
  else if(val == 'R')
  {
    right();
  }
   /*********Left*********/
  else if(val == 'L')
  {
   
   left(); 
    }
 
  /*********STOP*********/
  else if(val = 'S')
  {
    
    stopp();

  }
}
void forward()
{
   analogWrite(en1,255);
    analogWrite(en2,255);
    Serial.println("FORWARD");
    digitalWrite(lm1,HIGH);  
    digitalWrite(lm2,LOW);
    digitalWrite(rm1,HIGH);
    digitalWrite(rm2,LOW);
}
 void backward()
 {
 analogWrite(en1,255);
    analogWrite(en2,255);
      Serial.println("BACK");
      digitalWrite(lm2,HIGH); 
      digitalWrite(lm1,LOW);      
      digitalWrite(rm2,HIGH);
      digitalWrite(rm1,LOW);
 }

 void left()
 {
   analogWrite(en1,255);
    analogWrite(en2,255);
    Serial.println("LEFT");
    digitalWrite(lm1,LOW);  
    digitalWrite(lm1,LOW);
    digitalWrite(rm1,HIGH);       
    digitalWrite(rm2,LOW);
  
 }

 void right()
 {
  analogWrite(en1,255);
    analogWrite(en2,255);
    Serial.println("LEFT");
    digitalWrite(lm1,HIGH);  
    digitalWrite(lm1,LOW);
    digitalWrite(rm1,LOW);       
    digitalWrite(rm2,LOW);
  
 }

 void stopp()
 {
  analogWrite(en1,255);
    analogWrite(en2,255);
     Serial.println("stop");
     digitalWrite(lm1,LOW);  
     digitalWrite(lm2,LOW); 
     digitalWrite(rm1,LOW);     
     digitalWrite(rm2,LOW);

 }
 }

