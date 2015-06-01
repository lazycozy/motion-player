#include <iostream>
#include <mraa.h>
#include <vector>

#include "driver/Adafruit_PWMServoDriver.h"
#include "driver/ServoController.h"
#include "anim/anim.h"

#define SG90_PERIOD_US 20000
#define SG90_PERIOD_MIN_US 500
#define SG90_PERIOD_MAX_US 2500
#define SERVO_CHNUM    16

int main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("usage:moplay <motion-file>\n");
		exit(1);
	}
	const char* filepath = argv[1];
	std::cout << "start moplay " << filepath << std::endl;

	std::cout << "initializing i2c..." << std::endl;
	mraa::I2c* i2c = new mraa::I2c(6);
	i2c->frequency(MRAA_I2C_HIGH);
	std::cout << "initializing pwm driver..." << std::endl;
	Adafruit_PWMServoDriver* pwm = new Adafruit_PWMServoDriver(i2c);
	std::cout << "initializing servo controller..." << std::endl;
	ServoController* servo = new ServoController(pwm, SG90_PERIOD_US, SG90_PERIOD_MIN_US, SG90_PERIOD_MAX_US);

	std::cout << "loading motion file:" << filepath << std::endl;
	anim::File* file = anim::File::load(filepath);
	if (!file) {
		fprintf(stderr, "Fail to load motion file\n");
		exit(1);
	}
	std::cout << "seting uo servo contoller" << std::endl;
	anim::File::Configurations config = file->getConfigurations();
	anim::File::Actuators acts = config.actuators;
	anim::File::Actuators::iterator ite;
	std::vector<int> portlist;
	for (ite = acts.begin(); ite != acts.end(); ++ite) {
		anim::File::Actuator& act = ite->second;
		std::cout << "add servo port=" << act.port << " ch=" << act.jointId << ",f=" << act.freq << ",min=" << act.min <<",max="<< act.max << ",vmin=" << act.val_min << ",vmax=" << act.val_max << std::endl;
		servo->addServo(act.port, act.jointId, act.freq, act.min, act.max, act.val_min, act.val_max);
		portlist.push_back(act.port);
	}

	std::cout << "starting up AnimationPlayer" << std::endl;
    anim::AnimationPlayer* player = new anim::AnimationPlayer;
    player->makeJoints(file);
    player->makeChannels(file);
    player->resetFrame();

	std::cout << "start!" << std::endl;
	std::vector<int>::iterator iport;
	while (1) {
		for (iport = portlist.begin(); iport != portlist.end(); ++iport) {
			int port = *iport;
			int ch = servo->getServoChNo(port);
			if (ch >= 0) {
				float angle = player->getValue(ch);
				servo->setAngle(port, angle);
			}
		}
		usleep(20*1000);
		uint frame = player->nextFrame();
		if (frame == anim::FRAME_INVALID) {
			break;
		}
	}
	std::cout << "finished!" << std::endl;
	// Finish
	for (iport = portlist.begin(); iport != portlist.end(); ++iport) {
		int ch = *iport;
		servo->setFaint(ch);
	}

	std::cout << "closing..." << std::endl;
	delete player;
	delete servo;
	delete pwm;
	delete i2c;

	return 0;
}
