#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, dgtl1,  sonarIn,        sensorSONAR_mm)
#pragma config(Sensor, dgtl3,  relayWizard,    sensorNone)
#pragma config(Sensor, dgtl4,  relayPara,      sensorNone)
#pragma config(Sensor, dgtl5,  leftAir,        sensorDigitalOut)
#pragma config(Sensor, dgtl6,  rightAir,       sensorDigitalOut)
#pragma config(Sensor, dgtl7,  switchOne,      sensorDigitalIn)
#pragma config(Sensor, dgtl8,  switchTwo,      sensorDigitalIn)
#pragma config(Sensor, dgtl9,  switchThree,    sensorDigitalIn)
#pragma config(Sensor, dgtl10, switchFree,     sensorDigitalIn)
#pragma config(Sensor, I2C_1,  rightFlapy,     sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  leftFlapy,      sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           ledDome,       tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           leftChest,     tmotorServoStandard, openLoop)
#pragma config(Motor,  port3,           leftFlap,      tmotorVex393_MC29, PIDControl, encoderPort, I2C_1)
#pragma config(Motor,  port4,           servoNeck,     tmotorServoStandard, openLoop)
#pragma config(Motor,  port5,           skitOne,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           skitTwo,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           skitThree,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           rightFlap,     tmotorVex393_MC29, PIDControl, reversed, encoderPort, I2C_2)
#pragma config(Motor,  port9,           rightChest,    tmotorServoStandard, openLoop)
#pragma config(Motor,  port10,          ledLogic,      tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

void lightsFade()
{
		if(SensorValue[switchOne]==1 && SensorValue[switchTwo]==1 && SensorValue[switchThree]==1) // If a button is pressed while in mid skit, the skit will stop
		{
		/*
			fade all lights through all colors slowly then revert into light blue
		*/
		}
		else
		{
			wait(.25);
		}
			wait(.25);
}

void lightsFlash()
{
		if(SensorValue[switchOne]==1 && SensorValue[switchTwo]==1 && SensorValue[switchThree]==1)
		{
			/*
				begin flashing all lights
				wait 2 seconds
				stop flashing and remain on blue
			*/
		}
		else
		{
			wait(.25);
		}
	wait(.25);
}


task neckMovement()
{
	int i = 0;
	while(SensorValue[switchOne]==1 && SensorValue[switchTwo]==1 && SensorValue[switchThree]==1)
	{
			int maxrandom1 = random[180];

			int randomPause = random[1];
			int randomPausePosition = random[maxrandom1];

			for(i = i; i<maxrandom1;i++ )
			{
						if(randomPause == 0){
							if(i == randomPausePosition)
								wait(3);
						}
						motor(servoNeck) = i++;
						wait10Msec(7);
			}

			wait(2 + random(5));

			int a = i;
			int maxrandom2 = -(random[180] + maxrandom1);
			randomPause = random[1];
			randomPausePosition = -random[-maxrandom2];

			for(a = i; a>maxrandom2;a--)
			{
				if(randomPause == 0){
							if(a == randomPausePosition)
								wait(3);
						}
				motor(servoNeck) = a--;
				wait10Msec(7);
			}

			i = a;
			wait(2 + random[5]);
	}

		wait(.25);
}

void torsoUp()
{

		if(SensorValue[switchOne]==1 && SensorValue[switchTwo]==1 && SensorValue[switchThree]==1)
		{
		SensorValue(leftAir) = 1;													// Extends the pneumatics

		}
}

void torsoDown()
{
		if(SensorValue[switchOne]==1 && SensorValue[switchTwo]==1 && SensorValue[switchThree]==1)
		{
			SensorValue(leftAir) = 0;													// Extends the pneumatics

		}
}

void wingExtendBoth()
{
	int degrees = 282;
	float ticks = (627.2/360.0) * degrees;
	nMotorEncoder[leftFlap] = 0;
		if(SensorValue[switchOne]==1 && SensorValue[switchTwo]==1 && SensorValue[switchThree]==1)
		{
		/*
			Set both wing mototrs to half power until wings are fully retracted
			Wait 2 seconds
			Set both motors to half power in reverse direction until wings are fully extended
		*/

		while(nMotorEncoder[leftFlap] < ticks){
		motor(leftFlap) = 25;
		}
		motor(leftFlap) = 0;

			wait(random(5));

			while(nMotorEncoder[leftFlap] > 0 ){
				motor(leftFlap) = -20;
			}
			motor(leftFlap) = 0;

	}

		wait(.25);
}

void dailyLife()
{
	int i = 0;
	if(SensorValue[switchOne]==1 && SensorValue[switchTwo]==1 && SensorValue[switchThree]==1)
		{
			while(SensorValue[switchOne]==1 && SensorValue[switchTwo]==1 && SensorValue[switchThree]==1 && i==0)
				{
			lightsFade(); 						//Fade Lights
			wait(3);									//Wait 3 seconds
			motor[skitOne]=127;				//play dailyLife skit
			wait(.5);									//Wait half a second
			motor[skitOne]=0;					//Turn off motor
			startTask(neckMovement); 	//Play Neck Movement
			lightsFlash();						//Flash Lights

			wingExtendBoth();					//Flap wings
			wait(1);
			torsoUp();								//bring torso up
			wait(1);
			torsoDown();							//torso down
			wait(100);

			i++;													//reapeat in random order until end of skit (use timing)
				}
			wait(5);
			stopTask(neckMovement);//wait 5 seconds
		}
		stopTask(neckMovement);
	wait(.25);
}

void extinction()
{
	int i = 0;
		if(SensorValue[switchOne]==1 && SensorValue[switchTwo]==1 && SensorValue[switchThree]==1)
		{
			while(SensorValue[switchOne]==1 && SensorValue[switchTwo]==1 && SensorValue[switchThree]==1 && i==0)
				{
			lightsFade(); 						//Fade Lights
			wait(3);									//Wait 3 seconds
			motor[skitTwo]=127;				//play extinction skit
			wait(.5);									//Wait half a second
			motor[skitTwo]=0;					//Turn off motor
			startTask(neckMovement); 					//Play Neck Movement
			lightsFlash();						//Flash Lights

			wingExtendBoth(); 							//Flap wings
			torsoUp();								//bring torso up
			wingExtendBoth();								//Flap Wings
			torsoDown();							//torso down
			wait(5);
			stopTask(neckMovement);
			i++;													//reapeat in random order until end of skit (use timing)
				}
			wait(5);									//wait 5 seconds
		}
	wait(.25);
}

void jurassicPeriod()
{
	int i = 0;
	if(SensorValue[switchOne]==1 && SensorValue[switchTwo]==1 && SensorValue[switchThree]==1)
		{
			while(SensorValue[switchOne]==1 && SensorValue[switchTwo]==1 && SensorValue[switchThree]==1 && i==0)
				{
			lightsFade(); 						//Fade Lights
			wait(3);									//Wait 3 seconds
			motor[skitThree]=127;			//play jurassicPeriod skit
			wait(.5);									//Wait half a second
			motor[skitThree]=0;				//Turn off motor
			startTask(neckMovement); 					//Play Neck Movement
			lightsFlash();						//Flash Lights

			wingExtendBoth();								//Flap Wings
			torsoUp();								//bring torso up
			wingExtendBoth();								//Flap Wings
			torsoDown();							//torso down
			wait(5);
			stopTask(neckMovement);
			i++;
		}													//reapeat in random order until end of skit (use timing)
																	//
			wait(5);									//wait 5 seconds
		}
	wait(.25);
}

void selection()
{
	while (1==1)
	{
		/*
			If Daily Life button is pressed play daily life class
			If Extinction is pressed play Extinction class
			If Jurasic Period is pressed play Jurasic Period class
		*/
			if (SensorValue[switchOne] == 0)
		  {
				wait(4);
				dailyLife();
				wait(1);
			}
				else
			{
				wait1Msec(1);
			}
			if (SensorValue[switchTwo] == 0)
			{
				wait(4);
				extinction();
				wait(1);
			}
				else
			{
				wait1Msec(1);
			}
			if (SensorValue[switchThree] == 0)
			{
				wait(4);
				jurassicPeriod();
				wait(1);
			}
			else
			{
				wait1Msec(1);
			}
		}
}


task main()
{
//* Code block to start entire program
	while (1==1)
		{
			if (SensorValue[sonarIn] >= 0 && SensorValue[sonarIn] <= 500)						//Sonar values before playing skit
			{
				selection ();
			}
		}


}
