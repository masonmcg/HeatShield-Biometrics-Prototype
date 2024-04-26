#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "wifi_network";
const char* password = "balls";
WebServer server(80);

void setup() {
  Serial.begin(115200);
  
  // Start access point
  WiFi.softAP(ssid, password);
  Serial.println("Access Point started.");
  
  // Print local IP address
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());

  // Start web server
  server.on("/", HTTP_GET, handleRoot);
  server.begin();
  Serial.println("HTTP server started.");
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  server.send(200, "text/plain", "Hello from ESP32-S2 Reverse TFT Feather!");
}
