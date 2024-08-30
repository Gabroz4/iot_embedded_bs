#ifndef __DOOR_TASK__
#define __DOOR_TASK__

#include "Task.h"
#include "MyServo.h"
#include "ProximitySensor.h"


typedef enum {CLOSED, CLOSING, OPENED, OPENING} DoorTaskState;

class DoorTask : public Task {
    public:
        DoorTask(Presence *presence, MyServo *servo);
        void tick();
        int period;
    private:
        Presence *presence;
        MyServo *servo;
        
        int openedTimeElapsed;

        DoorTaskState state;
        void closed();
        void opening();
        void closing();
        void opened();
};

#endif