# Smart Garbage System Project

This project is a smart garbage system developed using an ESP32. The system is designed to monitor and manage garbage bin levels efficiently. It features real-time monitoring, automated bin opening, and status updates on a Blynk dashboard.

## Team Members
- Mohamed Mostafa
- Ahmed Wesam
- Dina Khaled
- Manar Ashraf
- Youssef Essam

## Project Features
1. **LED Indicators:**
   - **Red LED:** Lights up when the garbage bin is full.
   - **Green LED:** Lights up when the garbage bin is empty.
   
2. **Ultrasonic Sensor:**
   - The bin opens automatically when the distance measured by the ultrasonic sensor is short, indicating that an object is close to the bin.

3. **Blynk Dashboard Integration:**
   - The system's status and sensor data are uploaded in real-time to a Blynk dashboard for remote monitoring.

## Hardware Components
- ESP32
- Ultrasonic Sensor
- Red and Green LEDs
- Servo Motor
- Blynk-compatible board

## How It Works
- When the garbage bin is empty, the green LED lights up.
- As garbage fills the bin, the ultrasonic sensor monitors the level.
- When the bin is full, the red LED lights up.
- The bin automatically opens when an object is detected near it (i.e., when the ultrasonic sensor measures a short distance).
- All data is sent to a Blynk dashboard for remote monitoring.

## Installation and Setup
1. **Hardware Setup:**
   - Connect the ultrasonic sensor, LEDs, and servo motor to the ESP32 as per your circuit design.

2. **Blynk Setup:**
   - Set up a Blynk project and obtain an authentication token.
   - Configure the ESP32 to connect to your Wi-Fi and link it to the Blynk project using the token.

3. **Upload Code:**
   - Upload the provided code to the ESP32 using the Arduino IDE or any other compatible platform.
   - Monitor the serial output for debugging information.

4. **Run the System:**
   - Power up the ESP32 and watch the system in action. The LEDs will indicate the bin status, and the Blynk dashboard will display real-time data.

## Future Improvements
- Add more bins and integrate them into a single dashboard.
- Implement a notification system to alert when the bin is full.
- Explore additional sensors for more accurate garbage level monitoring.

