#include"ShadeLayer.h"

bool ShadeLayer::init() {
	if(!CCLayer::init())
		return false;
	//CCAssert(uiLayer, "uiLayer == NULL!");
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	/* 半透明层 */
	CCLayerColor* layerColor = CCLayerColor::create();
	layerColor->setColor(ccc3(0, 0, 0));
	layerColor->setOpacity(150);
	layerColor->setContentSize(CCSizeMake(visibleSize.width, visibleSize.height));
	this->addChild(layerColor);
	
	/* 全屏菜单，屏蔽下层点击事件 */
	CCMenuItemImage* item = CCMenuItemImage::create();
	item->setContentSize(CCSizeMake(visibleSize.width, visibleSize.height));
	//item->initWithTarget(this, menu_selector(ShadeLayer::itemCallback));
	CCMenu* menu = CCMenu::create(item, NULL);
	menu->setTouchPriority(-1280);
	this->addChild(menu);
	return true;
}

void itemCallback(CCObject* pSender){
}