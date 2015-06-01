/*
 * ServoController.cpp
 *
 *  Created on: May 17, 2015
 *      Author: cozy
 */

#include "ServoController.h"
#include "Adafruit_PWMServoDriver.h"
#include <iostream>

struct ServoParam {
	int port;
	int chno;
	int cycle_us;
	int min_us;
	int max_us;
	int width_us;
	float value_min;
	float value_max;
};

ServoController::ServoController(Adafruit_PWMServoDriver* pwm, int cylce_us, int min_us, int max_us)
:_pwm(pwm), _cycle_us(cylce_us), _min_us(min_us), _max_us(max_us)
{
	if (_pwm) {
		_pwm->begin();
		_pwm->setPWMFreq(1000000.0/_cycle_us);
	}
}

ServoController::~ServoController() {
}

void ServoController::addServo(int port, int chno, int cycle_us, int min_us, int max_us, float min_val, float max_val) {
	struct ServoParam param;
	param.port = port;
	param.chno = chno;
	param.cycle_us = cycle_us;
	param.min_us = min_us;
	param.max_us = max_us;
	param.width_us = max_us - min_us;
	param.value_min = min_val;
	param.value_max = max_val;
	_params.push_back(param);
}

const ServoParam* ServoController::getServo(int port)
{
	std::list<ServoParam>::iterator ite;
	for (ite = _params.begin(); ite != _params.end(); ++ite) {
		if (ite->port == port) {
			return &(*ite);
		}
	}
	return NULL;
}

int ServoController::setAngle(int port, float angle) {

	if (angle > 110.f || angle < -110.f) {
		std::cout << "out of range port: " << port << " angle: " << angle << std::endl;
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
	float us = ite->min_us + ite->width_us * (angle + -ite->value_min) / (ite->value_max - ite->value_min);
	//std::cout << "port:" << port << " us:" << us << std::endl;
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

int ServoController::getServoChNo(int port) {
	const ServoParam* pp = getServo(port);
	if (pp) {
		return pp->chno;
	}
	return -1;
}
