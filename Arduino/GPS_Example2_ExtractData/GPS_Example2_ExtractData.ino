#include <SoftwareSerial.h>

SoftwareSerial gps(0, 1);
String gpsData;

void setup() {
  Serial.begin(115200);
  gps.begin(9600);
}

void loop() {
  if (gps.available()) {
    char gpsChar = gps.read();
    gpsData += gpsChar;
    if (gpsChar == '\n') { // Check for end of sentence
      if (gpsData.startsWith("$GNRMC")) {
        // Split the GNRMC sentence into individual fields based on comma
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
        String status = parts[2]; // Status (A for valid, V for invalid)
        String latitude = parts[3]; // Latitude
        String latDirection = parts[4]; // Latitude direction (N/S)
        String longitude = parts[5]; // Longitude
        String lonDirection = parts[6]; // Longitude direction (E/W)
        String date = parts[9]; // Date
        String validData = parts[12]; // Valid data (N for no data, A for data valid)

        // Print extracted data to serial monitor
        Serial.print("Time: ");
        Serial.println(time);
        Serial.print("Latitude: ");
        Serial.print(latitude);
        Serial.print(" ");
        Serial.println(latDirection);
        Serial.print("Longitude: ");
        Serial.print(longitude);
        Serial.print(" ");
        Serial.println(lonDirection);
        Serial.print("Date: ");
        Serial.println(date);
        Serial.print("Valid data: ");
        Serial.println(validData);
        Serial.println(" ");
      }
      gpsData = ""; // Clear the data buffer for the next sentence
    }
  }
}
