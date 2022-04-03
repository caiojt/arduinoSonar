#include <HCSR04.h>
HCSR04 hc(2, 3); //sonar pins

//pins
int yellow = 6;
int red1 = 4;
int red2 = 5;
int buzz = 8;


void setup() {
  Serial.begin(9600);
  pinMode(yellow, OUTPUT);
  digitalWrite(yellow, LOW);   
  pinMode(red1, OUTPUT);
  digitalWrite(red1, LOW); 
  pinMode(red2, OUTPUT);
  digitalWrite(red2, LOW); 
}

void loop() {

int distance1 =  hc.dist(); //gets first reading
Serial.println(distance1);
blinksYellowLED();
int distance2 = hc.dist(); //gets second reading
Serial.println(distance2);
blinksYellowLED();
int distance3 = hc.dist(); //gets second reading
Serial.println(distance3);

int detected = (distance2-distance1) + (distance3-distance2); //captures abrupt change detected between 3 readings
Serial.print("diff: ");
Serial.println(abs(detected));
  if ((distance1 > 0 && distance1 <15) || (distance2 > 0 && distance2 <15) || (distance3 > 0 && distance3 <15) ){
    //put your hands in front of the alarm to disable for 4 hours
    digitalWrite(yellow, HIGH);
        delay(14400000); //stops for 4 hours
    digitalWrite(yellow, LOW);
   }
  else
  if (abs(detected) > 30) { //abrupt change in sonar detected
   emitAlert();
 }             
}

void blinksYellowLED(){

  digitalWrite(yellow, HIGH);  
  delay(200);   
  digitalWrite(yellow, LOW);
  delay(200);             
}

void emitAlert() { //buzzer and LED blinking

 for (int i = 1;i < 10; i++){ //repeats 10 times
  for(int hz = 440; hz < 1000; hz++){
    tone(buzz, hz, 50);
    if (hz > 440 && hz< 840){ //blinks during buzz interval
      digitalWrite(red1, HIGH);
      digitalWrite(red2, HIGH);
    }
    else{
      digitalWrite(red1, LOW);
      digitalWrite(red2, LOW);
    }
    delay(2);
  }
  for(int hz = 1000; hz > 440; hz--){
    tone(buzz, hz, 50);
     if (hz > 440 && hz< 840){
      digitalWrite(red1, HIGH);
      digitalWrite(red2, HIGH);
     }
    else{
      digitalWrite(red1, LOW);
      digitalWrite(red2, LOW);
    }
    delay(2);
  }
}
digitalWrite(red1, HIGH);
digitalWrite(red2, HIGH);
delay(86400000); //sleeps arduino for 1 day
digitalWrite(red1, LOW);
digitalWrite(red2, LOW);

}
  
