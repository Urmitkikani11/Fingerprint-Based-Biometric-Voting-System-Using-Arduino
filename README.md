# 🗳️ Fingerprint-Based Biometric Voting System Using Arduino

A secure and interactive voting system that uses **fingerprint authentication** for voter validation and ensures **one person, one vote**. This Arduino-based project combines biometric security with user-friendly feedback through an LCD, buzzer, and LEDs.

---

## 🔐 Features

- **Fingerprint Sensor Integration** (Adafruit Fingerprint)
- **LCD Feedback** via I2C 16x2 Display
- **One-Time Voting** using voter ID check
- **Real-Time Vote Count Tracking**
- **Buzzer Alerts** for invalid attempts or confirmations
- **LED Indicators**: Yellow (voting), Green (success)
- **Buttons for Voting** (3 candidates), Enrollment, Confirmation, and Result viewing

---

## ⚙️ Hardware Requirements

| Component               | Quantity |
|------------------------|----------|
| Arduino Uno            | 1        |
| Fingerprint Sensor     | 1        |
| I2C 16x2 LCD           | 1        |
| Push Buttons           | 6        |
| Buzzer                 | 1        |
| LEDs (Green, Yellow)   | 2        |
| Jumper Wires           | -        |
| Breadboard             | 1        |

---

## 🔧 Functional Overview

- **Enroll New Voters** using the fingerprint sensor (up to 127 IDs)
- **Authenticate Voter Identity** before voting
- **Prevent Duplicate Voting** with fingerprint and tracking
- **Vote for 1 of 3 Candidates** via dedicated buttons
- **Display Winner** with majority votes
- **Visual & Audible Feedback** for every action

---

## 🧠 Logic Flow

1. Enroll voter fingerprint (`Enroll` button)
2. Confirm to start vote (`Confirm` button)
3. Authenticate fingerprint and allow voting if valid
4. Use voting buttons to cast vote for:
   - `Charlie` (Button 1)
   - `Alice` (Button 2)
   - `Bob` (Button 3)
5. View result using `Result` button

---

## 💬 LCD Messages

- "Welcome to Voting System"
- "Stored ID: X", "Valid Voter", "Already Voted"
- "Not Valid Voter", "Vote Cancelled", "Voted: Alice", etc.

---

## 🔒 Security Features

- Fingerprint-based voter ID prevents impersonation
- Voting only allowed if user has not voted before
- Voter status tracked using an internal array
- Enforced 10-second timeout window for vote casting

---

## 📜 Result Logic

- Displays candidate with highest votes
- If tied, displays `"Winner: Tie"`

---

## 📝 Notes

- Make sure `Adafruit_Fingerprint` library is installed
- Uses `SoftwareSerial` on pins 8 (TX) and 9 (RX)
- LCD uses I2C interface on address `0x27`

---

## 📄 License

This project is open-source and developed for educational purposes. Feel free to adapt, enhance, and share.

