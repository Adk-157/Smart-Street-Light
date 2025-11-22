import serial
import time
import pyrebase

# Firebase Configuration
firebase_config = {
    "apiKey": "AIzaSyDRJOgy8LfNAL0JfPOyMQOiBPaN7gIcrIA",
    "authDomain": "es-project-f29d8.firebaseapp.com",
    "databaseURL": "https://es-project-f29d8-default-rtdb.asia-southeast1.firebasedatabase.app",
    "storageBucket": "es-project-f29d8.firebasestorage.app"
}

# Initialize Firebase
firebase = pyrebase.initialize_app(firebase_config)
db = firebase.database()

# Initialize Serial Communication with LoRa
serial_port = "/dev/ttyUSB0"  # Replace with the correct serial port
baud_rate = 9600  # Adjust based on your LoRa settings
ser = serial.Serial(serial_port, baud_rate, timeout=1)

# Function to process Firebase data and send via LoRa
def process_and_send_data():
    try:
        # Fetch brightness and statuses from Firebase
        brightness = db.child("street_lights").child("brightness").child("0").get().val()
        status = db.child("street_lights").child("statuses").child("0").get().val()

        # Prepare data to send
        data_to_send = f"{status},{brightness}"  # Format: "1,75" (status,brightness)
        print(f"Sending data: {data_to_send}")

        # Send data to LoRa
        ser.write(data_to_send.encode())
        time.sleep(1)  # Allow time z

    except Exception as e:
        print(f"Error: {e}")

# Main Loop
if _name_ == "_main_":
    while True:
        process_and_send_data()
        time.sleep(2)  # Adjust as necessary to avoid overwhelming the system