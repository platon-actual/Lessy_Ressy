#include <FastLED.h>

#define FASTLED_ALLOW_INTERRUPTS 0
#define FASTLED_ESP8266_RAW_PIN_ORDER

#include <ESP8266WiFi.h>

//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager

#include "matrix_functions.h"
#include "index.h"


// tu vieja en tanga ya no es lo que era
char tecla = 0;
String comando;

#define FANTOM 'f'
#define FANTOM2 'l'
#define DEMO_TIME 10

#define LED_PIN 5

#define NUM_LEDS 64
#define LEDS_EN_TOTAL NUM_LEDS
//CRGB leds[NUM_LEDS];

ESP8266WebServer server(80);

void Demo1(){
  for (int i=0; i < NUM_LEDS; i++){
    leds_pixel[i] = CRGB::Black;
    FastLED.show();
    delay (25);
  }
  for (int i=NUM_LEDS; i > 0; i--){
    leds_pixel[i] = CRGB::White;
    FastLED.show();
    delay (25);
  }
  for (int i=0; i < NUM_LEDS; i++){
    leds_pixel[i] = CRGB::Orange;
    FastLED.show();
    delay (25);
  }
}

void setLed(){
  int n_led = server.arg("N_LED").toInt();
  int color_id = server.arg("COLOR").toInt();
  switch (color_id){
    case COLOR_AZUL:
      leds_pixel[n_led] = setRgbColor(CRGB::Blue);
      break;
    case COLOR_ROJO:
      leds_pixel[n_led] = setRgbColor(CRGB::Red);
      break;
  }
  //leds_pixel[n_led] = setRgbColor(color);
  FastLED.show();

}

void handleRoot(){
  String s = MAIN_page;
  server.send(200, "text/html", s);
}

//gets called when WiFiManager enters configuration mode
void configModeCallback (WiFiManager *myWiFiManager) {
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());
  //if you used auto generated SSID, print it
  Serial.println(myWiFiManager->getConfigPortalSSID());
  //entered config mode, make led toggle faster
}

void SerialProc(){
  comando = "";
  while (Serial.available() > 0){
    tecla = Serial.read();
    comando += tecla;

    switch (tecla){
      case 'u':
      case 'U':
        for (int i=0; i < NUM_LEDS; i++) leds_pixel[i] = CRGB::Black;
        FastLED.show();
        break;
      case 'r':
        for (int i=0; i < NUM_LEDS; i++) leds_pixel[i] = CRGB::Red;
        FastLED.show();
        break;
      case 'g':
        for (int i=0; i < NUM_LEDS; i++) leds_pixel[i] = CRGB::Green;
        FastLED.show();
        break;
      case 'b':
        for (int i=0; i < NUM_LEDS; i++) leds_pixel[i] = CRGB::Blue;
        FastLED.show();
        break;
      case 'w':
        for (int i=0; i < NUM_LEDS; i++) leds_pixel[i] = CRGB::White;
        FastLED.show();
        break;
      case FANTOM:
        for (int i=0; i < NUM_LEDS; i++){
          leds_pixel[i].r = fantasma[i].r; //= CRGB::White;
          leds_pixel[i].g = fantasma[i].g;
          leds_pixel[i].b = fantasma[i].b;
          FastLED.show();
        }
        break;
      case FANTOM2:
        ZigZag(fantasma, 8, 64, leds_pixel);
          FastLED.show();
        break;
      case 'p':
        ZigZag(spugface, 8, 64, leds_pixel);
          FastLED.show();
        break;
      case 'd':
        Demo1();
        break;
    }
  }
  //FastLED.delay(50);
  //delay(50);

  if (comando != ""){

  Serial.print("DEBUG: coso1 ->");
  Serial.println(comando);
  }
}

void setup() {
  FastLED.addLeds<APA106, LED_PIN, RGB>(leds_pixel, leds_totales);

  Serial.begin(115200);

  //WiFiManager
  //Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wifiManager;

  //set callback that gets called when connecting to previous WiFi fails, and enters Access Point mode
  wifiManager.setAPCallback(configModeCallback);

  //fetches ssid and pass and tries to connect
  //if it does not connect it starts an access point with the specified name
  //here  "AutoConnectAP"
  //and goes into a blocking loop awaiting configuration
  if (!wifiManager.autoConnect()) {
    Serial.println("failed to connect and hit timeout");
    //reset and try again, or maybe put it to deep sleep
    ESP.reset();
    delay(1000);
  }

  //if you get here you have connected to the WiFi
  Serial.println("connected...yeey :)");

  server.on("/", handleRoot);
  server.on("/setLed", setLed);
  server.begin();

}



void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
  SerialProc(); // RE BETA
}
