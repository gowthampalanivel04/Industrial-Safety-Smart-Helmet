#include <Arduino.h>
#include <BlynkSimpleEsp32.h>
#include "config.h"
#include "alert.h"

bool alertSent = false;

void checkAlerts(float temp, int spo2, bool gas, bool noise, float ax) {

    bool abnormal = false;
    String alertMsg = "";

    if (temp > 38) {
        abnormal = true;
        alertMsg += "High Temp | ";
    }

    if (spo2 < 90 && spo2 > 20) {
        abnormal = true;
        alertMsg += "Low SpO2 | ";
    }

    if (gas) {
        abnormal = true;
        alertMsg += "Gas Detected | ";
    }

    if (noise) {
        abnormal = true;
        alertMsg += "High Noise | ";
    }

    if (abs(ax) > 0.75) {
        abnormal = true;
        alertMsg += "Possible Fall | ";
    }

    // Buzzer control
    digitalWrite(BUZZER, abnormal ? HIGH : LOW);

    // Send alert only once
    if (abnormal && !alertSent) {
        Blynk.logEvent("alert", alertMsg);
        alertSent = true;
    }

    if (!abnormal) {
        alertSent = false;
    }
}
