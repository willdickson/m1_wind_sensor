import time
import sys
import matplotlib.pyplot as plt
from m1_wind_sensor import M1WindSensor

duration = 15.0
wind_sensor = M1WindSensor()
wind_sensor.start()

t0 = time.time()

time_list, angle_list, speed_list = [], [], []

while True:

    data = wind_sensor.get_data()
    if data is not None:
        time_list.append(data['time']*1.0e-3)
        angle_list.append(data['angle'])
        speed_list.append(data['speed'])
        print(data)

    if time.time() - t0 > duration:
        wind_sensor.stop()
        break;

plt.figure(1)
ax0 = plt.subplot(2,1,1)
plt.plot(time_list, angle_list,'.')
plt.ylabel('angle (deg)')
plt.grid('on')
plt.title('Met One Wind Sensor')

plt.subplot(2,1,2,sharex=ax0)
plt.plot(time_list, speed_list,'.')
plt.ylabel('speed (m/s)')
plt.grid('on')

plt.show()
