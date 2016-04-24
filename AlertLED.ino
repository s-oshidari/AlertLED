#include "AlertLED.h"

void standBy(unsigned long secs) {
  ledChangeColor(0, 0, 0, 0);
  unsigned long millisecs = secs * 1000;
  Serial.println(F("\n[ESP] Standing by..."));
  wakeUpTime = millis() + millisecs;
}

void startTimer() {
  updateColorSet();
  ticker.attach_ms(1000/COLOR_CYCLE_FPS, ledStatusLoop);
}

void setup() {
  Serial.begin(115200);
  Serial.println(F("\nStart\n"));
  
  // RGPLED
  ledBegin();
  if ( ESP.getResetReason() == "Power on" || ESP.getResetReason() == "External System" ) {
    ledChangeColor(255, 0, 0, 60);
  }
  
  // WiFi
  connectWiFi();
  
  // OTA
  beginOTA();
  
  // Start timer of controlling LED and updating info
  startTimer();
  
  
  Serial.println(F("\nEnd of setup()\n"));
}

void loop() {
  ArduinoOTA.handle();
  
  // 最終更新時刻からUPDATE_INTERVALが経過したら再更新
  if ( millis() - lastChecked > UPDATE_INTERVAL *60 *1000 ) {
    Serial.println(F("\n[Loop] data is too old, refreshing..."));
    ticker.detach();
    startTimer();
  }
  
  // 連続稼働が30日間を超えたらリセット
  if ( millis() > 30 *24 *60 *60 *1000 ) {
    Serial.println(F("\n[Loop] 30 days passed, resetting..."));
    ESP.reset();
  }
  
  // スヌーズボタンが押されたらdeep-sleep
  snoozeBtn.update();
  if ( snoozeBtn.fell() ) {
    Serial.print(F("[Loop] Snoozing...")); Serial.print(SNOOZE_INTERVAL); Serial.println("mins");
    standBy(SNOOZE_INTERVAL *60);
  }
}


