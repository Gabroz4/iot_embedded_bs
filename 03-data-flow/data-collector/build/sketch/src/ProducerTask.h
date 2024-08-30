#line 1 "C:\\Users\\gabri\\Desktop\\Laptop-to-pc\\secondo_semestre\\iot\\03-data-flow\\data-collector\\src\\ProducerTask.h"
#ifndef __PRODUCER_TASK__
#define __PRODUCER_TASK__

#include "MsgService.h"
#include "ProximitySensor.h"
#include "Task.h"

class ProducerTask : public Task {
   private:
    MsgService* msgService;
    ProximitySensor *sensor;

   public:
    ProducerTask(MsgService* msgService, ProximitySensor *sensor);
    void tick();
};

#endif
