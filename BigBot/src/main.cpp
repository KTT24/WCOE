/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       kutterthornton                                            */
/*    Created:      10/27/2024, 2:37:42 PM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// ================== Other Delcarations ==================

// A global instance of competition
competition Competition;

// A global instance of the controller
controller Controller2;

// Delcare the brain variable 
brain Brain;

// Decalre the pneumatic variable digtial out 
digital_out pneumatic = digital_out(Brain.ThreeWirePort.B);

// ================== Declare the motors ==================

// Right motors
motor leftMotorFront = motor(PORT8, ratio18_1, true);
motor leftMotorMiddle = motor(PORT9, ratio18_1, true);
motor leftMotorBack = motor(PORT10, ratio18_1, true);

// Left motors
motor rightMotorFront = motor(PORT1, ratio18_1, false);
motor rightMotorMiddle = motor(PORT2, ratio18_1, false);
motor rightMotorBack = motor(PORT3, ratio18_1, false);

// Motor group for the left and right motors
motor_group leftMotors = motor_group(leftMotorFront, leftMotorMiddle, leftMotorBack);
motor_group rightMotors = motor_group(rightMotorFront, rightMotorMiddle, rightMotorBack);

// Intake and belt motors
motor intakeMotor = motor(PORT11, ratio18_1, true);
motor beltMotor = motor(PORT12, ratio18_1, true);

// Drive train
drivetrain Drivetrain = drivetrain(leftMotors, rightMotors, 319.19, 295, 295, mm, 1);


// ============== Custom Methods ==============


// Intake system method
void intake(int time) {
  int totalTime = time + 0.75;
  intakeMotor.spin(fwd, 100, percent);
  wait(0.75, sec);
  beltMotor.spin(fwd, 100, percent);
  wait(totalTime, sec);
  beltMotor.stop();
  intakeMotor.stop();
}

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  // Set up motors
  intakeMotor.setVelocity(100, percent);
  beltMotor.setVelocity(90, percent);

  Drivetrain.setDriveVelocity(100, percent);
  Drivetrain.setStopping(brake);


  


  // Set the stopping mode for the motors
  beltMotor.setStopping(hold);
  intakeMotor.setStopping(brake);
  
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // PRint to the brian screen that Autonomous is running
  Brain.Screen.clearScreen();
  Brain.Screen.print("Autonomous Period is active");

  if (Competition.isAutonomous()) {
    Drivetrain.driveFor(-6, inches, true);
    pneumatic.set(true);
    beltMotor.spin(fwd, 100, percent);
  }


  // Drivetrain.turnFor(10, degrees);
  // Drivetrain.driveFor(-27, inches, true);
  // wait(0.125, sec);
  // pneumatic.set(true);
  // Drivetrain.driveFor(23, inches, true);



  // Gets bottom donut 
  // intakeMotor.spin(fwd);
  // Drivetrain.driveFor(-10, inches, true);
  // wait(0.125, sec);
  // beltMotor.spin(fwd, 50, percent);
  // intakeMotor.stop();



  // Move the robot forward for 2 seconds
  

  
  // wait(1, sec);
  
  // Turn the robot right for 1 second
  // Drivetrain.turnFor(90, degrees);

  
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop

  // Set the stopping mode for the motors
  beltMotor.setStopping(hold);
  intakeMotor.setStopping(brake);

  while (1) {

    // Brian screen print
    Brain.Screen.clearScreen();
    Brain.Screen.print("User Control Period is active");

    // Get the velocity of the left and right motors
    int forward = Controller2.Axis3.position();
    int turn = Controller2.Axis1.position();

    // Speed values for the left and right motors
    int leftSpeed = forward + turn;
    int rightSpeed = forward - turn;

    // Set the speed of the left and right motors
    leftMotorFront.spin(fwd, leftSpeed, percent);
    leftMotorMiddle.spin(fwd, leftSpeed, percent);
    leftMotorBack.spin(fwd, leftSpeed, percent);

    rightMotorFront.spin(fwd, rightSpeed, percent);
    rightMotorMiddle.spin(fwd, rightSpeed, percent);
    rightMotorBack.spin(fwd, rightSpeed, percent);

    // Intake and belt control
    if (Controller2.ButtonR1.pressing()) {
      beltMotor.spin(fwd, 100, percent);
    } else if (Controller2.ButtonR2.pressing()) {
      beltMotor.spin(reverse, 100, percent);
    } else {
      beltMotor.stop();
    }

    if (Controller2.ButtonL1.pressing()) {
      intakeMotor.spin(fwd, 100, percent);
    } else if (Controller2.ButtonL2.pressing()) {
      intakeMotor.spin(reverse, 100, percent);
    } else {
      intakeMotor.stop();
    }

    // Pneumatic control
    if (Controller2.ButtonA.pressing()) {
      pneumatic.set(true);
    } else if (Controller2.ButtonB.pressing()) {
      pneumatic.set(false);
    }

    // Add a short delay to prevent overwhelming the CPU
    vex::task::sleep(20);
  }
}

// Main will set up the competition functions and callbacks.
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
