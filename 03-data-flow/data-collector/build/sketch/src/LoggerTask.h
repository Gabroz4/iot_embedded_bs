#line 1 "C:\\Users\\gabri\\Desktop\\Laptop-to-pc\\secondo_semestre\\iot\\03-data-flow\\data-collector\\src\\LoggerTask.h"
#ifndef __LOGGER_TASK__
#define __LOGGER_TASK__

#include "MsgService.h"
#include "Task.h"

class LoggerTask : public Task {
   private:
    MsgService* inputChannel;
    MsgService* outputChannel;

   public:
    LoggerTask(MsgService* inputChannel, MsgService* outputChannel);
    void tick();
};

#endif
