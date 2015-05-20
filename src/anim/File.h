/*
 * AnimationLoader.h
 *
 *  Created on: May 15, 2015
 *      Author: cozy
 */

#ifndef ANIM_ANIMATIONLOADER_H_
#define ANIM_ANIMATIONLOADER_H_

#include <string>
#include <map>

namespace anim {

class File {
public:
	File();
	virtual ~File();

	static File* load(const char* path);

	typedef struct {
		int id;
		std::string name;
		float min;
		float max;
	} Joint;

	typedef struct {
		int id;
		int port;
		int freq;
		int min;
		int max;
		int jointId;
	} Actuator;

	typedef std::map<int, Actuator> Actuators;
	typedef std::map<int, Joint> Joints;

	typedef struct {
		Joints    joints;
		Actuators actuators;
	} Configurations;

	const Configurations& getConfigurations();

private:
	Configurations _config;
};

} // namespace

#endif /* ANIM_ANIMATIONLOADER_H_ */
