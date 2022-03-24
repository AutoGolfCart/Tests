#include <mcp2515.h>

// Pins
#define CTRL_L_PWM 9
#define CTRL_R_PWM 6
#define CTRL_ENABLE 8

struct can_frame canMsg;
MCP2515 mcp2515(10);


void setup() {
  Serial.begin(115200);
  
  mcp2515.reset();
  mcp2515.setBitrate(CAN_125KBPS);
  mcp2515.setNormalMode();
  
  // Set pinmode
  pinMode(CTRL_ENABLE, OUTPUT);
  pinMode(CTRL_L_PWM, OUTPUT);
  pinMode(CTRL_R_PWM, OUTPUT);

  // Set all to low
  digitalWrite(CTRL_ENABLE, LOW);
  digitalWrite(CTRL_L_PWM, LOW);
  digitalWrite(CTRL_R_PWM, LOW);

  // Enable
  digitalWrite(CTRL_ENABLE, HIGH);
}

void loop() {
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {
    Serial.print(canMsg.can_id, HEX); // print ID
    Serial.print(" "); 
    Serial.print(canMsg.can_dlc, HEX); // print DLC
    Serial.print(" ");
    
    for (int i = 0; i<canMsg.can_dlc; i++)  {  // print the data
      Serial.print(canMsg.data[i],HEX);
      Serial.print(" ");
    }

    Serial.println();
    
    int duty_cycle = (canMsg.data[6] << 8) | canMsg.data[7];
    
    if (duty_cycle < 0) { duty_cycle = duty_cycle * -1; }
    if (duty_cycle > 255) { duty_cycle = 255; }
    
    Serial.println("Duty Cycle: " + String(duty_cycle));

    if (canMsg.data[0] == 0x01) {
      Serial.println("FWD");
      analogWrite(CTRL_R_PWM, 0);
      analogWrite(CTRL_L_PWM, duty_cycle);
      
    } else if (canMsg.data[0] == 0x02) {
      Serial.println("REV");
      analogWrite(CTRL_L_PWM, 0);
      analogWrite(CTRL_R_PWM, duty_cycle);
      
    }
    
  }
}
