import psutil
import serial
import time
import toml
import pyowm

# Sorry for the massive dict, but I need to convert between
# OWM's icons and mine.
cond = {'01d': 'A', '01n': 'A', '02d': 'B', '02n': 'B', '03d': 'C', '03n': 'C',
	'04d': 'C', '04n': 'C', '09d': 'D', '09n': 'D', '10d': 'D', '10n': 'D',
	'11d': 'E', '11n': 'E', '13d': 'F', '13n': 'F', '50d': 'G'
}

baud = 9600
port = 'COM3'
ser = serial.Serial(port, baud)
conf = toml.load("config.toml")
lastHour = 0

owm = pyowm.OWM(conf["owm"]["key"])

try:
	while 1:
		# Prepare for writing.
		data = ord('B').to_bytes(1, byteorder="big")
		ser.write(data) 
		# Time bytes
		data = ord('C').to_bytes(1, byteorder="big")
		ser.write(data)
		hour = int(time.strftime("%I"))
		ser.write(hour.to_bytes(1, byteorder="big"))
		data = int(time.strftime("%M")).to_bytes(1, byteorder="big")
		ser.write(data)
		# CPU Usage
		data = ord('D').to_bytes(1, byteorder="big")
		ser.write(data)
		data = int(psutil.cpu_percent(interval=0.5)).to_bytes(1, byteorder="big")
		ser.write(data)
		# Weather
		if(hour != lastHour):
			lastHour = hour
			obs = owm.weather_at_id(int(conf["owm"]["city"]))
			w = obs.get_weather()
			degc = int(w.get_temperature("celsius")["temp"])
			icon = cond[w.get_weather_icon_name()]
		data = ord('E').to_bytes(1, byteorder="big")
		ser.write(data)
		ser.write(ord(icon).to_bytes(1, byteorder="big"))
		ser.write(degc.to_bytes(1, byteorder="big"))
		# Flush the buffers
		data = ord('Z').to_bytes(1, byteorder="big")
		ser.write(data)
		time.sleep(0.1)

except KeyboardInterrupt:
	print("Ctrl - C recieved. Exiting.")

finally:
	ser.close()
