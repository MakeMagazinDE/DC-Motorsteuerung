
// Simpler Regler für DC Motoren

#define MESS A0
#define STEUER 10

#define U_EMK_SOLL 110   // Gewünschte U_EMK ~ gewünschte Drehzahl

int iMess[10]; // Array für 10 Werte - für Mittelwertbildung
int ptr;

int U_korrektur;  // Korrekturwert zur Betriebsspannung
int UB;           // Betriebsspannung

void setup() {                
  Serial.begin(9600);
  pinMode(STEUER, OUTPUT);   
  pinMode(MESS,INPUT);  
  ptr = 0;
  U_korrektur = 0;
  UB = 255;
}

void loop() {
  int mittelWert;
  int U_EMK;
  
  UB = 150 + U_korrektur;  // Einstelle der Betriebsspannung
  analogWrite(STEUER, UB); // durch PWM
  
  iMess[ptr++] = analogRead(MESS);  // Strommessung
  if (ptr>9) ptr=0;
  mittelWert = 0;
  for (int i=0; i<10; i++) mittelWert += iMess[i];  // Mittelwertbildung
  mittelWert = mittelWert / 10;
  
  U_EMK = UB - mittelWert;  // Ableiten der Generatorspannung aus UB und Messwert
  U_korrektur = (U_EMK_SOLL - U_EMK)/2;   // Korrekturwert für UB 
                                          // (Faktor /2 durch Ausprobieren)
  
  if (U_korrektur > 50) U_korrektur = 100;   // Korrekturwert maximal +/-100
  if (U_korrektur < -50) U_korrektur = -100; 

  Serial.print("Messwert=");    // Ausgabe über serielle Schnittstelle
  Serial.print(mittelWert);
  Serial.print("  U_EMK=");
  Serial.print(U_EMK);
  Serial.print("   UB=");
  Serial.println(UB);
  
  delay(10);
}
