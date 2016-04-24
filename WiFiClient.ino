String sendRequest() {
  WiFiClient client;
  if (!client.connect(apiHost, apiPort)) {
    Serial.println(F("\n[WiFiClient] Connection failed."));
    ledErrorAndCheckAgainLater();
  }
  
  String reqUrl = "http://" + (String)apiHost + ":" + (String)apiPort + apiUri;
  Serial.println(F("\n[WiFiClient] Sending request to...")); Serial.println(reqUrl);
  
  client.print("GET " + apiUri + " HTTP/1.1\r\n");
  client.print("Host: " + (String)apiHost + ":" + (String)apiPort + "\r\n");
  client.print("Connection: close\r\n");
  client.print("\r\n");
  delay(10);
  
  Serial.println(F("\n[WiFiClient] Reading header lines..."));
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == ""  ) continue;
    if (line == "\r") break;
    Serial.print(F("[WiFiClient] h: ")); Serial.println(line);
  }
  
  Serial.println(F("\n[WiFiClient] Reading body..."));
  String body = client.readStringUntil('\n');
  Serial.print(F("[WiFiClient] b: ")); Serial.println(body);
  client.stop();
  
  lastChecked = millis();
  
  return body;
}

void updateColorSet() {
  String response = sendRequest();
  String resCode  = response.substring(0,1);
  if (resCode.toInt() == 0) {
    Serial.println(F("\n[Parsing] No update"));
    standBy(UPDATE_INTERVAL *60);
  }
  colorSetInString = response.substring(1);
  colorSetCount    = colorSetInString.length() / 12;
}

