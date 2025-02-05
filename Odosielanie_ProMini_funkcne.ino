#include <Wire.h>
#include <Adafruit_BME280.h>
#include <SoftwareSerial.h>

// Piny pre RS485
#define RE_DE_PIN 2       // Riadenie vysielania/prijímania
#define RX_PIN 10         // RS485 RO -> Arduino RX
#define TX_PIN 11         // Arduino TX -> RS485 DI

SoftwareSerial rs485Serial(RX_PIN, TX_PIN);

Adafruit_BME280 bme;

void setup() {
  // Nastavenie RE/DE pinu
  pinMode(RE_DE_PIN, OUTPUT);
  // Prijímací režim
  digitalWrite(RE_DE_PIN, LOW);

  // Inicializácia Serial1 pre RS485
  rs485Serial.begin(9600);
  Serial.begin(9600);

  // Inicializácia BME280
  Wire.begin();
  bool status = bme.begin(0x76); 
  if (!status) {
    Serial.println("BME280 senzor sa nenasiel!");
    while (1) {
    }
  }
}

void loop() {
  // Prečítame teplotu z BME280
  float temp = bme.readTemperature();

  String dataString = String(temp);

  // Odosielací režim
  digitalWrite(RE_DE_PIN, HIGH);
  
  rs485Serial.println(dataString);
  rs485Serial.flush();

  // Prijímací režim
  digitalWrite(RE_DE_PIN, LOW);

  Serial.print("Odoslana teplota: ");
  Serial.println(temp);

  delay(2000);
}
