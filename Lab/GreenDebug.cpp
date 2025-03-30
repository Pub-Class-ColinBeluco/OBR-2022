int vdE = A15;
int vdD = A14;

byte LED_G = 26;
byte lED = 22;
byte rED = 30;

long vdEAmount[10];
long vdDAmount[10];

char color = 'd';

void setup() {
  pinMode(vdE, INPUT_PULLUP);
  pinMode(vdD, INPUT_PULLUP);

  pinMode(LED_G, OUTPUT);
  pinMode(lED, OUTPUT);
  pinMode(rED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  leftRead();
  rightRead();
}

void leftRead() {
  if  (mediaE() >= 700)  {
    digitalWrite(lED, LOW);
    digitalWrite(rED, LOW);
    digitalWrite(LED_G, LOW);
  }
  if  ((mediaE() >= 58) && (mediaE() < 700)) {
    digitalWrite(lED, LOW);
    digitalWrite(rED, LOW);
    digitalWrite(LED_G, HIGH);
  }
  if  (mediaE() < 58)  {
    digitalWrite(lED, HIGH);
    digitalWrite(rED, LOW);
    digitalWrite(LED_G, LOW);
  }
}

void rightRead()  {
    if  (mediaD() >= 700)  {
    digitalWrite(lED, LOW);
    digitalWrite(rED, LOW);
    digitalWrite(LED_G, LOW);
  }
  if  ((mediaD() >= 56) && (mediaD() < 700)) {
    digitalWrite(lED, LOW);
    digitalWrite(rED, LOW);
    digitalWrite(LED_G, HIGH);
  }
  if  (mediaD() < 56)  {
    digitalWrite(lED, LOW);
    digitalWrite(rED, HIGH);
    digitalWrite(LED_G, LOW);
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
