# 🚨 Emergency Call System

An **Emergency Call System (eCall)** built with **C++17** that simulates accident detection in vehicles, logs accident data, and notifies both:
- **AWS IoT Core** (V2C communication)
- **Local Flask server** (V2I/V2C simulation)

This project uses:
- **OOP with inheritance & polymorphism** (Vehicle base class, `car` and `truck` subclasses)
- **Smart pointers (`unique_ptr`)** for memory safety
- **Multithreading** to send notifications in parallel
- **nlohmann/json** for structured accident logging
- **Paho MQTT C++ client** for AWS IoT integration
- **POSIX sockets** for local server communication


---

## ⚙️ Features

- **Vehicle Simulation**
  - Users input speed, acceleration, and location.
  - Accident detection logic based on thresholds and duration.
- **Accident Logging**
  - Accident data is appended to `build/accident.json`.
- **AWS IoT Core Notification**
  - Sends accident details via MQTT over TLS.
- **Flask Server Notification**
  - Sends accident data to a local Flask REST endpoint.
- **Threaded Notifications**
  - AWS + Flask notifications are sent **simultaneously**.

---

## 🚗 Accident Detection Logic

Accident is detected if:

```cpp
(speed < speed_threshold && acceleration < accel_threshold && duration < 10)
```
---

## 🔧 Dependencies
- C++17

- CMake ≥ 3.10

- nlohmann/json

- Eclipse Paho MQTT C++

- Flask (for local server simulation)

Ubuntu install commands:

```cpp
sudo apt-get install nlohmann-json3-dev
sudo apt-get install libpaho-mqttpp3-dev
pip install flask

```
---
## 👨‍💻 Author

Developed by **Bassant Ehab**


