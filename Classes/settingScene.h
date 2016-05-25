/*�Ի��򳡾����ͷ�ļ�*/
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
	//���ڴ������¼�
	bool ccTouchBegan(CCTouch*, CCEvent*);
    CREATE_FUNC(PopScene);
private:
    //ע�ᴥ���¼���ʵ��ccTouchBegan()����
    void registerWithTouchDispatcher();
    //bool ccTouchBegan(CCTouch * touch,CCEvent * pevent);
    
    //���öԻ����title
    void setTitle(CCObject* sender);
    //���öԻ�����ı�����
    void setContent(CCObject* psender);
    void closeButton(CCObject * object);
	void InputName(cocos2d::CCObject* sender);
	CCMenuItemToggle* m_pItemVoice;
	CCTextFieldTTF*	m_pNameInput;
	std::string m_sNameSave; 

};
#endif