#ifndef WIFI_CONNECT_H_
#define WIFI_CONNECT_H_

// 👉 Je nach ESP-Typ die passende WLAN-Bibliothek einbinden
#if defined(ESP8266)
  #include <ESP8266WiFi.h>
  #define LED_ON  LOW   // LED ist invertiert beim ESP8266
  #define LED_OFF HIGH
#elif defined(ESP32)
  #include <WiFi.h>
  #define LED_BUILTIN 2
  #define LED_ON  HIGH  // LED ist normal geschaltet beim ESP32
  #define LED_OFF LOW
#else
  #error "Nur ESP8266 oder ESP32 werden unterstützt"
#endif

// 👉 Diese Funktion verbindet das Gerät mit dem WLAN und zeigt Netzwerkdetails an
void wifi_connect(const char* ssid, const char* password)
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LED_OFF); // LED aus
  // 👉 Verhindert, dass SSID und Passwort dauerhaft im Flash gespeichert werden
  WiFi.persistent(false);

  // 👉 Setzt den ESP in den WLAN-Station-Modus (kein Access Point)
  WiFi.mode(WIFI_STA);

  // 👉 Automatische Wiederverbindung aktivieren, falls Verbindung verloren geht
  WiFi.setAutoReconnect(true);

  // 👉 Starte die Verbindung mit den übergebenen Zugangsdaten
  WiFi.begin(ssid, password);

// 👉 Zeilenumbruch für saubere Anzeige im Seriellen Monitor
  Serial.println("\n");
  
  // 👉 Ausgabe im seriellen Monitor
  Serial.print("📶 Verbinde mit WLAN: ");
  Serial.println(ssid);

  // 👉 Warte solange, bis das Gerät verbunden ist
  while (!WiFi.isConnected()) 
  {
    digitalWrite(LED_BUILTIN, LED_ON);  // LED an
    delay(200);
    digitalWrite(LED_BUILTIN, LED_OFF); // LED aus
    delay(200);
    Serial.print("."); //Wartepunkte auf dem seriellen Monitor...
  }


  // 👉 Verbindung erfolgreich: LED dauerhaft an
  digitalWrite(LED_BUILTIN, LED_ON);

  // 👉 Verbindung erfolgreich
  Serial.println("\n✅ WLAN verbunden!");

  // 👉 Zeige jetzt Informationen zum Netzwerk an
  Serial.println("🔎 Netzwerkinformationen:");

  // 👉 Zeige an, welcher ESP verwendet wird
#if defined(ESP8266)
  Serial.println("Modul: ESP8266");
#elif defined(ESP32)
  Serial.println("Modul: ESP32");
#endif

  // 👉 Zeige SSID (Name des WLANs)
  Serial.print("SSID: "); Serial.println(WiFi.SSID());

  // 👉 Zeige zugewiesene IP-Adresse
  Serial.print("IP-Adresse: "); Serial.println(WiFi.localIP());

  // 👉 Zeige MAC-Adresse (Hardware-Adresse)
  Serial.print("MAC-Adresse: "); Serial.println(WiFi.macAddress());

  // 👉 Zeige Signalstärke (RSSI = Received Signal Strength Indicator)
  Serial.print("RSSI: "); Serial.print(WiFi.RSSI()); Serial.println(" dBm");

  // 👉 Zeige Gateway-Adresse (z. B. dein Router)
  Serial.print("Gateway: "); Serial.println(WiFi.gatewayIP());

  // 👉 Zeige Subnetzmaske
  Serial.print("Subnetzmaske: "); Serial.println(WiFi.subnetMask());

  // 👉 Zeige DNS-Server (z. B. für Webseiten-Namen)
  Serial.print("DNS 1: "); Serial.println(WiFi.dnsIP(0));
  Serial.print("DNS 2: "); Serial.println(WiFi.dnsIP(1));

  // 👉 Trennlinie zur besseren Übersicht
  Serial.println("==============================");
}

#endif // WIFI_CONNECT_H_
