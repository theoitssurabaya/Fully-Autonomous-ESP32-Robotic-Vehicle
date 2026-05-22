#include <Arduino.h>

#define ENA_BACK    4
#define ENB_BACK    5
#define IN1_BACK    15
#define IN2_BACK    2
#define IN3_BACK    13
#define IN4_BACK    12

#define ENA_FRONT   23
#define ENB_FRONT   22
#define IN1_FRONT   27
#define IN2_FRONT   26
#define IN3_FRONT   18
#define IN4_FRONT   19

#define TRIG_FRONT_LEFT   25
#define ECHO_FRONT_LEFT   33
#define TRIG_FRONT_CENTER 32
#define ECHO_FRONT_CENTER 35  
#define TRIG_FRONT_RIGHT  14
#define ECHO_FRONT_RIGHT  34
#define TRIG_RIGHT        21
#define ECHO_RIGHT        36
#define TRIG_LEFT         16
#define ECHO_LEFT         17

#define DIST_THRESHOLD    35
#define PIVOT_DELAY       400
#define BACKUP_TIME       450

#define CH_ENA_BACK       0
#define CH_ENB_BACK       1
#define CH_ENA_FRONT      2
#define CH_ENB_FRONT      3

#define PWM_FULL          255
#define PWM_HALF          255

long readDistanceCM(int trigPin, int echoPin) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    long duration = pulseIn(echoPin, HIGH, 30000);
    return duration * 0.034 / 2;
}

void setSpeed(int speed) {
    ledcWrite(CH_ENA_BACK, speed);
    ledcWrite(CH_ENB_BACK, speed);
    ledcWrite(CH_ENA_FRONT, speed);
    ledcWrite(CH_ENB_FRONT, speed);
}

void stopMotor() {
    setSpeed(0);
}

void maju() {
    setSpeed(PWM_FULL);
    digitalWrite(IN1_BACK, LOW);
    digitalWrite(IN2_BACK, HIGH);
    digitalWrite(IN3_BACK, HIGH);
    digitalWrite(IN4_BACK, LOW);

    digitalWrite(IN1_FRONT, HIGH);
    digitalWrite(IN2_FRONT, LOW);
    digitalWrite(IN3_FRONT, LOW);
    digitalWrite(IN4_FRONT, HIGH);
}

void mundur() {
    setSpeed(PWM_HALF);
    digitalWrite(IN1_BACK, HIGH);
    digitalWrite(IN2_BACK, LOW);
    digitalWrite(IN3_BACK, LOW);
    digitalWrite(IN4_BACK, HIGH);

    digitalWrite(IN1_FRONT, LOW);
    digitalWrite(IN2_FRONT, HIGH);
    digitalWrite(IN3_FRONT, HIGH);
    digitalWrite(IN4_FRONT, LOW);
}

void pivotKanan() {
    setSpeed(PWM_HALF);
    digitalWrite(IN1_BACK, HIGH);
    digitalWrite(IN2_BACK, LOW);
    digitalWrite(IN3_BACK, HIGH);
    digitalWrite(IN4_BACK, LOW);

    digitalWrite(IN1_FRONT, HIGH);
    digitalWrite(IN2_FRONT, LOW);
    digitalWrite(IN3_FRONT, HIGH);
    digitalWrite(IN4_FRONT, LOW);
}

void pivotKiri() {
    setSpeed(PWM_HALF);
    digitalWrite(IN1_BACK, LOW);
    digitalWrite(IN2_BACK, HIGH);
    digitalWrite(IN3_BACK, LOW);
    digitalWrite(IN4_BACK, HIGH);

    digitalWrite(IN1_FRONT, LOW);
    digitalWrite(IN2_FRONT, HIGH);
    digitalWrite(IN3_FRONT, LOW);
    digitalWrite(IN4_FRONT, HIGH);
}

void setup() {
    Serial.begin(115200);

    pinMode(IN1_BACK, OUTPUT);
    pinMode(IN2_BACK, OUTPUT);
    pinMode(IN3_BACK, OUTPUT);
    pinMode(IN4_BACK, OUTPUT);
    
    pinMode(IN1_FRONT, OUTPUT);
    pinMode(IN2_FRONT, OUTPUT);
    pinMode(IN3_FRONT, OUTPUT);
    pinMode(IN4_FRONT, OUTPUT);

    ledcSetup(CH_ENA_BACK, 1000, 8);
    ledcSetup(CH_ENB_BACK, 1000, 8);
    ledcSetup(CH_ENA_FRONT, 1000, 8);
    ledcSetup(CH_ENB_FRONT, 1000, 8);

    ledcAttachPin(ENA_BACK, CH_ENA_BACK);
    ledcAttachPin(ENB_BACK, CH_ENB_BACK);
    ledcAttachPin(ENA_FRONT, CH_ENA_FRONT);
    ledcAttachPin(ENB_FRONT, CH_ENB_FRONT);

    setSpeed(PWM_FULL);

    pinMode(TRIG_FRONT_LEFT, OUTPUT);
    pinMode(ECHO_FRONT_LEFT, INPUT);
    pinMode(TRIG_FRONT_CENTER, OUTPUT);
    pinMode(ECHO_FRONT_CENTER, INPUT);
    pinMode(TRIG_FRONT_RIGHT, OUTPUT);
    pinMode(ECHO_FRONT_RIGHT, INPUT);
    pinMode(TRIG_RIGHT, OUTPUT);
    pinMode(ECHO_RIGHT, INPUT);
    pinMode(TRIG_LEFT, OUTPUT);
    pinMode(ECHO_LEFT, INPUT);

    Serial.println("System starting. Robot ready to navigate.");
}

void loop() {
    long distFL = readDistanceCM(TRIG_FRONT_LEFT, ECHO_FRONT_LEFT);
    long distFC = readDistanceCM(TRIG_FRONT_CENTER, ECHO_FRONT_CENTER);
    long distFR = readDistanceCM(TRIG_FRONT_RIGHT, ECHO_FRONT_RIGHT);

    bool obstacleDetected = (distFL < DIST_THRESHOLD && distFL > 0) ||
                            (distFC < DIST_THRESHOLD && distFC > 0) ||
                            (distFR < DIST_THRESHOLD && distFR > 0);

    if (obstacleDetected) {
        Serial.println("Obstacle detected ahead.");
        stopMotor();
        delay(200);

        Serial.println("Reversing...");
        mundur();
        delay(BACKUP_TIME);

        stopMotor();
        delay(300);

        long distRight = readDistanceCM(TRIG_RIGHT, ECHO_RIGHT);
        long distLeft  = readDistanceCM(TRIG_LEFT, ECHO_LEFT);

        if (distRight > distLeft) {
            Serial.println("Pivoting right...");
            pivotKanan();
        } else {
            Serial.println("Pivoting left...");
            pivotKiri();
        }

        delay(PIVOT_DELAY);
        stopMotor();
        delay(200);
    } else {
        maju();
    }

    delay(80);
}
