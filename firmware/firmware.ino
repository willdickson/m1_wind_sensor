#include "Streaming.h"
#include "pin_defs.h"
#include "constants.h"
#include "m1_wind_sensor.h"

typedef M1WindSensor<WindSpeedPin, WindDirectionPin> WindSensor; 


void setup()
{
    WindSensor::initialize();
}


void loop()
{
    WindSensor::update_on_loop();
    WindSensor::check_messages();
    WindSensor::send_data();
    delay(LoopDelayDtMS);
}

