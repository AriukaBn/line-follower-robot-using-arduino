#include <SparkFun_TB6612.h>
#include <SoftwareSerial.h>

// Bluetooth Module
SoftwareSerial mySerial(11, 12);

// Motor Driver Pins
#define AIN1 2
#define AIN2 4
#define BIN1 7
#define BIN2 8
#define PWMA 5
#define PWMB 6
#define STBY 9

// Motor Offsets
const int offsetA = -1;
const int offsetB = -1;

// Motor Objects
Motor motor1(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motor2(BIN1, BIN2, PWMB, offsetB, STBY);

void setup() {
    Serial.begin(9600);
    mySerial.begin(9600);
    
    // Ensure STBY is HIGH to enable motors
    pinMode(STBY, OUTPUT);
    digitalWrite(STBY, HIGH);
}

void loop() {
    if (mySerial.available() > 0) {
        char utga = mySerial.read();
        Serial.print("Received: ");
        Serial.println(utga);

        // Control Motors Based on Received Character
        switch (utga) {
            case 'F': moveMotors(250, 255); break; // Forward
            case 'B': moveMotors(-255, -255); break; // Backward
            case 'L': moveMotors(255, 125); break; // Turn Left
            case 'R': moveMotors(125, 255); break; // Turn Right
            case 'S': moveMotors(0, 0); break; // Stop
            case 'G': moveMotors(-55, 255); break; // Forward-Left
            case 'I': moveMotors(255, -55); break; // Forward-Right
            case 'H': moveMotors(255, -255); break; // Backward-Left
            case 'J': moveMotors(-225, 255); break; // Backward-Right
            default: Serial.println("Invalid Command"); break;
        }
    }
}

// Function to Control Motor Speeds
void moveMotors(int speed1, int speed2) {
    speed1 = constrain(speed1, -255, 255);
    speed2 = constrain(speed2, -255, 255);
    
    motor1.drive(speed1);
    motor2.drive(speed2);
}
