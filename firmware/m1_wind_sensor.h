#ifndef WIND_SENSOR_H
#define WIND_SENSOR_H
#include "constants.h"
#include "m1_speed_sensor.h"
#include "m1_direction_sensor.h"
#include <Arduino.h>
#include "Streaming.h"
#include "ArduinoJson.h"

template<int TSpeedSensorPin, int TDirectionSensorPin>
class M1WindSensor
{

    public:

        static void initialize();
        static void check_messages();
        static void send_data();
        static void update_on_loop();
        static inline void update_on_timer();
        static inline void update_on_speed_sensor_pin();

    protected:

        typedef M1SpeedSensor<TSpeedSensorPin> SpeedSensor_;
        typedef M1DirectionSensor<TDirectionSensorPin> DirectionSensor_;

        static IntervalTimer intervalTimer_;
        static bool send_enabled_;
        static volatile bool send_flag_;

    private:

        M1WindSensor() {};
        ~M1WindSensor() {};
};


template<int TSpeedSensorPin, int TDirectionSensorPin>
void M1WindSensor<TSpeedSensorPin, TDirectionSensorPin>::initialize()
{
    send_enabled_ = false;
    send_flag_ = false;

    Serial.begin(Baudrate);

    analogReadResolution(AinReadResolution);
    analogReadAveraging(AinReadAveraging);

    SpeedSensor_::initialize();
    DirectionSensor_::initialize();

    intervalTimer_.begin(update_on_timer, SendTimerPeriodUS);
}


template<int TSpeedSensorPin, int TDirectionSensorPin>
void M1WindSensor<TSpeedSensorPin, TDirectionSensorPin>::check_messages()
{
    while (Serial.available() > 0)
    {
        uint8_t cmd = Serial.read();
        switch (cmd) 
        {
            case 'b':
                send_enabled_ = true;
                break;

            case 'e':
                send_enabled_ = false;
                break;
        }
    }
}


template<int TSpeedSensorPin, int TDirectionSensorPin>
void M1WindSensor<TSpeedSensorPin, TDirectionSensorPin>::send_data()
{
    if (send_flag_ && send_enabled_)
    {
        send_flag_ = false;

        float angle = DirectionSensor_::angle();
        float speed = SpeedSensor_::speed();
        
        StaticJsonBuffer<SendJsonBufferSize> json_buffer;
        JsonObject &json_msg = json_buffer.createObject();

        json_msg["time"] = millis();
        json_msg["angle"] = angle;
        json_msg["speed"] = speed;

        json_msg.printTo(Serial);
        Serial << endl;

    }
}


template<int TSpeedSensorPin, int TDirectionSensorPin>
inline void M1WindSensor<TSpeedSensorPin, TDirectionSensorPin>::update_on_loop()
{
    SpeedSensor_::update_on_loop();
}


template<int TSpeedSensorPin, int TDirectionSensorPin>
inline void M1WindSensor<TSpeedSensorPin, TDirectionSensorPin>::update_on_timer()
{
    send_flag_ = true;
}


template<int TSpeedSensorPin, int TDirectionSensorPin>
bool M1WindSensor<TSpeedSensorPin, TDirectionSensorPin>::send_enabled_ = false;


template<int TSpeedSensorPin, int TDirectionSensorPin>
volatile bool M1WindSensor<TSpeedSensorPin, TDirectionSensorPin>::send_flag_ = false;


template<int TSpeedSensorPin, int TDirectionSensorPin>
IntervalTimer M1WindSensor<TSpeedSensorPin, TDirectionSensorPin>::intervalTimer_;


#endif

