#line 1 "C:\\Users\\gabri\\Desktop\\Laptop-to-pc\\secondo_semestre\\iot\\03-data-flow\\data-collector\\src\\Task.h"
#ifndef __TASK__
#define __TASK__

#include <Arduino.h>

class Task {
    int timeElapsed;

   protected:
    int taskPeriod;

   public:
    virtual void init(int period) {
        taskPeriod = period;
        timeElapsed = 0;
    }

    virtual void tick() = 0;

    bool updateAndCheckTime(int basePeriod) {
        timeElapsed += basePeriod;
        if (timeElapsed >= taskPeriod) {
            timeElapsed = 0;
            return true;
        } else {
            return false;
        }
    }
};

#endif
