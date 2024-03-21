#include <SoftwareSerial.h>
#include <TFT_eSPI.h>
SoftwareSerial gps(0, 1);
String gpsData;
TFT_eSPI tft;

void setup() {
  Serial.begin(115200);
  gps.begin(9600);

  tft.begin(); //start TFT LCD 
  tft.setRotation(3); //set screen rotation 
  tft.fillScreen(TFT_BLACK); //fill background 

  tft.setFreeFont(&FreeSans12pt7b); //set font type 
  tft.setTextColor(TFT_WHITE); //set text color 
  tft.drawString("GPS Information",70,30);

  tft.setFreeFont(&FreeSans9pt7b);
  tft.drawString("Date: ", 25, 80);
  tft.drawString("Time:  ", 25, 110);
  tft.drawString("Latitude:  ", 25, 140);
  tft.drawString("Longitude:  ", 25, 170);
  tft.drawString("Valid Data:  ", 25, 200);

}

void loop() {
  if (gps.available()) {
    char gpsChar = gps.read();
    
    gpsData += gpsChar;
    if (gpsChar == '\n') {
      if (gpsData.startsWith("$GNRMC")) {
        // Split the GNRMC sentence
        Serial.print("Raw GNRMC Data:  ");
        Serial.println(gpsData);
        int startIndex = 0;
        int endIndex = gpsData.indexOf(',');
        String parts[13]; 
        int partIndex = 0;
        while (endIndex >= 0) {
          parts[partIndex++] = gpsData.substring(startIndex, endIndex);
          startIndex = endIndex + 1;
          endIndex = gpsData.indexOf(',', startIndex);
        }
        parts[partIndex] = gpsData.substring(startIndex);

        // Extract information
        String time = parts[1]; // Time
        // String hh = (int)(time.substring(0, 2); // GMT Time
        String hh = String((int)(time.substring(0, 2).toInt() + 9));
        String mm = time.substring(2, 4);
        String ss = time.substring(4, 6);
        String status = parts[2]; // Status (A for valid, V for invalid)
        String latitude = parts[3]; // Latitude
        String latDirection = parts[4]; // Latitude direction (N/S)
        String longitude = parts[5]; // Longitude
        String lonDirection = parts[6]; // Longitude direction (E/W)
        String date = parts[9]; // Date
        String day = date.substring(0, 2);
        String month = date.substring(2, 4);
        String year = "20" + date.substring(4); 
        String validData = parts[12]; // Valid data (N: no data, A: data valid)

        // Convert latitude and longitude to degrees, minutes, and seconds
        float latDegrees = latitude.substring(0, 2).toFloat();
        float latMinutes = latitude.substring(2, 9).toFloat();
        float lonDegrees = longitude.substring(0, 3).toFloat();
        float lonMinutes = longitude.substring(3, 10).toFloat();

        // Convert minutes to seconds
        float latSeconds = (latMinutes - int(latMinutes)) * 60.0;
        float lonSeconds = (lonMinutes - int(lonMinutes)) * 60.0;

        // Combine degrees, minutes, and seconds into strings
        String latStr = String(int(latDegrees)) + "°" + String(int(latMinutes)) + "'" + String(latSeconds, 1) + "\"" + latDirection;
        String lonStr = String(int(lonDegrees)) + "°" + String(int(lonMinutes)) + "'" + String(lonSeconds, 1) + "\"" + lonDirection;

        tft.setFreeFont(&FreeSans9pt7b);

        tft.fillRect(80,80, 250, 25, TFT_BLACK);
        tft.fillRect(80,110, 250, 25, TFT_BLACK);
        tft.fillRect(102,140, 225, 25, TFT_BLACK);
        tft.fillRect(120,170, 205, 25, TFT_BLACK);
        tft.fillRect(120,200, 200, 25, TFT_BLACK);

        // tft.drawString("Date: " + date, 25, 80);
        String formattedDate = day + "/" + month + "/" + year;
        tft.drawString("Date:          " + formattedDate, 25, 80);
        
        tft.drawString("Time:         " + hh + " : " + mm + " : " + ss, 25, 110);
        tft.drawString("Latitude:     " + latStr, 25, 140);
        tft.drawString("Longitude:  " + lonStr, 25, 170);
        tft.drawString("Valid Data:  " + validData, 25, 200);
      }
      gpsData = ""; 
    }
  }
}
