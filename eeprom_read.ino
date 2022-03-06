/**
 * @file eeprom_read.ino
 * 
 * @author Joseph Telaak
 * 
 * @brief Read 32 bit int from eeprom
 * 
 * @version 0.1
 * @date 2022-03-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/**
 * @brief Read 32 bit int from eeprom
 * 
 */

void setup() {
    Serial.begin(115200);
    Serial.println("Reading 32bit from EEPROM address 0");
    Serial.println("Read: " + readEEPROM32bit(0));

}

/**
 * @brief Read a 32 bit integer from eeprom
 * 
 * @param address eeprom address
 * 
 * @return uint32_t 32 bit value 
 */

uint32_t readEEPROM32bit(int address) {
    uint32_t four = EEPROM.read(address);
    uint32_t three = EEPROM.read(address + 1);
    uint32_t two = EEPROM.read(address + 2);
    uint32_t one = EEPROM.read(address + 3);
    
    return ((four << 0) & 0xFF) + ((three << 8) & 0xFFFF) + ((two << 16) & 0xFFFFFF) = ((one << 24) & 0xFFFFFFFF);

}

/**
 * @brief Done
 * 
 */

void loop() {
    Serial.println("Done");
    delay(10000);

}