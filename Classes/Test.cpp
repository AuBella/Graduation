#include"Test.h"
bool Test::init(){
    if ( !CCLayer::init() )
        return false;
	CCLabelTTF* pLabel = CCLabelTTF::create("BaiBai", "fonts/Marker Felt", 40);//Ҫ��ʾ�����ݣ����壬�ֺ�  
	pLabel->setString("TestTest");  
	pLabel->setColor(ccc3(0,0,0)); 
	pLabel->setPosition(ccp(520, 520));  
	this->addChild(pLabel);  
    return true;
}