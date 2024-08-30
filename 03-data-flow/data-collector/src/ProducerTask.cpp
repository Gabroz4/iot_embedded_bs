#include "ProducerTask.h"
#include "ProximitySensor.h"
#include <ArduinoJson.h>

ProducerTask::ProducerTask(MsgService* msgService, ProximitySensor *sensor) {
    this->msgService = msgService;
    this->sensor = sensor;
}

void ProducerTask::tick() {
    if (msgService->isConnected()) {
        unsigned long data = millis();

        // Create a JSON document
        StaticJsonDocument<256> doc;

        // Add the message to the JSON document
        doc["type"] = "distance";
        doc["value"] = sensor->getDistance();

        // Serialize the JSON document to a string
        String jsonMsg;
        serializeJson(doc, jsonMsg);

        // Send the JSON string
        this->msgService->sendMsg(String(jsonMsg));
    }
}