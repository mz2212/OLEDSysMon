import psutil
import serial
import time

baud = 9600
port = 'COM3'
ser = serial.Serial(port, baud)

try:
	while 1:
		# Prepare for writing.
		data = ord('B').to_bytes(1, byteorder="big")
		ser.write(data) 
		# Time bytes
		data = ord('C').to_bytes(1, byteorder="big")
		ser.write(data)
		data = int(time.strftime("%I")).to_bytes(1, byteorder="big")
		ser.write(data)
		data = int(time.strftime("%M")).to_bytes(1, byteorder="big")
		ser.write(data)
		# CPU Usage
		data = ord('D').to_bytes(1, byteorder="big")
		ser.write(data)
		data = int(psutil.cpu_percent(interval=0.5)).to_bytes(1, byteorder="big")
		ser.write(data)
		# Flush the buffers
		data = ord('Z').to_bytes(1, byteorder="big")
		ser.write(data)
		time.sleep(0.1)

except KeyboardInterrupt:
	print("Ctrl - C recieved. Exiting.")

finally:
	ser.close()