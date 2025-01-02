/*
   This code uses the MPU6050 sensor to calculate earthquake magnitude and display it on an LCD screen (using I2C).

   - Accelerometer values (X, Y, Z) are averaged to calculate total acceleration (totalAcc).
   - Total acceleration is converted to the Richter scale to determine earthquake magnitude.
   - The determined magnitude is displayed on a 16x2 LCD, with only magnitudes greater than 2.0 shown.

   - LEDs indicate earthquake severity based on the following ranges:
   - **Green LED (2-5.0)**: Mild earthquake
   - **Yellow LED (5.1-7.0)**: Moderate earthquake
   - **Red LED (7.1 and above)**: Severe earthquake
   - The buzzer sounds for magnitudes 4.5 and above.

   Hardware Connections:
   - MPU6050 sensor connected via I2C (SDA, SCL).
   - LCD screen connected via I2C.
   - Code is compatible with Arduino and the standard Wire library.

   LCD screen connections:
   - SDA: A4
   - SCL: A5
*/

#include "Wire.h"
#include <MPU6050_light.h>
#include <LiquidCrystal_I2C.h>

// LED Pins
#define greenLed1 9
#define greenLed2 8
#define greenLed3 7

#define yellowLed1 6
#define yellowLed2 5

#define redLed1 4
#define redLed2 3
#define redLed3 2

// Buzzer Pin
int buzzerPin = 10;

// Variables for accelerometer values
float accX, accY, accZ;
float totalAcc = 0;
float filtered_acc = 0;
float earthquakeMagnitude = 0;

// Create MPU6050 object and LCD object
MPU6050 mpu(Wire);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {

  // Initialize LED pins as output
  pinMode(greenLed1, OUTPUT);
  pinMode(greenLed2, OUTPUT);
  pinMode(greenLed3, OUTPUT);

  pinMode(yellowLed1, OUTPUT);
  pinMode(yellowLed2, OUTPUT);

  pinMode(redLed1, OUTPUT);
  pinMode(redLed2, OUTPUT);
  pinMode(redLed3, OUTPUT);

  pinMode(buzzerPin, OUTPUT);

  // Start serial communication for debugging
  Serial.begin(9600);
  Wire.begin();

  // Initialize MPU6050 sensor
  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while (status != 0) {}  // Stop everything if MPU6050 is not connected

  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  mpu.calcOffsets(true, true);  // Calibrate gyro and accelerometer
  Serial.println("Done!\n");

  // Initialize LCD screen
  lcd.begin();
  lcd.backlight();  // Turn on LCD backlight
  lcd.setCursor(0, 0);
  lcd.print("Earthquake Sensor");
}

void loop() {

  mpu.update();

  // Read accelerometer values
  accX = mpu.getAccX();
  accY = mpu.getAccY();
  accZ = mpu.getAccZ();

  // Calculate total acceleration by averaging X, Y, and Z values
  totalAcc = (accX + accY + accZ) / 3;
  // Apply a scaling factor for the total acceleration value
  filtered_acc = totalAcc * 10;

  // Convert the total acceleration to earthquake magnitude
  earthquakeMagnitude = filtered_acc - 0.2;

  // Reset LEDs before updating them
  resetLeds();

  // Debugging output
  Serial.print("Filtered Average Acceleration: ");
  Serial.println(filtered_acc, 3);
  Serial.println("=========================");
  Serial.print("Earthquake Magnitude: ");
  Serial.println(earthquakeMagnitude, 1);

  // Display earthquake severity on LEDs and sound buzzer if necessary
  if (earthquakeMagnitude > 0.0 && earthquakeMagnitude <= 1.0) {
    digitalWrite(greenLed1, HIGH);  // Very mild
    noTone(buzzerPin);
  }
  else if (earthquakeMagnitude > 1.0 && earthquakeMagnitude <= 2.0) {
    digitalWrite(greenLed1, HIGH);
    digitalWrite(greenLed2, HIGH);  // Mild
    noTone(buzzerPin);
  }
  else if (earthquakeMagnitude > 2.0 && earthquakeMagnitude <= 3.0) {
    digitalWrite(greenLed1, HIGH);
    digitalWrite(greenLed2, HIGH);
    digitalWrite(greenLed3, HIGH);  // Moderate
    noTone(buzzerPin);
  }
  else if (earthquakeMagnitude > 3.0 && earthquakeMagnitude <= 4.0) {
    digitalWrite(yellowLed1, HIGH);  // Strong
    noTone(buzzerPin);
  }
  else if (earthquakeMagnitude > 4.0 && earthquakeMagnitude <= 5.0) {
    digitalWrite(yellowLed1, HIGH);
    digitalWrite(yellowLed2, HIGH);  // Very strong
    tone(buzzerPin, 1000, 200); // 1000Hz for 200ms
    delay(200);
    noTone(buzzerPin);
  }
  else if (earthquakeMagnitude > 5.0 && earthquakeMagnitude <= 6.0) {
    digitalWrite(redLed1, HIGH);  // Dangerous
    tone(buzzerPin, 2000, 500); // 2000Hz for 500ms
    delay(200);
    noTone(buzzerPin);
  }
  else if (earthquakeMagnitude > 6.0 && earthquakeMagnitude <= 7.0) {
    digitalWrite(redLed1, HIGH);
    digitalWrite(redLed2, HIGH);  // Very dangerous
    tone(buzzerPin, 3000, 1000); // 3000Hz for 1s
    delay(500);
    noTone(buzzerPin);
  }
  else if (earthquakeMagnitude > 7.0) {
    digitalWrite(redLed1, HIGH);
    digitalWrite(redLed2, HIGH);
    digitalWrite(redLed3, HIGH);  // Critical
    tone(buzzerPin, 4000, 2000); // 4000Hz for 2s
    delay(1000);
    noTone(buzzerPin);
  }

  // Display earthquake magnitude on LCD
  lcd.setCursor(0, 0);
  lcd.print("Magnitude: ");
  lcd.setCursor(0, 1);
  lcd.print(abs(earthquakeMagnitude), 1);

  // Pause for a while before the next loop iteration
  delay(500);
}

// Function to reset LED states to LOW
void resetLeds() {
  digitalWrite(greenLed1, LOW);
  digitalWrite(greenLed2, LOW);
  digitalWrite(greenLed3, LOW);

  digitalWrite(yellowLed1, LOW);
  digitalWrite(yellowLed2, LOW);

  digitalWrite(redLed1, LOW);
  digitalWrite(redLed2, LOW);
  digitalWrite(redLed3, LOW);

  digitalWrite(buzzerPin, LOW);
  noTone(buzzerPin);
}
