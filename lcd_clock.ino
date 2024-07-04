#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

// Initialize the LCD with I2C address 0x3F and a 16x2 display
LiquidCrystal_I2C lcd(0x27, 16, 2);


const char *ssid     = "very_good_wifi"; //ur wifi name
const char *password = "password123"; // and password





WiFiUDP ntpUDP;
#define offset 10800   //gmt+3 u can add gmt in ur time zone (+1 gmt = 3600)
NTPClient timeClient(ntpUDP, "time.google.com", offset);

void setup() {

  lcd.begin();
  lcd.backlight();
  lcd.clear();


  // Wifi starting...
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
      lcd.setCursor(0, 0);
  lcd.print("Connecting");
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Conneted!");

  delay(1000);
  timeClient.begin();


}

void loop() {
  timeClient.update();
  
  time_t epochTime = timeClient.getEpochTime();
  String formattedTime = timeClient.getFormattedTime();
  
  struct tm *ptm = gmtime((time_t *)&epochTime);


  int monthDay = ptm->tm_mday;
  int currentMonth = ptm->tm_mon + 1;
  int currentYear = ptm->tm_year + 1900;
  String currentDate = String(monthDay) + "/" + String(currentMonth) + "/" + String(currentYear);


  lcd.setCursor(0, 0);
  lcd.print("Date:" + currentDate);
  lcd.setCursor(0, 1);
  lcd.print("Time:" + formattedTime);
  delay(500);
}
