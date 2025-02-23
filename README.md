# RFID-Based Smart Access Control System

## 🚀 Overview
Managing security and employee access in buildings is challenging due to unauthorized entry, manual attendance tracking errors, and inefficient access control systems. Our solution is an **RFID-based smart door lock system** integrated with a **MongoDB attendance tracker**, ensuring **secure, automated, and real-time** access control.

With a simple **RFID card scan**, authorized employees gain seamless entry, while unauthorized attempts are instantly blocked and logged. The system eliminates manual attendance tracking errors, enhances security, and provides real-time monitoring for efficient workforce management.

---

## 🔥 Features
- **Seamless Access** – Employees enter using RFID cards, ensuring only authorized personnel can access the premises.
- **Automated Attendance Tracking** – Every entry is logged in a **MongoDB database**, eliminating manual errors.
- **Real-Time Monitoring** – Management can track entry logs remotely via a web-based dashboard.
- **Scalability** – Easily integrates with existing access control systems and supports multiple access points.

---

## 📌 System Architecture

The project consists of:
1. **RFID Module (RC522 or similar)** – Reads RFID card data.
2. **Microcontroller (ESP32/Raspberry Pi)** – Processes data and communicates with the database.
3. **MongoDB Database** – Stores attendance logs securely.
4. **Door Lock Mechanism (Solenoid/Relay)** – Controls physical access.
5. **Web Dashboard** – Displays real-time logs and allows remote monitoring.

### 📡 Data Flow:
1. Employee scans **RFID card**.
2. **Microcontroller** verifies credentials from the database.
3. If **authorized**, the **door unlocks** and attendance is recorded.
4. If **unauthorized**, access is denied and an alert is triggered.
5. Managers can view **real-time logs** on the dashboard.

---

## 📐 PCB Schematic
![alt text](https://github.com/shivam-sensei/RFID_Door-security/blob/main/assets/inside_newest.png?raw=true)
![alt text](https://github.com/shivam-sensei/RFID_Door-security/blob/main/assets/with_nano.png?raw=true)
![alt text](https://github.com/shivam-sensei/RFID_Door-security/blob/main/assets/Screenshot%202025-02-24%20003139.png?raw=true)

---

## 🏆 Hackathon Contribution
This project is designed to **enhance security and efficiency** in access control systems, making buildings **smarter and safer**. It is ideal for offices, co-working spaces, and industrial sites.

💡 Developed by: Vangaurd Minds

🌟 **GitHub Repository**: [RFID Door Security](https://github.com/shivam-sensei/RFID_Door-security)

---

🎯 **Future Improvements**
- **Biometric Integration** – Combine with fingerprint or facial recognition for multi-factor authentication.
- **Mobile App** – Access logs and manage entry permissions via a mobile application.
- **Cloud-Based AI Analytics** – Detect suspicious access patterns using AI-driven insights.

🔒 **Secure. Automated. Reliable.**
