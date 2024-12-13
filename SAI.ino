#include <WiFi.h>
#include "SinricPro.h"
#include "SinricProSwitch.h"

#define WIFI_SSID "Your-WiFi-Name"
#define WIFI_PASS "Your-WiFi-Password"
#define APP_KEY "Your-App-Key"
#define APP_SECRET "Your-App-Secret"

#define RelayPin1 23
#define RelayPin2 22
#define wifiLed 2

void setup() {
  Serial.begin(9600);
  pinMode(RelayPin1, OUTPUT);
  pinMode(RelayPin2, OUTPUT);
  pinMode(wifiLed, OUTPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) delay(250);

  SinricProSwitch &lightSwitch = SinricPro["Your-Device-ID1"];
  SinricProSwitch &fanSwitch = SinricPro["Your-Device-ID2"];

  lightSwitch.onPowerState([](String, bool &state) {
    digitalWrite(RelayPin1, state ? LOW : HIGH);
    return true;
  });

  fanSwitch.onPowerState([](String, bool &state) {
    digitalWrite(RelayPin2, state ? LOW : HIGH);
    return true;
  });

  SinricPro.begin(APP_KEY, APP_SECRET);
}

void loop() {
  SinricPro.handle();
}
