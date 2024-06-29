
int motorPin1_2 =19;
int motorPin2_2 =21;
int enablePin_2 =18;


void setup() {
  // put your setup code here, to run once:

  pinMode(motorPin1_2, OUTPUT);
  pinMode(motorPin2_2, OUTPUT);
  pinMode(enablePin_2, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  delay(5000);

  digitalWrite(enablePin_2,HIGH);
  digitalWrite(motorPin2_2 , LOW);
  digitalWrite(motorPin1_2 , HIGH);
  delay(2500);
  digitalWrite(motorPin2_2 , HIGH);
  digitalWrite(motorPin1_2 , LOW);
  delay(200);  
  digitalWrite(enablePin_2, LOW);

  delay(5000);


  


}
