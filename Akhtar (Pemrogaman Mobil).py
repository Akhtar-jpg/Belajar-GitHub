#codingan akhtar

import serial
import time

class ParkingCounter:
    def _init_(self, total_spots):
        self.total_spots = total_spots
        self.car_count = 0

    def update_counts(self, car_count, spots_left):
        self.car_count = car_count
        print(f"Updated Status - Cars: {self.car_count}, Spots Left: {spots_left}")

    def spots_left(self):
        return self.total_spots - self.car_count

# Inisialisasi serial komunikasi dengan Arduino
arduino = serial.Serial('COM3', 9600)  # Ubah 'COM3' sesuai dengan port Arduino
time.sleep(2)  # Tunggu Arduino agar siap

# Inisialisasi sistem parkir
total_spots = 50
parking_lot = ParkingCounter(total_spots)

while True:
    if arduino.in_waiting > 0:
        data = arduino.readline().decode().strip()  # Baca data dari Arduino
        if "car_count" in data and "spots_left" in data:
            parts = data.split(",")
            car_count = int(parts[0].split(":")[1])
            spots_left = int(parts[1].split(":")[1])

            # Update status parkiran
            parking_lot.update_counts(car_count, spots_left)

    time.sleep(0.5)