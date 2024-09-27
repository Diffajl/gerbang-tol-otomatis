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
bool yellowPhaseComplete = false; 

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

    if (!yellowPhaseComplete) {
      digitalWrite(ledYellow, HIGH);
      delay(500);  
      digitalWrite(ledYellow, LOW);
      
      yellowPhaseComplete = true;
    }

    digitalWrite(ledGreen, HIGH);
    
    servo.write(35);

    if (!buzzerPlayed) {
      tone(buzzer, 1000, 100);
      buzzerPlayed = true;
    }
    delay(2000);
    
  } else {
    servo.write(130); 

    digitalWrite(ledGreen, LOW);
    digitalWrite(ledYellow, LOW);  
    digitalWrite(ledRed, HIGH);

    buzzerPlayed = false;
    yellowPhaseComplete = false;
  }
}
