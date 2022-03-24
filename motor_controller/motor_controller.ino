/**
 * @file motor_controller.ino
 * 
 * @author Joseph Telaak
 * 
 * @brief Runs the motor using a bts7960 motor controller
 * 
 * @version 0.1
 * @date 2022-02-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

// Pins
#define CTRL_L_PWM 9
#define CTRL_R_PWM 6
#define CTRL_ENABLE 8

/**
 * @brief Setup run once
 * 
 */

void setup() {
    // Debug
    Serial.begin(115200);

    // Set pinmode
    Serial.println("Setting outputs");
    pinMode(CTRL_ENABLE, OUTPUT);
    pinMode(CTRL_L_PWM, OUTPUT);
    pinMode(CTRL_R_PWM, OUTPUT);

    // Set all to low
    Serial.println("Writing all low");
    digitalWrite(CTRL_ENABLE, LOW);
    digitalWrite(CTRL_L_PWM, LOW);
    digitalWrite(CTRL_R_PWM, LOW);

    // Enable
    Serial.println("Enabling motor controller");
    digitalWrite(CTRL_ENABLE, HIGH);

}

/**
 * @brief Loop
 * 
 */

void loop() {
    // Forwards
    Serial.println("Forward half power");
    analogWrite(CTRL_R_PWM, 128);
    delay(2500);

    // Stop
    Serial.println("Stopping");
    analogWrite(CTRL_R_PWM, 0);
    delay(500);

    // Backwards
    Serial.println("Backward half power");
    analogWrite(CTRL_L_PWM, 128);
    delay(2500);

    // Stop
    Serial.println("Stopping");
    analogWrite(CTRL_L_PWM, 0);
    delay(500);
    
}