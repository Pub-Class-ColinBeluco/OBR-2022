#define motor1  7
#define motor1t 6
#define motor2  5
#define motor2t 4

#define lED     22
#define LED_G   26
#define LED_B   28
#define rED     30

byte daFrente = 52;
byte extEsq   = 42;
byte Esq      = 46;
byte doMeio   = 44;
byte Dir      = 48;
byte extDir   = 50;

int vdE = A15;
int vdD = A14;

long vdEAmount[10];
long vdDAmount[10];

int guBoiola = 0;


void setup() {
  pinMode(motor1, OUTPUT);
  pinMode(motor1t, OUTPUT);
  pinMode(motor2, OUTPUT);
  pinMode(motor2t, OUTPUT);
  delay(10);

  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(lED, OUTPUT);
  pinMode(rED, OUTPUT);
  delay(10);

  pinMode(daFrente, INPUT);
  pinMode(doMeio, INPUT);
  pinMode(Esq,    INPUT);
  pinMode(Dir,    INPUT);
  pinMode(extEsq, INPUT);
  pinMode(extDir, INPUT);
  delay(10);

  pinMode(vdE, INPUT_PULLUP);
  pinMode(vdD, INPUT_PULLUP);

  Serial.begin(9600);
  delay(10);
}

void loop() {
  Esq = digitalRead(46);
  Dir = digitalRead(48);
  extEsq = digitalRead(42);
  extDir = digitalRead(50);
  
  if  ((Esq == 0) && (Dir == 0))  MOVE(47, 0, 47, 0);
  
  if  (((extEsq == 1) && (Esq == 1)) || ((Dir == 1) && (extDir == 1)))  {
    PARE();
    delay(300);
    leftRead();
    rightRead();
    PARE();
    delay(50000);
  }

  if  ((Esq == 1) && (Dir == 0))  MOVE(0, 100, 130, 0);
  if  ((Esq == 0) && (Dir == 1))  MOVE(130, 0, 0, 100);
}

byte compact()  {
  return extEsq + extDir + Esq + Dir;
}

void PARE() {
  MOVE(200, 200, 200, 200);
  delay(500);
  MOVE(0, 0, 0, 0);
}

void  MOVE(byte m1, byte m1t, byte m2, byte m2t)  {
  analogWrite(motor1, m1);
  analogWrite(motor1t, m1t);
  analogWrite(motor2, m2);
  analogWrite(motor2t, m2t);
}

void leftRead() {
  if  (mediaE() >= 700)  {
    digitalWrite(lED, LOW);
    digitalWrite(rED, LOW);
    digitalWrite(LED_G, LOW);
  }
  if  ((mediaE() >= 59) && (mediaE() < 700)) {
    digitalWrite(lED, LOW);
    digitalWrite(rED, LOW);
    if  (mediaE() < 59) digitalWrite(lED, HIGH);
    digitalWrite(LED_G, HIGH);
  }
  if  (mediaE() < 59)  {
    digitalWrite(lED, HIGH);
    digitalWrite(rED, LOW);
    digitalWrite(LED_G, LOW);
  }
}

void rightRead()  {
    if  (mediaD() >= 700)  {
    digitalWrite(lED, LOW);
    digitalWrite(rED, LOW);
    digitalWrite(LED_B, LOW);
  }
  if  ((mediaD() >= 56) && (mediaD() < 700)) {
    digitalWrite(lED, LOW);
    digitalWrite(rED, LOW);
    if  (mediaE() < 59) digitalWrite(lED, HIGH);
    digitalWrite(LED_B, HIGH);
  }
  if  (mediaD() < 56)  {
    digitalWrite(lED, LOW);
    digitalWrite(rED, HIGH);
    if  (mediaE() < 59) digitalWrite(lED, HIGH);
    digitalWrite(LED_B, LOW);
  }
}

long mediaE() {                                         // Filtro de média de Verde-Esquerda
  vdE = analogRead(A15);
  for(int i = 9; i>0; i--) vdEAmount[i] = vdEAmount[i-1];
  vdEAmount[0]  = vdE;
  long JoinE = 0;
  for(int i = 0; i<10; i++)  JoinE += vdEAmount[0];
  return JoinE/10;
//  if  ((angleY <= (pAng * -1)) || (angleY >= pAng)) {return 0;}
//  else {return JoinE/n;}
}
long mediaD() {                                         // Filtro de média de Verde-Direita
  vdD = analogRead(A14);
  for(int i = 9; i>0; i--) vdDAmount[i] = vdDAmount[i-1];
  vdDAmount[0]  = vdD;
  long JoinD = 0;
  for(int i = 0; i<10; i++)  JoinD += vdDAmount[0];
  return JoinD/10;
////  if  ((angleY <= (pAng * -1)) || (angleY >= pAng)) {return 0;}
////  else {return JoinD/n;}
}
