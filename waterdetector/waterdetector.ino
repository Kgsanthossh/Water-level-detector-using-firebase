#include <Arduino.h>
#include "Firebase_ESP_Client.h"
#if defined(ESP32)
  #include <WiFi.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
#endif

#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

#define WIFI_SSID "iQOO Z7 5G"
#define WIFI_PASSWORD "santhossh23"

#define API_KEY "AIzaSyAPoftP_Qjk9OfAfzXX34-KNlK0z4SN6Yo"
#define DATABASE_URL "waterleveldetector-1d181-default-rtdb.firebaseio.com/"  

#define TRIG_PIN D1  
#define ECHO_PIN D2  


int tankHeight = 100;


FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

bool signupOK = false;

void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());

  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;
  config.token_status_callback = tokenStatusCallback;

  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("Firebase SignUp OK");
    signupOK = true;
  } else {
    Serial.printf("SignUp FAILED: %s\n", config.signer.signupError.message.c_str());
  }

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop() {
  delay(3000);  

  
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  int distance = duration * 0.034 / 2;
  int waterLevel = tankHeight - distance;
  if (waterLevel < 0) waterLevel = 0;

  Serial.print("Water Level (cm): ");
  Serial.println(waterLevel);

  String status = "NORMAL";
  if (waterLevel < 20) status = "LOW";
  else if (waterLevel > 90) status = "HIGH";

  if (Firebase.ready() && signupOK) {
    Firebase.RTDB.setInt(&fbdo, "Tank/Level", waterLevel);
    Firebase.RTDB.setString(&fbdo, "Tank/Status", status);
    Serial.println("Data sent to Firebase");
  } else {
    Serial.println("Firebase not ready or signup failed");
  }

  Serial.println("--------------------------");
}
