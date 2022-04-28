from email import message
import serial

arduino = serial.Serial("/dev/tty.usbmodem141101", 115200, timeout=.1)

command = "(4081) 10 1 12 1 255 0 0 0"
message = bytes(command.encode())

arduino.write(message)