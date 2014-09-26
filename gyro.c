void turnCounterClockwise(int degrees)
{
	float rotSpeed = 0;
  float heading = 0;

  HTGYROstartCal(gyro);

  wait1Msec(250);

	time1[T2] = 0;

	while(heading < degrees) //gyro is upside down
  {
    while (time1[T2] < 25)
    {
      wait1Msec(1);
    }

    time1[T2]=0;

    rotSpeed = HTGYROreadRot(gyro);
    heading += rotSpeed * 0.025;

    nxtDisplayCenteredBigTextLine(3, "%2.0f", heading);

  	motor[rightMotor] = turnSpeed;
  	motor[leftMotor] = -1*turnSpeed;
  }
  motor[rightMotor] = 0;
  motor[leftMotor] = 0;
}

void turnClockwise(int degrees)
{
	float rotSpeed = 0;
  float heading = 0;

  HTGYROstartCal(gyro);

  wait1Msec(250);

	time1[T2] = 0;

	while(heading > -1*degrees) //gyro is upside down
  {
    while (time1[T2] < 25)
    {
      wait1Msec(1);
    }

    time1[T2]=0;

    rotSpeed = HTGYROreadRot(gyro);
    heading += rotSpeed * 0.025;

    nxtDisplayCenteredBigTextLine(3, "%2.0f", heading);

  	motor[rightMotor] = -1*turnSpeed;
  	motor[leftMotor] = turnSpeed;
  }
  motor[rightMotor] = 0;
  motor[leftMotor] = 0;
}

void driveWithEncoders(int rightSpeed, int leftSpeed, int value)
{
	nMotorEncoder[rightMotor] = 0;
	if(value > 0)
	{
  	while(nMotorEncoder[rightMotor] < value)
  	{
    	motor[rightMotor] = rightSpeed;
     	motor[leftMotor] = leftSpeed;
     	wait1Msec(10);
		}
	}
	else
	{
  	while(nMotorEncoder[rightMotor] > value)
  	{
    	motor[rightMotor] = rightSpeed;
     	motor[leftMotor] = leftSpeed;
     	wait1Msec(10);
		}
	}
	motor[rightMotor] = 0;
	motor[leftMotor] = 0;
}

void driveWithEncodersWithStop(int rightSpeed, int leftSpeed, int value)
{
	long lastTime = nSysTime;
	int lastEncoderValue = nMotorEncoder[rightMotor];
	nMotorEncoder[rightMotor] = 0;
	if(value > 0)
	{
  	while(nMotorEncoder[rightMotor] < value)
  	{
  		if(nSysTime - lastTime > TIME_CHECK_INTERVAL)
	  	{
	  		if (abs(nMotorEncoder[rightMotor] - lastEncoderValue) < ENCODER_DELTA_IN_TIME_CHECK_INTERVAL)
	  		{
	  			turn = true;
	  			break;
	  		}
	  	  lastEncoderValue = nMotorEncoder[rightMotor];
	  	  lastTime = nSysTime;
			}

    	motor[rightMotor] = rightSpeed;
     	motor[leftMotor] = leftSpeed;
     	wait1Msec(10);
		}
	}
	motor[rightMotor] = 0;
	motor[leftMotor] = 0;
}
