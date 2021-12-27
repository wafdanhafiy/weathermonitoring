#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

DHT dht(D3, DHT11);  // (sensor pin, sensor type)
BlynkTimer timer;

#define BLYNK_TEMPLATE_ID             "TMPLYL6H3s0Y"
#define BLYNK_DEVICE_NAME             "Weather Monitoring"
#define BLYNK_AUTH_TOKEN              "zAdfBEB50NE9sw0Jtw_1dmWXIeasjxZJ"

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "wirelessId";
char pass[] = "12345678";

void weather() {
  int h = dht.readHumidity();
  double t = dht.readTemperature();
  int r = analogRead(A0);
  int l = digitalRead(D4);

  r = map(r, 0, 1023, 100, 0);

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Blynk.virtualWrite(V0, t);  // V0 for Temperature
  Blynk.virtualWrite(V1, h);  // V1 for Humidity
  Blynk.virtualWrite(V2, r);  // V2 for Rainfall

  if (l == 0) {
    WidgetLED led1(V3);
    led1.on();
  } else if (l == 1) {
    WidgetLED led1(V3);
    led1.off();
  }
}

void setup() {
  // Debug console
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  dht.begin();
  // Setup a function to be called every second
  timer.setInterval(1000L, weather);
}

void loop() {
  Blynk.run();
  timer.run();
}
