/*
 * Initializing sensors
 */

#define MOTOR_A_1A 9 // right
#define MOTOR_A_1B 10 // right
#define MOTOR_B_1A 5 // left
#define MOTOR_B_1B 6 // left
//#include <NewPing.h>

// Speed of the wheels to drive straight
int rSpeed = 125; //135
int lSpeed = 160; //170

int left_sen = A0; // A = left
int center_sen = A1; // B = center
int right_sen = A2; // C = right
int ValSens_A = 0;
int ValSens_B = 0;
int ValSens_C = 0;
/*
//FRONT SENSOR
#define TRIGGER_FRONT 3
#define ECHO_FRONT 4

//LEFT SENSOR
#define TRIGGER_LEFT 12
#define ECHO_LEFT 13
#define MAX_DISTANCE 200

NewPing leftsonar(TRIGGER_LEFT, ECHO_LEFT, MAX_DISTANCE);
NewPing frontsonar(TRIGGER_FRONT, ECHO_FRONT, MAX_DISTANCE);
*/
#define LEFTTHRESHOLD 20
#define FRONTTHRESHOLD 20

#define centerThres 100
#define leftThres 95
#define rightThres 80

void setup() {

   pinMode(left_sen, INPUT);
   pinMode(center_sen, INPUT);
   pinMode(right_sen, INPUT);

   pinMode(MOTOR_A_1A, OUTPUT);
   pinMode(MOTOR_A_1B, OUTPUT);
   pinMode(MOTOR_B_1A, OUTPUT);
   pinMode(MOTOR_B_1B, OUTPUT);

   Serial.begin(9600); 
}

void loop(){  
  photoDebug();
  photoMovement();
}

void backupRight(){
  left();
  delay(100);
  back();
}

void photoDebug(){
  int valLeft = analogRead(left_sen);
  int valMid = analogRead(center_sen);
  int valRight = analogRead(right_sen);
  int left = (valLeft > leftThres) ? 0 : 1; //1 is black, 0 is white
  int mid = (valMid > centerThres) ? 0 : 1;
  int right = (valRight > rightThres) ? 0 : 1;
  Serial.print("left: ");
   Serial.print(valLeft);
   Serial.print("  mid: ");
   Serial.print(valMid);
   Serial.print("  right: ");
   Serial.print(valRight);
   Serial.print("  l: ");
   Serial.print(left);
   Serial.print("  m: ");
   Serial.print(mid);
   Serial.print("  r: ");
   Serial.println(right);
}
void photoMovement(){
  int valLeft = analogRead(left_sen);
  int valMid = analogRead(center_sen);
  int valRight = analogRead(right_sen);
  bool mid = valMid > centerThres;
  bool leftB = valLeft > leftThres;
  bool rightB = valRight > rightThres;
  if(mid && leftB && rightB){
      Serial.print("  back ");
     back();
     delay(100);
  }else if(leftB){
    Serial.print("  turn right ");
    right();
    delay(100);
  }else if(rightB){
    Serial.print("  turn left ");
    left();
    delay(100);
  }else{
    Serial.print("  forward ");
    forward();
    delay(100);
  }
  stop();
  delay(50); 
}
/*
void sonarDebug(){
  unsigned int ldistance = leftsonar.ping_cm();
  unsigned int fdistance = frontsonar.ping_cm();
  Serial.print("left: ");
   Serial.print(ldistance);
   Serial.print("cm, front: ");
   Serial.print(fdistance);
   Serial.println("cm");

}

// 
void sonarMovement(){
   unsigned int ldistance = leftsonar.ping_cm();
   unsigned int fdistance = frontsonar.ping_cm();
   if(fdistance < 15){
    if(ldistance < 25){ //wall on the left side
      back();
      delay(1000);
      left();
      delay(1000);
    }else{              //no wall on the left side
      back();
      delay(1000);
      right();
      delay(1000);
    }
  }else{
    if(ldistance > 30){
        right();
        delay(1000);
        forward();
        delay(1000);
    }else{
       forward();
       delay(1000);
    }
  }
  stop();
  delay(500);
}
*/
void back() {
          //LEFT MOTOR
          analogWrite(MOTOR_A_1A, rSpeed);
          analogWrite(MOTOR_A_1B, 0);
          //RIGHT MOTOR
          analogWrite(MOTOR_B_1A, lSpeed);
          analogWrite(MOTOR_B_1B, 0);
}
void forward() {
          //LEFT MOTOR
          analogWrite(MOTOR_A_1A, 0);
          analogWrite(MOTOR_A_1B, rSpeed);
          //RIGHT MOTOR
          analogWrite(MOTOR_B_1A, 0);
          analogWrite(MOTOR_B_1B, lSpeed);
}
void left() {
          //LEFT MOTOR
          analogWrite(MOTOR_A_1A, 0);
          analogWrite(MOTOR_A_1B, rSpeed);
          //RIGHT MOTOR
          analogWrite(MOTOR_B_1A, lSpeed);
          analogWrite(MOTOR_B_1B, 0);
}
void right() {
          //LEFT MOTOR
          analogWrite(MOTOR_A_1A, rSpeed);
          analogWrite(MOTOR_A_1B, 0);
          //RIGHT MOTOR
          analogWrite(MOTOR_B_1A, 0);
          analogWrite(MOTOR_B_1B, lSpeed);
}
void stop() {
          //LEFT MOTOR
          analogWrite(MOTOR_A_1A, 0);
          analogWrite(MOTOR_A_1B, 0);
          //RIGHT MOTOR
          analogWrite(MOTOR_B_1A, 0);
          analogWrite(MOTOR_B_1B, 0);
}
