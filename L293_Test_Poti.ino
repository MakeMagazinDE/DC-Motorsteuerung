// L293 Demo mit Potentiometer

#define DRIVE_1 7
#define DRIVE_2 8
#define PWM     9
#define POTI   A0

int potiWert;
int pwmSpeed;

void setup() {
  pinMode(DRIVE_1,OUTPUT);
  pinMode(DRIVE_2,OUTPUT);
  pinMode(PWM,OUTPUT);
  pinMode(PWM,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  potiWert = analogRead(POTI);  // Wert zwischen 0...1024

  if (potiWert > 512) {
     digitalWrite(DRIVE_1, LOW);   // Rechts
     digitalWrite(DRIVE_2, HIGH);
  }
  else {
     digitalWrite(DRIVE_1, HIGH);   // Links
     digitalWrite(DRIVE_2, LOW);
  }  
  
  pwmSpeed = abs(potiWert-512)/2;   // Geschwindigkeit
  analogWrite(PWM, pwmSpeed);
}
