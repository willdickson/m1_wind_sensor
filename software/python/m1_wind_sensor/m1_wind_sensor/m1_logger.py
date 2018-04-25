from __future__ import print_function
import os
import sys
import time
import signal
import argparse
import datetime
import matplotlib.pyplot as plt
from m1_wind_sensor import M1WindSensor


class M1Logger(object):
    
    def __init__(self,port='/dev/ttyACM0',filename='data.txt', window_size=60.0):
        self.window_size = window_size 
        self.filename = filename 
        self.wind_sensor = M1WindSensor(port)

        self.time_init = time.time()
        self.time_list = []
        self.angle_list = []
        self.speed_list = []

        plt.ion()
        self.fig = plt.figure(1)

        # Setup axis and line for angle data
        self.angle_axis = plt.subplot(211) 
        self.angle_line, = plt.plot([0,1], [0,1],'b')
        plt.grid('on')
        plt.ylabel('angle (deg)')
        self.angle_axis.set_xlim(0,self.window_size)
        self.angle_axis.set_ylim(0,360)
        title_str = 'M1 Wind Sensor'
        plt.title(title_str)
        self.angle_line.set_xdata([])
        self.angle_line.set_ydata([])

        # Setup axis and line for speed data
        self.speed_axis = plt.subplot(212) 
        self.speed_line, = plt.plot([0,1], [0,1],'b')
        plt.grid('on')
        plt.xlabel('t (sec)')
        plt.ylabel('speed (mph)')
        self.speed_axis.set_xlim(0,self.window_size)
        self.speed_axis.set_ylim(0.0,8.0)
        self.speed_line.set_xdata([])
        self.speed_line.set_ydata([])
        self.fig.canvas.flush_events()

        signal.signal(signal.SIGINT,self.sigint_handler)


    def sigint_handler(self,signum,frame):
        self.done = True


    def run(self):

        self.done = False
        self.wind_sensor.start()

        print()

        with open(self.filename,'w') as output_fid:
            while not self.done:
                # Read data from sensor
                data = self.wind_sensor.get_data()
                if data is None:
                    continue

                # Get current and elapsed time and write data to file
                time_now = time.time()
                time_elapsed = time_now - self.time_init
                output_fid.write('{0} {1} {2}\n'.format(time_now,data['angle'],data['speed']))

                # Add data to lists and remove data older then window size
                speed_mph = convert_to_mph(data['speed'])
                self.time_list.append(time_elapsed)
                self.angle_list.append(data['angle'])
                self.speed_list.append(speed_mph)
                while (self.time_list[-1] - self.time_list[0]) > self.window_size: 
                    self.time_list.pop(0)
                    self.angle_list.pop(0)
                    self.speed_list.pop(0)

                #print('time  (sec):   {0:1.2f}'.format(time_elapsed))
                #print('angle (deg):   {0:1.2f}'.format(data['angle']))
                #print('speed (mph):   {0:1.2f}'.format(speed_mph))

                display_dict = {'time': time_elapsed, 'angle': data['angle'], 'speed': speed_mph}
                sys.stdout.write(' time (s): {time:1.2f}, angle (deg): {angle:1.2f}, speed (mpg): {speed:1.2f} \r'.format(**display_dict))
                sys.stdout.flush()

                xmin = self.time_list[0]
                xmax = max(self.window_size, self.time_list[-1])

                # Update angle line
                self.angle_line.set_xdata(self.time_list)
                self.angle_line.set_ydata(self.angle_list)
                self.angle_axis.set_xlim(xmin,xmax)

                # Update speed line
                self.speed_line.set_xdata(self.time_list)
                self.speed_line.set_ydata(self.speed_list)
                self.speed_axis.set_xlim(xmin,xmax)

                self.fig.canvas.flush_events()

        print()
        print('\n* quiting')
        self.wind_sensor.stop()


# Utility
# ---------------------------------------------------------------------------------------

def m1_logger_app():

    parser = argparse.ArgumentParser()
    parser.add_argument('-p', '--port', help='met one sensor serial port', default='/dev/ttyACM0')
    parser.add_argument('-w', '--window', help='length of  display window (sec)', type=int, default=60)
    args = parser.parse_args()

    port = args.port
    window_size = args.window


    print()
    print('M1 Wind Sensor - Data Logger')
    print('---------------------------------------------------')
    print()

    print('* device port {0}'.format(port))
    print('* window size {0}'.format(window_size))
    
    log_dir = os.path.join(os.environ['HOME'], 'm1_wind_data')
    print('* log directory: {0}'.format(log_dir))
    if not os.path.exists(log_dir):
        print('* creating log directory')
        os.mkdir(log_dir)
    else:
        print('* log directory exists')

    now = time.time()
    timestamp_str = datetime.datetime.fromtimestamp(now).strftime('%Y_%m_%d_%H_%M_%S')
    log_filename = os.path.join(log_dir,'m1_wind_data_{0}.txt'.format(timestamp_str))

    logger = M1Logger(port=port,filename=log_filename,window_size=window_size)
    logger.run()



def convert_to_mph(value):
    """
    Converts value in m/s to miles per hour mph
    """
    return 2.23694*value


