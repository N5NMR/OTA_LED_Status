#include <ArduinoOTA.h>          // 👉 Bibliothek für Over-The-Air Updates (OTA)
#include "wifi_connect.h"        // 👉 Eigene WiFi-Verbindungs-Bibliothek (z.B. wifi_connect-Funktion)

// 📶 WLAN-Zugangsdaten (hier freies WLAN ohne Passwort)
const char* ssid = "WIFI NAME";
const char* password = "PASSWORD";       // 

void setup() 
{
  Serial.begin(115200);          // 👉 Serielle Schnittstelle starten (für Debug-Ausgaben)
  delay(1000);                  // 👉 Kleiner Wartezeit-Puffer, damit alles stabil startet
  Serial.println("\n");               // 👉 Kleiner Wartezeit-Puffer, damit alles stabil startet
  Serial.print("Programmname: ");
  Serial.println(__FILE__);
  delay(200);
  
  wifi_connect(ssid, password);  // 👉 WLAN-Verbindung aufbauen (eigene Funktion aus wifi_connect.h)

  // 👉 OTA Update-Name setzen, damit man das Gerät im Netzwerk erkennen kann
  ArduinoOTA.setHostname("OTA_NAME");

  // 👉 OTA Passwort setzen, damit nur autorisierte Geräte Updates machen können
  ArduinoOTA.setPassword("Password");

  // 👉 OTA-Service starten (damit OTA-Updates empfangen werden können)
  ArduinoOTA.begin();
}

void loop() 
{
  ArduinoOTA.handle();           // 👉 OTA-Dienst überwachen, damit Updates erkannt und verarbeitet werden
}
