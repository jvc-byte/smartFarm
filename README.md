# Environmental Monitoring with C++ and Blynk

This project provides C++ code for integrating various environmental sensors, such as ultrasonic, pH, and soil moisture sensors, to monitor conditions in applications like fish ponds and agricultural soil. The data collected from these sensors is sent to the Blynk platform, enabling remote monitoring and control through a cloud-based service.

## Table of Contents

1. [Features](#features)
2. [Hardware Requirements](#hardware-requirements)
3. [Software Requirements](#software-requirements)
4. [Installation](#installation)
5. [Wiring Diagram](#wiring-diagram)
6. [Configuration](#configuration)
7. [Usage](#usage)
8. [Troubleshooting](#troubleshooting)
9. [Contributing](#contributing)
10. [License](#license)
11. [Contact](#contact)

## Features

- Real-time monitoring of environmental parameters such as pH, soil moisture, and water levels.
- Integration with the Blynk platform for remote monitoring and control.
- Easy-to-use C++ code for sensor communication and data transmission.
- Applicable to smart agriculture, fish pond management, and other environmental monitoring projects.

## Hardware Requirements

- Microcontroller (ESP8266 or ESP32)
- Ultrasonic Sensor
- pH Sensor
- Soil Moisture Sensor
- Jumper Wires
- Breadboard (optional)
- Power Supply

## Software Requirements

- [Arduino IDE](https://www.arduino.cc/en/software)
- Blynk Library - can be downloaded directly from the arduino IDE.
- Hardware Libraries - library for the microcontrollers. Also availabel in arduino IDE.

## Installation

1. **Clone this repository**:
    ```bash
    git clone https://github.com/jvc-byte/smartFarm.git
    cd smartFarm
    ```

2. **Install Arduino IDE**: 
   Download and install the [Arduino IDE](https://www.arduino.cc/en/software).

3. **Install required libraries**:
   Open the Arduino IDE and install the following libraries via the Library Manager:

   - Blynk
   - Esp8266 0r Esp32

4. Open the project in Arduino IDE depending on your application.

## Wiring Diagram

Contact this [email](mailto:jvc8463@gmail.com) for detailed explanation on any connection.

## Configuration

1. **Blynk Setup**:
   - Sign up for a Blynk account at [Blynk](https://blynk.io/).
   - Create a new project in the Blynk app.
   - Note down the Blynk Authentication Token provided.

2. **Edit the code**:
   - Open the `.ino` file corresponding to your project.
   - Replace `YourAuthToken` with your Blynk Authentication Token.
   - Update the Wi-Fi credentials:
     ```cpp
     char ssid[] = "YourNetworkName";
     char pass[] = "YourPassword";
     ```

3. **Upload the code**:
   - Connect your microcontroller to your computer.
   - Upload the code to your microcontroller via the Arduino IDE.

## Usage

1. **Power on your microcontroller**: Ensure all sensors are correctly connected and powered.
2. **Open the Blynk app**: Monitor real-time data from the sensors on your mobile device.
3. **Automate actions**: Use the Blynk app to set up automation based on sensor data (e.g., trigger alarms, control actuators).

## Troubleshooting

- **No data in Blynk app**: Double-check your Wi-Fi credentials and Blynk Authentication Token.
- **Sensor readings are incorrect**: Verify the sensor connections and calibrate if necessary.
- **Compilation errors**: Ensure all required libraries are installed in the Arduino IDE.

## Contributing

Feel free to submit issues or pull requests to improve this project. Contributions are always welcome!

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Contact

- [Email](mailto:jvc8463@gmail.com)
- [Twitter](https://x.com/jvc_byte) 
