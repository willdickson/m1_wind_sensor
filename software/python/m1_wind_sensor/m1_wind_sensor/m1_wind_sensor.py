from __future__ import print_function
import serial
import time
import json
import threading
import Queue


class M1WindSensor(serial.Serial):

    Baudrate = 115200
    ResetSleepDt = 0.5
    MaxQueueSize = 1000


    def __init__(self,port='/dev/ttyACM0',timeout=10.0):
        param = {'baudrate': self.Baudrate, 'timeout': timeout}
        super(M1WindSensor,self).__init__(port,**param)
        time.sleep(self.ResetSleepDt)
        self.data_queue = Queue.Queue()
        self.stop_event = threading.Event()


    def start(self):
        self.stop_event.clear()
        self.write('b\n')
        worker = threading.Thread(target=self.receive_data)
        worker.daemon = True
        worker.start()


    def stop(self):
        self.write('e\n')
        self.stop_event.set()


    def receive_data(self):
        while not self.stop_event.is_set():
            line = self.readline()
            try:
                line = json.loads(line)
            except ValueError:
                continue
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


