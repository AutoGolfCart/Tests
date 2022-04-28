/**
 * @file can_injector.ino
 * 
 * @author your name (you@domain.com)
 * 
 * @brief 
 * 
 * @version 0.1
 * 
 * @date 2022-03-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

// CAN Lib
#include <mcp2515.h>

// CAN Frames
struct can_frame can_msg_in;
struct can_frame can_msg_out;

struct can_frame test_msg;

// CAN Pins
#define CAN_CS 10
#define CAN_INT 2

// CAN
MCP2515 mcp2515(CAN_CS);
uint8_t m_can_dlc = 8;



/** @brief Arduino Setup */
void setup() {
    // Serial
    Serial.begin(115200);
    
    // CAN Setup
    mcp2515.reset();
    mcp2515.setBitrate(CAN_125KBPS);
    mcp2515.setNormalMode();

    // Attach interrupt
    attachInterrupt(digitalPinToInterrupt(CAN_INT), printMessage, FALLING);
    
    // Print header
    Serial.println("CAN Injector");
    Serial.println("Example Message: (0x000) 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00");

    // test_msg.can_dlc = 8;
    // test_msg.can_id = 4801;

    // test_msg.data[0] = 1;
    // test_msg.data[1] = 2;
    // test_msg.data[2] = 3;
    // test_msg.data[3] = 4;
    // test_msg.data[4] = 5;
    // test_msg.data[5] = 6;
    // test_msg.data[6] = 7;
    // test_msg.data[7] = 8;

    // sendCANMessage(test_msg.can_id, test_msg.data);
    

    String drive_com_msg = "(4081) 10 1 12 1 255 0 0 0";
    // Serial.println("MSG-TO-PARSE: " + drive_com_msg);

    //Serial.println("Index of \'>\': " + String(drive_com_msg.indexOf(">")));
    //Serial.println(drive_com_msg.substring(drive_com_msg.indexOf(">")+1));

    // adapterSendMessage(drive_com_msg);

}1

/** @brief Arduino Loop */
void loop() {
    //Serial.println("Enter Message: ");
    //adapterSendMessage(Serial.readString());

    //adapterSendMessage("(4081) 10 1 12 1 255 0 0 0");
    //delay(2000);

}

/** @brief Print out the received can frame*/
void printMessage() {
    // Start log
    Serial.print("CAN-RX: (" + String(can_msg_in.can_id) + ") ");

    // Print data
    for (int i = 0; i < can_msg_in.can_dlc; i++) {
        Serial.print(String(can_msg_in.data[i]) + " ");

    }

    // New Line
    Serial.println();

}

/**
 * @brief Sends a message through the CAN Adapter
 * 
 * @param drive_com_msg Message to send (8x bytes separated by spaces)
 */

void adapterSendMessage(String drive_com_msg) {
    // Get the ID indexes
    String id_msg = drive_com_msg.substring(0, drive_com_msg.indexOf(")") + 2);
    id_msg.replace("(", "");
    id_msg.replace(")", "");
    id_msg.replace(" ", "");

    // Convert ID
    const char *nptr = id_msg.c_str();
    char *endptr;
    uint32_t id = strtoul(nptr, &endptr, 10);

    // Serial.print("ID: ");
    // Serial.println(id, HEX);

    // Split the data string
    char string[128];
    drive_com_msg.substring(drive_com_msg.indexOf(")") + 2).toCharArray(string, sizeof(string));
    String data_points[8];

    char *p;
    char delimiter[] = " ";

    int i = 0;
    p = strtok(string, delimiter);

    while(p && i < 8) {
        data_points[i] = p;
        p = strtok(NULL, delimiter);
        ++i;

    }

    uint8_t data[8];

    for (i = 0; i < 8; ++i) {
        data[i] = data_points[i].toInt();
        
    }

    // Serial.print("DATA: ");

    // for (i = 0; i < 8; ++i) {
    //     Serial.print(data[i], HEX);
    //     Serial.print(", ");
        
    // }

    // Serial.println();

    // Send message
    sendCANMessage(id, data);

}

/**
 * @brief Send a message of the can bus
 * 
 * @param id ID of the CAN device to send message to
 * @param m_data Data to send to the CAN device
 */

void sendCANMessage(uint32_t id, uint8_t m_data[8]) {
    // Assign ID
    can_msg_out.can_id = id;

    // Assign dlc
    can_msg_out.can_dlc = m_can_dlc;

    // Map data
    for (int i = 0; i < m_can_dlc; i++) {
        can_msg_out.data[i] = m_data[i];

    }

    // Start log
    Serial.print("CAN-TX: (");
    Serial.print(can_msg_out.can_id, HEX);
    Serial.println(") ");

    // Print data
    for (int i = 0; i < can_msg_out.can_dlc; i++) {
        Serial.print(can_msg_out.data[i], HEX);
        Serial.print(" ");

    }

    // New Line
    Serial.println();

    // Send message
    mcp2515.sendMessage(&can_msg_out);

}
