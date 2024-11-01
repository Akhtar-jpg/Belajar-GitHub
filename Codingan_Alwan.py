import serial
import time

# Inisialisasi koneksi serial
ser = serial.Serial('COM3', 9600)  # Ganti 'COM3' dengan port yang sesuai
time.sleep(2)

kapasitas_motor = 10
kapasitas_mobil = 5
jumlah_motor = 0
jumlah_mobil = 0

try:
    while True:
        if ser.in_waiting > 0:
            data = ser.readline().decode('utf-8').strip()
            if data == "motor masuk":
                jumlah_motor += 1
                print(f"Jumlah motor: {jumlah_motor}/{kapasitas_motor}")
            elif data == "motor keluar":
                jumlah_motor -= 1
                print(f"Jumlah motor: {jumlah_motor}/{kapasitas_motor}")
            elif data == "Parkir motor penuh":
                print("Parkir motor penuh!")

            # Cek kapasitas parkir mobil (opsional jika ditambahkan)
            # if jumlah_mobil >= kapasitas_mobil:
            #     print("Parkir mobil penuh!")

except KeyboardInterrupt:
    print("Program dihentikan.")
finally:
    ser.close()
