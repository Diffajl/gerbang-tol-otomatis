#include <Servo.h>
#define trigPin 7
#define echoPin 8
#define servoPin 2
#define buzzer 10
#define ledRed 4
#define ledYellow 13
#define ledGreen 11

Servo servo;

int angle = 10;
long duration;
int distance;
bool buzzerPlayed = false; 

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  servo.attach(servoPin);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = duration * 0.034 / 2;
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(100);

  if (distance < 10) {
    digitalWrite(ledRed, LOW);
    digitalWrite(ledYellow, HIGH);
    delay(500);
    digitalWrite(ledYellow, LOW);
    digitalWrite(ledGreen, HIGH);
    servo.write(35);

    if (!buzzerPlayed) {
      tone(buzzer, 1000, 100); // Durasi 100 ms
      buzzerPlayed = true; // Tandai bahwa buzzer sudah berbunyi
    }
    delay(2000);
    
  // } else if (distance < 70) {
  //   // Kondisi jarak antara 10 cm - 50 cm (Lampu kuning menyala)
  //   digitalWrite(ledYellow, HIGH);
  //   digitalWrite(ledRed, LOW);
  //   digitalWrite(ledGreen, LOW);
  //   buzzerPlayed = false; // Reset flag ketika keluar dari kondisi hijau
  } else {
    // Kondisi jarak lebih dari 50 cm (Lampu merah menyala)
    servo.write(130); // Menggerakkan servo ke 180 derajat
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledYellow, LOW);
    digitalWrite(ledRed, HIGH);
    buzzerPlayed = false; // Reset flag ketika keluar dari kondisi hijau
  }
}
