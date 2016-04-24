Adafruit_NeoPixel RGBLED = Adafruit_NeoPixel(1, PIN_LED_C, NEO_RGB + NEO_KHZ800);

void ledBegin() {
  pinMode(PIN_LED_V, OUTPUT);
  digitalWrite(PIN_LED_V, HIGH);
  RGBLED.begin();
  delay(10);
  RGBLED.show();

  // 明るさ半分スイッチ
  pinMode(PIN_BTN_LED_HALF, INPUT_PULLUP);
  
  // スヌーズボタン
  snoozeBtn.attachWithInterval(PIN_BTN_SNOOZE, INPUT_PULLUP, 10);
}

void ledChangeColor(int r, int g, int b, int br) {
  if (isLedHalfOn()) {
    br = br / 4;
  }
  
  RGBLED.setBrightness(br);
  RGBLED.setPixelColor(0, r, g, b);
  RGBLED.show();
}

bool isLedHalfOn() {
  if (digitalRead(PIN_BTN_LED_HALF) == LOW) {
    return true;
  }
  return false;
}

void ledStatusLoop() {
  if ( millis() < wakeUpTime ) {
    return;
  }
  
  String color_str = colorSetInString.substring(12*colorSetNow, 12*colorSetNow+12);
  float br = color_str.substring(3*0, 3*1).toInt();
  int r  = color_str.substring(3*1, 3*2).toInt();
  int g  = color_str.substring(3*2, 3*3).toInt();
  int b  = color_str.substring(3*3, 3*4).toInt();
  
  float _interval = br / COLOR_CYCLE_FPS /3;
  float _br;
  
  switch (ledPhase) {
    
    case LED_UP:
      _br = _interval * ledPhaseCounter;
      ledPhaseCounter++;
      if ( _br + _interval > br ) { //次のステップが範囲を超える場合は次のフェーズへ
        ledPhase = LED_ON;
        ledPhaseCounter = 0;
      }
      break;
      
    case LED_ON:
      _br = br;
      ledPhaseCounter++;
      if (ledPhaseCounter > ( COLOR_CYCLE_INTERVAL / (1000/COLOR_CYCLE_FPS) )) {
        ledPhase = LED_DOWN;
        ledPhaseCounter = 0;
      }
      break;
      
    case LED_DOWN:
      _br = br - (_interval * ledPhaseCounter);
      ledPhaseCounter++;
      if ( _br - _interval < 0 ) { //次のステップが範囲を超える場合は次のフェーズへ
        ledPhase = LED_UP;
        ledPhaseCounter = 0;
        
        // 最後のフェーズが完了したら次の色へ
        if (colorSetNow == colorSetCount-1) {
          colorSetNow = 0;
        } else {
          colorSetNow++;
        }
      }
      break;
      
  }
  
  ledChangeColor(r, g, b, (int)_br);
}

void ledError() {
  int delaySec = 800;
  int r = 255; int g = 0; int b = 0;
  ledChangeColor(r, g, b); delay(delaySec);
  ledChangeColor(0, 0, 0); delay(delaySec);
  ledChangeColor(r, g, b); delay(delaySec);
  ledChangeColor(0, 0, 0); delay(delaySec);
  ledChangeColor(r, g, b); delay(delaySec);
  ledChangeColor(0, 0, 0); delay(delaySec);
  ledChangeColor(r, g, b); delay(delaySec);
}

void ledErrorAndSleep() {
  ledError();
  standBy(UPDATE_INTERVAL *60);
}

void ledErrorAndCheckAgainLater() {
  ledError();
  delay(UPDATE_INTERVAL *60 *1000);
  ESP.reset();
}

