# Earthquake Detection System with MPU6050

This project demonstrates how to detect earthquake severity using the MPU6050 accelerometer and gyroscope sensor with Arduino. The system measures the total acceleration (combined X, Y, Z axis values) and calculates the earthquake severity based on the Richter scale. The severity is displayed on an LCD screen and visualized with LEDs and buzzer alerts.

## Features

- **Earthquake Severity Calculation**: Based on accelerometer data from the MPU6050 sensor.
- **Richter Scale Mapping**: Converts the total acceleration into an earthquake severity value.
- **LCD Display**: Shows the calculated earthquake severity in real-time.
- **LED Indicators**: Visualize the severity with color-coded LEDs:
  - **Green LEDs** (Light: 2.0 - 5.0)
  - **Yellow LEDs** (Moderate: 5.1 - 7.0)
  - **Red LEDs** (Severe: 7.1 and above)
- **Buzzer Alerts**: Buzzer sounds for significant earthquake readings (Richter scale > 4.5).
  
## Hardware Requirements

- **Arduino Board** (e.g., Arduino Uno)
- **MPU6050 Sensor** (for measuring acceleration and rotation)
- **LCD Screen (I2C)**: 16x2 LCD display to show earthquake severity
- **LEDs**: Green, Yellow, and Red LEDs for visual indicators
- **Buzzer**: To emit sound alerts for significant earthquakes
- **Jumper Wires** and **Breadboard** for connections

## Connections

- **MPU6050 (I2C)**:
  - SDA: A4
  - SCL: A5

- **LCD (I2C)**:
  - SDA: A4
  - SCL: A5

- **LEDs and Buzzer**: 
  - Green LEDs: Pin 9, 8, 7
  - Yellow LEDs: Pin 6, 5
  - Red LEDs: Pin 4, 3, 2
  - Buzzer: Pin 10

## Software Requirements

- **Arduino IDE**
- **MPU6050_light Library**: For easy communication with the MPU6050 sensor
- **Wire Library**: For I2C communication with the sensor and LCD

## Installation

1. **Install the Required Libraries**:
   - Open Arduino IDE.
   - Go to **Sketch** -> **Include Library** -> **Manage Libraries**.
   - Search for **MPU6050_light** and install it.
   - Search for **LiquidCrystal_I2C** and install it.

2. **Upload the Code**:
   - Connect your Arduino board to the computer.
   - Open the `earthquake_detection_system.ino` file in Arduino IDE.
   - Select the correct board and port in the **Tools** menu.
   - Click **Upload** to upload the code to your Arduino board.

3. **Connect the Hardware**:
   - Wire up the MPU6050 sensor and LCD to your Arduino as per the connections mentioned above.
   - Connect the LEDs and buzzer to the specified pins.

4. **Test the System**:
   - Open the **Serial Monitor** in Arduino IDE to see the filtered acceleration and earthquake severity values.
   - Check the LCD display for real-time updates.
   - Observe the LEDs and hear the buzzer for appropriate alerts based on earthquake severity.

## How It Works

1. The MPU6050 sensor continuously provides accelerometer (X, Y, Z) data.
2. The total acceleration is calculated by averaging the accelerometer values.
3. The total acceleration is mapped to the Richter scale to determine earthquake severity.
4. Based on the severity, the following actions take place:
   - **LEDs** show different colors for varying severity levels.
   - **Buzzer** sounds for significant earthquakes (Richter scale > 4.5).
5. The severity value is displayed on the 16x2 LCD.

## Earthquake Severity Levels

- **Light Earthquake** (2.0 - 5.0): Green LEDs
- **Moderate Earthquake** (5.1 - 7.0): Yellow LEDs
- **Severe Earthquake** (7.1 and above): Red LEDs

## Future Improvements

- Implement data logging for storing earthquake data over time.
- Add support for wireless communication (e.g., Wi-Fi or Bluetooth) to send alerts to mobile devices.
- Improve filtering algorithms to reduce noise in accelerometer readings.

