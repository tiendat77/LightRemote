#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

#ifndef STASSID
// #define STASSID "Gryffindor"
// #define STAPSK  "XnU3Xz^`"
#define STASSID "Slytherin"
#define STAPSK  "9WF^F^ua"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

// Bot Token (Get from Botfather)
#define BOT_TOKEN "XXXXXXXXXX:XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
#define CHAT_ID "XXXXXXXXXX"

WiFiClientSecure client;
UniversalTelegramBot bot(BOT_TOKEN, client);

// Checks for new messages every 1 second.
int botRequestDelay = 1000;
unsigned long lastTimeBotRan;

const int ledPin = 2;
bool ledState = LOW;

// Handle what happens when you receive new messages
void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));

  for (int i=0; i<numNewMessages; i++) {
    // Chat id of the requester
    String chat_id = String(bot.messages[i].chat_id);
    if (chat_id != CHAT_ID){
      bot.sendMessage(chat_id, "Unauthorized user: " + chat_id, "");
      // continue;
    }

    // Print the received message
    String text = bot.messages[i].text;
    Serial.println(text);

    String from_name = bot.messages[i].from_name;

    if (text == "/start") {
      String welcome = "Welcome, " + from_name + ".\n";
      welcome += "Use the following commands to control your outputs.\n\n";
      welcome += "/led_on to turn GPIO ON \n";
      welcome += "/led_off to turn GPIO OFF \n";
      welcome += "/state to request current GPIO state \n";
      bot.sendMessage(chat_id, welcome, "");
    }

    if (text == "/led_on") {
      bot.sendMessage(chat_id, "LED state set to ON", "");
      ledState = HIGH;
      digitalWrite(ledPin, ledState);
    }

    if (text == "/led_off") {
      bot.sendMessage(chat_id, "LED state set to OFF", "");
      ledState = LOW;
      digitalWrite(ledPin, ledState);
    }

    if (text == "/state") {
      if (digitalRead(ledPin)){
        bot.sendMessage(chat_id, "LED is ON", "");
      }
      else{
        bot.sendMessage(chat_id, "LED is OFF", "");
      }
    }
  }
}

void setup() {
  Serial.begin(115200);

  #ifdef ESP8266
    client.setInsecure();
  #endif

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState);

  // Connect to Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());
}

void loop() {
  if (millis() > lastTimeBotRan + botRequestDelay)  {
    Serial.println("check");
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while(numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    lastTimeBotRan = millis();
  }
}

void handleTelegramBot() {
  // check for new message every 1 second
  if (millis() > lastTimeBotCheck + 100)  {
    Serial.println("check");
    lastTimeBotCheck = millis();
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    handleTelegramMessage(1);

//    while(numNewMessages) {
//      Serial.println("handleNewMessages");
//      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
//    }
  }
}

// Handle Telegram Bot when message receive
void handleTelegramMessage(int len) {
  Serial.println("handleNewMessages");
  Serial.println(String(len));

  for (int i = 0; i < len; i++) {
    String chat_id = String(bot.messages[i].chat_id);

    if (chat_id != ChatID){
      bot.sendMessage(chat_id, "Unauthorized user", "");
      continue;
    }

    String from_name = bot.messages[i].from_name;
    String text = bot.messages[i].text;

    if (text == "/start") {
      String welcome = "Welcome, " + from_name + ".\n";
      welcome += "Use the following commands to control your outputs.\n\n";
      welcome += "/light1 to turn on/turn off light 1 \n";
      welcome += "/light2 to turn on/turn off light 2 \n";
      welcome += "/state to request current lights state \n";
      bot.sendMessage(chat_id, welcome, "");
      return;
    }

    if (text == "/light1") {
      light1 = !light1;
      String message = "Light 1 state set to " + light1 ? "ON" : "OFF";
      bot.sendMessage(chat_id, message, "");
      digitalWrite(LIGHT1, !light1);
      return;
    }

    if (text == "/light2") {
      light2 = !light2;
      String message = "Light 2 state set to " + light2 ? "ON" : "OFF";
      bot.sendMessage(chat_id, message, "");
      digitalWrite(LIGHT2, !light2);
      return;
    }

    if (text == "/state") {
      String message = "Light status:";
      message += "\nLight 1 is " + light1 ? "ON" : "OFF";
      message += "\nLight 2 is " + light2 ? "ON" : "OFF";
      bot.sendMessage(chat_id, message, "");
      return;
    }
  }
}