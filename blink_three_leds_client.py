import serial
import time

def safe_read_line_serial(ser):
    return str.strip(ser.readline().decode('utf-8'))

while True:
    ser = serial.Serial('/dev/cu.usbmodem0000000000001', 115200, timeout=0.5)
    ser.write({0x31})
    time.sleep(0.2)
    print(safe_read_line_serial(ser))

    ser.write({0x32})
    time.sleep(0.2)
    print(safe_read_line_serial(ser))

    ser.write({0x33})
    time.sleep(0.2)
    print(safe_read_line_serial(ser))
