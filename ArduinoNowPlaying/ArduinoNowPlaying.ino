#define LED_PIN 5
#define RIGHT_BUTTON_PIN 6
#define MIDDLE_BUTTON_PIN 3
#define LEFT_BUTTON_PIN 2

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD address and geometry and library initialization
const byte lcdAddr = 0x27;  // Address of I2C backpack
const byte lcdCols = 16;    // Number of character in a row
const byte lcdRows = 2;     // Number of lines

LiquidCrystal_I2C lcd(lcdAddr, lcdCols, lcdRows);

// Demo parameters
const byte lcdScrollRow = 0;          // Number of a demo row counting from 0
const unsigned int digitDelay = 500;  // Miliseconds before displaying next digit

void setup() {

  Serial.begin(115200);
  while (!Serial) {
    // some boards need to wait to ensure access to serial over USB
  }
  
  // put your setup code here, to run once:
  //Buttons= D2, D3, D4
  pinMode(LEFT_BUTTON_PIN, INPUT);
  pinMode(MIDDLE_BUTTON_PIN, INPUT);
  pinMode(RIGHT_BUTTON_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(LEFT_BUTTON_PIN), notify, CHANGE);
  attachInterrupt(digitalPinToInterrupt(MIDDLE_BUTTON_PIN), notify, CHANGE);
  attachInterrupt(digitalPinToInterrupt(RIGHT_BUTTON_PIN), notify, CHANGE);
  
  //Middle Led = D5
  digitalWrite(LED_PIN, LOW); // do this first
  pinMode(LED_PIN, OUTPUT);
  //https://github.com/mrkaleArduinoLib/LiquidCrystal_I2C/blob/master/examples/Autoscroll/Autoscroll.ino
  lcd.init();
  lcd.backlight();  
  //lcd.autoscroll();
  lcd.setCursor(0, 1);
  lcd.print("RandoArtist");
  lcd.setCursor(0, lcdScrollRow);
  lcd.print("A Place In Heaven (Super extended mix)");
  //lcd.setCursor(lcdCols, lcdScrollRow);
  lcd.setCursor(0, 1);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED_PIN, LOW); // do this first
  lcd.scrollDisplayLeft();
  delay(500);
  digitalWrite(LED_PIN, HIGH); // do this first
  lcd.scrollDisplayLeft();
  delay(500);
}

void notify() { 
   //ISR function
   Serial.println("Received Interrupt");
}
