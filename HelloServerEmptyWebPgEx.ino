// This code is derived from the HelloServer Example
// in the (ESP32) WebServer library .
//
// It hosts a webpage which has one temperature reading to display.
// The webpage is always the same apart from the reading which would change.
// The getTemp() function simulates getting a temperature reading.
// homePage.h contains 2 constant string literals which is the two parts of the
// webpage that never change.
// handleRoot() builds up the webpage by adding as a C++ String:
// homePagePart1 + getTemp() +homePagePart2
// It then serves the webpage with the command:
// server.send(200, "text/html", message);
// Note the text is served as html.
//
// Replace the code in the homepage.h file with your own website HTML code.
//
// This example requires only an ESP32 and download cable. No other hardware is reuired.
// A wifi SSID and password is required.
// Written by: Natasha Rohan  12/3/23
//
#include <WiFi.h>
#include <WiFiClient.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include "homepage.h"
#include <DFRobot_DHT11.h>
#include "MAX30100_PulseOximeter.h"
#define REPORTING_PERIOD_MS 1000
#define ADC_VREF_mV 3300.0  // in millivolt
#define ADC_RESOLUTION 4096.0
#define PIN_LM35 35  // ESP32 pin GPIO36 (ADC0) connected to LM35

PulseOximeter pox;
uint32_t tsLastReport = 0;
float BPM = -1.0F;

Adafruit_MMA8451 mma = Adafruit_MMA8451();

const char* ssid = "Seansiphone";
const char* password = "gabtoocool";

WebServer server(80);

//temp function to simulate temp sensor
String getTemp() {
  int adcVal = analogRead(PIN_LM35);
  float milliVolt = adcVal * (ADC_VREF_mV / ADC_RESOLUTION);
  float tempC = milliVolt / 10;
   Serial.print("Temperature: ");
  Serial.print(tempC);   // print the temperature in °C
  Serial.print("°C\n");
  return String(tempC);
  //Lm35 is working in it's Non linear range within the ESP32
}

String getHumi() {
  //String humi = String(DHT.humidity);
  return String("WIP");
}


String getO2() {
  pox.update();
  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
    Serial.print("SpO2:");
    Serial.print(pox.getSpO2());
    Serial.println("%");
    tsLastReport = millis();
  }
  String O2 = String(pox.getSpO2());
  return O2;
}


void handleRoot() {
  // String message = homePagePart1 + getTemp() + homePagePart2 + getHumi() + homePagePart3 + getAcc() + homePagePart4 + getBPM() + homePagePart5;  // + getO2() + homePagePart6 ;
  String message = homePagePart1 + getTemp() + homePagePart2 + getHumi() + homePagePart3 + getAcc() + homePagePart4 + getBPM() + homePagePart5 + getO2() + homePagePart6 ;
  //String message = homePagePart1 + getTemp()  + homePagePart2;
  server.send(200, "text/html", message);
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

void setup(void) {
  Serial.begin(115200);

  Serial.println("Adafruit MMA8451 test!");


  if (!mma.begin()) {
    Serial.println("Couldnt start");
    while (1)
      ;
  }
  Serial.println("MMA8451 found!");

  mma.setRange(MMA8451_RANGE_2_G);

  Serial.print("Range = ");
  Serial.print(2 << mma.getRange());
  Serial.println("G");


  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

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

  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);
  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");

  Serial.print("Initializing pulse oximeter..");

  if (!pox.begin()) {
    Serial.println("FAILED");
    for (;;)
      ;
  } else {
    Serial.println("SUCCESS");
  }

  pox.setOnBeatDetectedCallback(onBeatDetected);
}
void onBeatDetected() {
  Serial.println("Beat!");
}

void loop(void) {
  pox.update();
  delay(2);  //allow the cpu to switch to other tasks
  server.handleClient();
}

String getBPM() {
  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
    BPM = pox.getHeartRate();
    Serial.print("Heart rate:");
    Serial.print(BPM);
    tsLastReport = millis();
  }
  return String(BPM);
}



String getAcc() {
  sensors_event_t event;
  int x;//,y,z,ans;
  x=event.acceleration.x;
  //y=event.acceleration.y;
  //z=event.acceleration.z;
  mma.getEvent(&event);
  //Serial.print("X: \t");
  Serial.print(event.acceleration.x);
  //Serial.print(event.acceleration.y);
  //Serial.print(event.acceleration.z);
  //Serial.println("\t");
  //ans = sqrt((x*x)+(y*y)+(z*z));
  return String(x);
  Serial.print(x);
}
