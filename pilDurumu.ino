// 12V Akü Batarya Durumu Ölçme - Voltage Divider ile
// Analog Pin A0'a bağlı gerilim ölçümü

const int batteryPin = A0;  // Analog pin
const float referenceVoltage = 5.0;  // Arduino referans gerilimi
const int maxAnalogValue = 1023;     // 10-bit ADC maksimum değeri

// 12V akü için gerilim seviyeleri
const float maxBatteryVoltage = 13.15;  // Tam dolu akü gerilimi
const float minBatteryVoltage = 10.5;  // Boş akü gerilimi (kritik seviye)

// Voltage divider oranı: 20kΩ + 10kΩ
const float R1 = 20000.0;
const float R2 = 10000.0;
const float voltageDividerRatio = R2 / (R1 + R2);

void setup() {
  Serial.begin(9600);
  Serial.println("12V Akü Batarya Durumu Monitörü");
  Serial.println("================================");
  Serial.println("Voltage Divider: 20kΩ + 10kΩ");
  delay(2000);
}

void loop() {
  // Analog okuma (10 kez okuyup ortalama al - daha stabil)
  long analogSum = 0;
  for(int i = 0; i < 10; i++) {
    analogSum += analogRead(batteryPin);
    delay(10);
  }
  int analogValue = analogSum / 10;
  
  // Analog değeri gerçek gerilime çevir
  float measuredVoltage = (analogValue * referenceVoltage) / maxAnalogValue;
  
  // Gerçek akü gerilimini hesapla (voltage divider oranıyla çarp)
  float batteryVoltage = measuredVoltage / voltageDividerRatio;
  
  // Batarya yüzdesini hesapla
  float batteryPercentage = calculateBatteryPercentage(batteryVoltage);
  
  // Serial monitöre yazdır
  Serial.println("--- Batarya Durumu ---");
  Serial.print("Analog Okuma: ");
  Serial.println(analogValue);
  Serial.print("A0 Pindeki Gerilim: ");
  Serial.print(measuredVoltage, 2);
  Serial.println(" V");
  Serial.print("Gerçek Akü Gerilimi: ");
  Serial.print(batteryVoltage, 2);
  Serial.println(" V");
  Serial.print("Batarya Durumu: %");
  Serial.println(batteryPercentage, 1);
  
  // Batarya durumu göstergesi
  printBatteryStatus(batteryPercentage, batteryVoltage);
  Serial.println();
  
  delay(300000);  
}

float calculateBatteryPercentage(float voltage) {
  // Gerilimi yüzdeye çevir
  if (voltage >= maxBatteryVoltage) {
    return 100.0;
  } else if (voltage <= minBatteryVoltage) {
    return 0.0;
  } else {
    return ((voltage - minBatteryVoltage) / (maxBatteryVoltage - minBatteryVoltage)) * 100.0;
  }
}

void printBatteryStatus(float percentage, float voltage) {
  Serial.print("Durum: ");
  
  if (percentage >= 80) {
    Serial.println("Dolu ████████████");
  } else if (percentage >= 60) {
    Serial.println("İyi ██████████░░");
  } else if (percentage >= 40) {
    Serial.println("Orta ████████░░░░");
  } else if (percentage >= 20) {
    Serial.println("Düşük ██████░░░░░░");
  } else if (percentage >= 10) {
    Serial.println("Kritik ████░░░░░░░░");
  } else {
    Serial.println("Boş ██░░░░░░░░░░");
  }
  
  // Detaylı voltaj yorumu
  if (voltage >= 12.4) {
    Serial.println("✅ Akü durumu mükemmel");
  } else if (voltage >= 12.0) {
    Serial.println("✅ Akü durumu iyi");
  } else if (voltage >= 11.8) {
    Serial.println("⚠️ Akü biraz düşük");
  } else if (voltage >= 11.5) {
    Serial.println("⚠️ UYARI: Batarya seviyesi düşük!");
  } else {
    Serial.println("🔴 KRİTİK: Acil şarj gerekli!");
  }
}