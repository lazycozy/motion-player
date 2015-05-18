/*
 * ServoController.cpp
 *
 *  Created on: May 17, 2015
 *      Author: cozy
 */

#include "ServoController.h"
#include "Adafruit_PWMServoDriver.h"

struct ServoParam {
	int port;
	int cycle_us;
	int min_us;
	int max_us;
	int width_us;
};

ServoController::ServoController(Adafruit_PWMServoDriver* pwm, int cylce_us, int min_us, int max_us)
:_pwm(pwm), _cycle_us(cylce_us), _min_us(min_us), _max_us(max_us)
{
	if (_pwm) {
		_pwm->begin();
		_pwm->setPWMFreq(1000000/_cycle_us);
	}
}

ServoController::~ServoController() {
}

void ServoController::addServo(int port, int cycle_us, int min_us, int max_us) {
	struct ServoParam param;
	param.port = port;
	param.cycle_us = cycle_us;
	param.min_us = min_us;
	param.max_us = max_us;
	param.width_us = max_us - min_us;
	_params.push_back(param);
}

int ServoController::setAngle(int port, float angle) {
	if (angle > 90.f || angle < -90.f) {
		return 0;
	}
	std::list<ServoParam>::iterator ite;
	for (ite = _params.begin(); ite != _params.end(); ++ite) {
		if (ite->port == port) {
			break;
		}
	}
	if (ite == _params.end()) {
		return 0;
	}
	float us = ite->min_us + ite->width_us * (angle+90.f) / 180.f;
	int pulselen = us * PCA9685_RESOLUTION / ite->cycle_us;
	if (_pwm) {
		_pwm->setPWM(port, 0, pulselen);
	}
	return pulselen;
}

void ServoController::setFaint(int port) {
	if (_pwm) {
		_pwm->setPWM(port, 0, 0);
	}
}
