#include <mcp4xxx.h>

using namespace icecave::arduino;

MCP4XXX* digi_pot;

#define SPEED_CTRL_CS 9

void setup() {

    Serial.begin(115200);

    digi_pot = new MCP4XXX(SPEED_CTRL_CS);
    
    for (int i = 0; i < 260; i++) {
        digi_pot->increment();
        
    }
}

void loop() {

    digi_pot -> decrement();

    delay(200);

}