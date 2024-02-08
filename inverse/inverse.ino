// Include the Servo library 
#include <Servo.h> 
double l1=39;
double l2=39;
int a;
int c;
// Declare the Servo pin 
int servoPin1 = 3; 
int servoPin2 = 5; 
int servoPinB = 4; 
// Create a servo object 
Servo Servo1;
Servo Servo2;
Servo ServoB; 
void setup() { 
 
   Serial.begin(9600);
  Serial.setTimeout(999999);
   Servo1.attach(servoPin1);
   Servo2.attach(servoPin2);
   ServoB.attach(servoPinB); 
   Servo1.write(55);
  Servo2.write(55);
  ServoB.write(90);
}
int area(double s1, double s2, double s3){
  int sem = (s1+s2+s3)/2;
  return sqrt(sem*(sem-s1)*(sem-s2)*(sem-s3)); // area by heron's formula
}
void movToPos(int x, int y, int z){
  double b = atan(double(y)/double(x))*(180/3.1415);// angle for base servo
  double l = sqrt(x*x + y*y);
  double d = sqrt(l*l + z*z);
  double h = area(l1,l2,d)*2/d;
  double phi = atan(z/l)*(180/3.1415);
  double theta = asin(h/l1) *(180/3.1415);
  double delta = asin(h/l2) *(180/3.1415);

  double a1 = theta + phi;//}
  double a2 = theta + delta;  // angle for upper servo
  movToAngle(b,a1,a2);
}
void movToAngle(double b, double a1, double a2){
  Servo1.write(int(95 - a1));
  Servo2.write(int(180-a2));
  ServoB.write(90 - int(b));
  Serial.print("angle1 = ");
  Serial.println(int(95 - a1));
  Serial.print("angle2 = ");
  Serial.println(int(180-a2));
  Serial.print("b = ");
  Serial.println(90 - int(b));
   
}
int x=-1,y=-1,z=1;
void loop(){ 
  if(Serial.available()>0){
    while(x==-1)
    {
   x = Serial.parseInt();
   }
  Serial.println(x);
  while(y==-1&&x!=-1&&z==1){
    if(Serial.available()>0){
   y = Serial.parseInt();}}
  Serial.println(y);
  while(z==1&&y!=-1&&x!=-1){
    if(Serial.available()>0){
  z = Serial.parseInt();}}
  Serial.println(z);
  if(x!=-1&&y!=-1&&z!=1){
  movToPos(x,y,z);}
  x=-1,y=-1,z=1;
  }
  

}