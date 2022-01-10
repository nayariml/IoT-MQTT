#include <SoftwareSerial.h> // Comunicação serial
#include <ESP8266WiFi.h>
#include <PubSubClient.h> // MQTT Protocol

#include <ArduinoJson.h> 

SoftwareSerial ps1(D6, D5);

//__ Informações do WIFI
const char* ssid = "2G_NET";
const char* password = "50080";

//variaveis auxiliares
float umidadeSolo=0;

//Strings envio dados json
String Str1 = "umidadeSolo";

 
//__ Informações do dispositivo
#define DEVICE_TYPE  "RHT"
#define DEVICE_ID    "SENSOR1"

//__ Informações da conexão com o servidor
#define ORG     "zooebh"
#define TOKEN   "SZ5&Me7a3tS_kSVsL)"
 
//__ Variáveis de conexão com o servidor (Não customizaveis)
char server[]   = ORG ".messaging.internetofthings.ibmcloud.com";
char topic[]    = "iot-2/evt/status/fmt/json";
char authMeth[] = "use-token-auth";
char token[]    = TOKEN;
char clientId[] = "d:" ORG ":" DEVICE_TYPE ":" DEVICE_ID;
//char cmdTopic[] = "iot-2/cmd/led/fmt/json";
 
 
 //__Inicia WIFI
WiFiClient wifiClient;
PubSubClient client(server, 1883, NULL, wifiClient);

void setup() { 
 //__Inicializa a serial
  Serial.begin(115200);//inicializa a porta serial
  ps1.begin(115200);// faz a leitura serial 115200
  
  Serial.println();
   
 // while (!Serial) continue;
   
//__Conexão 

  Serial.println();
  Serial.print("Conectando-se na rede "); Serial.print(ssid);
 
  //__ Conecta-se na rede WIFI
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  } 
  Serial.println("");
 
  Serial.print("Conectado, endereço de IP: ");
  Serial.println(WiFi.localIP());
}
 
void enviaDado(float dado1){
  String payload = "{\"d\":{\"" + Str1 + "\":";
 
 payload += dado1;
 payload += "}}";
  Serial.print("Sending payload: ");
 
 Serial.println(payload);
 
 //__ Envia o dado
 
 if (client.publish(topic, (char*) payload.c_str())) {
 
   Serial.println("Publish ok");
 
 } else {
 
   Serial.println("Publish failed");
 
 }
 
}

//__ Função principal
 
void loop() {
 
 
 
 //__ Verifica se está conectada a cloud para envio dos dados
 
 if (!!!client.connected()) {
 
   //__ Caso não esteja conectada, tenta a conexão
 
   Serial.print("Reconectando-se em ");
 
   Serial.println(server);
 
   while (!!!client.connect(clientId, authMeth, token)) {
 
     Serial.print(".");
 
     delay(500);
 
   }
 
   Serial.println();
 
 }
 
 
 
 //__ Le Sensores
 
 umidadeSolo = LeUmidadeSolo();
 enviaDado(umidadeSolo);

  //__ Faz o envio a cada 10 segundos.
 
 delay(1000);
 
}
 
 
 
//__Função que faz a leitura do nível de umidade
 
float LeUmidadeSolo(void){
 
    
   float Umidade;
 

StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(ps1);
 
  //if (root == JsonObject::invalid())
  //{
  //  return;
//  }

root.prettyPrintTo(Serial);

  
  int data1=root["sensor1"];
  Serial.println(data1);
 
 
   Umidade = data1;
 
   return Umidade;
 
}
 
