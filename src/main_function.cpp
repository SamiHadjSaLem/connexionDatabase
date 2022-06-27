#include <stdint.h>
#include <WiFiClient.h>
#include <HTTPClient.h>


void initWiFi(const char* ssid, const char* password) {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi ..");
  unsigned long timeout = millis();
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
    if (millis() - timeout > 5000)
      goto this_place;
  }
  this_place:
  
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println("\n");

}

void convert_char_to_tab(String chaine, const char* delimator, String tab[]){
  int len = chaine.length();
  char str_array[len+1];
  chaine.toCharArray(str_array, len+1);
  //char delimator[] = ",";
  char *p = strtok(str_array, delimator);
  int inc = 0;
  while(p != NULL)
  {
      //Serial.println(p);
      tab[inc] = p;
      //Serial.println(tab[inc]);
      p = strtok(NULL, delimator);
      inc+=1;
  }
}


String httpGETRequest(String serverName) {
  WiFiClient client;
  HTTPClient http;
    
  // Your IP address with path or Domain name with URL path 
  http.begin(serverName);
  int httpResponseCode = http.GET();
  
  String payload = "{}"; 
  
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}

String http_GET_Request(String serverName,  String getData) {
  WiFiClient client;
  HTTPClient http;

  http.begin(serverName);                                                 //--> Specify request destination
  http.addHeader("Content-Type", "application/x-www-form-urlencoded"); //Specify content-type header
  int httpCodeGet = http.POST(getData);                                //--> Send the request
  String payload="";
  if (httpCodeGet>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpCodeGet);
    payload = http.getString();
  }
  else {
    Serial.print(httpCodeGet);
  }
  http.end();
  return payload;
}
/*String printHex(byte *buffer, byte bufferSize) {
  String tag="";
  for (byte i = 0; i < bufferSize; i++) {
    tag +=(buffer[i] < 0x10 ? "0" : "") + String(buffer[i], HEX);
  }
  return tag;
}*/
