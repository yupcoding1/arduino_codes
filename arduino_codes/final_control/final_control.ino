int motorPin1_1 =12;
int motorPin2_1 =14;
int enablePin_1 =13;

int motorPin1_2 =26;
int motorPin2_2 =25;
int enablePin_2 =27;

int motorPin1_3 =32;
int motorPin2_3 =35;
int enablePin_3 =33;

int motorPin1_4 =19;
int motorPin2_4 =21;
int enablePin_4 =18;

void row1(){
  digitalWrite(enablePin_1, HIGH);
  digitalWrite(motorPin1_1 , LOW);
  digitalWrite(motorPin2_1 , HIGH);
  delay(5000);
  digitalWrite(enablePin_1,LOW);
  digitalWrite(enablePin_4,HIGH);
  digitalWrite(motorPin1_4 , LOW);
  digitalWrite(motorPin2_4 , HIGH);
  delay(4000);
}

void row2(){
  digitalWrite(enablePin_2, HIGH);
  digitalWrite(motorPin1_2 , LOW);
  digitalWrite(motorPin2_2 , HIGH);
  delay(5000);
  digitalWrite(enablePin_2,LOW);
  digitalWrite(enablePin_4,HIGH);
  digitalWrite(motorPin1_4 , LOW);
  digitalWrite(motorPin2_4 , HIGH);
  delay(3000);
}

void row3(){
  digitalWrite(enablePin_3, HIGH);
  digitalWrite(motorPin1_3 , LOW);
  digitalWrite(motorPin2_3 , HIGH);
  delay(5000);
  digitalWrite(enablePin_3,LOW);
  digitalWrite(enablePin_4,HIGH);
  digitalWrite(motorPin1_4 , LOW);
  digitalWrite(motorPin2_4 , HIGH);
  delay(2000);
}

void setup() {
  // put your setup code here, to run once:
//row 1
  pinMode(motorPin1_1, OUTPUT);
  pinMode(motorPin2_1, OUTPUT);
  pinMode(enablePin_1, OUTPUT);
  digitalWrite(enablePin_1,LOW);
//row 2
  pinMode(motorPin1_2, OUTPUT);
  pinMode(motorPin2_2, OUTPUT);
  pinMode(enablePin_2, OUTPUT);
  digitalWrite(enablePin_2,LOW);
//row 3
  pinMode(motorPin1_3, OUTPUT);
  pinMode(motorPin2_3, OUTPUT);
  pinMode(enablePin_3, OUTPUT);
  digitalWrite(enablePin_3,LOW);
//
  pinMode(motorPin1_4, OUTPUT);
  pinMode(motorPin2_4, OUTPUT);
  pinMode(enablePin_4, OUTPUT);
  digitalWrite(enablePin_4,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
row1();
row2();
row3();
}
