
/* TAZROUT IoT Irrigation System - ESP32 Module
  Day 1: LED Blink - Environment Setup

  Developer: KHENFRI Moussa
  Date: February 1, 2026
  Week: 1 - ESP32 Fundamentals

  Learning Objectives:
  - Understand ESP32 GPIO control
  - Master digital output operations
  - Verify Wokwi simulation environment

  Hardware:
  - ESP32 DevKit v1
  - LED connected to GPIO 2
  - 220 ohm resistor
*/

const int LED_PIN = 2 ;

const int BLINK_INTERVAL = 1000;

void setup()
{
  pinMode(LED_PIN, OUTPUT);

  Serial.begin(115200);
  Serial.println("=================================");
  Serial.println("TAZROUT - Day 1: LED Blink Test");
  Serial.println("=================================");
  Serial.println("LED Pin: GPIO 2");
  Serial.println("Frequency: 1Hz (500ms ON, 500ms OFF)");
  Serial.println("=================================");
}
void loop() {
  // Turn LED ON
  digitalWrite(LED_PIN, HIGH);
  Serial.println("LED: ON");
  delay(BLINK_INTERVAL);

  // Turn LED OFF
  digitalWrite(LED_PIN, LOW);
  Serial.println("LED: OFF");
  delay(BLINK_INTERVAL);
}

