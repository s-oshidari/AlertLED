// pin mapping
#define PIN_LED_C        12
#define PIN_LED_V        14
#define PIN_CONF_MODE     4  //PULLDOWN状態で起動するとConfig Modeに移行する
#define PIN_BTN_LED_HALF  5
#define PIN_BTN_SNOOZE   13

// API info
char deviceId[] = "ALED-001";
char  apiHost[] = "ik1-344-32156.vs.sakura.ne.jp";
int     apiPort = 4567;
String   apiUri = "/api/status-led/get?device_id=" + (String)deviceId;

// general settings
#define UPDATE_INTERVAL   5  // データ更新間隔（分）
#define SNOOZE_INTERVAL  90  // スヌーズボタンでスリープする時間（分）

// RGBLED
#define DEFAULT_LED_BRIGHTNESS   100
#define COLOR_CYCLE_INTERVAL    2000  // 1つの色が点灯している時間
#define COLOR_CYCLE_FPS           15

// WiFiManager
#define WIFI_TIMEOUT     180  // タイムアウト
#define WIFI_MIN_SIGNAL  30   // 信号強度

