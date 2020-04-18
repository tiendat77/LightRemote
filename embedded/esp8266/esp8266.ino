/*
  Author:
  _____ ___ _____ _   _   ____    _  _____   _   _ _   ___   ___   _ _   _
 |_   _|_ _| ____| \ | | |  _ \  / \|_   _| | | | | | | \ \ / / \ | | | | |
   | |  | ||  _| |  \| | | | | |/ _ \ | |   | |_| | | | |\ V /|  \| | |_| |
   | |  | || |___| |\  | | |_| / ___ \| |   |  _  | |_| | | | | |\  |  _  |
   |_| |___|_____|_| \_| |____/_/   \_\_|   |_| |_|\___/  |_| |_| \_|_| |_|

  Date created 8-Apr-2020
*/

/*
  Gryffindor
  XnU3Xz^`

  Slytherin
  9WF^F^ua
*/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include "ESP8266WebServer.h"

#ifndef STASSID
#define STASSID "Gryffindor"
#define STAPSK  "XnU3Xz^`"
#endif

const char* ssid     = STASSID;
const char* password = STAPSK;

ESP8266WebServer server(80);

const int LED = LED_BUILTIN;
const int LIGHT1 = 12;
const int LIGHT2 = 13;

boolean light1 = false;
boolean light2 = false;

String indexPage = "";
String headerPage = "";
String footerPage = "";

// Handler
void handleRoot();
void handleGetStatus();
void handleUpdateLight1();
void handleUpdateLight2();
void handleNotFound();

void setup(void) {
  pinMode(LIGHT1, OUTPUT);
  pinMode(LIGHT2, OUTPUT);

  Serial.begin(9600);
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

  genIndexPage();

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
  String response = getLightStatus();
  server.send(200, "application/json", response);
}

void handleUpdateLight1() {
  String state = server.arg(0);
  light1 = state.equals("true");
  digitalWrite(LIGHT1, !light1);

  String response = getLightStatus();
  server.send(200, "application/json", response);
}

void handleUpdateLight2() {
  String state = server.arg(0);
  light2 = state.equals("true");
  digitalWrite(LIGHT2, !light2);

  String response = getLightStatus();
  server.send(200, "application/json", response);
}

void handleRoot() {
  indexPage = headerPage;

  if (light1) {
    indexPage += "<input hidden name=\"status\" id=\"status1\" value=\"false\">";
    indexPage += "<button type=\"submit\" class=\"action on\">Light 1</button>";
  } else {
    indexPage += "<input hidden name=\"status\" id=\"status1\" value=\"true\">";
    indexPage += "<button type=\"submit\" class=\"action off\">Light 1</button>";
  }

  indexPage += "</form>";
  indexPage += "<form action=\"/api/update/light2\" target=\"hiddenFrame\">";

  if (light2) {
    indexPage += "<input hidden name=\"status\" id=\"status2\" value=\"false\">";
    indexPage += "<button type=\"submit\" class=\"action on mt-20\">Light 2</button>";
  } else {
    indexPage += "<input hidden name=\"status\" id=\"status2\" value=\"true\">";
    indexPage += "<button type=\"submit\" class=\"action off mt-20\">Light 2</button>";
  }

  indexPage += footerPage;

  server.send(200, "text/html", indexPage);
}

void handleNotFound() {
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
}

// UTILS
String getLightStatus() {
  String response = "{ light1: " + String(light1) + ", light2: " + String(light2) + " }";
  return response;
}

void genIndexPage() {
  headerPage += "<!DOCTYPE html><html lang=\"en\"><head> <meta charset=\"UTF-8\"> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"> <title>Light Remote</title> <style>.container{width: 100vw; height: 100vh; overflow: hidden; display: flex; justify-content: center; align-items: center; position: relative;}.main{display: flex; flex-direction: column; justify-content: center; align-items: center; overflow: auto;}.action{min-width: 200px; min-height: 50px; box-shadow: 2px 2px rgba(123, 124, 180, 0.6);}.on{background: #1ee870;}.off{background: #dedede;}.mt-20{margin-top: 20px;}.hide{position: absolute; top: -1; left: -1; width: 1px; height: 1px;}</style></head><body> <div class=\"container\"> <iframe name=\"hiddenFrame\" class=\"hide\"></iframe> <div class=\"main\"> <form action=\"/api/update/light1\" method=\"GET\" target=\"hiddenFrame\">";

  footerPage += "</form></div></div></body></html>";
}
