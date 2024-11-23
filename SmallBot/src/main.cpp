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

// A global instance of competition
competition Competition;

// A global instance of the controller
controller Controller1;

// Delcare the brain variable 
brain Brain;

// Left Motor
motor leftMotorFront = motor(PORT9, ratio18_1, true);
motor leftMotorBack = motor(PORT10, ratio18_1, true);

// Right Motors
motor rightMotorFront = motor(PORT11, ratio18_1, true);
motor rightMotorBack = motor(PORT12, ratio18_1, true);

// ============= Motor Groups ===============
motor_group leftDrive(leftMotorFront, leftMotorBack);
motor_group rightDrive(rightMotorFront, rightMotorBack);

// ============= Drivetrain ===============
drivetrain Drivetrain = drivetrain(leftDrive, rightDrive, 319.19, 320, 320, mm, 1);



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
  //Motor11.setVelocity(50, percent); // Set initial velocity to 50%
  //Motor11.setStopping(brake);       // Set stopping mode to brake
  
  
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
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
  //Brain.Screen.clearScreen();
  //Brain.Screen.print("Autonomous Running....");


  //Motor11.spin(forward);


  
  
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
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ================= Joystick Values =================
    double driveJoy = Controller1.Axis4.position();
    double turnJoy = Controller1.Axis2.position();

    // =================== Drive Code ====================
    leftDrive.spin(forward, driveJoy + turnJoy, percent);
    rightDrive.spin(forward, driveJoy - turnJoy, percent);
  
    
    

    


    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
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
