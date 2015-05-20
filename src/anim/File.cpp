/*
 * AnimationLoader.cpp
 *
 *  Created on: May 15, 2015
 *      Author: cozy
 */

#include "File.h"
#include  "AnimationTrack.h"
#include "../picojson/picojson.h"
#include <iostream>
//#include <unistd.h>
#include <fstream>

namespace anim {

File::File() {
	// TODO Auto-generated constructor stub

}

File::~File() {
	// TODO Auto-generated destructor stub
}

class toto_motion : public picojson::deny_parse_context {

};

File* File::load(const char* path) {
	File* file = new File();

	std::ifstream ifs(path);
	picojson::value root;
	ifs >> root;
	picojson::object &hdr = root.get<picojson::object>()["header"].get<picojson::object>();
    std::cout << "name: " << hdr["name"].get<std::string>() << std::endl;
    std::cout << "file: " << hdr["configuration-file"].get<std::string>() << std::endl;

	picojson::object &cfg = root.get<picojson::object>()["configurations"].get<picojson::object>();
	picojson::array &joints = cfg["joints"].get<picojson::array>();
	for (JointId i = 0; i < joints.size(); i++) {
		picojson::object &joint = joints[i].get<picojson::object>();
		std::cout << "name: " << joint["name"].get<std::string>() << std::endl;
	}
	picojson::array &acts = cfg["actuators"].get<picojson::array>();
	for (uint i = 0; i < acts.size(); i++) {
		picojson::object& actuator = acts[i].get<picojson::object>();
		picojson::object& pwm = actuator["pwm"].get<picojson::object>();
		Actuator act;
		act.id = i;
		act.port    = actuator["port"].get<double>();
		act.freq    = pwm["freq"].get<double>();
		act.min     = pwm["min"].get<double>();
		act.max     = pwm["max"].get<double>();
		act.jointId = actuator["joint-id"].get<double>();
		file->_config.actuators.insert(std::map<int,Actuator>::value_type(i, act));
		std::cout << "id: " << act.id;
		std::cout << "port: " << act.port;
		std::cout << "freq: " << act.freq;
		std::cout << "min: " << act.min;
		std::cout << "max: " << act.max;
		std::cout << "joint-id: " << act.jointId;
		std::cout << std::endl;
	}
	return file;
}

const File::Configurations& anim::File::getConfigurations() {
	return _config;
}

} // namespace
