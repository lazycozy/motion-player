#include <mraa.h>
#include "driver/Adafruit_PWMServoDriver.h"

#include "anim/AnimationLoader.h"
#include "anim/AnimationPlayer.h"

#define PWM_COUNT_MAX 4095
#define PWM_COUNT_MIN 0

#define SG90_PERIOD_US 20000
#define SG90_FREQ      (1000000/SG90_PERIOD_US)
#define SG90_DUTY_MIN  (PWM_COUNT_MAX*500/SG90_PERIOD_US)
#define SG90_DUTY_MAX  (PWM_COUNT_MAX*2500/SG90_PERIOD_US)
#define SG90_DUTY_MID  ((SG90_DUTY_MIN+SG90_DUTY_MAX)/2)
#define SERVOMIN       SG90_DUTY_MIN
#define SERVOMAX       SG90_DUTY_MAX

int main(int argc, char *argv[])
{
	//AnimationPlayer& player = new AnimationPlayer()/*= AnimationLoader::loadJSON("/tmp/0.json")*/;
	//player.reset();
	mraa::I2c i2c(6);
	Adafruit_PWMServoDriver pwm(i2c);

	pwm.setPWMFreq(SG90_FREQ);  // Analog servos run at ~60 Hz updates

	// loop forever toggling the on board LED every second
	for (;;) {
		//AnimationFrame frame = player.next();

		//int step = (SERVOMAX - SERVOMIN)/50;
		int step = 1;
		for (uint16_t pulselen = SERVOMIN; pulselen <= SERVOMAX; pulselen += step) {
			for (uint16_t servo = 0; servo < 14; servo += 2) {
				pwm.setPWM(servo, 0, pulselen);
			}
			//usleep(100);
		}
		//usleep(500000);
		for (uint16_t pulselen = SERVOMAX; pulselen >= SERVOMIN; pulselen -= step) {
			for (uint16_t servo = 0; servo < 14; servo += 2) {
				pwm.setPWM(servo, 0, pulselen);
			}
			//usleep(100);
		}
		//usleep(500000);
	}

	//player.release();

	return 0;
}
