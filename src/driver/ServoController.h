/*
 * ServoController.h
 *
 *  Created on: May 17, 2015
 *      Author: cozy
 */

#ifndef DRIVER_SERVOCONTROLLER_H_
#define DRIVER_SERVOCONTROLLER_H_

#include "Adafruit_PWMServoDriver.h"
#include <list>

struct ServoParam;

class ServoController {
public:
	ServoController(Adafruit_PWMServoDriver* pwm, int cylce_us, int min_us, int max_us);
	virtual ~ServoController();

	void addServo(int port, int cycle_us, int min_us, int max_us);
	int setAngle(int port, float angle);
	void setFaint(int port);

private:
	Adafruit_PWMServoDriver* _pwm;
	int _cycle_us;
	int _min_us;
	int _max_us;
	std::list<ServoParam> _params;
};

#endif /* DRIVER_SERVOCONTROLLER_H_ */
