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

}

/** @brief Print out the received can frame*/
void printMessage() {
  // Start message
  Serial.print("CAN-RX: (");
  Serial.print(can_msg_out.can_id, HEX);
  Serial.print(") ");

  // Print data
  for (int i = 0; i < can_msg_in.dlc; i++) {
    Serial.print(can_msg_out.data[i], HEX);
    Serial.print(" ");

  }

  // End Line
  Serial.println();

}

/** @brief Arduino Loop */
void loop() {
  Serial.println("Enter Message: ");
  adapterSendMessage(Serial.readString());
  
}

/**
 * @brief Sends a message through the CAN Adapter
 * 
 * @param drive_com_msg Message to send (8x bytes separated by spaces)
 */

void adapterSendMessage(String drive_com_msg) {
    // Get the ID indexes
    int id_begin_index = drive_com_msg.indexOf("(");
    int id_end_index = drive_com_msg.indexOf(")");

    // Check ID
    if (id_begin_index == -1 || id_end_index == -1) {
        Serial.println("Err: CAN message is missing ID");
        return;

    }

    // Get the ID
    String str_id = drive_com_msg.substring(id_begin_index, id_end_index - 1);
    byte id_buf[4];
    str_id.toCharArray(id_buf, sizeof(id_buf));
    uint32_t set_id = id_buf[0] | (id_buf[1] << 8) | (id_buf[2] << 16) | (id_buf[3] << 24);

    // Clear ID
    drive_com_msg.replace(drive_com_msg.substring(0, id_end_index + 1), "");

    // Clear Spaces
    drive_com_msg.replace(" ", "");

    // Get data
    uint8_t data_buf[8];
    drive_com_msg.toCharArray(data_buf, sizeof(data_buf));

    // Send message
    sendCANMessage(set_id, data_buf);

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
    Serial.print(") ");

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
