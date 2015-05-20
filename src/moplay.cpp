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
	//upm::Jhd1313m1* lcd = new upm::Jhd1313m1(0);

	//AnimationPlayer& player = AnimationLoader::loadJSON("/tmp/0.json");
	//player.reset();
	mraa::I2c* i2c = new mraa::I2c(6);
	i2c->frequency(MRAA_I2C_HIGH);

	Adafruit_PWMServoDriver* pwm = new Adafruit_PWMServoDriver(i2c);

	ServoController* servo = new ServoController(pwm, SG90_PERIOD_US, SG90_PERIOD_MIN_US, SG90_PERIOD_MAX_US);
	anim::File* file = anim::File::load("/tmp/motion-000,json");
	anim::File::Configurations config = file->getConfigurations();
	std::map<int, anim::File::Actuator> acts = config.actuators;
	std::map<int, anim::File::Actuator>::iterator ite;
	for (ite = acts.begin(); ite != acts.end(); ++ite) {
		anim::File::Actuator& act = ite->second;
		servo->addServo(act.id, act.freq, act.min, act.max);
	}

	// loop forever toggling the on board LED every second
	for (;;) {
		//AnimationFrame frame = player.next();

		static int joint2port[] = {
				0,2,4,6,8,10,12,
		};
		for (float angle = -90.f; angle <= 90.f; angle += 3.6f) {
			for (int joint = 0; joint < 7; ++joint) {
				servo->setAngle(joint2port[joint], angle);
			}
			usleep(20*1000);
		}
		for (float angle = 90.f; angle >= -90.f; angle -= 3.6f) {
			for (int joint = 0; joint < 7; ++joint) {
				servo->setAngle(joint2port[joint], angle);
			}
			usleep(20*1000);
		}
		for (int joint = 0; joint < 7; ++joint) {
			servo->setFaint(joint2port[joint]);
		}
		usleep(5*1000*1000);
	}

	//player.release();

	delete servo;
	delete pwm;
	delete i2c;

	return 0;
}
