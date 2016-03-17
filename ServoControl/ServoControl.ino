/*******************************************************
* ServoControl
*
* Listen for serial commands to set servo position
*
* Hardware Notes
* - pin 2: Tilt Servo Control - see servoPinTilt
* - pin 3: Pan Servo Control  - see servoPinPan
* - Supply 9V input to ensure servos have enough power
*/

#include <Servo.h>  //Used to control the Pan/Tilt Servos

// control command strings
String commandSetTilt = "TILT";
String commandSetPan  = "PAN";

bool announceActions = true;

// servo pin out configuration
int servoPinTilt = 2;
int servoPinPan  = 3;

// servo objects
Servo servoTilt;
Servo servoPan;

// serial read variables
String command;
String data;

void setup() {
  // attach servo objects to hardware pins
  servoTilt.attach(servoPinTilt);
  servoPan.attach(servoPinPan);

  // initialize servos at 90 degrees
  servoTilt.write(90);
  servoPan.write(90);

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
    if ( command == commandSetTilt ) {
      if ( announceActions ) {
        Serial.print("Set Tilt to  ");
        Serial.print(data);
        Serial.println();
      }
      // char data at index 0 - 48 = numeric degrees to set servo to
      servoTilt.write(data.toInt());
    }
    if ( command == commandSetPan ) {
      if ( announceActions ) {
        Serial.print("Set Pan  to  ");
        Serial.print(data);
        Serial.println();
      }
      servoPan.write(data.toInt());
    }

  }
}


