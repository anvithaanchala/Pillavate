# Pillavate: Smart Self-Adjusting Pillow for CHF Patients

Pillavate is an embedded system that detects signs of breathing distress in Congestive Heart Failure (CHF) patients and automatically adjusts pillow elevation. It uses real-time heart rate and oxygen saturation data to respond intelligently and safely.

## 🔧 Features

- Real-time vitals monitoring with MAX30100 (SpO₂ + BPM)
- Linear actuator to adjust pillow height
- Intelligent thresholding with optional ML-based anomaly detection
- C++ firmware for Arduino
- Lightweight Python ML model using Isolation Forest

## 🧠 Technologies Used

- Arduino (C++), Pulse Oximeter Library
- Python (scikit-learn, pandas)
- Isolation Forest for anomaly detection
- MAX30100 Sensor, Linear Actuator

## 🚀 Getting Started

### Hardware Required

- Arduino Uno/Nano
- MAX30100 Pulse Oximeter sensor
- Linear Actuator with relay/motor driver
- Breadboard, jumpers, power supply

### Software Setup

1. Open `pillavate.ino` in Arduino IDE.
2. Install libraries:
   - `MAX30100_PulseOximeter`
3. Upload code and connect hardware.
4. Optionally run `pillavate_model.py` to train/test the ML model.

### Python Model (Optional)

```bash
pip install pandas scikit-learn joblib
python pillavate_model.py
```

---

## 📈 Example Output

```
BPM: 78 SPO2: 97
State: NORMAL

BPM: 130 SPO2: 89
State: CRITICAL → Pillow Raised
```

---

## 👩‍🔬 Maintainer

**Anvitha Anchala**  
[LinkedIn](https://linkedin.com/in/anvitha-anchala) | [GitHub](https://github.com/anvithaanchala)
