# Light Remote Project
> Remote control home appliances by smartphone

The purpose of this project is build an android-app to control home appliances.

<p align="center">
  <img src="assets/app/app-icon.png" with="120px" height="120px" alt="logo" />
</p>

## Requirements
1. ESP8266 Module
2. Android phone running 5.0 (Lollipop) or higher
3. WiFi network

## Create a Telegram bot for ESP8266 board

Open Telegram and follow the next steps to create a Telegram Bot:

1. Search for “botfather” and click the BotFather as shown below. Or open this link t.me/botfather in your smartphone.

<img src="assets/app/telegram-botfather.png" with="120px" height="120px" alt="logo" />

2. Type /newbot and follow the instructions to create your bot. Give it a name and username.

3. If your bot is successfully created, you’ll receive a message with a link to access the bot and the bot token. Save the bot token because you’ll need it so that the ESP8266 can interact with the bot.

## Preparing Arduino IDE
To install the ESP32 board in your Arduino IDE, follow these next instructions:
1. In Arduino IDE, go to File> Preferences.
2. Enter `https://dl.espressif.com/dl/package_esp32_index.json` into the “Additional Board Manager URLs” field as shown in the figure below. Then, click the “OK” button.

    **Note**: if you already have the boards URL, you can separate the URLs with a comma.

3. Open the Boards Manager. Go to Tools > Board > Boards Manager…
4. Search for ESP32 and press install button for the “ESP32 by Espressif Systems“.
5. That’s it. It should be installed after a few seconds.

You also have to install Universal Telegram Bot Library and ArduinoJson Library. Follow the next steps to install the library from zip file:
1. Download [Universal Telegram Bot](https://github.com/tiendat77/LightRemote/blob/master/esp8266/libraries/Universal-Arduino-Telegram-Bot.zip) and [ArduinoJson](https://github.com/tiendat77/LightRemote/blob/master/esp8266/libraries/ArduinoJson.zip)
2. Open Sketch > Include Library > Add.ZIP Library...
3. Add the library you’ve just downloaded.

## ESP8266
[Arduino Library](https://github.com/esp8266/Arduino)

Connection:
| PIN          | Device    | Description        |
| -----------  | --------- | ------------------ |
| GPIO12       | Light 1   | Light 1 control    |
| GPIO13       | Light 2   | Light 2 control    |
| GPIO15       | LED       | Show wifi signal status |

## Usage
1. Upload [the sketch](https://github.com/tiendat77/LightRemote/blob/master/esp8266/webserver/) to the ESP8266 via [Arduino IDE](https://www.arduino.cc/en/software)
2. Install [Light Remote](https://github.com/tiendat77/LightRemote/blob/master/LightRemote.apk) application to your smartphone
3. Connect ESP8266 and your smartphone to the same WiFi network
4. Open Light Remote application, then open *App Settings* and make sure *ESP Address* is correct.
5. Enjoy!

## Demos :boom:
![LightRemote](assets/app/demo.png?raw=true "LightRemote Demo")

## Open source libraries
- [Universal Telegram Bot Library](https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot)
- [ArduinoJson Library](https://github.com/bblanchon/ArduinoJson)

## License

MIT © 2020 [TienDat](mailto:huynhztienzdat@gmail.com), see [the license](https://github.com/tiendat77/LightRemote/blob/master/LICENSE).