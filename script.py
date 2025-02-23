import serial
# import time
import serial.tools.list_ports
from attendance_markup import make_attendance

#returning True to arduino when id matches
#returning False when not matching
#returning Error when script doesn't run

# AUTHORIZED_UID = "B0:5E:88:E"

def setUpPort():
    global use
    # Set up the port
    ports = serial.tools.list_ports.comports()
    portsList = []
    for one in ports:
        portsList.append(str(one))
        print(str(one))

    com = input("Input COM Port for Arduino #: ")
    use = str(com)

# LOG_FILE = "uids_log.txt"
# logging UID and timestamp locally
# def log_uid(uid, status):
#     with open(LOG_FILE, "a") as file:
#         timestamp = time.strftime("%d-%m-%y %H:%M")
#         file.write(f"{timestamp} - UID: {uid} - Status: {status}\n")

setUpPort()

uid = ''
arduino = serial.Serial(port='/dev/ttyUSB0', baudrate=115200, timeout=0.1)

while True:
    data = arduino.readline()
    if data:  # Check if data is not empty
        decoded_data = data.decode('utf-8').strip()
        decoded_data = decoded_data.split()
        
        # Extract UID from the data
        for i in range(len(decoded_data)):
            if decoded_data[i] == 'UID:':
                uid = decoded_data[i + 1]

                result = make_attendance(uid)
                
                # Check if UID is authorized
                if  result == 1:
                    print("Access Granted! ")
                    print("UID: ", uid)
                    arduino.write(b"True\n")
                    # log_uid(uid, "Authorized")
                elif result == 0:
                    print("Unauthorized UID ")
                    print("UID: ", uid)
                    arduino.write(b"False\n")
                    # log_uid(uid, "Unauthorized")
                elif result == "Error":
                    print("Server Error")
                    arduino.write(b"mongodb Error\n")
                else:
                    print("Something is wrong")
                    arduino.write(b"Something went wrong\n")


