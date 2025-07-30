 💧 Water Level Detector using Firebase and Blynk IoT

This project is an IoT-based water level monitoring system designed using **NodeMCU ESP8266**, an **ultrasonic sensor**, **Firebase Realtime Database**, and **Blynk IoT platform**. It provides real-time water level updates and sends alerts to a mobile device, helping users efficiently manage water usage in tanks or reservoirs.



 Components Used

- NodeMCU ESP8266
- Ultrasonic Sensor (HC-SR04)
- Firebase Realtime Database
- Blynk IoT App (Mobile)
- Arduino IDE
- Jumper wires, USB cable, Breadboard



 Features

- 🚰 Real-time water level detection
- ☁️ Data logging using Firebase Realtime Database
- 📱 Visual display and alerts through Blynk mobile app
- 📊 Percentage-based level indicator (Low / Medium / High)
- 💡 Can be extended to control pumps automatically


 Blynk Interface

- Gauge widget to show live water level in %
- Notifications when water level is too low or full
- Optional control button for water pump (manual override)



 Firebase Integration

- Sends water level data in real-time
- Stores values in Firebase for logging
- Easy to expand for analytics or history tracking

---

 How to Use

1. Connect the ultrasonic sensor to NodeMCU:
   - Trig → D1
   - Echo → D2
   - Vcc → 3.3V
   - GND → GND

2. Upload the code using **Arduino IDE**.
3. Add your **Firebase host**, **API key**, and **Blynk Auth Token** in the code.
4. Open the **Blynk mobile app** to view real-time water levels.
5. Monitor data on Firebase from anywhere.



