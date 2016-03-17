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

#include <Servo.h>  //Used to control the Pan/Tilt Servos

// control command strings
String commandSetPan  = "PAN";
String commandSetTilt = "TILT";

bool announceActions = true;

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

  // initialize servos at 90 degrees
  servoPan.write(90);
  servoTilt.write(90);

  // initialize serial connection at 57600
  Serial.begin(57600);
  Serial.println("ServoControl Ready");
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


