// Bibliotecas e definições

#include <Adafruit_GFX.h>
#include <WiFi.h>
#include "PubSubClient.h"
#include <Adafruit_SSD1306.h>
#include <ESP32Servo.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 6

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Variáveis e configuração do WI-FI

const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* mqttServer = "broker.hivemq.com";
int port = 1883;
String stMac;
char mac[50];
char clientId[50];
int estado, tipo = 0, copos; 
String sumo;
String extra;
String salgado;
String pagamento;
String stMessage;
const int Pinledsala = 2;
const int Pinledquarto1 = 4;
const int Pinledquarto2 = 5; 
const int Pinledcozinha = 18; 
const int Pinledgaragem = 19;
const int Pinledmotorgaragem = 13;

// Configuração do WI-FI

WiFiClient espClient;
PubSubClient client(espClient);

// Configuração do Servo

Servo myservo;
int pos = 0;

// Configuração do sensor

const int Pinsensor = 12;
const int Pinledsensor = 14;
int valor = 0;
int estado_sensor = LOW;

// Operações

void setup() {

  // Parte do IOT
  Serial.begin(115200);
  randomSeed(analogRead(0));

  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  wifiConnect();

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.macAddress());
  stMac = WiFi.macAddress();
  stMac.replace(":", "_");
  Serial.println(stMac);
  
  client.setServer(mqttServer, port);
  client.setCallback(callback);
  pinMode(Pinledsala, OUTPUT);
  pinMode(Pinledquarto1, OUTPUT);
  pinMode(Pinledquarto2, OUTPUT);
  pinMode(Pinledcozinha, OUTPUT);
  pinMode(Pinledgaragem, OUTPUT);
  pinMode(Pinledmotorgaragem, OUTPUT);
  pinMode(Pinledsensor, OUTPUT);
  pinMode(Pinsensor, INPUT);

  // Parte do servo 

  myservo.attach(33);
}

void wifiConnect() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
}

void mqttReconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    long r = random(1000);
    sprintf(clientId, "clientId-%ld", r);
    if (client.connect(clientId)) {
      Serial.print(clientId);
      Serial.println(" connected");
      client.subscribe("IFSP/ledsala");
      client.subscribe("IFSP/ledquarto1");
      client.subscribe("IFSP/ledquarto2");
      client.subscribe("IFSP/ledcozinha");
      client.subscribe("IFSP/ledgaragem");
      client.subscribe("IFSP/fruitinc");
      client.subscribe("IFSP/motorgaragem");
      client.subscribe("IFSP/sensor");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Mensagem recebida no topico: ");
  Serial.print(topic);
  Serial.print(". Messagem: ");
  String stMessage;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    stMessage += (char)message[i];
  }
  Serial.println();

  if (String(topic) == "IFSP/ledsala") {
    Serial.print("Saida alterada para ");
    if(stMessage == "on"){
      Serial.println("on");
      digitalWrite(Pinledsala, HIGH);
    }
    else if(stMessage == "off"){
      Serial.println("off");
      digitalWrite(Pinledsala, LOW);
    }
  }

  if (String(topic) == "IFSP/ledquarto1") {
    Serial.print("Saida alterada para ");
    if(stMessage == "on"){
      Serial.println("on");
      digitalWrite(Pinledquarto1, HIGH);
    }
    else if(stMessage == "off"){
      Serial.println("off");
      digitalWrite(Pinledquarto1, LOW);
    }
  }

  if (String(topic) == "IFSP/ledquarto2") {
    Serial.print("Saida alterada para ");
    if(stMessage == "on"){
      Serial.println("on");
      digitalWrite(Pinledquarto2, HIGH);
    }
    else if(stMessage == "off"){
      Serial.println("off");
      digitalWrite(Pinledquarto2, LOW);
    }
  }
 
  if (String(topic) == "IFSP/ledcozinha") {
    Serial.print("Saida alterada para ");
    if(stMessage == "on"){
      Serial.println("on");
      digitalWrite(Pinledcozinha, HIGH);
    }
    else if(stMessage == "off"){
      Serial.println("off");
      digitalWrite(Pinledcozinha, LOW);
    }
  }

  if (String(topic) == "IFSP/ledgaragem") {
    Serial.print("Saida alterada para ");
    if(stMessage == "on"){
      Serial.println("on");
      digitalWrite(Pinledgaragem, HIGH);
    }
    else if(stMessage == "off"){
      Serial.println("off");
      digitalWrite(Pinledgaragem, LOW);
    }
  }
  

  if (String(topic) == "IFSP/fruitinc"){

    if(stMessage == "on"){

      if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F("SSD1306 allocation failed"));
        for(;;);
      }

      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(BLACK, WHITE);
      display.setCursor(10, 10);
      display.println("FruitInc");
      display.setTextColor(WHITE);
      display.startscrollright(0x00, 0x0f);
      display.setCursor(10, 50);
      display.println("Bem-Vindo");
      display.display(); 
      Serial.begin(9600);
      delay(10000);
      display.stopscroll();
      display.clearDisplay();

      estado = 0;
      copos = 0;
    }

    if(estado == 0){

      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(BLACK, WHITE);
      display.setCursor(10, 0);
      display.println("FruitInc");
      display.setCursor(10, 20);
      display.setTextColor(WHITE);
      display.println("Quantos copos?");
      Serial.println("Quantos copos?");
      display.setCursor(50, 40);
      display.println(copos);
      display.display();

      Serial.println("Escolha: +, - ou ok");

      if(stMessage == "+"){
        copos += 1;
        copos = copos;
      }

      if (stMessage == "-") {
        copos -= 1;
        copos = copos;
      }

      if (stMessage == "ok") {
        estado = 1;
      }

      display.clearDisplay();
    }  

    if(estado == 1){

      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(BLACK, WHITE);
      display.setCursor(10, 0);
      display.println("FruitInc");
      display.setCursor(10, 10);
      display.setTextColor(WHITE);

      display.setCursor(10, 20);
      display.println("Escolha o seu sumo:");

      display.setCursor(10, 30);
      display.println("Laranja");
      display.setCursor(10, 40);
      display.println("Limao");
      display.setCursor(10, 50);
      display.println("Uva");

      display.display();

      Serial.println("Escolha: limao, laranja ou uva");

      if (stMessage == "limao") { 
        sumo = "Limao";
        estado = 2;
      }

      if (stMessage == "laranja") { 
        sumo = "laranja";
        estado = 2;    
      }

      if (stMessage == "uva") { 
        sumo = "Uva";
        estado = 2;    
      }

      display.clearDisplay();
    }

    if(estado == 2){

      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(BLACK, WHITE);
      display.setCursor(10, 0);
      display.println("FruitInc");
      display.setCursor(10, 10);
      display.setTextColor(WHITE);

      display.setCursor(10, 20);
      display.println("Escolha seu extra");
      display.setCursor(10, 30);
      display.println("Maca-Verde");
      display.setCursor(10, 40);
      display.println("Acai");
      display.setCursor(10, 50);
      display.println("Mirtilo");

      display.setCursor(50, 50);
      display.display();

      Serial.println("Escolha: maca_verde, açai ou mirtilo");

      if (stMessage == "maca_verde") {
        extra = "Maca-Verde";
        estado = 3;
      }

      if (stMessage == "acai") {
        extra = "acai";
        estado = 3;    
      }

      if (stMessage == "mirtilo") {
        extra = "Mirtilo";
        estado = 3;    
      }

      display.clearDisplay();
    }

    if(estado == 3){

      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(10, 10);
      display.println("FruitInc");
      display.setCursor(0, 30);

      String frase2;

      if (tipo == 0) {
        frase2 = "Preparando os copos...";
      }else {
        String frase = "Colocando ";
        frase2 = frase + String(sumo) + " copos...";
      }

      display.println(frase2);
      display.setCursor(50, 50);
      display.display();

      delay(5000);

      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(10, 10);
      display.println("FruitInc");
      display.setCursor(0, 30);

      String frase3 = "Adicionando sumo de " + String(sumo) + "...";

      display.println(frase3);
      display.setCursor(50, 50);
      display.display();

      delay(5000);

      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(10, 10);
      display.println("FruitInc");
      display.setCursor(0, 30);

      String frase4 = "Colocando o extra de " + String(extra) + "...";

      display.println(frase4);
      display.setCursor(50, 50);
      display.display();

      delay(5000);

      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(10, 10);
      display.println("FruitInc");
      display.setCursor(0, 30);
      display.println("Seu pedido esta pronto!");
      display.setCursor(50, 50);
      display.display();
      delay(5000);

      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(10, 10);
      display.println("FruitInc");
      display.setCursor(0, 30);
      display.println("Para reiniciar o processo, digite on");
      display.setCursor(50, 50);
      display.display();

      estado = 6;
    }
  }

  if (String(topic) == "IFSP/motorgaragem") {
    
    if(stMessage == "1")
    {
      Serial.write("Subindo...");
      for(pos = 0; pos <= 180; pos += 1)
      {
        myservo.write(pos);
        digitalWrite(Pinledmotorgaragem, HIGH);
        delay(15);
      }
      digitalWrite(Pinledmotorgaragem, LOW);
      Serial.println("Pronto!");
    }

    if(stMessage == "0")
    {
      Serial.println("Descendo...");
      for(pos = 180; pos >= 0; pos -= 1)
      {
        myservo.write(pos);
        digitalWrite(Pinledmotorgaragem, HIGH);
        delay(15);
      }
      digitalWrite(Pinledmotorgaragem, LOW);
      Serial.println("Pronto!");
    }
  }

  if(String(topic) == "IFSP/sensor")
  {
    while(stMessage == "on")
    {
      valor = digitalRead(Pinsensor);
      if(valor == HIGH)
      {
        digitalWrite(Pinledsensor, HIGH);
        if(estado_sensor == LOW)
        {
          Serial.println("Presença detectada");
          stMessage = "Presença detectada";
          estado_sensor = HIGH;
        }
      }
      else 
      {
        digitalWrite(Pinledsensor, LOW);
        if(estado_sensor == HIGH)
        {
          Serial.println("Sem presença");
          stMessage = "Sem presença";
          estado_sensor = LOW;
        }
      }
    }

    if(stMessage == "off")
    {
      digitalWrite(Pinledsensor, LOW);
    }
  }
}

void loop() {
  delay(10);
  if (!client.connected()) {
    mqttReconnect();
  }
  client.loop();
}
