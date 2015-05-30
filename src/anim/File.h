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
		const char* name;
		const char* cfgfile;
	} Header;

	typedef struct {
		int id;
		std::string name;
		float min;
		float max;
		float trim;
	} Joint;

	typedef struct {
		int id;
		int port;
		int freq;
		int min;
		int max;
		int jointId;
	} Actuator;

	typedef std::map<int,Actuator> Actuators;
	typedef std::map<int,Joint> Joints;

	typedef struct {
		Joints    joints;
		Actuators actuators;
	} Configurations;

	typedef enum {
		FUNC_LINEAR,
		FUNC_EASE_IN,
		FUNC_EASE_OUT,
		FUNC_EASE_IN_OUT,
	} FuncType;

	typedef struct {
		int frame;
		float value;
		FuncType function;
	} KeyFrame;

	typedef std::map<int, KeyFrame> KeyFrames;

	typedef struct {
		int jointId;
		KeyFrames keyFrames;
	} Track;

	typedef std::map<int,Track> Tracks;

	typedef struct {
		int totalFrames;
		int frameRate;
		Tracks tracks;
	} Animation;

	const Configurations& getConfigurations();
	const Animation& getAnimation();
	const Track& findTrack(int jointId);

private:
	Header _header;
	Configurations _config;
	Animation _animation;
};

} // namespace

#endif /* ANIM_ANIMATIONLOADER_H_ */
