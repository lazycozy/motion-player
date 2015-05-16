/*
 * AnimationLoader.cpp
 *
 *  Created on: May 15, 2015
 *      Author: cozy
 */

#include "AnimationLoader.h"
#include  "AnimationTrack.h"
#include "../picojson/picojson.h"
#include <iostream>
//#include <unistd.h>
#include <fstream>

AnimationLoader::AnimationLoader() {
	// TODO Auto-generated constructor stub

}

AnimationLoader::~AnimationLoader() {
	// TODO Auto-generated destructor stub
}

class toto_motion : public picojson::deny_parse_context {

};

void AnimationLoader::loadJSON(const char* path) {
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
}
