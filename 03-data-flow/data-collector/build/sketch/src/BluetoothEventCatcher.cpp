#line 1 "C:\\Users\\gabri\\Desktop\\Laptop-to-pc\\secondo_semestre\\iot\\03-data-flow\\data-collector\\src\\BluetoothEventCatcher.cpp"
#include "BluetoothEventCatcher.h"

#include "Arduino.h"

BluetoothEventCatcher::BluetoothEventCatcher(BluetoothMsgService* bluetoothMsgService) {
    this->bluetoothMsgService = bluetoothMsgService;
}

void BluetoothEventCatcher::tick() {
    if (bluetoothMsgService->isChannelAvailable()) {
        bluetoothMsgService->channelEvent();
    }
}
