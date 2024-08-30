#ifndef __SMARTLAMP_TASK__
#define __SMARTLAMP_TASK__

#include "Task.h"
#include "Led.h"
#include "LightSensor.h"
#include "Button.h"

#define DEBOUNCE_TIME 150

typedef enum {AUTOMATIC, MANUAL} SmartLampTaskState;

class SmartLampTask : public Task {
    public:
        SmartLampTask(Light *smartLamp, LightSensor *lightSensor, SimpleButton *button);
        void tick();
        int period;
        int pressedTime = DEBOUNCE_TIME;
        bool ledState;
        
        
    private:
        Light *smartLamp;
        LightSensor *lightSensor;
        SimpleButton *button;
        SmartLampTaskState state;

        void automatic();
        void manual();
};

#endif