#include <LiquidCrystal_I2C.h>
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(D3, DHT11); //(sensor pin,sensor type)
BlynkTimer timer;

char auth[] = "l871L2JUtMDDx4khimWJsCNcPZYfJxIh";  // the Auth code
char ssid[] = "Mang haji_plus";  // WIFI Name
char pass[] = "mutiahilman";  // WIFI Password

void weather() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  int r = analogRead(A0);
  bool l = digitalRead(D4);

  r = map(r, 0, 1023, 100, 0);
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Blynk.virtualWrite(V0, t);  // V0 untuk Temperature
  Blynk.virtualWrite(V1, h);  // V1 untuk Humidity
  Blynk.virtualWrite(V2, r);  // V2 untuk Rainfall

  if (l == 0) {
    WidgetLED led1(V3);
    led1.on();
    lcd.setCursor(9, 1);
    lcd.print("L :");
    lcd.print("High");
    lcd.print(" ");
  } else if (l == 1) {
    WidgetLED led1(V3);
    led1.off();
    lcd.setCursor(9, 1);
    lcd.print("L :");
    lcd.print("Low");
    lcd.print(" ");
  }

  lcd.setCursor(0, 0);
  lcd.print("T :");
  lcd.print(t);

  lcd.setCursor(0, 1);
  lcd.print("H :");
  lcd.print(h);

  lcd.setCursor(9, 0);
  lcd.print("R :");
  lcd.print(r);
  lcd.print("  ");
}

void setup() {
  Serial.begin(9600); // See the connection status in Serial Monitor
  lcd.init();
  lcd.backlight();
  Blynk.begin(auth, ssid, pass);
  dht.begin();
  // Setup a function to be called every second
  timer.setInterval(10L, weather);
}

void loop() {
  Blynk.run(); // Initiates Blynk
  timer.run(); // Initiates SimpleTimer
}
