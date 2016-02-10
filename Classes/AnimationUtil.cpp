#include "AnimationUtil.h"


AnimationUtil::AnimationUtil() {}


AnimationUtil::~AnimationUtil() {}


CCAnimation* AnimationUtil::getAnimation( const char* filename, int frame, int fps ) {
	CCAnimation* animation = CCAnimation::create();

	CCSprite* texture = CCSprite::create( filename );
	float h = texture->getContentSize().height;
	float w = texture->getContentSize().width / frame;

	for ( int i = 0; i < frame; ++i ) {
		CCSpriteFrame* spriteFrame = CCSpriteFrame::create( filename, CCRect( i*w, 0, w, h ) );
		animation->addSpriteFrame( spriteFrame );
	}
	animation->setDelayPerUnit( 1.0f / fps );

	return animation;
}