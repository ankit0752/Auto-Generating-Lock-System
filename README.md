# Auto-Generating-Lock-System

To create an auto-generating lock system with Arduino, you will need the following components:
Arduino (Uno or Mega) - For processing the logic.
GSM Module (SIM800L or similar) - For sending SMS.
Keypad or Button (Optional) - For user interaction.
Servo Motor or Solenoid Lock - For controlling the lock.
LCD Display (Optional) - To display information to the user.
Power Supply - To power the system.
Resistors, Jumper Wires, and Breadboard - For making connections.
**Key Features:**
Generate a random password each time access is required.
Send the password via SMS to the user's mobile phone.
Compare user input with the generated password to unlock the lock.
Here's the complete Arduino code:

**Libraries Required:**
SoftwareSerial.h (for communication with the GSM module)
Servo.h (if using a servo motor)
EEPROM.h (optional, to store the password)
