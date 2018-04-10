from __future__ import print_function
import serial
import time
import json
import threading
import Queue


class WindSensor(serial.Serial):

    Baudrate = 115200
    ResetSleepDt = 0.5
    MaxQueueSize = 1000


    def __init__(self,port='/dev/ttyACM0',timeout=10.0):
        param = {'baudrate': self.Baudrate, 'timeout': timeout}
        super(WindSensor,self).__init__(port,**param)
        time.sleep(self.ResetSleepDt)
        self.data_queue = Queue.Queue()
        self.stop_event = threading.Event()


    def start(self):
        self.stop_event.clear()
        worker = threading.Thread(target=self.receive_data)
        worker.daemon = True
        worker.start()


    def stop(self):
        self.stop_event.set()


    def receive_data(self):
        while not self.stop_event.is_set():
            line = self.readline()
            line = json.loads(line)
            self.data_queue.put(line)
            while self.data_queue.qsize() > self.MaxQueueSize:
                try:
                    self.get_nowait()
                except Queue.Empty:
                    pass
        self.stop_event.clear()


    def get_data(self):
        try:
            data = self.data_queue.get_nowait()
        except Queue.Empty:
            data = None
        return data


# ---------------------------------------------------------------------------------------
if __name__ == '__main__':

    # Testing -- move to examples

    import matplotlib.pyplot as plt
    import sys

    duration = 15.0

    wind_sensor = WindSensor()
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









