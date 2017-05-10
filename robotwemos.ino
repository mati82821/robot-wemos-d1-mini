#include <ESP8266WiFi.h>
#include <WiFiUDP.h>
#include <Ticker.h>
IPAddress apIP(192, 168, 1, 1);
IPAddress remote;
int aia = D4;
int aib = D3;
int bia = D2;
int bib = D1;
int stan = LOW;
char bufor[255];
WiFiUDP UDP;
void setup() {
  // put your setup code here, to run once:
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP("Robot");
  Serial.begin(9600);
  UDP.begin(4210);
  pinMode(D0, OUTPUT);
  pinMode(D8, OUTPUT);
  pinMode(D7, INPUT);
  pinMode(aia, OUTPUT);
  pinMode(aib, OUTPUT);
  pinMode(bia, OUTPUT);
  pinMode(bib, OUTPUT);
  digitalWrite(aib, HIGH);
  digitalWrite(bib, HIGH);
  digitalWrite(aia, HIGH);
  digitalWrite(bia, HIGH);
}

void loop() {
    
  // put your main code here, to run repeatedly:
int packetSize = UDP.parsePacket();
if (packetSize){
    remote = UDP.remoteIP();
    int len = UDP.read(bufor, 255);
    if (len > 0)
      bufor[len] = 0;

    switch (bufor[0])
    {
      case 'p':
      digitalWrite(aib, HIGH);
      digitalWrite(bib, HIGH);
      digitalWrite(aia, LOW);
      digitalWrite(bia, LOW);
      break;
      case 't':
      digitalWrite(aib, LOW);
      digitalWrite(bib, LOW);
      digitalWrite(aia, HIGH);
      digitalWrite(bia, HIGH);
      break;
      case 'r':
      digitalWrite(aib, HIGH);
      digitalWrite(bib, LOW);
      digitalWrite(aia, LOW);
      digitalWrite(bia, HIGH);
      break;
      case 'l':
      digitalWrite(aib, LOW);
      digitalWrite(bib, HIGH);
      digitalWrite(aia, HIGH);
      digitalWrite(bia, LOW);
      break;
      case 's':
      digitalWrite(aib, HIGH);
      digitalWrite(bib, HIGH);
      digitalWrite(aia, HIGH);
      digitalWrite(bia, HIGH);
      break;
      case 'e': 
      stan = ~stan;
      digitalWrite(D0, stan);
      break;
    }
  }
}
