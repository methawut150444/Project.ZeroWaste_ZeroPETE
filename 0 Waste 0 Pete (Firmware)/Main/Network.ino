#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

HTTPClient http;

#define ssid "PIPhone"
#define pass "methawut150444"

void WiFi_setup(){
  WiFi.begin(ssid, pass);
  ConnectingNetwork_IMG();
  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    // Serial.println(".");
  }
  // Serial.println("WiFi connected");
}

void RecordData(){
  String url = "https://script.google.com/macros/s/AKfycbwxZ0vVVj9ei54iq5Nf44W3YyvmInjW0rki_Y3S1zP0i7TdY0ul5eOlkRM9rPj9DiQ/exec?";
  url += "studentID=";    
  url += String(studentID); 

  url += "&";

  url += "amountBottle="; 
  url += String(amountBottle); 

  url += "&";

  url += "amountCap=";    
  url += String(amountCap); 

  http.begin(url.c_str()); 
  http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);

  int httpResponseCode = http.GET(); // Make the request
    
  if (httpResponseCode > 0) {
    String payload = http.getString();
    Serial.println("Data received from Google Sheet:");
    Serial.println(payload);

    StaticJsonDocument<200> doc; // Adjust size as needed
    DeserializationError error = deserializeJson(doc, payload);

    if (!error){
      totalPoint = String(doc["totalPoint"]);
      totalBottle = String(doc["totalBottle"]);
      totalCap = String(doc["totalCap"]);
    }
    else {
      Serial.print("JSON Parsing Failed: ");
      Serial.println(error.c_str());
    }
    
  } 
  else {
    Serial.print("Error on HTTP request: ");
    Serial.println(httpResponseCode);
  }
  
  http.end(); // Free resources


}











