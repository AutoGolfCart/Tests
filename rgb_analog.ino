/**
 * @file rgb_analog.ino
 * @author joseph telaak
 * 
 * @brief This program tests controlling an rgb light using the arduino analog pins
 * 
 * @version 0.1
 * @date 2022-02-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

// Pin definitions
#define RED_PIN A0
#define GREEN_PIN A1
#define BLUE_PIN A2

/**
 * @brief Setup function
 */

void setup() {
    // Set pins to output
    pinMode(RED_PIN, OUTPUT);
    pinMode(GREEN_PIN, OUTPUT);
    pinMode(BLUE_PIN, OUTPUT);

    // Set serial debug
    Serial.begin(9600);

}

/**
 * @brief Continuously executed code
 * 
 */

void loop() {
    digital_test();
    analog_test();

}

/**
 * @brief Pure digital test. Sets each pin to high and then low
 * 
 */

void digital_test() {
    // Purely digital running (6 colors)
    Serial.write("Running through pure digital tests");

    // Red pin
    Serial.write("Setting red pin high");
    digitalWrite(RED_PIN, HIGH);
    delay(1000);
    digitalWrite(RED_PIN, LOW);
    Serial.write("Setting red pin low");

    // Blue pin
    Serial.write("Setting green pin high");
    digitalWrite(GREEN_PIN, HIGH);
    delay(1000);
    digitalWrite(GREEN_PIN, LOW);
    Serial.write("Setting green pin low");

    // Green ping
    Serial.write("Setting blue pin high");
    digitalWrite(BLUE_PIN, HIGH);
    delay(100);
    digitalWrite(BLUEPIN, LOW);
    Serial.write("Setting blue pin low");

    // Done
    Serial.write("Pure digital test complete");

}

/**
 * @brief Analog test. Tests different duty cycle values
 * 
 */

void analog_test() {
    // Purely digital running (6 colors)
    Serial.write("Running through analog tests");

    for (int i = 2; i < 255; i = i * 2) {
        Serial.write("Running blue pin at " + i);
        analogWrite(BLUE_PIN, i);

    }

    // Reset
    digitalWrite(BLUE_PIN, LOW);

    // Done
    Serial.write("Done analog tests");
    
}