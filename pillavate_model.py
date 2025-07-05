import pandas as pd
from sklearn.ensemble import IsolationForest
import joblib

# Step 1: Create training data (healthy vitals)
data = pd.DataFrame({
    'spo2': [98, 97, 96, 99, 98, 97],
    'bpm': [72, 75, 70, 73, 74, 71]
})

# Step 2: Fit Isolation Forest model
model = IsolationForest(contamination=0.1, random_state=42)
model.fit(data)

# Step 3: Save model for deployment or testing
joblib.dump(model, 'pillavate_model.pkl')

# Step 4: Simulate prediction
sample = pd.DataFrame({'spo2': [91], 'bpm': [130]})
prediction = model.predict(sample)

print("Status:", "Anomaly Detected" if prediction[0] == -1 else "Normal")
