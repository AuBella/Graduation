#ifndef _COMMON_H_
#define _COMMON_H_

//#include "cocos2d.h"
//#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID)
//#include "iconv\iconv.h"
//#endif

namespace common
{
	template <class T>
	void ShowNumber(T* _pNode, int score, int wordWight, int wordHeight, float locationX, float locationY, 
		const char* path, int tag = 888, int depth = 0, float scale = 1 , bool isTime = false)
	{
		char cNum[255];
		if ( isTime )
			sprintf(cNum, "%.2d", score);
		else
			sprintf(cNum, "%d", score);
		cocos2d::CCLabelAtlas* label = (cocos2d::CCLabelAtlas*)_pNode->getChildByTag(tag);
		if ( !label )
		{
			label = cocos2d::CCLabelAtlas::create("0123456789", path, wordWight, wordHeight, '0');
			_pNode->addChild(label,depth,tag);
		}
		label->setPosition(ccp(locationX,locationY));
		label->setScale(scale);
		label->setString(cNum);
	}

	template <class T>
	void ShowNumberUpdate(T* _pNode, int score, int tag = 888, float scale = 0.0f , bool isTime = false)
	{
		char cNum[255];
		if ( isTime )
			sprintf(cNum, "%.2d", score);
		else
			sprintf(cNum, "%d", score);
		cocos2d::CCLabelAtlas* label = (cocos2d::CCLabelAtlas*)_pNode->getChildByTag(tag);
		label->setString(cNum);
		if ( scale != 0.0f )
			label->setScale(scale);
	}

	template <class T>
	void RunNewAnimation(cocos2d::CCSprite* _pSprite,
		const char* _pAnimationPath, const int _iAnimationNum, T _Rect,
		bool _bRepear = false, bool _bReverse = false, float _fMovieFrame = 0.1f, cocos2d::CCCallFunc* _pCallFunc = NULL)
	{
		char str1[100] = {0};
		cocos2d::CCArray* animFrames = cocos2d::CCArray::createWithCapacity(_iAnimationNum);
		for(int i = 1; i <= _iAnimationNum; i++) 
		{
			int j = i;
			if ( _bReverse )
				j = _iAnimationNum - i + 1;
			sprintf(str1,"%d.png", j);
			std::string str2 = _pAnimationPath;
			str2 += str1;
			cocos2d::CCSpriteFrame* frame = cocos2d::CCSpriteFrame::create(str2.c_str(), _Rect);
			animFrames->addObject(frame);
		}
		cocos2d::CCAnimation* pAnimation = cocos2d::CCAnimation::createWithSpriteFrames(animFrames, _fMovieFrame);
		if ( _pCallFunc )
		{
			cocos2d::CCSequence* pSequence = NULL;
			pSequence = cocos2d::CCSequence::create( cocos2d::CCAnimate::create(pAnimation), _pCallFunc, NULL);
			if ( _bRepear )
				_pSprite->runAction( cocos2d::CCRepeatForever::create(pSequence) );
			else
				_pSprite->runAction( pSequence );
		}
		else
		{
			cocos2d::CCAnimate* pAnimate = cocos2d::CCAnimate::create(pAnimation);
			if ( _bRepear )
				_pSprite->runAction( cocos2d::CCRepeatForever::create(pAnimate) );
			else
				_pSprite->runAction( pAnimate );
		}
	}

	template <class T>
	cocos2d::CCSprite* CreateAnimation(const char* _pNodePath, T _NodeLocation, T _AnimationAnchorPoint,
		const char* _pAnimationPath, const int _iAnimationNum, cocos2d::CCRect _Rect,
		bool _bRepear = false, bool _bReverse = false, float _fMovieFrame = 0.1f, cocos2d::CCCallFunc* _pCallFunc = NULL)
	{
		cocos2d::CCSprite* pNode = cocos2d::CCSprite::create(_pNodePath);
		pNode->setPosition(_NodeLocation);
		pNode->setAnchorPoint(_AnimationAnchorPoint);
		RunNewAnimation(pNode, _pAnimationPath, _iAnimationNum, _Rect, _bRepear, _bReverse, _fMovieFrame, _pCallFunc);
		return pNode;
	}

	template <class T>
	cocos2d::CCAnimation* CreateAnimationFrame(const char* _pPath, T _iAnimationNum, cocos2d::CCRect _rect, float _fMovieFrame = 0.1f, bool _bReverse = false)
	{
		cocos2d::CCArray* animFrames = cocos2d::CCArray::createWithCapacity(_iAnimationNum);
		for(int i = 1; i <= _iAnimationNum; i++) 
		{
			char str1[100] = {0};
			int j = i;
			if ( _bReverse )
				j = _iAnimationNum - i + 1;
			sprintf(str1,"%d.png", j);
			std::string str2 = _pPath;
			str2 += str1;
			cocos2d::CCSpriteFrame* frame = cocos2d::CCSpriteFrame::create(str2.c_str(), _rect);
			animFrames->addObject(frame);
		}
		cocos2d::CCAnimation* pAnimation = cocos2d::CCAnimation::createWithSpriteFrames(animFrames, _fMovieFrame);
		return pAnimation;
	}

	template <class T>
	cocos2d::CCAnimation* CreateAnimationFrame(cocos2d::CCTexture2D** _pAnimationTexture, T _iAnimationNum, float _fMovieFrame, bool _bReverse = false)
	{
		cocos2d::CCArray* animFrames = cocos2d::CCArray::createWithCapacity(_iAnimationNum);
		for(int i = 0; i < _iAnimationNum; i++) 
		{
			cocos2d::CCSpriteFrame* frame = cocos2d::CCSpriteFrame::createWithTexture(_pAnimationTexture[i],
				cocos2d::CCRect(0, 0, _pAnimationTexture[0]->getContentSize().width, _pAnimationTexture[0]->getContentSize().height) );
			animFrames->addObject(frame);
		}
		cocos2d::CCAnimation* pAnimation = cocos2d::CCAnimation::createWithSpriteFrames(animFrames, _fMovieFrame);
		return pAnimation;
	}

	template <class T>
	void RunNewAnimation(cocos2d::CCSprite* _pSprite,
		cocos2d::CCTexture2D** _pAnimationTexture, T _iAnimationNum, /*T _Rect,*/
		bool _bRepear = false, bool _bReverse = false, float _fMovieFrame = 0.1f, cocos2d::CCCallFunc* _pCallFunc = NULL)
	{
		cocos2d::CCAnimation* pAnimation = CreateAnimationFrame(_pAnimationTexture, _iAnimationNum, _fMovieFrame);
		if ( _pCallFunc )
		{
			cocos2d::CCSequence* pSequence = NULL;
			pSequence = cocos2d::CCSequence::create( cocos2d::CCAnimate::create(pAnimation), _pCallFunc, NULL);
			if ( _bRepear )
				_pSprite->runAction( cocos2d::CCRepeatForever::create(pSequence) );
			else
				_pSprite->runAction( pSequence );
		}
		else
		{
			cocos2d::CCAnimate* pAnimate = cocos2d::CCAnimate::create(pAnimation);
			if ( _bRepear )
				_pSprite->runAction( cocos2d::CCRepeatForever::create(pAnimate) );
			else
				_pSprite->runAction( pAnimate );
		}
	}

	template <class T>
	cocos2d::CCSprite* CreateAnimation(cocos2d::CCTexture2D* _pSpriteTexture, T _NodeLocation, T _AnimationAnchorPoint,
		cocos2d::CCTexture2D** _pAnimationTexture, const int _iAnimationNum, /*cocos2d::CCRect _Rect,*/
		bool _bRepear = false, bool _bReverse = false, float _fMovieFrame = 0.1f, cocos2d::CCCallFunc* _pCallFunc = NULL)
	{
		cocos2d::CCSprite* pSprite = cocos2d::CCSprite::createWithTexture(_pSpriteTexture);
		pSprite->setPosition(_NodeLocation);
		pSprite->setAnchorPoint(_AnimationAnchorPoint);
		RunNewAnimation(pSprite, _pAnimationTexture, _iAnimationNum, /*_Rect, */_bRepear, _bReverse, _fMovieFrame, _pCallFunc);
		return pSprite;
	}

	template <class T>
	void AddTextureCacheArray(T* _p, std::string _str, int _num)
	{
		for ( int i = 0; i < _num; i++ )
		{
			char buffer[255];
			sprintf(buffer, "%d.png", i+1);
			_p[i] = cocos2d::CCTextureCache::sharedTextureCache()->addImage( (_str+buffer).c_str() );
			_p[i]->retain();
		}
	}

	template <class T>
	void RemoveTextureCacheArray(T* _p, int _num)
	{
		for ( int i = 0; i < _num; i++ )
		{
			_p[i]->release();
		}
	}

//	template <class T>
//	const char* GBKToUTF8(std::string & gbkStr, T p = 0, const char* toCode = "gb2312", const char* fromCode = "utf-8")
//	{
//#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID)
//		iconv_t iconvH;
//		iconvH = iconv_open(fromCode, toCode);
//		if (iconvH == 0)
//		{
//			return NULL;
//		}
//		const char* strChar = gbkStr.c_str();
//		const char** pin = &strChar;
//		size_t strLength = gbkStr.length();
//		char* outbuf = (char*) malloc(strLength*4);
//		char* pBuff = outbuf;
//		memset( outbuf, 0, strLength*4);
//		size_t outLength = strLength*4;
//		if (-1 == iconv(iconvH, pin, &strLength, &outbuf, &outLength))
//		{
//			iconv_close(iconvH);
//			return NULL;
//		}
//		gbkStr = pBuff;
//		iconv_close(iconvH);
//#endif
//		return (gbkStr.c_str());
//	}
}

#endif
