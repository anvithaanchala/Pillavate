#include <Wire.h>
#include "MAX30100_PulseOximeter.h"

#define REPORTING_PERIOD_MS 1000
#define ACTUATOR_PIN 9
#define ACTUATION_DURATION 8000  // 8 seconds

PulseOximeter pox;
uint32_t tsLastReport = 0;
unsigned long lastActuationTime = 0;
bool actuatorExtended = false;

enum State { RESTING, ELEVATING, CHECKING };

State systemState = RESTING;

void setup() {
  Serial.begin(9600);
  pinMode(ACTUATOR_PIN, OUTPUT);

  if (!pox.begin()) {
    Serial.println("FAILED to initialize pulse oximeter");
    while (1);
  } else {
    Serial.println("Pulse oximeter initialized");
  }

  pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
}

void elevatePillow() {
  digitalWrite(ACTUATOR_PIN, HIGH);
  actuatorExtended = true;
  lastActuationTime = millis();
  Serial.println("Pillow elevating...");
}

void lowerPillow() {
  digitalWrite(ACTUATOR_PIN, LOW);
  actuatorExtended = false;
  Serial.println("Pillow lowering...");
}

void loop() {
  pox.update();

  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
    float bpm = pox.getHeartRate();
    float spo2 = pox.getSpO2();

    Serial.print("BPM: "); Serial.print(bpm);
    Serial.print(" SPO2: "); Serial.println(spo2);

    // Decision logic based on reported criteria
    if ((bpm >= 70 && bpm <= 100) || (spo2 < 93)) {
      if (!actuatorExtended && systemState == RESTING) {
        elevatePillow();
        systemState = ELEVATING;
      }
    }

    if (actuatorExtended && (millis() - lastActuationTime > ACTUATION_DURATION)) {
      // Check again to see if parameters are back in range
      float recheck_bpm = pox.getHeartRate();
      float recheck_spo2 = pox.getSpO2();

      if ((recheck_bpm < 70) && (recheck_spo2 >= 93)) {
        lowerPillow();
        systemState = RESTING;
      } else {
        elevatePillow();  // Extend again if distress persists
        systemState = ELEVATING;
      }
    }

    tsLastReport = millis();
  }
}
