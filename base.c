#pragma config(Sensor, in1,    clawPot,        sensorPotentiometer)
#pragma config(Sensor, in2,    liftLeftPot,    sensorPotentiometer)
#pragma config(Sensor, in3,    liftRightPot,   sensorPotentiometer)
#pragma config(Sensor, dgtl1,  leftEncoder,    sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  rightEncoder,   sensorQuadEncoder)
#pragma config(Motor,  port1,           flywheelLeft,  tmotorVex393TurboSpeed_HBridge, openLoop)
#pragma config(Motor,  port2,           clawFlip,      tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           driveLeftFront, tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port4,           driveLeftBack, tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port5,           liftBottom,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           liftTop,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           driveRightFront, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           driveRightBack, tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           conveyor,      tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port10,          flywheelRight, tmotorVex393TurboSpeed_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX2)

#pragma competitionControl(Competition)

#include "Vex_Competition_Includes.c"

#include "mapping.c"
#include "utils.c"
#include "atomic.c"
#include "tasks.c"
#include "helpers.c"
#include "controllers.c"

// ---- MAIN CONTROL

void pre_auton() {
	// stop tasks while changing from autonomous to usercontrol
	bStopTasksBetweenModes = true;
}

task autonomous() {
	startAllTasks();
	// 85 is p much max speed since speed is nonlinear, 60 is reasonable speed
	bool isRed = true;
	// practice as if red, then negative of drive angles for blue
	angleMultiplier = isRed ? 1 : -1;
	// false --> starting position closer to flags
	// true --> starting position closer to posts
	bool startNearFlags = false;
	// completely different routines by sides
	if (startNearFlags) {
		// -- shoot ball
		// spin up flywheel for a few seconds
		runFlywheel(2);
		wait(3);
		// shoot
		moveConveyor(127);
		wait(1);
		// stop
		moveConveyor(0);
		stopFlywheel();

		// -- remove bands
		moveLift(100);
		flipClaw();
		waitMS(500);
		flipClaw();
		waitMS(500);
		moveLift(-50);
		waitMS(200);
		moveLift(0);

		// -- flip clap
		driveStraight(80, 40);
		moveLift(100);
		waitMS(500);
		flipClaw();
		moveLift(-50);
		driveStraight(80, -20);

		// -- go on platform
	} else {
		// -- go on platform
		/*wait(1);
		driveStraight(80, 24);
		rotateAngle(90);
		driveStraight(110, 80);*/
	}
	angleMultiplier = 1;
}

task usercontrol() {
	startAllTasks();
	while (true) {
		if (vexRT[Btn8D]) {
			driveStraight(80, 24);
		}
		if (vexRT[Btn8R]) {
			rotateAngle(360);
		}
		if (vexRT[Btn8L]) {
			flipClaw();
		}
		doClaw();
		doDrive();
		doArms();
		doConveyor();
		doFlywheel();
	}
}
