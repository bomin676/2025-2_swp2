#include <Servo.h>
#include <math.h>

#define PIN_SERVO 10
#define PIN_TRIG 12
#define PIN_ECHO 13

#define THRESHOLD_UP 25
#define THRESHOLD_DOWN 15

int startAngle = 0;
int stopAngle  = 90;

Servo myServo;

bool isBarrierUp = false;

unsigned long MOVING_TIME = 3000;

long readStableDistance() {
  long sum = 0;
  for (int i = 0; i < 10; i++) {
    digitalWrite(PIN_TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(PIN_TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(PIN_TRIG, LOW);
    pinMode(PIN_ECHO, INPUT);
    long duration = pulseIn(PIN_ECHO, HIGH);
    
    long distance = duration * 0.034 / 2;
    sum += distance;
    delay(10);
  }
  return sum / 10;
}

void smoothMoveSigmoid(int targetAngle) {
  unsigned long moveStartTime = millis();
  int currentAngle = myServo.read();

  int startValue = currentAngle;
  int endValue = targetAngle;

  while (millis() - moveStartTime <= MOVING_TIME) {
    double progressRatio = (double)(millis() - moveStartTime) / MOVING_TIME;
    double sigmoidInput = 10.0 * (progressRatio - 0.5);
    double sigmoidOutput = 1.0 / (1.0 + exp(-sigmoidInput));
    int nextAngle = startValue + sigmoidOutput * (endValue - startValue);
    myServo.write(nextAngle);
    delay(15);
  }
  myServo.write(targetAngle);
}

void setup() {
  myServo.attach(PIN_SERVO);
  pinMode(PIN_TRIG, OUTPUT);
  myServo.write(startAngle);
  delay(500);
  Serial.begin(9600);
}

void loop() {
  long distance = readStableDistance();
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance <= THRESHOLD_UP && !isBarrierUp) {
    smoothMoveSigmoid(stopAngle);
    isBarrierUp = true;
  }
  else if (distance <= THRESHOLD_DOWN && isBarrierUp) {
    smoothMoveSigmoid(startAngle);
    isBarrierUp = false;
  }
  else if (distance > THRESHOLD_UP && isBarrierUp) {
      smoothMoveSigmoid(startAngle);
      isBarrierUp = false;
  }
  
  delay(100);
}
