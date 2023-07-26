#include <Encoder.h>

#define ENCA 2
#define ENCB 23
#define PWMA 5
#define DIRA1 27
#define DIRA2 26



#define MOTORA_FORWARD(pwm)    do{digitalWrite(DIRA1,LOW); digitalWrite(DIRA2,HIGH);analogWrite(PWMA,pwm);}while(0)
#define MOTORA_STOP(x)         do{digitalWrite(DIRA1,LOW); digitalWrite(DIRA2,LOW); analogWrite(PWMA,0);}while(0)
#define MOTORA_BACKOFF(pwm)    do{digitalWrite(DIRA1,HIGH);digitalWrite(DIRA2,LOW); analogWrite(PWMA,pwm);}while(0)


Encoder myEnc(ENCA, ENCB);

//measure them accurately
const int ticks_per_rev = 1300;//int ticks ( number of encoder ticks in one revolution of the motor shaft)
const float wheel_diameter = 0.08;//in meters (diameter of the wheel used for motion.)


double Setpoint, Input, Output;
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
  float go_to = 0.50;
  float num_revs = go_to/(PI*wheel_diameter);
  int ticks = num_revs*ticks_per_rev;
 
  Setpoint = ticks;
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


    if(Output > 0)
      MOTORA_FORWARD(pwm);
    else
      MOTORA_BACKOFF(pwm);
  }

    
  Serial.print(Setpoint);Serial.print("\t");
  Serial.println(Input);

  Serial.print(Setpoint);Serial.print("\t");
  Serial.println(Input);
  Serial.print(Setpoint);Serial.print("\t");
  Serial.println(Input);
  Serial.print(Setpoint);Serial.print("\t");
  Serial.println(Input);
}
