# 🗳️ Fingerprint-Based Biometric Voting System Using Arduino

A secure and interactive voting system that uses **fingerprint authentication** to validate voters and ensure **one person, one vote**. Built with Arduino, this system integrates biometric security with user-friendly features like an LCD interface, buzzer, and LED indicators.

[![License: MIT](https://img.shields.io/badge/License-MIT-red.svg)](LICENSE)

---

## 🔐 Features

-  **Fingerprint Sensor Integration** (Adafruit Fingerprint)
-  **LCD Feedback** via I2C 16x2 Display
-  **One-Time Voting** using voter ID check
-  **Real-Time Vote Count Tracking**
-  **Buzzer Alerts** for invalid or confirmed attempts
-  **LED Indicators**: Yellow (voting in progress), Green (successful vote)
-  **Voting Buttons** for 3 candidates + controls for enrollment, confirmation, and result viewing

---

## ⚙️ Hardware Requirements

| Component               | Quantity |
|------------------------|----------|
| Arduino Uno            | 1        |
| Fingerprint Sensor     | 1        |
| I2C 16x2 LCD Display   | 1        |
| Push Buttons           | 6        |
| Buzzer                 | 1        |
| LEDs (Green, Yellow)   | 2        |
| Jumper Wires           | –        |
| Breadboard             | 1        |

---

## 🔧 Functional Overview

-  **Enroll New Voters** using the fingerprint sensor (supports up to 127 users)
-  **Authenticate Voter Identity** before allowing vote
-  **Prevent Duplicate Voting** using fingerprint + internal tracking
-  **Vote for 1 of 3 Candidates** via dedicated buttons:
  - Button 1 → Charlie
  - Button 2 → Alice
  - Button 3 → Bob
-  **Display Winner** after all voting
-  **Visual & Audible Feedback** for every action

---

## 🧠 Logic Flow

1. Press `Enroll` to register a fingerprint.
2. Press `Confirm` to initiate vote.
3. Authenticate fingerprint — vote allowed only once per voter.
4. Cast vote via one of the 3 candidate buttons.
5. Press `Result` to view the current winner.

---

## 💬 LCD Messages

- "Welcome to Voting System"
- "Stored ID: X", "Valid Voter", "Already Voted"
- "Not Valid Voter", "Vote Cancelled", "Voted: Alice", etc.

---

## 🔒 Security Features

-  Fingerprint-based voter ID to prevent impersonation
-  Duplicate vote detection
-  Voter status stored in internal array
-  10-second timeout window for casting vote

---

## 📜 Result Logic

-  Displays candidate with the highest vote count
-  In case of tie, shows: `"Winner: Tie"`

---

## 📁 Project Files

- 📄 [ Report PDF](./Report/22BEC137_ASSIGNMENT_ES.pdf)
- 💾 [ Arduino Code](./CODE/Arduino_Code.ino)

---

## 📩 Contact

For questions or collaboration: [📧 Urmitkikani1184@gmail.com](mailto:Urmitkikani1184@gmail.com)

---

## 📄 License

This project is licensed under the [MIT License](LICENSE) – free to use, modify, and distribute for educational purposes.
