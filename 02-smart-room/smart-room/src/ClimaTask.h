#ifndef __CLIMA_TASK__
#define __CLIMA_TASK__

#include "Task.h"
#include "Light.h"
#include "TemperatureSensor.h"

typedef enum { HEATING_HALF, COOLING_HALF, HEATING_FULL, COOLING_FULL, IDLE } ClimaTaskState;

class ClimaTask : public Task {
   public:
    ClimaTask(TemperatureSensor *tempSensor, Light *cooler_half, Light *cooler_full, Light *heating_half, Light *heating_full);

    ClimaTaskState getState();
    void tick();
    int period;

   private:
    ClimaTaskState state;

    TemperatureSensor *tempSensor;
    Light *cooler_half, *cooler_full;
    Light *heater_half, *heater_full;

    void heating_half();
    void heating_full();
    void cooling_half();
    void cooling_full();
    void idle();
};

#endif