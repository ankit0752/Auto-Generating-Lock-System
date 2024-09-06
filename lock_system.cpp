#include <SoftwareSerial.h>
#include <Servo.h>
#include <EEPROM.h>

// Pins for GSM Module (SIM800L)
SoftwareSerial gsm(7, 8); // RX, TX

// Servo motor control
Servo myServo;
int servoPin = 9; // Pin connected to Servo

// Variables
String randomPassword = "";
String userPassword = "";
int passwordLength = 6; 
String phoneNumber = "+91_______"; // Enter the user's phone number


String generatePassword() {
  String newPassword = "";
  for (int i = 0; i < passwordLength; i++) {
    newPassword += String(random(0, 10)); // Generate random number 0-9
  }
  return newPassword;
}

// Function to send SMS with password
void sendSMS(String password) {
  gsm.println("AT+CMGF=1"); // Set GSM to text mode
  delay(1000);
  gsm.println("AT+CMGS=\"" + phoneNumber + "\""); // Enter the phone number
  delay(1000);
  gsm.println("Your password is: " + password); // Send the password
  delay(1000);
  gsm.write(26); // End the SMS command
  delay(1000);
}

// Function to unlock the lock
void unlockLock() {
  myServo.write(90); // Rotate the servo to unlock position
  delay(5000); // Keep it unlocked for 5 seconds
  myServo.write(0); // Lock it back
}

// Setup function
void setup() {
  // Initialize the serial communication
  Serial.begin(9600);
  gsm.begin(9600); // Initialize GSM
  myServo.attach(servoPin); // Initialize Servo
  myServo.write(0); // Set servo to lock position

  // Generate a random password and store it
  randomPassword = generatePassword();
  EEPROM.put(0, randomPassword); // Store password in EEPROM
  sendSMS(randomPassword); // Send the password via SMS

  Serial.println("Password sent via SMS. Waiting for user input...");
}

// Function to get user input (in real implementation, this would be done via a keypad or other input method)
String getUserInput() {
  String input = "";
  while (Serial.available() == 0) {
    // Wait for user input
  }
  input = Serial.readString();
  return input;
}


void loop() {
  // Get user password input
  userPassword = getUserInput();
  Serial.println("User entered: " + userPassword);


  if (userPassword == randomPassword) {
    Serial.println("Access Granted!");
    unlockLock(); // Unlock the lock
  } else {
    Serial.println("Access Denied!");
  }

  // After access, generate a new password and send it via SMS
  randomPassword = generatePassword();
  EEPROM.put(0, randomPassword); // Store new password
  sendSMS(randomPassword); // Send the new password via SMS

  Serial.println("New password generated and sent via SMS.");
}
