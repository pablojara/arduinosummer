#include <Stepper.h>

#define STEPS 4096 

#define 90STEPS 520

#define 180STEPS 1040

Stepper stepper(STEPS, 4, 5, 6, 7);

// constants won't change. They're used here to set pin numbers:
const int sensor0_pin = 2;     // the number of the sensor0 cilinder pin
const int sensor1_pin = 3;     // the number of the sensor1 claw pin
const int sensor2_pin = 4;     // the number of the sensor2 base pin

const int relay0_pin =  11;      // the number of the relay0 pin
const int relay1_pin =  12;      // the number of the relay1 pin
const int relay2_pin =  13;      // the number of the relay2 pin

/* Actuators sensors state */

int sensor0_state = 0;         // variable for reading the sensor0 cilinder status
int sensor1_state = 0;         // variable for reading the sensor1 claw status
int sensor2_state = 0;         // variable for reading the sensor2 base status

/* States for controlling actuators moves */

bool cilinderUpState = false;
bool cilinderDownState = false;

bool clawCloseState = false;
bool clawOpenState = false;

bool baseRotateState = false;
bool baseRotateState = true;

/* Timers for actuators control */

unsigned long lastTimeCilinderUp = 0;
const long intervalCilinderUp = 3000;

unsigned long lastTimeCilinderDown = 0;
const long intervalCilinderDown = 3000;

unsigned long lastTimeClawOpen = 0;
const long intervalClawOpen = 3000;

unsigned long lastTimeClawClosed = 0;
const long intervalClawClosed = 3000;

unsigned long lastTimeBaseRotateForward = 0;
const long intervalBaseRotateForward = 3000;

unsigned long lastTimeBaseRotateBackward = 0;
const long intervalBaseRotateBackward = 3000;

unsigned long lastTimeWaitPrint = 0;
const long intervalPrint = 3000;

/* Log messages */

const char *cilinderUpLog = { "Getting cilinder up\n"};
const char *cilinderDownLog = { "Getting cilinder down\n"};
const char *clawOpenLog = { "Opening claw\n"};
const char *clawCloseLog = { "Closing claw\n"};
const char *rotateBaseForwardLog = { "Rotating base forwards\n"};
const char *rotateBaseBackwardLog = { "Rotating base backwards\n"};
const char *waitPrintLog = { "Waiting for print\n"};


void setup() {

  stepper.setSpeed(5);

  Serial.begin(9600);
  
  pinMode(relay0_pin, OUTPUT);

  pinMode(sensor0_pin, INPUT);
}

void loop() {
  
  mainPrintSequence();
  lastPrintSequence();

}

void mainPrintSequence()
{  
  unsigned long currentMillis = millis();  
  lastTimeCilinderUp = millis();

  /* Cilinder up */
  while(currentMillis -lastTimeCilinderUp < intervalCilinderUp)
  {
    Serial.print(cilinderUpLog);
    digitalWrite(relay0_pin, HIGH);
    currentMillis = millis();
  }
  

  currentMillis = millis();
  lastTimeClawClosed = millis();

  /* Claw close */
  while(currentMillis - lastTimeClawClosed < intervalClawClosed)
  {
    Serial.print(clawCloseLog);
    digitalWrite(relay0_pin, HIGH);
    digitalWrite(relay1_pin, HIGH);
    currentMillis = millis();
  }

  for(int i = 0; i < 4; i++)
  { 
    currentMillis = millis();
    lastTimeWaitPrint = millis();
  
    /* Wait print */ 
    while(currentMillis - lastTimeWaitPrint < intervalPrint)
    {
      Serial.print(waitPrintLog);
      currentMillis = millis();
    }
  
    currentMillis = millis();
    lasTimeCilinderDown = millis();
  
    /* Cilnder down */
    while(currentMillis -lastTimeCilinderDown < intervalCilinderDown)
    {
      Serial.print(cilinderDownLog);
      digitalWrite(relay0_pin, LOW);
      currentMillis = millis();
    }
  
    /* Turn 90º */
    stepper.step(90STEPS);
  
    currentMillis = millis();
    lastTimeCilinderUp = millis();
     
    /* Cilinder up */
    while(currentMillis -lastTimeCilinderUp < intervalCilinderUp)
    {
      Serial.print(cilinderUpLog);
      digitalWrite(relay0_pin, HIGH);
      currentMillis = millis();
    }
  }

  currentMillis = millis();
  lastTimeClawClosed = millis();

  /* Claw open */
  while(currentMillis - lastTimeClawOpen < intervalClawOpen)
  {
    Serial.print(clawOpenLog);
    digitalWrite(relay0_pin, HIGH);
    digitalWrite(relay1_pin, LOW);
    currentMillis = millis();
  }

  currentMillis = millis();
  lasTimeCilinderDown = millis();
  
  /* Cilnder down */
  while(currentMillis -lastTimeCilinderDown < intervalCilinderDown)
  {
    Serial.print(cilinderDownLog);
    digitalWrite(relay0_pin, LOW);
    currentMillis = millis();
  }
  
}

void lastPrintSequence()
{
  unsigned long currentMillis = millis();  
  lastTimeBaseRotateForward = millis();

  /* Rotate base forwards 90º */
  while(currentMillis - lastTimeBaseRotateForward < intervalBaseRotateForward)
  {
    Serial.print(cilinderUpLog);
    digitalWrite(relay0_pin, HIGH);
    currentMillis = millis();
  }

  currentMillis = millis();
  lastTimeCilinderUp = millis();
     
  /* Cilinder up */
  while(currentMillis -lastTimeCilinderUp < intervalCilinderUp)
  {
    Serial.print(cilinderUpLog);
    digitalWrite(relay0_pin, HIGH);
    currentMillis = millis();
  }

  currentMillis = millis();
  lastTimeClawClosed = millis();

  /* Claw close */
  while(currentMillis - lastTimeClawClosed < intervalClawClosed)
  {
    Serial.print(clawCloseLog);
    digitalWrite(relay0_pin, HIGH);
    digitalWrite(relay1_pin, HIGH);
    currentMillis = millis();
  }

  currentMillis = millis();
  lasTimeCilinderDown = millis();

  /* Cilnder down */
  while(currentMillis -lastTimeCilinderDown < intervalCilinderDown)
  {
    Serial.print(cilinderDownLog);
    digitalWrite(relay0_pin, LOW);
    currentMillis = millis();
  }

  /* Turn 90º */
  stepper.step(90STEPS);

  currentMillis = millis();
  lastTimeCilinderUp = millis();
     
  /* Cilinder up */
  while(currentMillis -lastTimeCilinderUp < intervalCilinderUp)
  {
    Serial.print(cilinderUpLog);
    digitalWrite(relay0_pin, HIGH);
    currentMillis = millis();
  }
  

  currentMillis = millis();
  lastTimeWaitPrint = millis();

  /* Wait print */ 
  while(currentMillis - lastTimeWaitPrint < intervalPrint)
  {
    Serial.print(waitPrintLog);
    currentMillis = millis();
  }

  currentMillis = millis();
  lasTimeCilinderDown = millis();

  /* Cilnder down */
  while(currentMillis -lastTimeCilinderDown < intervalCilinderDown)
  {
    Serial.print(cilinderDownLog);
    digitalWrite(relay0_pin, LOW);
    currentMillis = millis();
  }

  /* Turn 180º */
  stepper.step(180STEPS);

  currentMillis = millis();
  lastTimeCilinderUp = millis();
     
  /* Cilinder up */
  while(currentMillis -lastTimeCilinderUp < intervalCilinderUp)
  {
    Serial.print(cilinderUpLog);
    digitalWrite(relay0_pin, HIGH);
    currentMillis = millis();
  }

  currentMillis = millis();
  lastTimeWaitPrint = millis();

  /* Wait print */ 
  while(currentMillis - lastTimeWaitPrint < intervalPrint)
  {
    Serial.print(waitPrintLog);
    currentMillis = millis();
  }

  currentMillis = millis();
  lastTimeClawOpen = millis();

  /* Claw open */
  while(currentMillis - lastTimeClawOpen < intervalClawOpen)
  {
    Serial.print(clawOpenLog);
    digitalWrite(relay0_pin, HIGH);
    digitalWrite(relay1_pin, LOW);
    currentMillis = millis();
  }

  currentMillis = millis();
  lasTimeCilinderDown = millis();
  
  /* Cilnder down */
  while(currentMillis -lastTimeCilinderDown < intervalCilinderDown)
  {
    Serial.print(cilinderDownLog);
    digitalWrite(relay0_pin, LOW);
    currentMillis = millis();
  }
    
}
