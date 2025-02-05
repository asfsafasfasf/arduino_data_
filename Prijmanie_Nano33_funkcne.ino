#define RE_DE_PIN 2

void setup() {
  // Pin na ovládanie RE/DE
  pinMode(RE_DE_PIN, OUTPUT);
  // Prijímací režim
  digitalWrite(RE_DE_PIN, LOW);

  // Inicializácia Serial1 pre RS485
  Serial1.begin(9600);
  Serial.begin(9600);

  Serial.println("Zacinam prijimat data z RS485...");
}

void loop() {
  // Prijímací režim
  digitalWrite(RE_DE_PIN, LOW);

  // Ak je niečo dostupné v Serial bufferi
  if (Serial1.available()) {
    String inData = Serial1.readStringUntil('\n');
    inData.trim();

    float temp = inData.toFloat();

    Serial.print("Prijata teplota: ");
    Serial.print(temp);
    Serial.println(" °C");
  }

  delay(100);
}