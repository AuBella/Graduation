#ifndef ShadeLayer_H

#define ShadeLayer_H

#include "cocos2d.h"
USING_NS_CC;

class ShadeLayer : public CCLayer{
public:
	bool init();
	void itemCallback(CCObject* pSender);
	CREATE_FUNC(ShadeLayer);
};

#endif
