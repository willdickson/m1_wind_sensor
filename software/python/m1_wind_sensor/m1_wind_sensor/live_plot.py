import time
import signal
import matplotlib.pyplot as plt
from wind_sensor import WindSensor



class WindSensorLivePlot(object):
    
    def __init__(self,port='/dev/ttyACM0',filename='data.txt'):
        self.window_size = 60.0
        self.filename = filename 
        self.wind_sensor = WindSensor(port)

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
        plt.xlabel('t (sec)')
        plt.ylabel('angle (deg)')
        self.angle_axis.set_xlim(0,self.window_size)
        self.angle_axis.set_ylim(0,360)
        plt.title("Met One Wind Sensor ")
        self.angle_line.set_xdata([])
        self.angle_line.set_ydata([])

        # Setup axis and line for speed data
        self.speed_axis = plt.subplot(212) 
        self.speed_line, = plt.plot([0,1], [0,1],'b')
        plt.grid('on')
        plt.xlabel('t (sec)')
        plt.ylabel('speed (m/s)')
        self.speed_axis.set_xlim(0,self.window_size)
        self.speed_axis.set_ylim(0.0,4.0)
        self.speed_line.set_xdata([])
        self.speed_line.set_ydata([])
        self.fig.canvas.flush_events()

        signal.signal(signal.SIGINT,self.sigint_handler)


    def sigint_handler(self,signum,frame):
        self.done = True


    def run(self):

        self.done = False
        self.wind_sensor.start()

        with open(self.filename,'w') as output_fid:
            while not self.done:
                # Read data from sensor
                data = self.wind_sensor.get_data()
                if data is None:
                    continue
                print(data)

                # Get current and elapsed time
                time_now = time.time()
                time_elapsed = time_now - self.time_init

                # Add data to lists and remove data older then window size
                self.time_list.append(time_elapsed)
                self.angle_list.append(data['angle'])
                self.speed_list.append(data['speed'])
                while (self.time_list[-1] - self.time_list[0]) > self.window_size: 
                    self.time_list.pop(0)
                    self.angle_list.pop(0)
                    self.speed_list.pop(0)

                output_fid.write('{0} {1} {2}\n'.format(time_now,data['angle'],data['speed']))

                # Update angle line
                self.angle_line.set_xdata(self.time_list)
                self.angle_line.set_ydata(self.angle_list)
                xmin = self.time_list[0]
                xmax = max(self.window_size, self.time_list[-1])
                self.angle_axis.set_xlim(xmin,xmax)

                # Update speed line
                self.speed_line.set_xdata(self.time_list)
                self.speed_line.set_ydata(self.speed_list)
                xmin = self.time_list[0]
                xmax = max(self.window_size, self.time_list[-1])
                self.speed_axis.set_xlim(xmin,xmax)

                self.fig.canvas.flush_events()

        print('\nquiting')




# -----------------------------------------------------------------------------
if __name__ == '__main__':

    live_plot = WindSensorLivePlot()
    live_plot.run()


