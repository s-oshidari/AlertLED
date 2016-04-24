WiFiManager wifiManager;

void configModeCallback(WiFiManager *myWiFiManager) {
  Serial.println("\n[WiFiManager] Device is now on Config Mode");
  ledChangeColor(255, 255, 0);
}

void connectWiFi() {
  
  // callbacks
  wifiManager.setAPCallback(configModeCallback);
  
  // settings
  wifiManager.setConfigPortalTimeout(WIFI_TIMEOUT);     // タイムアウト
  wifiManager.setMinimumSignalQuality(WIFI_MIN_SIGNAL); // 信号強度
  
  pinMode(PIN_CONF_MODE, INPUT_PULLUP); delay(10);
  
  if ( digitalRead(PIN_CONF_MODE) == HIGH ) {
    wifiManager.autoConnect();
  } else {
    
    // 強制的にConfiguration Portalに移行する
    Serial.println(F("\n[WiFiManager] Config mode requested"));
    if (!wifiManager.startConfigPortal(deviceId)) {
      
      // タイムアウト
      Serial.println(F("\n[WiFiManager] Failed to connect"));
      ledErrorAndCheckAgainLater();
    }
  }
  
  Serial.println(F("\n[WiFiManager] Connection establised"));
}

