//#define DHTPIN 3 // By default its connected to pin D3, it can be changed, define it before the #include of the library
#include "Arduino_SensorKit.h"
#define BUZZER 5
#define Environment Environment_I2C
#define LED 6  

int potentiometer = A0;
long lastSend = 0;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  Environment.begin();
  Oled.begin();
  pinMode(BUZZER, OUTPUT); 	
  pinMode(LED,OUTPUT);
  pinMode(potentiometer, INPUT);
  
  while(!Serial);

  Accelerometer.begin();
  
}

void loop() {
  if (Accelerometer.readZ() >= 0.5) {
    int sensor_value = analogRead(potentiometer); //Read the value from the potentiometer connected to the A0 pin
    int value = map(sensor_value, 0, 1023, 30, -16);
    delay(10);
    Oled.setFlipMode(1); 
  }
  if (Accelerometer.readX() <= -0.6) {
    int sensor_value = analogRead(potentiometer); //Read the value from the potentiometer connected to the A0 pin
    int value = map(sensor_value, 0, 1023, 30, -16);
    delay(10);
    Oled.setFlipMode(1); 
  }
   if (Accelerometer.readX() >= 0.6) {
    delay(10);
    Oled.setFlipMode(0); 
    int sensor_value = analogRead(potentiometer); //Read the value from the potentiometer connected to the A0 pin
    int value = map(sensor_value, 0, 1023, 0, 46);
  }
  Oled.setFont(u8x8_font_inb21_2x4_r); 
  Oled.setCursor(0, 32);  
  Oled.print(Environment.readTemperature());
  Oled.println(" C");
  Oled.refreshDisplay();  
  
  int sensor_value = analogRead(potentiometer); //Read the value from the potentiometer connected to the A0 pin
  int value = map(sensor_value, 0, 1023, 30, -16);
  Oled.setCursor(0, 36);
  Oled.print("M=");
  Oled.print(value);
  Oled.println(" C");
  Oled.refreshDisplay();

  // FIXED SERIAL BLOCK
  if(millis() - lastSend > 10000){
    int current_sensor_value = analogRead(potentiometer); 
    int current_map_value = map(current_sensor_value, 0, 1023, 30, -16);
    
    // Sends: Temperature,Maximum
    Serial.print(Environment.readTemperature());
    Serial.print(",");
    Serial.println(current_map_value);

    lastSend = millis();
  }
  
  if (Environment.readTemperature() >= value) {
    tone(BUZZER, 10); 
    delay(50);
    noTone(BUZZER);
    delay(50);
    digitalWrite(LED, HIGH); 
    delay(50);
    digitalWrite(LED, LOW); 
    delay(50);
    
    if(millis() - lastSend > 10000){
      int warning_sensor_value = analogRead(potentiometer); 
      int warning_map_value = map(warning_sensor_value, 0, 1023, 30, -16);       
      
      // We send the same format so Python doesn't break
      Serial.print(Environment.readTemperature());
      Serial.print(",");
      Serial.println(warning_map_value);

      lastSend = millis();
    }
  }
}
  
