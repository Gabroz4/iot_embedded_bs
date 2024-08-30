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
