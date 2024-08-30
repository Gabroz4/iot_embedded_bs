#line 1 "C:\\Users\\gabri\\Desktop\\Laptop-to-pc\\secondo_semestre\\iot\\03-data-flow\\data-collector\\src\\SerialMsgService.h"
#ifndef __SERIAL_MSG_SERVICE__
#define __SERIAL_MSG_SERVICE__

#include "Arduino.h"
#include "MsgService.h"

/**
 * MsgService that use the Arduino Serial.
 */
class SerialMsgService : public MsgService {
   protected:
    char read();

   public:
    void sendMsg(String msg);
    void sendMsg(float msg);
    void sendMsg(int msg);
    SerialMsgService(String name, unsigned long baudRate);
    bool isChannelAvailable();
    bool isConnected();
};
#endif
