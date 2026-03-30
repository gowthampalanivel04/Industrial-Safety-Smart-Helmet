## Firmware Description

This project is implemented using ESP32 and integrates multiple sensors to monitor worker safety in real-time.

### Sensors & Modules Used
- DHT11 → Temperature & Humidity monitoring
- MQ Gas Sensor → Gas leakage detection
- Sound Sensor → Noise level detection
- MPU6050 → Motion / fall detection using accelerometer
- MAX30105 → SpO2 (oxygen level) monitoring
- GPS Module → Location tracking
- Buzzer → Alert system
- Blynk IoT → Remote monitoring & alerts

### Working Principle
- The ESP32 continuously reads data from all sensors
- Sensor data is processed to detect abnormal conditions:
  - High temperature (>38°C)
  - Low SpO2 (<90%)
  - Gas detection
  - High noise levels
  - Sudden movement (fall detection using MPU6050)
- If any abnormal condition is detected:
  - Buzzer is activated
  - Alert is sent via Blynk IoT platform
- GPS coordinates are tracked and can be sent to the cloud

### Communication
- WiFi (ESP32) is used to connect to Blynk Cloud
- Virtual pins:
  - V0 → Health data
  - V1 → Environmental data
  - V2 → GPS data

### Key Features in Code
- Multi-sensor integration using I2C and GPIO
- Real-time data monitoring
- Event-based alert system
- IoT cloud communication (Blynk)
- Fall detection using accelerometer threshold
## Project Structure

smart-helmet/
├── src/        # Source code (main .ino / .c files)
├── include/    # Header files
├── docs/       # Documentation (report, diagrams)
├── images/     # Project images (circuit, setup)
├── README.md
