/*
 * AnimationPlayer.cpp
 *
 *  Created on: May 15, 2015
 *      Author: cozy
 */

#include "AnimationPlayer.h"

#include <iostream>

namespace anim {

AnimationPlayer::AnimationPlayer() {
	// TODO Auto-generated constructor stub

}

AnimationPlayer::~AnimationPlayer() {
	// TODO Auto-generated destructor stub
}

void AnimationPlayer::makeJoints(File* file) {
	const File::Joints& joints = file->getConfigurations().joints;
	File::Joints::const_iterator ite;
	for (ite = joints.begin(); ite != joints.end(); ++ite) {

	}
}

void AnimationPlayer::makeChannels(File* file) {
	const File::Joints& joints = file->getConfigurations().joints;
	File::Joints::const_iterator ijoint;
	for (ijoint = joints.begin(); ijoint != joints.end(); ++ijoint) {
		const File::Joint& joint = ijoint->second;
		AnimationChannel channel;
		// set range of channel
		std::cout << "range " << "" << " to " << "" << std::endl;
		channel.setRange(joint.min, joint.max);
		// set key frames to channel
		const File::Track& track = file->findTrack(joint.id);
		File::KeyFrames::const_iterator ikey = track.keyFrames.begin();
		for (; ikey != track.keyFrames.end(); ++ikey) {
			const File::KeyFrame& key = ikey->second;
			std::cout << "add key frame:" << key.frame << " value:" << key.value << std::endl;
			channel.addKeyFrame(key.frame, key.value);
		}
		// add a channel to this player
		_channels.insert(std::map<int,AnimationChannel>::value_type(joint.id, channel));
	}
}

void AnimationPlayer::resetFrame() {
	_curFrame = 0;
	Channels::iterator ite;
	for (ite = _channels.begin(); ite != _channels.end(); ++ite) {
		AnimationChannel& channel = ite->second;
		channel.setFrame(0);
	}
}

int AnimationPlayer::nextFrame() {
	Channels::iterator ite;
	for (ite = _channels.begin(); ite != _channels.end(); ++ite) {
		AnimationChannel& channel = ite->second;
		channel.nextFrame();
	}

	_curFrame++;
	return _curFrame;
}

float AnimationPlayer::getValue(int channel) {
	return _channels[channel].value();
}

} // namespace anim

