#pragma once

#include "cocos2d.h"
USING_NS_CC;

class AnimationUtil {
public:
	AnimationUtil();
	~AnimationUtil();

	static CCAnimation* getAnimation( const char* filename, int frame, int fps );
};

