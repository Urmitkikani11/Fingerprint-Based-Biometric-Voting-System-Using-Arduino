#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

LiquidCrystal_I2C lcd(0x27, 16, 4);
SoftwareSerial mySerial(8, 9);  // TX = 8, RX = 9 for fingerprint sensor
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

// Button pins
#define button1 2  
#define button2 3  
#define button3 4  
#define resultButton 5  
#define enrollButton 6  
#define confirmButton 7  

// Buzzer and LED pins
#define buzzer 10      
#define yellowLED 11   
#define greenLED 12    

// Vote counts and voter tracking
int votes1 = 0, votes2 = 0, votes3 = 0;  
int voterID = 1;  
bool hasVoted[100] = {false};  

void setup() {
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  mySerial.begin(57600);
  
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  pinMode(resultButton, INPUT_PULLUP);
  pinMode(enrollButton, INPUT_PULLUP);
  pinMode(confirmButton, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);

  if (finger.verifyPassword()) {
    Serial.println("Fingerprint sensor found!");
  } else {
    Serial.println("Fingerprint sensor not detected!");
    while (1);
  }

  displayWelcomeScreen();
  displayMainMenu();
}

void loop() {
  if (digitalRead(enrollButton) == LOW) {  
    enrollFingerprint();
    delay(500);
    displayMainMenu();
  }

  if (digitalRead(confirmButton) == LOW) {  
    startVoting();
    delay(500);
  }

  if (digitalRead(resultButton) == LOW) {
    declareResult();
    delay(3000);
    displayMainMenu();
  }
}

void displayWelcomeScreen() {
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("Welcome to");
  lcd.setCursor(0, 2);
  lcd.print("Voting System");
  delay(2000);
}

void displayMainMenu() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("1. New Voter");
  lcd.setCursor(0, 1);
  lcd.print("2. Start Voting");
  lcd.setCursor(0, 3);
  lcd.print("Voters: ");
  lcd.print(voterID - 1);
}

void enrollFingerprint() {
  if (voterID > 127) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Memory Full!");
    delay(2000);
    return;
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enroll ID: ");
  lcd.print(voterID);
  lcd.setCursor(0, 1);
  lcd.print("Place Finger...");

  int p = -1;
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
  }

  finger.image2Tz(1);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Remove Finger");
  delay(2000);
  
  while (finger.getImage() != FINGERPRINT_NOFINGER) delay(100);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Place Again...");
  while (finger.getImage() != FINGERPRINT_OK);

  finger.image2Tz(2);
  
  if (finger.createModel() == FINGERPRINT_OK && finger.storeModel(voterID) == FINGERPRINT_OK) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Stored ID: ");
    lcd.print(voterID);
    voterID++;
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Enroll Failed!");
  }
  delay(2000);
}

void startVoting() {
  if (voterID == 1) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("No Voters Enrolled!");
    delay(2000);
    return;
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Place Finger");

  int voter = getFingerprintID();
  if (voter != -1) {  
    if (!hasVoted[voter - 1]) {  
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Valid Voter");
      delay(1000);
      displayVotingScreen();
      
      digitalWrite(yellowLED, HIGH);
      unsigned long voteStart = millis();
      
      while (millis() - voteStart < 10000) {
        if (digitalRead(button1) == LOW) { 
          votes1++; 
          hasVoted[voter - 1] = true;  
          voteSuccessful("Charlie");
          return; 
        }
        if (digitalRead(button2) == LOW) { 
          votes2++; 
          hasVoted[voter - 1] = true;  
          voteSuccessful("Alice");
          return; 
        }
        if (digitalRead(button3) == LOW) { 
          votes3++; 
          hasVoted[voter - 1] = true;  
          voteSuccessful("Bob");
          return; 
        }
      }
      
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Vote Cancelled");
      delay(2000);
    } else {  
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Already Voted!");
      lcd.setCursor(0, 1);
      lcd.print("ID: ");
      lcd.print(voter);
      
      for (int i = 0; i < 3; i++) {  
        digitalWrite(buzzer, HIGH);
        delay(300);
        digitalWrite(buzzer, LOW);
        delay(300);
      }
      
      delay(2000);
    }
  } else {  
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Not Valid Voter");
    delay(2000);
  }
}

void voteSuccessful(String candidate) {
  digitalWrite(yellowLED, LOW);
  digitalWrite(greenLED, HIGH);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Voted: ");
  lcd.print(candidate);
  
  digitalWrite(buzzer, HIGH);
  delay(300);
  digitalWrite(buzzer, LOW);
  
  delay(1000);
  digitalWrite(greenLED, LOW);
}

int getFingerprintID() {
  int p = finger.getImage();
  if (p != FINGERPRINT_OK) return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK) return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK) return -1;

  return finger.fingerID;
}

void displayVotingScreen() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("1. Charlie");
  lcd.setCursor(0, 1);
  lcd.print("2. Alice");
  lcd.setCursor(0, 2);
  lcd.print("3. Bob");
}

void declareResult() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Winner: ");
  String winner = (votes1 > votes2 && votes1 > votes3) ? "Charlie" :
                  (votes2 > votes1 && votes2 > votes3) ? "Alice" :
                  (votes3 > votes1 && votes3 > votes2) ? "Bob" : "Tie";
  lcd.print(winner);
  delay(3000);
}
