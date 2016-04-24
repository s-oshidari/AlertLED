#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <WiFiClient.h>
#include <Adafruit_NeoPixel.h>
#include <Ticker.h>
#include <Bounce2.h>
#include "config.h"

// global objects
String colorSetInString;
int colorSetCount;
int colorSetNow = 0;
enum colorPhase {
  LED_UP,
  LED_ON,
  LED_DOWN
};
int ledPhase = LED_UP;
int ledPhaseCounter = 0;
unsigned long wakeUpTime = 0;
unsigned long lastChecked;
Ticker ticker;
Bounce snoozeBtn = Bounce();

// headers: main
void beginOTA();
void standBy(unsigned long secs);
void startTimer();

// headers: RGBLED
bool isLedHalfOn();
void ledBegin();
void ledChangeColor(int r, int g, int b, int br = DEFAULT_LED_BRIGHTNESS);
void ledStatusLoop();
void ledError();
void ledErrorAndSleep();
void ledErrorAndCheckAgainLater();

// headers: WiFiClient
String sendRequest();
void updateColorSet();

// headers: WiFiManager
void connectWiFi();


