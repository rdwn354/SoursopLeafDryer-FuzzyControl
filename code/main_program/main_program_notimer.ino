#include "MAX6675.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET     -1 
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int dataPin   = 4;
const int clockPin  = 6;
const int selectPin = 5;
MAX6675 thermoCouple(selectPin, dataPin, clockPin);

// Define the pin connected to the relay
const int relay1 = 2; // Change this to match your setup
const int relay2 = 3;

uint32_t start, stop;

void setup() {
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  Serial.begin(9600);
  SPI.begin();
  thermoCouple.begin();
  thermoCouple.setSPIspeed(4000000);
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
}

void loop() {
  delay(100);
  start = micros();
  int status = thermoCouple.read();
  stop = micros();
  float temp = thermoCouple.getTemperature();

  Serial.print(millis());
  Serial.print("\tstatus: ");
  Serial.print(status);
  Serial.print("\ttemp: ");
  Serial.print(temp);
  Serial.print("\tus: ");
  Serial.println(stop - start);

  // Display temperature on OLED
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Temp: ");
  display.print(temp);
  display.println(" C");
  display.display();

  // Check temperature and control relay
  if (temp > 50) {
    digitalWrite(relay1, LOW);
    digitalWrite(relay2, LOW);
  } else {
    digitalWrite(relay1, HIGH);
    digitalWrite(relay2, HIGH);
  }

  delay(1000);
}
