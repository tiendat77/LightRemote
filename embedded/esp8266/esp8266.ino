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
#define STASSID "Slytherin"
#define STAPSK  "9WF^F^ua"
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

// Handler
void handleRoot();
void handleGetStatus();
void handleUpdateLight1();
void handleUpdateLight2();
void handleNotFound();

void setup(void) {
  pinMode(LIGHT1, OUTPUT);
  pinMode(LIGHT2, OUTPUT);

  digitalWrite(LIGHT1, !light1);
  digitalWrite(LIGHT2, !light2);

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
  String response = "{ \"light1\": " + String(light1) + ", \"light2\": " + String(light2) + " }";
  return response;
}

void genIndexPage() {
  indexPage = "<!DOCTYPE html><html lang=\"en\"><head> <meta charset=\"UTF-8\"> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"> <title>Light Remote</title> <style>.container{width: 100vw; height: 100vh; overflow: hidden; display: flex; justify-content: center; align-items: center; position: relative;}.main{display: flex; flex-direction: column; justify-content: center; align-items: center; overflow: auto; padding: 24px;}.title{font-size: 2em; font-style: italic; font-weight: 800; color: #6c868ec2;}.action{min-width: 200px; min-height: 50px; color: #6b6b6be8; font-size: 1.2em; font-style: italic; font-weight: 600; border: none; border-radius: 4px; box-shadow: 3px 5px 4px 0px rgba(199, 198, 136, 0.52);}.on{background: #fcff7bad;}.off{background: #c4cec4bf;}.mt-20{margin-top: 20px;}</style> <script src=\"https://code.jquery.com/jquery-1.11.3.js\"></script></head><body> <div class=\"container\"> <div class=\"main\"> <div style=\"margin-bottom: 30px;\"> <span class=\"title\">Light Remote</span> </div><div> <input hidden name=\"status\" id=\"status1\" value=\"false\"> <button type=\"submit\" id='light1' class=\"action\">Light 1</button> </div><div> <input hidden name=\"status\" id=\"status2\" value=\"false\"> <button type=\"submit\" id='light2' class=\"action mt-20\">Light 2</button> </div></div></div><script>$(document).ready(function (){$.ajax({url: '/api/list', type: 'get', dataType: 'json', error: function (a, b){console.error(b);}, success: function (res){setStatus(res);}}); $('#light2').click(function (e){e.preventDefault(); var value=$('#status2').val(); $.ajax({url: '/api/update/light2', data:{status: value}, type: 'get', dataType: 'json', error: function (a, b){console.error(b);}, success: function (res){setStatus(res);}});}); $('#light1').click(function (e){e.preventDefault(); var value=$('#status1').val(); $.ajax({url: '/api/update/light1', data:{status: value}, type: 'get', dataType: 'json', error: function (a, b){console.error(b);}, success: function (res){setStatus(res);}});});}); function setStatus(res){if (res.light1){$('#status1').val(\"false\"); $('#light1').addClass('on'); $('#light1').removeClass('off');}if (!res.light1){$('#status1').val(\"true\"); $('#light1').addClass('off'); $('#light1').removeClass('on');}if (res.light2){$('#status2').val(\"false\"); $('#light2').addClass('on'); $('#light2').removeClass('off');}if (!res.light2){$('#status2').val(\"true\"); $('#light2').addClass('off'); $('#light2').removeClass('on');}}</script></body></html>";
}
