#include <iostream>
#include <mraa.h>
#include "driver/Adafruit_PWMServoDriver.h"
#include "driver/ServoController.h"
#include "anim/anim.h"

#define PWM_COUNT_MAX 4095
#define PWM_COUNT_MIN 0

#define SG90_PERIOD_US 20000
#define SG90_PERIOD_MIN_US 500
#define SG90_PERIOD_MAX_US 2500
#define SG90_FREQ      (1000000/SG90_PERIOD_US)
#define SG90_DUTY_MIN  (PWM_COUNT_MAX*SG90_PERIOD_MIN_US/SG90_PERIOD_US)
#define SG90_DUTY_MAX  (PWM_COUNT_MAX*SG90_PERIOD_MAX_US/SG90_PERIOD_US)
#define SG90_DUTY_MID  ((SG90_DUTY_MIN+SG90_DUTY_MAX)/2)
#define SERVOMIN       SG90_DUTY_MIN
#define SERVOMAX       SG90_DUTY_MAX

int main(int argc, char *argv[])
{
	std::cout << "start moplay" << std::endl;

	//upm::Jhd1313m1* lcd = new upm::Jhd1313m1(0);

	//AnimationPlayer& player = AnimationLoader::loadJSON("/tmp/0.json");
	//player.reset();
	mraa::I2c* i2c = new mraa::I2c(6);
	i2c->frequency(MRAA_I2C_HIGH);

	Adafruit_PWMServoDriver* pwm = new Adafruit_PWMServoDriver(i2c);

	ServoController* servo = new ServoController(pwm, SG90_PERIOD_US, SG90_PERIOD_MIN_US, SG90_PERIOD_MAX_US);
	anim::File* file = anim::File::load("/home/root/motion-000.json");
//	anim::File* file = anim::File::load("/homr/root/0.json");
	if (!file) {
		return 0;
	}
	anim::File::Configurations config = file->getConfigurations();
	anim::File::Actuators acts = config.actuators;
	anim::File::Actuators::iterator ite;
	for (ite = acts.begin(); ite != acts.end(); ++ite) {
		anim::File::Actuator& act = ite->second;
		std::cout << "add servo port=" << act.port << ",f=" << act.freq << ",min=" << act.min <<",max="<< act.max << std::endl;
		servo->addServo(act.port, act.freq, act.min, act.max);
	}

    anim::AnimationPlayer* player = new anim::AnimationPlayer;
    player->makeJoints(file);
    player->makeChannels(file);
    player->resetFrame();

	// loop forever toggling the on board LED every second
	for (;;) {
		int frame = player->nextFrame();

		static int joint2port[] = {
				0,2,4,6,8,10,12,
		};
		for (int joint = 0; joint < 7; ++joint) {
			int ch = joint;
			float angle = player->getValue(ch);
			servo->setAngle(joint2port[joint], angle);
		}
		usleep(20*1000);
	}

	delete player;
	delete servo;
	delete pwm;
	delete i2c;

	return 0;
}
