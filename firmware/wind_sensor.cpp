#include "wind_sensor.h"
#include "pin_defs.h"
#include "constants.h"
#include "Streaming.h"


WindSensor::WindSensor()
{ 
    send_flag_ = false;
}


void WindSensor::initialize(void(*interval_timer_cb)(), void(*speed_sensor_pin_cb)())
{ 
    Serial.begin(Baudrate);

    analogReadResolution(AinReadResolution);
    analogReadAveraging(AinReadAveraging);

    speed_sensor_.initialize(WindSpeedPin, speed_sensor_pin_cb);
    direction_sensor_.initialize(WindDirectionPin);

    interval_timer_cb_= interval_timer_cb;
    interval_timer_.begin(interval_timer_cb_, SendTimerPeriodUS);
}


void WindSensor::update_on_loop()
{
    speed_sensor_.update_on_loop();
}


void WindSensor::send_data()
{
    if (send_flag_)
    {
        send_flag_ = false;
        float angle = direction_sensor_.angle();
        float speed = speed_sensor_.speed();
        Serial << "[" << _FLOAT(angle,AngleSendDigits) << ", " << _FLOAT(speed,SpeedSendDigits) << "]" <<  endl;
    }
}


