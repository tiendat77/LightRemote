/*
  Author:
  _____ ___ _____ _   _   ____    _  _____   _   _ _   ___   ___   _ _   _ 
|_   _|_ _| ____| \ | | |  _ \  / \|_   _| | | | | | | \ \ / / \ | | | | |
  | |  | ||  _| |  \| | | | | |/ _ \ | |   | |_| | | | |\ V /|  \| | |_| |
  | |  | || |___| |\  | | |_| / ___ \| |   |  _  | |_| | | | | |\  |  _  |
  |_| |___|_____|_| \_| |____/_/   \_\_|   |_| |_|\___/  |_| |_| \_|_| |_|
                                                                          
  Date created 8-Apr-2020 
*/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include "ESP8266WebServer.h"

#ifndef STASSID
#define STASSID "Gryffindor"
#define STAPSK  "your-password"
#endif

const char* ssid     = STASSID;
const char* password = STAPSK;

ESP8266WebServer server(80);

const int LED = LED_BUILTIN;
const int LIGHT1 = 4;
const int LIGHT2 = 5;

boolean light1 = false;
boolean light2 = false;

const String indexPage = "<html><head><title>ESP8266 Web Server</title></head><body><h1>ESP8266 Web Server Work!/</h1></body></html>";

// Handler
void handleRoot();
void handleGetStatus();
void handleUpdateLight1();
void handleUpdateLight2();
void handleNotFound();

void setup(void) {
  pinMode(LIGHT1, OUTPUT);
  pinMode(LIGHT2, OUTPUT);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, 0);

  Serial.begin(115200);
  WiFi.begin(ssid, password);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);

  server.on("/api/list", handleGetStatus);

  server.on("/api/update/light1", handleUpdateLight1);

  server.on("/api/update/light2", handleUpdateLight2);

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("Server started");
}

void loop(void) {
  server.handleClient();
}

// WEB SERVER HANDLER
void handleGetStatus() {
  digitalWrite(LED, 1);
  String response = getLightStatus();
  server.send(200, "application/json", response);
  digitalWrite(LED, 0);
}

void handleUpdateLight1() {
  digitalWrite(LED, 1);

  String state = server.arg(0);

  if (state.equals("true")) {
    light1 = true;
  } else {
    light1 = false;
  }

  digitalWrite(LIGHT1, light1);

  String response = getLightStatus();
  server.send(200, "application/json", response);
  digitalWrite(LED, 0);
}

void handleUpdateLight2() {
  digitalWrite(LED, 1);
  String message = "Parameters:\n";

  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }

  String response = getLightStatus();
  server.send(200, "application/json", response);
  digitalWrite(LED, 0);
}

void handleRoot() {
  digitalWrite(LED, 1);
  server.send(200, "text/html", indexPage);
  digitalWrite(LED, 0);
}

void handleNotFound() {
  digitalWrite(LED, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }

  server.send(404, "text/plain", message);
  digitalWrite(LED, 0);
}

// UTILS
String getLightStatus() {
  String response = "{ light1: " + String(light1) + ", light2: " + String(light2) + " }";
  return response;
}
