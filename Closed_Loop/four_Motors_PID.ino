#include <Encoder.h>

#define PWMA 12
#define DIRA1 34
#define DIRA2 35
#define ENCA 18
#define ENCB 31

#define PWMB 8
#define DIRB1 37
#define DIRB2 36
#define ENCB1 19
#define ENCB2 38

#define PWMC 5//9
#define DIRC1 43
#define DIRC2 42
#define ENCC1 3
#define ENCC2 49

#define PWMD 6//5
#define DIRD1 A5//26
#define DIRD2 A4//27
#define ENCD1 2
#define ENCD2 1 //23


#define MOTORA_FORWARD(pwm)    do{digitalWrite(DIRA1,LOW); digitalWrite(DIRA2,HIGH);analogWrite(PWMA,pwm);}while(0)
#define MOTORA_STOP(x)         do{digitalWrite(DIRA1,LOW); digitalWrite(DIRA2,LOW); analogWrite(PWMA,0);}while(0)
#define MOTORA_BACKOFF(pwm)    do{digitalWrite(DIRA1,HIGH);digitalWrite(DIRA2,LOW); analogWrite(PWMA,pwm);}while(0)

#define MOTORB_FORWARD(pwm)    do{digitalWrite(DIRB1,LOW); digitalWrite(DIRB2,HIGH);analogWrite(PWMB,pwm);}while(0)
#define MOTORB_STOP(x)         do{digitalWrite(DIRB1,LOW); digitalWrite(DIRB2,LOW); analogWrite(PWMB,0);}while(0)
#define MOTORB_BACKOFF(pwm)    do{digitalWrite(DIRB1,HIGH);digitalWrite(DIRB2,LOW); analogWrite(PWMB,pwm);}while(0)

#define MOTORC_FORWARD(pwm)    do{digitalWrite(DIRC1,LOW); digitalWrite(DIRC2,HIGH);analogWrite(PWMC,pwm);}while(0)
#define MOTORC_STOP(x)         do{digitalWrite(DIRC1,LOW); digitalWrite(DIRC2,LOW); analogWrite(PWMC,0);}while(0)
#define MOTORC_BACKOFF(pwm)    do{digitalWrite(DIRC1,HIGH);digitalWrite(DIRC2,LOW); analogWrite(PWMC,pwm);}while(0)

#define MOTORD_FORWARD(pwm)    do{digitalWrite(DIRD1,LOW); digitalWrite(DIRD2,HIGH);analogWrite(PWMD,pwm);}while(0)
#define MOTORD_STOP(x)         do{digitalWrite(DIRD1,LOW); digitalWrite(DIRD2,LOW); analogWrite(PWMD,0);}while(0)
#define MOTORD_BACKOFF(pwm)    do{digitalWrite(DIRD1,HIGH);digitalWrite(DIRD2,LOW); analogWrite(PWMD,pwm);}while(0)




Encoder myEnc(ENCA, ENCB);
Encoder myEncB(ENCB1, ENCB2);//
Encoder myEncC(ENCC1, ENCC2);//
Encoder myEncD(ENCD1, ENCD2);//

//measure them accurately
const int ticks_per_rev = 1300;//int ticks ( number of encoder ticks in one revolution of the motor shaft)
const float wheel_diameter = 0.08;//in meters (diameter of the wheel used for motion.)


double Setpoint, Input, Output;
double SetpointB, InputB, OutputB;//
double SetpointC, InputC, OutputC;//
double SetpointD, InputD, OutputD;//


double Kp = 0.8, Ki = 0, Kd = 0;
double P, I, D;
double error;

unsigned int t1 = 0;
unsigned int t2 = 0;
double dt = 10;
int pwm = 0;
bool state = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  //pinMode(PWMA, OUTPUT);
  pinMode(DIRA1, OUTPUT);
  pinMode(DIRA2, OUTPUT);

  t1 = millis();
  t2 = millis();

  //distance to cover in meter
  float go_to = 1.50;
  float num_revs = go_to/(PI*wheel_diameter);
  int ticks = num_revs*ticks_per_rev;
 
  Setpoint = ticks;
  SetpointB = ticks;
  SetpointC = ticks;
  SetpointD = ticks;
}

void loop() {
  // put your main code here, to run repeatedly:
  

  if ((millis() - t1) >=  dt)
  {
    t1 = millis();
    Input = myEnc.read();
    error = Setpoint - Input;
    P = Kp * error;
    D = Kd * error / dt;
    I += Ki * error * dt;
    Output = -(P + I + D);

    pwm = abs((int)Output);
    if (pwm > 100) pwm = 100;


    if(Output > 0){
      MOTORA_FORWARD(pwm);
      MOTORB_FORWARD(pwm);
      MOTORC_FORWARD(pwm);
      MOTORD_FORWARD(pwm);}
    else{
      MOTORA_BACKOFF(pwm);
      MOTORB_BACKOFF(pwm);
      MOTORC_BACKOFF(pwm);
      MOTORD_BACKOFF(pwm);}
  }
    
  Serial.print(Setpoint);Serial.print("\t");
  Serial.println(Input);
  Serial.print(SetpointB);Serial.print("\tInput: ");
  Serial.println(Input);
  /*Serial.print(SetpointC);Serial.print("\tInput: ");
  Serial.println(Input);
  Serial.print(SetpointD);Serial.print("\tInput: ");
  Serial.println(Input);*/
}
