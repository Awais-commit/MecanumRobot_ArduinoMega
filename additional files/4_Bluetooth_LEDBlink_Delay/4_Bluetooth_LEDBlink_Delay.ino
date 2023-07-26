#define ledPin 13
String val;
int numBlinks = 0;
int delayTime = 0;

void setup() {
  pinMode(ledPin,OUTPUT);
  digitalWrite(ledPin,LOW);
  Serial.begin(9600);
  Serial1.begin(9600);

}

void loop() {
  if(Serial1.available()){
    val = Serial1.readStringUntil('\n'); //Read te numaric input for nummber of blinks from bluetooth
    numBlinks = val.substring(0,val.indexOf(',')).toInt();
    delayTime = val.substring(val.indexOf(',')+1, val.length()).toInt();

    if (numBlinks !=0 && delayTime !=0){
      Serial.println(numBlinks);
      Serial.println(delayTime);
      blinkLED(numBlinks, delayTime);
    }
  }
}

void blinkLED(int numBlinks, int delayTime){
  for(int i = 0; i < numBlinks; i++ ){
    digitalWrite(ledPin,HIGH);
    delay(delayTime);
    digitalWrite(ledPin,LOW);
    delay(delayTime);
  }  

}
