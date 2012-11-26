int leftBumperPin = 7;
int leftBumperVal = 0;
//float leftTime = 0;
boolean leftBumped = false;
int lastLeft = 0;
int rightBumperPin = 9;
int rightBumperVal = 0;
boolean rightBumped = false;
int lastRight = 0;

int bleftBumperPin = 8;
int bleftBumperVal = 0;
//float leftTime = 0;
boolean bleftBumped = false;
int blastLeft = 0;
int brightBumperPin = 10;
int brightBumperVal = 0;
boolean brightBumped = false;
int blastRight = 0;

int lastBump = 0;

int drivePow = 225;

int pwm_a = 3;  //PWM control for motor outputs 1 and 2 is on digital pin 3
int pwm_b = 11;  //PWM control for motor outputs 3 and 4 is on digital pin 11
int dir_a = 12;  //dir control for motor outputs 1 and 2 is on digital pin 12
int dir_b = 13;  //dir control for motor outputs 3 and 4 is on digital pin 13

void setup() {
  pinMode(rightBumperPin, INPUT);
  pinMode(leftBumperPin, INPUT);
  pinMode(brightBumperPin, INPUT);
  pinMode(bleftBumperPin, INPUT);
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(pwm_a, OUTPUT);  //Set control pins to be outputs
  pinMode(pwm_b, OUTPUT);
  pinMode(dir_a, OUTPUT);
  pinMode(dir_b, OUTPUT);
  Serial.begin(9600);
  Serial.println("hey");
}

void checkBackBump(int times){
  blastLeft = 0;
  blastRight = 0;
  for(int i = 0; i <  times/5; i++){
      delay(50);
      bleftBumperVal = digitalRead(bleftBumperPin);
      if(bleftBumperVal == 1 && blastLeft++ > 5){
        Serial.println("bumped l");
        analogWrite(pwm_a, 0);
        analogWrite(pwm_b, 0);
        digitalWrite(dir_a, HIGH);
        digitalWrite(dir_b, HIGH);
        analogWrite(pwm_a, drivePow);
        analogWrite(pwm_b, drivePow);
        delay(400);
        analogWrite(pwm_a, 0);
        analogWrite(pwm_b, 0);
        digitalWrite(dir_a, LOW);
        digitalWrite(dir_b, LOW);
        return;
      }
      brightBumperVal = digitalRead(brightBumperPin);
      if(brightBumperVal == 1 && blastRight++ > 5){
        Serial.println("bumped r");
        analogWrite(pwm_a, 0);
        analogWrite(pwm_b, 0);
        digitalWrite(dir_a, HIGH);
        digitalWrite(dir_b, HIGH);
        analogWrite(pwm_a, drivePow);
        analogWrite(pwm_b, drivePow);
        delay(400);
        analogWrite(pwm_a, 0);
        analogWrite(pwm_b, 0);
        digitalWrite(dir_a, LOW);
        digitalWrite(dir_b, LOW);
        return;
      }
    }
}

void turn(char dir){
  if(millis() - lastBump > 2000){
    lastBump = millis();
    Serial.print("turn dir: ");
    Serial.println(dir);
    analogWrite(pwm_a, 0);
    analogWrite(pwm_b, 0);
    delay(1000);
    digitalWrite(dir_a, LOW);
    digitalWrite(dir_b, LOW);
    Serial.println("back");
    analogWrite(pwm_a, drivePow);
    analogWrite(pwm_b, drivePow);
    delay(400);
    checkBackBump(20);
    analogWrite(pwm_a, 0);
    analogWrite(pwm_b, 0);
    delay(1000);
    Serial.println("turn");
    delay(200);
    if(dir == 'l')
      analogWrite(pwm_b, 255);
    else
      analogWrite(pwm_a, 255);
    delay(600);
    if(dir == 'b')
      checkBackBump(46);
    else if(dir == 'l')
      checkBackBump(24);
    else if(dir == 'r')
      checkBackBump(24);
  }
}

void loop() {
  digitalWrite(2, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  
  digitalWrite(dir_a, HIGH);
  digitalWrite(dir_b, HIGH);
  
//  delay(10);
  
  leftBumperVal = digitalRead(leftBumperPin);
  if(leftBumperVal == 1 ){
    analogWrite(pwm_a, 0);
    analogWrite(pwm_b, 0);
    if(millis() - lastLeft > 2000){
      lastLeft = millis();
      leftBumped = true;
      Serial.print("left: ");
      Serial.println(millis());
    }
  }
  else
    leftBumped = false;
  
  rightBumperVal = digitalRead(rightBumperPin);
//  Serial.println(rightBumperVal);
  if(rightBumperVal == 0 ){
    analogWrite(pwm_a, 0);
    analogWrite(pwm_b, 0);
    if( millis() - lastRight > 2000){
      lastRight = millis();
      rightBumped = true;
      Serial.print("right: ");
      Serial.println(millis());
    }
  }
  else
    rightBumped = false;
//  Serial.println("_____________________");
  if(leftBumped && rightBumped)
    turn('b'); 
  else if(leftBumped){
    lastLeft = false;
    turn('l');
  }
  else if(rightBumped){
    lastRight = false;
    turn('r');
  }
  else{
    digitalWrite(dir_a, HIGH);
    digitalWrite(dir_b, HIGH);
    analogWrite(pwm_a, drivePow);
    analogWrite(pwm_b, drivePow);
  }
  leftBumped = false;
  rightBumped = false;
//  delay(200);
//  digitalWrite(pwm_a, 0);
//  digitalWrite(pwm_b, 0);
}
