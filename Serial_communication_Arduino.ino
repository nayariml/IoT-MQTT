//PROGRAMA PARA O Arduino

#include <SoftwareSerial.h>
#include <ArduinoJson.h>

#define s1 A0
//#define s2 A1

SoftwareSerial ps1(5, 6); //Porta serial 1: RX=5, TX, 6

int AV1;
//int AV2;

void setup(){
 
 
 ps1.begin(115200); //Comunicação serial
 
pinMode(s1, INPUT); // Define o pino 1 como entrada sensor 1
//pinMode(s2, INPUT); 
 }

StaticJsonBuffer<1000> jsonBuffer;
JsonObject& root = jsonBuffer.createObject();

void loop()
{

  AV1 = analogRead(s1); // Faz a leitura analógica de s1
 
  //AV2 = analogRead(s2);
  
  if (isnan(AV1)) { //verificador 
    return;
  }
 //Serial.println(AV1);
  root["sensor1"] = AV1;
  //root["sensor2"] = AV2;
   
  if(ps1.available()>0){
  //ps1.write(AV);
  
  root.printTo(ps1);
    }
      
  delay(1550);
}
