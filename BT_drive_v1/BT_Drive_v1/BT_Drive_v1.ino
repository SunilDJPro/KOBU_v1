#include <BluetoothSerial.h> //ESP-32 Dev Module
#include <Arduino.h>
BluetoothSerial SerialBT;

// Motor Driver Pins (adjust these based on your setup)
const int ENA = 16;     // Enable pin for left motors (PWM)
const int ENB = 17;     // Enable pin for right motors (PWM)
const int IN1 = 18;     // Motor A forward
const int IN2 = 19;     // Motor A backward
const int IN3 = 21;     // Motor B forward
const int IN4 = 22;     // Motor B backward

int speedValue = 255;   // Default speed (max)

// Function to set motor speeds
void setMotorSpeed(int pwmValue) {
    analogWrite(ENA, pwmValue);
    analogWrite(ENB, pwmValue);
}

// Function to move car forward
void moveForward() {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
}

// Function to move car backward
void moveBackward() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
}

// Function to turn left
void turnLeft() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
}

// Function to turn right
void turnRight() {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
}

// Function to stop the car
void stopCar() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
}

void setup() {
    // Initialize Bluetooth
    SerialBT.begin("ESP32_RC_Car");  // Bluetooth name

    // Initialize motor driver pins
    pinMode(ENA, OUTPUT);
    pinMode(ENB, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);

    // Set initial speed
    setMotorSpeed(speedValue);
}

void loop() {
    if (SerialBT.available()) {
        char command = SerialBT.read();

        // Handle direction commands
        switch (command) {
            case 'F':  // Forward
                moveForward();
                break;
            case 'B':  // Backward
                moveBackward();
                break;
            case 'L':  // Left
                turnLeft();
                break;
            case 'R':  // Right
                turnRight();
                break;
            case 'S':  // Stop
                stopCar();
                break;
            case '0':  // Speed control (0-90) // Not yet implemented
                speedValue = (command - '0') * 25;
                setMotorSpeed(speedValue);
                break;
            case 'q':  // Max speed
                speedValue = 240;
                setMotorSpeed(speedValue);
                break;
            default:
                // Invalid command, ignore
                break;
        }
    }
}
