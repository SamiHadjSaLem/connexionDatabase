#ifndef __main_function__
#define __main_function__

void initWiFi(const char* ssid, const char* password);
void convert_char_to_tab(String chaine, const char* delimator, String tab[]);
String httpGETRequest(String serverName);
String http_GET_Request(String serverName,  String getData);
void printHex(byte *buffer, byte bufferSize);

#endif
