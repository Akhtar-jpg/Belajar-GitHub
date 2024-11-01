#include <LiquidCrystal.h>

// Inisialisasi pin LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Konfigurasi Pin Ultrasonic Sensor
const int trigPin = 9;
const int echoPin = 8;

// Konfigurasi Pin Buzzer (opsional)
const int buzzerPin = 10;

// Pengaturan variabel
int total_spots = 50;          // Total tempat parkir
int car_count = 0;             // Jumlah mobil yang terparkir
int min_distance = 10;         // Batas jarak (cm) untuk deteksi kendaraan

void setup() {
  // Inisialisasi pin
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);

  // Inisialisasi LCD
  lcd.begin(16, 2);
  lcd.print("Parking System");
  delay(2000);
  lcd.clear();

  // Inisialisasi Serial
  Serial.begin(9600);
}

void loop() {
  int distance = getDistance();

  // Jika ada kendaraan dalam jarak tertentu, anggap kendaraan masuk atau keluar
  if (distance < min_distance) {
    delay(500); // Tunggu sebentar untuk stabilisasi

    // Kendaraan masuk
    if (spotsLeft() > 0) {
      car_count++;
      lcd.clear();
      lcd.print("Vehicle Entered");
      updateDisplay();
      sendStatusToPython(); // Kirim status parkir ke Python
      delay(2000);
    } else {
      // Tampilkan bahwa parkiran penuh dan nyalakan buzzer
      lcd.clear();
      lcd.print("Parking Full!");
      digitalWrite(buzzerPin, HIGH);
      delay(1000);
      digitalWrite(buzzerPin, LOW);
    }
  } else {
    // Kendaraan keluar
    if (car_count > 0) {
      car_count--;
      lcd.clear();
      lcd.print("Vehicle Exited");
      updateDisplay();
      sendStatusToPython(); // Kirim status parkir ke Python
      delay(2000);
    }
  }
}

// Fungsi untuk menghitung jarak dari sensor ultrasonik
int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;
  return distance;
}

// Fungsi untuk menghitung sisa tempat parkir
int spotsLeft() {
  return total_spots - car_count;
}

// Fungsi untuk memperbarui tampilan LCD
void updateDisplay() {
  lcd.clear();
  lcd.print("Cars: ");
  lcd.print(car_count);
  lcd.setCursor(0, 1);
  lcd.print("Spots Left: ");
  lcd.print(spotsLeft());
}

// Fungsi untuk mengirim status parkir ke Python
void sendStatusToPython() {
  Serial.print("car_count:");
  Serial.print(car_count);
  Serial.print(",spots_left:");
  Serial.println(spotsLeft());
}