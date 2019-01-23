


#include "MQ135.h"
#include <dht.h>

int adcPin = 0; 
int adcValue = 0; 
float v; 
float rs, ppm; 
 int dht_apin =2; 
 float c;
 
dht DHT;
void setup (){
Serial.begin (9600);
//GSMSerial.begin(9600);

pinMode(A5,INPUT);
pinMode(13,OUTPUT);
Serial.println("Welcome this is ammonia detector");
Serial.println("Waiting to heat up the sensor........");
delay(120000);


}
void loop() {
  adcValue = analogRead (A5); 
v = adcValue * (5.00/1024); 
 
MQ135 gasSensor = MQ135(A5);
DHT.read11(dht_apin);
/*c=analogRead(A5);
if(c>500)
{
  digitalWrite(13,HIGH);
  Serial.println("AT+CMGF=1");    
  delay(1000);  
  Serial.println("AT+CMGS=\"+919340486817\"\r"); 
  delay(1000);
  Serial.println("Unhygiene or pollution or High level of gas detected!!!");
  delay(20000);
  }*/
float air_quality = gasSensor.getPPM();
//float rzero = gasSensor.getRZero();
//Serial.println (rzero);
//delay(10000);
if(air_quality>10)
{
  digitalWrite(13,HIGH);
  //Serial.println("AT+CMGF=1");    
  delay(1000);  
  Serial.println("ATD+919340662260;"); 
  delay(1000);
  Serial.println("HIgh level of NH3 detected!!!");
  delay(180000);
  }
  digitalWrite(13,LOW);
Serial.print("NH3 level = ");
Serial.print (air_quality);
Serial.println("_ppm");
//Serial.println ("\n");
 Serial.print("Current humidity = ");
 
    Serial.print(DHT.humidity);
 
    Serial.print("%  ");
 
    Serial.print("temperature = ");
 
    Serial.print(DHT.temperature); 
 
    Serial.println("C  ");
    Serial.println("\n");
 
delay(2000);
}

