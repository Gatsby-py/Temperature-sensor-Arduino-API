import time
import serial
import requests

api_url = "http://203c15850d9512ad1238gudqhheyyyyyb.oast.pro"
port = '/dev/cu.usbmodem11201'

while True: # Keep trying forever hhh
    try:
        # 1. Try to open the serial port
        ser = serial.Serial(port, 9600, timeout=1)
        print("--- Connected ---")

        while True: # Stay in this loop while the Arduino is plugged in
            line = ser.readline().decode().strip()
            
            if line:
                print(line)
                try:
                    temperature, maximum = map(float, line.split(","))
                    response = requests.post(api_url, json={"temperature": temperature, "maximum": maximum})
                    print("Sent", response.status_code)
                    print(" ")
                except:
                    pass

    except (serial.SerialException, FileNotFoundError, OSError):
        # 2. This part runs if the Arduino is unplugged or the port isn't found
        print("Arduino not found. Retrying in 5 seconds...")
        print()
        time.sleep(5)
        continue # Go back to the top and try to connect again
    
    except KeyboardInterrupt:
        print("Manual Stop")
        break