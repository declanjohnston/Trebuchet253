#include <phys253.h>
#include <LiquidCrystal.h>
#include <PID.h>
#include <State.h>
#include <initialize.h>
#include <Bounce2.h>




int state;
int lstate;
bool left;
bool right;
int timer;
int encoderCount = 0;
bool flag;
int hashCount = 0;
int count;
Bounce BounceLiftUp = Bounce();
Bounce BounceLiftDown = Bounce();
Bounce BounceSwitchZipline = Bounce();
Bounce BounceEncoder = Bounce();

PID pid=PID(motor);
State pos=State(QRD_LEFT, QRD_RIGHT,THRESH_QRD, QRD_CIRCLE_LEFT);
State circle=State(QRD_CIRCLE_LEFT, QRD_CIRCLE_RIGHT, THRESH_QRD, QRD_RIGHT);

void setup()
{
#include <phys253setup.txt>
  Serial.begin(9600) ;
  initPins();
  // remember to initialize values
  // derivative, integral, proportional,gain, speed
  pid.init(20,0,35,1,255, MOTOR_LEFT, MOTOR_RIGHT);
  BounceLiftUp.interval(3);
  BounceLiftUp.attach(SWITCH_LIFTUP);
  BounceLiftDown.interval(3);
  BounceLiftDown.attach(SWITCH_LIFTDOWN);
  BounceSwitchZipline.interval(3);
  BounceSwitchZipline.attach(SWITCH_ZIPLINE);
  BounceEncoder.interval(3);
  BounceEncoder.attach(ENCODER_LIFTPIN);
}
void loop() {
 flag = false;
 digitalWrite(MOTOR_LIFT_DIRECTION, HIGH);
 digitalWrite(MOTOR_LIFT_ON, HIGH);
 BounceLiftUp.update();
 while(!BounceLiftUp.read()){
  BounceLiftUp.update();
 }

 digitalWrite(MOTOR_LIFT_ON, LOW);

 encoderCount = 0;
 digitalWrite(MOTOR_LIFT_DIRECTION, LOW);
 digitalWrite(MOTOR_LIFT_ON, HIGH);
 BounceLiftDown.attach(SWITCH_LIFTDOWN);
 BounceLiftDown.update();
 while(encoderCount < ENCODER_LOWERARM && !BounceLiftDown.read()){
    BounceEncoder.update();
    if(BounceEncoder.rose()){
      encoderCount++;
      LCD.clear();
      LCD.print(encoderCount);
    }
    BounceLiftDown.update();
 }
 digitalWrite(MOTOR_LIFT_ON, LOW);
 exit(0);
}
