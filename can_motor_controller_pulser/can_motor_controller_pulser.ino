#include <SPI.h>
#include <mcp2515.h>

struct can_frame canMsg1;
struct can_frame canMsg2;
MCP2515 mcp2515(10);


void setup() {
  canMsg1.can_id  = 0x000;
  canMsg1.can_dlc = 8;
  canMsg1.data[0] = 0x01;
  canMsg1.data[1] = 0x00;
  canMsg1.data[2] = 0x00;
  canMsg1.data[3] = 0x00;
  canMsg1.data[4] = 0x00;
  canMsg1.data[5] = 0x00;
  canMsg1.data[6] = 0xff;
  canMsg1.data[7] = 0x00;

  canMsg2.can_id  = 0x00;
  canMsg2.can_dlc = 8;
  canMsg2.data[0] = 0x01;
  canMsg2.data[1] = 0x00;
  canMsg2.data[2] = 0x00;
  canMsg2.data[3] = 0x00;
  canMsg2.data[4] = 0x00;
  canMsg2.data[5] = 0x00;
  canMsg2.data[6] = 0x00;
  canMsg2.data[7] = 0x00;
  
  Serial.begin(115200);
  
  mcp2515.reset();
  mcp2515.setBitrate(CAN_125KBPS);
  mcp2515.setNormalMode();
  
}

void loop() {
  mcp2515.sendMessage(&canMsg1);

  delay(2000);
  
  mcp2515.sendMessage(&canMsg2);
  
  delay(2000);
  
}
