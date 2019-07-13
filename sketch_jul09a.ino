#include <Stepper.h>


#define STEPS 4096 

#define NUMSTEPS 520

Stepper stepper(STEPS, 4, 5, 6, 7);

// constants won't change. They're used here to set pin numbers:
const int sensor0_pin = 2;     // the number of the sensor0 pin
const int sensor1_pin = 3;     // the number of the sensor1 pin
const int sensor2_pin = 4;     // the number of the sensor2 pin

const int relay0_pin =  11;      // the number of the relay0 pin
const int relay1_pin =  12;      // the number of the relay1 pin
const int relay2_pin =  13;      // the number of the relay2 pin

/* Actuators sensors state */

int sensor0_state = 0;         // variable for reading the sensor0 status
int sensor1_state = 0;         // variable for reading the sensor1 status
int sensor2_state = 0;         // variable for reading the sensor2 status

/* States for controlling actuators moves */

bool cilinderUpState = false;
bool cilinderDownState = false;

bool clawCloseState = false;
bool clawOpenState = false;

bool servo90State = false;
bool servo180State = false;

/* Timers for actuators control */

unsigned long lastTimeCilinderUp = 0;
const long intervalCilinderUp = 3000;

unsigned long lastTimeCilinderDown = 0;
const long intervalCilinderDown = 3000;

unsigned long lastTimeClawOpen = 0;
const long intervalClawOpen = 3000;

unsigned long lastTimeClawClosed = 0;
const long intervalClawClosed = 3000;

unsigned long lastTimeservo90 = 0;
const long intervalServo90 = 3000;



unsigned long lastTimeWaitPrint = 0;
const long intervalPrint = 3000;

/* Log messages */

const char *cilinderUpLog = { "Getting cilinder up\n"};
const char *cilinderDownLog = { "Getting cilinder down\n"};
const char *clawOpenLog = { "Opening claw\n"};
const char *clawCloseLog = { "Closing claw\n"};
const char *waitPrintLog = { "Waiting for print\n"};


void setup() {

  stepper.setSpeed(5);

  Serial.begin(9600);
  
  pinMode(relay0_pin, OUTPUT);

  pinMode(sensor0_pin, INPUT);
}

void loop() {
  
  // read the state of the pushbutton value:
  sensor0_state = digitalRead(sensor0_pin);

  mainPrintSequence();
  
  /*
  if (sensor0_state == HIGH) {
     digitalWrite(relay0_pin, HIGH);
  } else {
     digitalWrite(relay0_pin, LOW);
  }
  */
}

void mainPrintSequence()
{  
  unsigned long currentMillis = millis();  
  lastTimeCilinderUp = millis();
  
  while(currentMillis -lastTimeCilinderUp < intervalCilinderUp)
  {
    Serial.print(cilinderUpLog);
    digitalWrite(relay0_pin, HIGH);
    currentMillis = millis();
  }
  
  currentMillis = millis();
  lastTimeClawClosed = millis();
  
  while(currentMillis - lastTimeClawClosed < intervalClawClosed)
  {
    Serial.print(clawCloseLog);
    digitalWrite(relay0_pin, HIGH);
    currentMillis = millis();
  }

  currentMillis = millis();
  lastTimeWaitPrint = millis();

  while(currentMillis - lastTimeWaitPrint < intervalPrint)
  {
    Serial.print(waitPrintLog);
    currentMillis = millis();
  }

    stepper.step(NUMSTEPS);


  
}
