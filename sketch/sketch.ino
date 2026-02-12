
#include "Arduino_SensorKit.h"



void setup() {
  Oled.begin();
  Oled.setFlipMode(true); // Sets the rotation of the screen
  Serial.begin(9600);
  Environment.begin();
}
 
void loop() {
  int random_value = analogRead(A0);   //read value from A0

  Serial.print("Temperature = ");
  Serial.print(Environment.readTemperature()); //print temperature
  Serial.println(" C");
  Serial.print("Humidity = ");
  Serial.print(Environment.readHumidity()); //print humidity
  Serial.println(" %");
  delay(2000);
 
  Oled.setFont(u8x8_font_chroma48medium8_r); 
  Oled.setCursor(0, 33);    // Set the Coordinates 
  Oled.print("Temp = ");
  Oled.print(Environment.readTemperature()); //print temperature
  Oled.println(" C");
  Oled.refreshDisplay();    // Update the Display 
  delay(1000);
}