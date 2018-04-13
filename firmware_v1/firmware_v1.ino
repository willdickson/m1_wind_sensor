#include "Streaming.h"
#include "constants.h"
#include "wind_sensor.h"


WindSensor wind_sensor; 


void setup()
{
    wind_sensor.initialize(on_interval_timer, on_speed_sensor_pin);
}


void loop()
{
    wind_sensor.update_on_loop();
    wind_sensor.send_data();
    delay(LoopDelayDtMS);
}


void on_interval_timer()
{
    wind_sensor.update_on_timer();
}


void on_speed_sensor_pin()
{
    wind_sensor.update_on_speed_sensor_pin();
}
