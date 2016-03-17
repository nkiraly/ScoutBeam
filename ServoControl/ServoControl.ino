/*******************************************************
* ServoControl
*
* Listen for serial commands to set servo position
*
* Hardware Notes
* - pin 2: Pan Servo Control  - see servoPinPan
* - pin 3: Tilt Servo Control - see servoPinTilt
* - Supply 9V input to ensure servos have enough power
*/

#include <Servo.h>

// control command strings
String commandSetPan  = "PAN";
String commandSetTilt = "TILT";

// behavior configuration
bool announceActions = true;
bool setupTestMovement = false;

// servo pin out configuration
int servoPinPan  = 2;
int servoPinTilt = 3;

// servo objects
Servo servoPan;
Servo servoTilt;

// serial read variables
String command;
String data;

void setup() {
  // attach servo objects to hardware pins
  servoPan.attach(servoPinPan);
  servoTilt.attach(servoPinTilt);

  // initialize serial connection at 57600
  Serial.begin(57600);

  // if config says so, do test movement loop
  if ( setupTestMovement ) {
    Serial.println("ServoControl Movement Test Starting");
    testMovement(90, 90, 130, 50);
    testMovement(130, 50, 50, 130);
    testMovement(50, 130, 130, 130);
    testMovement(130, 130, 50, 50);
    testMovement(50, 50, 90, 90);
    Serial.println("ServoControl Movement Test Finished");
  }

  // initialize servos at 90 degrees
  servoPan.write(90);
  servoTilt.write(90);

  Serial.println("ServoControl Ready");
}

void testMovement(int startP, int startT, int finishP, int finishT) {
  int currentP = startP;
  int currentT = startT;

  servoPan.write(currentP);
  servoTilt.write(currentT);

  while( currentP != finishP && currentT != finishT ) {
    if ( currentP < finishP ) {
      currentP++;
    }
    if ( currentP > finishP ) {
      currentP--;
    }
    if ( currentT < finishT ) {
      currentT++;
    }
    if ( currentT > finishT ) {
      currentT--;
    }
    servoPan.write(currentP);
    servoTilt.write(currentT);
    delay(50);
  }
  
}

void loop() {
  // Wait for a character on the serial port.
  if ( Serial.available() > 0 ) {

    command = Serial.readStringUntil(',');
    data = Serial.readStringUntil('\n');

    // with command and data read,
    // act on the command
    if ( command == commandSetPan ) {
      if ( announceActions ) {
        Serial.print("Set Pan  to  ");
        Serial.print(data);
        Serial.println();
      }
      servoPan.write(data.toInt());
    }
    if ( command == commandSetTilt ) {
      if ( announceActions ) {
        Serial.print("Set Tilt to  ");
        Serial.print(data);
        Serial.println();
      }
      servoTilt.write(data.toInt());
    }

  }
}


