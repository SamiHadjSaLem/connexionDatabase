#include <Arduino.h>
// #include <NTPClient.h> //https://github.com/taranais/NTPClient
#include <Wire.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <WiFiClient.h>
#include "SPIFFS.h"
#include <SPI.h>
// #include <MFRC522.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
// #include <AsyncElegantOTA.h>

#include "main_function.h"
// const char ssid_1[] = "ETUDIANT_Plus";
// const char password_1[] = "EnetcomEtud";
// const char WIFI_SSID[] = "ETUDIANT_Plus";
// const char WIFI_PASSWORD[] = "EnetcomEtud";
const char WIFI_SSID[] = "GLOBALNET";
const char WIFI_PASSWORD[] = "mahdia2019";


// const char *host = "http://10.1.110.106/ISA_PHP_File/connexionesp32/";
const char *host = "http://192.168.1.6/connexionEsp32/";

// IPAddress local_IP(192, 168, 1, 24); // Set your server's fixed IP address here
// IPAddress gateway(192, 168, 1, 1);   // Set your network Gateway usually your Router base address
// IPAddress subnet(255, 255, 255, 0); // Set your network sub-network mask here
// IPAddress dns(192, 198, 1, 1);

// IPAddress local_IP(10, 1, 110, 118); // Set your server's fixed IP address here
// IPAddress gateway(10, 1, 110, 1);   // Set your network Gateway usually your Router base address
// IPAddress subnet(255, 255, 255, 0); // Set your network sub-network mask here
// IPAddress dns(10, 1, 200, 1);
AsyncWebServer server(80);

int HTTP_PORT = 80;

String  op_name;
// String queryString = String("&id_card=") + String(id_card) + String("&op_name=") + String(op_name);
String payloadGet = "";
boolean tag_packet = true;
bool test = true;
String sParams[5], tab_all_operation[10], tab_operation[20], tab_temps[3], P_param[2], Gamme_param[5];
String Tag_id, get_response, Get_num_pipelette, Get_code_operation, Get_T_estim, Get_operation_line, tab, t_start, line_id, Operation, line_gamme, Machine_id;
int previous_line_gamme, nb_op;
float Rendement, temps_arret_min, T_estim;
unsigned long previousMillis_wifi = 0;
const long interval_wifi = 60000;
#define RST_PIN 26 // Configurable, see typical pin layout above
#define SS_PIN 2   // Configurable, see typical pin layout above

// MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  // Configures static IP address
  // if (!WiFi.config(local_IP, gateway, subnet, dns))
  // { //, primaryDNS, secondaryDNS
  //   Serial.println("STA Failed to configure");
  // }
  Serial.println("Connecting ...");
  while (WiFi.status() != WL_CONNECTED)
  { // Wait for the Wi-Fi to connect: scan for Wi-Fi networks, and connect to the strongest of the networks above
    delay(1000);
    Serial.print('.');
  }
  Serial.println("\nConnected to " + WiFi.SSID() + " Use IP address: " + WiFi.localIP().toString()); // Report which SSID and IP is in use

  

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(200, "text/plain", "Hi! I am ESP32."); });

  // AsyncElegantOTA.begin(&server); // Start ElegantOTA
  server.begin();
  Serial.println("HTTP server started");

  // timeClient.begin();
  // Set offset time in seconds to adjust for your timezone, for example:
  // GMT +1:00 for tunisia  // 1x60x60 = 3600
  // timeClient.setTimeOffset(3600);

  SPI.begin();        // Init SPI bus
  // mfrc522.PCD_Init(); // Init MFRC522


  String adress = WiFi.localIP().toString();
  String GetAddress, LinkGet, getData;
  GetAddress = "get_IpAdress.php";
  LinkGet = host + GetAddress; //--> Make a Specify request destination
  getData = "&IP_adress=" + adress;
  op_name = "";
  // int http_Code_Get=0;
  op_name = http_GET_Request(LinkGet, getData);

  // convert_char_to_tab(op_name, ",", sParams);
  // for (int x = 0; x < 3; x++)
  // {
  //   Serial.println(sParams[x]);
  // }

  Serial.println("result = " + op_name);
}


  

void loop()
{
  // String adress = WiFi.localIP().toString();
  // String GetAddress, LinkGet, getData;
  // GetAddress = "getIP.php";
  // LinkGet = host + GetAddress; //--> Make a Specify request destination
  // getData = "&IP_adress" + adress;
  // op_name = "";
  // int http_Code_Get=0;
  // op_name = http_GET_Request(LinkGet, getData);

  // convert_char_to_tab(op_name, ",", sParams);
  // for (int x = 0; x < 3; x++)
  // {
  //   Serial.println(sParams[x]);
  // }

  // Serial.println("result = " + op_name);
  //--> Print request response payload
  // f(op_name.length() < 50 && op_name.length() > 2)
  // 
    
  //   GetAddress = "update_chaine.php";
  //   LinkGet = host + GetAddress; //--> Make a Specify request destination
  //   getData = ("&L_name=") + sParams[1] +
  //             ("&F_name=") + sParams[0] +
  //             ("&DigiTex=") + Smart_box;
  //   String Get_data = "";
  //   Get_data = http_GET_Request(LinkGet, getData);
  //   Serial.print("Returned data from Server : ");
  //   Serial.println(Get_data);

  //   mfrc522.PICC_HaltA();
  //   mfrc522.PCD_StopCrypto1();
  //   goto operation_while;
  // }

  // while (true)
  // {
  // operation_while:

  //       String GetAddress, LinkGet, getData, var = "here";

  //       GetAddress = "controleuse_send_Tag.php";
  //       LinkGet = host + GetAddress; //--> Make a Specify request destination
  //       getData = "&State_Tag=" + String(var) + "&Tag_id=" + String(idcard);
  //       String update = "";
  //       update = http_GET_Request(LinkGet, getData);
  //       Serial.print("Returned data from Server : ");
  //       Serial.println(update); //--> Print request response payload

  //       // Step 1: chercher à travers le tag le numéro du packet  // done
  //       GetAddress = "get_pipelette_num.php";
  //       LinkGet = host + GetAddress; //--> Make a Specify request destination
  //       getData = "&Tag_id=" + String(idcard);
  //       Get_num_pipelette = http_GET_Request(LinkGet, getData);
  //       Serial.print("Returned data from Server : ");
  //       Serial.println(Get_num_pipelette); //--> Print request response payload
  //       convert_char_to_tab(Get_num_pipelette, ",", P_param);

  //       t_start = P_param[2];
  //       Serial.println(P_param[0]);

  //       // Step 2: select all operation in the current box  // done
  //       GetAddress = "get_all_operation_by_sb.php";
  //       LinkGet = host + GetAddress; //--> Make a Specify request destination
  //       getData = "&N_pipelette=" + String(P_param[0]) + "&DigiTex=" + String(Smart_box);
  //       Get_operation_line = http_GET_Request(LinkGet, getData);
  //       Serial.print("Returned data from Server : ");
  //       Serial.println(Get_operation_line); //--> Print request response payload

  //       for (int i = 0; i < 10; i++)
  //       {
  //         tab_all_operation[i] = "";
  //       }
  //       convert_char_to_tab(Get_operation_line, "?", tab_all_operation);
  //       // for pour parcourir le premier tableau

  //       for (int i = 0; i < 10; i++)
  //       {
  //         Serial.println("line" + String(i) + " = " + tab_all_operation[i]); //
  //         for (int i = 0; i < 10; i++)
  //         {
  //           tab_operation[i] = "";
  //         }
  //         convert_char_to_tab(tab_all_operation[i], ",", tab_operation);
  //         Serial.println(tab_operation[5]);
  //         Serial.println(test);
  //         if (tab_operation[5] == "" && test == true)
  //         { // enregistrer les données utile de la première tache disponible
  //           Serial.println("here");
  //           line_id = tab_operation[0];
  //           line_gamme = tab_operation[1];
  //           previous_line_gamme = line_gamme.toInt();
  //           Operation = tab_operation[3];
  //           Machine_id = tab_operation[4];
  //           T_estim = tab_operation[2].toFloat();
  //           Serial.println(T_estim);
  //           test = false;
  //           goto this_place;
  //           // Serial.println("line number =" + line_id);
  //           // break;
  //         }
  //         else if (tab_operation[5] == "" && test == false && tab_operation[0] != "")
  //         {
  //           if (tab_operation[1].toInt() == previous_line_gamme + 1)
  //           {
  //             Serial.println("heree"); //
  //             line_gamme += "," + tab_operation[1];
  //             previous_line_gamme = tab_operation[1].toInt();
  //             T_estim += tab_operation[2].toFloat();
  //             Serial.println(T_estim);
  //             line_id += "," + tab_operation[0]; // les ligne des oppération en cours
  //             Serial.println(line_id);
  //             Operation += "," + tab_operation[3];
  //           }
  //         }
  //       this_place:
  //         Serial.println("end loop");
  //       }

  //       // Step 4: update T_start in gamme table ... all we need is the line id  // done
  //       GetAddress = "update_insert_T_start.php"; // change
  //       LinkGet = host + GetAddress;              //--> Make a Specify request destination
  //       getData = ("&id=") + line_id +
  //                 ("&Pack_id=") + P_param[0] +
  //                 ("&Code_operation=") + line_gamme +
  //                 ("&Operation_name=") + Operation +
  //                 ("&Estim_Time=") + T_estim +
  //                 ("&Machine_id=") + Machine_id +
  //                 ("&DigiTex=") + Smart_box +
  //                 ("&T_start=") + t_start;
  //       get_response = http_GET_Request(LinkGet, getData); //--> Print HTTP return code
  //       Serial.print("Returned data from Server : ");
  //       Serial.println(get_response); //--> Print request response payload

  //       delay(700);
  //       digitalWrite(Led_green, HIGH);
      
  //   }
  //   mfrc522.PICC_HaltA();
  //   mfrc522.PCD_StopCrypto1();
  // }
}

