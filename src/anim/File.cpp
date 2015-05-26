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

static void loadHeader(File::Header& header, picojson::object& obj)
{
    std::cout << "name: " << obj["name"].get<std::string>() << std::endl;
    std::cout << "file: " << obj["configuration-file"].get<std::string>() << std::endl;
}

static void loadJoints(File::Joints& joints, picojson::array& array)
{
	int jointnum = array.size();
	std::cout << "joint num = " << jointnum << std::endl;
	for (int i = 0; i < jointnum; i++) {
		picojson::object &elem = array[i].get<picojson::object>();
		std::cout << "name: " << elem["name"].get<std::string>() << std::endl;
		File::Joint joint;
		joint.id = elem["id"].get<double>();
		joint.min = elem["min"].get<double>();
		joint.max = elem["max"].get<double>();
		joint.trim = elem["trim"].get<double>();
		joints.insert(File::Joints::value_type(joint.id, joint));
	}
}

static void loadActuators(File::Actuators& actuators, picojson::array& array)
{
	int num = array.size();
	std::cout << "actuator num = " << num << std::endl;
	for (int i = 0; i < num; i++) {
		picojson::object& actuator = array[i].get<picojson::object>();
		picojson::object& pwm = actuator["pwm"].get<picojson::object>();

		File::Actuator act;
		act.id = i;
		act.port    = actuator["port"].get<double>();
		act.freq    = pwm["freq"].get<double>();
		act.min     = pwm["min"].get<double>();
		act.max     = pwm["max"].get<double>();
		act.jointId = actuator["joint-id"].get<double>();
		actuators.insert(File::Actuators::value_type(act.port,act));
	}
}

static void loadConfigurations(File::Configurations& config, picojson::object& obj)
{
	// load joints
	loadJoints(config.joints, obj["joints"].get<picojson::array>());
	// load actuators
	loadActuators(config.actuators, obj["actuators"].get<picojson::array>());
}

static File::FuncType getFunctionId(std::string funcname)
{
	if (funcname == "linear") {
		return File::FUNC_LINEAR;
	} else if (funcname == "ease-in") {
		return File::FUNC_EASE_IN;
	} else if (funcname == "ease-out") {
		return File::FUNC_EASE_OUT;
	} else if (funcname == "ease-in-out") {
		return File::FUNC_EASE_IN_OUT;
	}
	return File::FUNC_LINEAR;
}

static void loadKeyFrames(File::KeyFrames& keyFrames, picojson::array& array)
{
	int num = array.size();
	std::cout << "keyframe num = " << num << std::endl;
    for (int i = 0; i < num; ++i) {
		picojson::object& elem = array[i].get<picojson::object>();
		File::KeyFrame keyFrame;
		keyFrame.frame = elem["frame"].get<double>();
		keyFrame.value = elem["angle"].get<double>();
		keyFrame.function = getFunctionId(elem["function"].get<std::string>());
		std::cout << "func=" << keyFrame.function << std::endl;
		keyFrames.insert(File::KeyFrames::value_type(keyFrame.frame, keyFrame));
    }
}

static void loadTracks(File::Tracks& tracks, picojson::array& array)
{
	int num = array.size();
	std::cout << "track num = " << num << std::endl;
	for (int i = 0; i < num; ++i) {
		picojson::object& tk = array[i].get<picojson::object>();
		File::Track track;
		track.jointId = tk["joint-id"].get<double>();
		loadKeyFrames(track.keyFrames, tk["keys"].get<picojson::array>());
		tracks.insert(File::Tracks::value_type(track.jointId, track));
	}
}

static void loadAnimation(File::Animation& animation, picojson::object& obj)
{
	animation.totalFrames = obj["total-frame-number"].get<double>();
	animation.frameRate = obj["frame-rate"].get<double>();
    loadTracks(animation.tracks, obj["tracks"].get<picojson::array>());
}

File* File::load(const char* path) {
	File* file = new File();

    std::cout << "load file: " << path << std::endl;
	std::ifstream ifs(path);
	if (!ifs.bad()) {
		//std::cout << ifs.rdbuf();
	}
	picojson::value root;
	ifs >> root;

	loadHeader(file->_header, root.get<picojson::object>()["header"].get<picojson::object>());
    loadConfigurations(file->_config, root.get<picojson::object>()["configurations"].get<picojson::object>());
    loadAnimation(file->_animation, root.get<picojson::object>()["animation"].get<picojson::object>());

    std::cout << "Finished!!" << std::endl;
	return file;
}

const File::Configurations& File::getConfigurations() {
	return _config;
}

const File::Animation& File::getAnimation() {
	return _animation;
}

const File::Track& File::findTrack(int jointId) {
	return _animation.tracks[jointId];
}

} // namespace

