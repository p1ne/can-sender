#include <Arduino.h>

#include <SPI.h>

#include <mcp_can.h>
#include <mcp_can_dfs.h>
#include "CANMessage.h"

CANMessage msg;

const int SPI_CS_PIN = 10;

MCP_CAN CAN(SPI_CS_PIN); 

void printHex(int num, int precision) {
     char tmp[16];
     char format[128];

     sprintf(format, "0x%%.%dX", precision);

     sprintf(tmp, format, num);
     Serial.print(tmp);
}

void setup()
{    
  msg.set( 0, 0, 0, 0x50f, 8, 0x01, 0x02, 0x03, 0x03, 0x04, 0x05, 0x06, 0x07 );

  Serial.begin(115200);
START_INIT:
  if(CAN_OK == CAN.begin(CAN_125KBPS, MCP_8MHz)) {
    Serial.println("CAN BUS Shield init ok!");
  } else {
    Serial.println("CAN BUS Shield init fail");
    Serial.println("Init CAN BUS Shield again");
    delay(100);
    goto START_INIT;
  }
  
}
void loop()
{

      CAN.sendMsgBuf(msg.header, 0, msg.len, msg.data);
      msg.print();
      delay(100);
}
