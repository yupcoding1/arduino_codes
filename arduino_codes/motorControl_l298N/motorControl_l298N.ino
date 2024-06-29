int motorPin1 =26;
int motorPin2 =25;
int enablePin =27;

const int freq =30000;
const int pwmChannel=0;
const int resolution=8;
int dutycycle =170;


void setup() {
  // put your setup code here, to run once:
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(enablePin, OUTPUT);

  ledcSetup(pwmChannel,freq,resolution);
  ledcAttachPin(enablePin,pwmChannel);
  ledcWrite(pwmChannel,dutycycle);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(motorPin1 , HIGH);
  digitalWrite(motorPin2 , LOW);
  delay(1000);

  digitalWrite(motorPin2 , HIGH);
  digitalWrite(motorPin1 , LOW);
  delay(1000);

  digitalWrite(motorPin1 , HIGH);
  digitalWrite(motorPin2 , LOW);
  
  for(int i=170 ;i<255;i++){
    dutycycle=i;
    ledcWrite(pwmChannel,dutycycle);
    delay(50);
  }
  dutycycle=170;
  ledcWrite(pwmChannel,dutycycle);
}
