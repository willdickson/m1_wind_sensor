from m1_wind_sensor import M1Logger

port = '/dev/ttyACM0'
logger = M1Logger(port=port)
logger.run()
