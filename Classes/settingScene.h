/*对话框场景类的头文件*/
#ifndef _POP_SCENE_H_
#define _POP_SCENE_H_
#include "cocos2d.h"
 
using namespace cocos2d;
 
class PopScene : public CCLayer{
public:
	PopScene();
    static CCScene * scene();
	bool canEnter;
    bool init();
	//用于处理触摸事件
	bool ccTouchBegan(CCTouch*, CCEvent*);
    CREATE_FUNC(PopScene);
private:
    //注册触摸事件，实现ccTouchBegan()方法
    void registerWithTouchDispatcher();
    //bool ccTouchBegan(CCTouch * touch,CCEvent * pevent);
    
    //设置对话框的title
    void setTitle(CCObject* sender);
    //设置对话框的文本内容
    void setContent(CCObject* psender);
    void closeButton(CCObject * object);
	void InputName(cocos2d::CCObject* sender);
	CCMenuItemToggle* m_pItemVoice;
	CCTextFieldTTF*	m_pNameInput;
	std::string m_sNameSave; 

};
#endif