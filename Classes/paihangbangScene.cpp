#include "paihangbangScene.h"
#include"baseRes.h"
#include"GlobalCtrl.h"
#include "Common.h"
 
//paihangbangScene::paihangbangScene(){
//}
bool paihangbangScene::init(){
	if(!CCLayer::init()){
		return false;
	}
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	
	CCSprite* backgroud = CCSprite::create("tu7/paihangbang/help.png");
    backgroud->setPosition(ccp(winSize.width/2-50,winSize.height/2));
	SetScaleY(backgroud);
	this->addChild(backgroud);
	CCSprite* pDi = CCSprite::create("tu7/paihangbang/di.png");
	pDi->setAnchorPoint(ccp(0,0));
    pDi->setPosition(ccp(100,0));
	backgroud->addChild(pDi, -1);
	m_pRankList = CCSprite::create("tu7/paihangbang/zhongkuang.png");
	m_pRankList->setAnchorPoint(ccp(0,0));
	m_pRankList->setPosition(ccp(50,40));
	pDi->addChild(m_pRankList);

	m_pRank1 = CCMenuItemToggle::createWithTarget(this, 
			menu_selector(paihangbangScene::OnRank1), 
			CCMenuItemImage::create( "tu7/paihangbang/gaofu.png", "tu7/paihangbang/gaofu2.png" ),
			CCMenuItemImage::create( "tu7/paihangbang/gaofu2.png", "tu7/paihangbang/gaofu2.png" ),
			NULL );
	m_pRank2 = CCMenuItemToggle::createWithTarget(this, 
		menu_selector(paihangbangScene::OnRank2), 
		CCMenuItemImage::create( "tu7/paihangbang/chengjiu.png", "tu7/paihangbang/chengjiu2.png" ),
		CCMenuItemImage::create( "tu7/paihangbang/chengjiu2.png", "tu7/paihangbang/chengjiu2.png" ),
		NULL );
	m_pRank3 = CCMenuItemToggle::createWithTarget(this, 
		menu_selector(paihangbangScene::OnRank3), 
		CCMenuItemImage::create( "tu7/paihangbang/jiangshi.png", "tu7/paihangbang/jiangshi2.png" ),
		CCMenuItemImage::create( "tu7/paihangbang/jiangshi2.png", "tu7/paihangbang/jiangshi2.png" ),
		NULL );
	m_pRank4 = CCMenuItemToggle::createWithTarget(this, 
		menu_selector(paihangbangScene::OnRank4), 
		CCMenuItemImage::create( "tu7/paihangbang/xingxing.png", "tu7/paihangbang/xingxing2.png" ),
		CCMenuItemImage::create( "tu7/paihangbang/xingxing2.png", "tu7/paihangbang/xingxing2.png" ),
		NULL );
	
	CCMenuItemImage* closeicon = CCMenuItemImage::create( 
		"Common/btn_pre_clo.png", "Common//btn_nor_clo.png", this, menu_selector(paihangbangScene::closeButton));
		m_pRank1->setPosition(ccp(162, 356));
		m_pRank2->setPosition(ccp(286, 356));
		m_pRank3->setPosition(ccp(410, 356));
		m_pRank4->setPosition(ccp(534, 356));
		closeicon->setPosition(ccp(620, 356));
		CCMenu* pMenu = CCMenu::create(m_pRank1, m_pRank2, m_pRank3, m_pRank4,closeicon, NULL);
		pMenu->setPosition(ccp(-50,43));
		pDi->addChild(pMenu);
	m_pRank1->setSelectedIndex(1);
	ShowRank(0);
   return true;
}
void paihangbangScene::closeButton(CCObject * psender){
	GlobalCtrl::getInstance()->canSetting  = true;
    this->removeFromParentAndCleanup(true);	
}
 
void paihangbangScene::OnRank1( cocos2d::CCObject* sender )
{
	m_pRank1->setSelectedIndex(1);
	m_pRank2->setSelectedIndex(0);
	m_pRank3->setSelectedIndex(0);
	m_pRank4->setSelectedIndex(0);
	ShowRank(0);
}

void paihangbangScene::OnRank2( cocos2d::CCObject* sender )
{
	m_pRank1->setSelectedIndex(0);
	m_pRank2->setSelectedIndex(1);
	m_pRank3->setSelectedIndex(0);
	m_pRank4->setSelectedIndex(0);
	ShowRank(1);
}

void paihangbangScene::OnRank3( cocos2d::CCObject* sender )
{
	m_pRank1->setSelectedIndex(0);
	m_pRank2->setSelectedIndex(0);
	m_pRank3->setSelectedIndex(1);
	m_pRank4->setSelectedIndex(0);
	ShowRank(2);
}

void paihangbangScene::OnRank4( cocos2d::CCObject* sender )
{
	m_pRank1->setSelectedIndex(0);
	m_pRank2->setSelectedIndex(0);
	m_pRank3->setSelectedIndex(0);
	m_pRank4->setSelectedIndex(1);
	ShowRank(3);
}

void paihangbangScene::ShowRank()
{	
	bool remove = false;
	if ( m_pRankList->getChildByTag(1) )
		remove = true;
	for ( int i = 0; i < 3; i++ )
	{
		if (remove)
			m_pRankList->removeChildByTag(i+1);
		CCSprite* pSprite = CCSprite::create("tu7/paihangbang/xiaokuang.png");
		pSprite->setAnchorPoint(ccp(0,0));
		pSprite->setPosition(ccp(12, 272-56*i));
		m_pRankList->addChild(pSprite, 0, i+1);

		if ( rank_rank[i] == 0 )
			continue;

		if ( rank_rank[i] < 4 )
		{
			char buffer[255];
			sprintf(buffer, "tu7/paihangbang/%d.png", rank_rank[i]);
			CCSprite* pMedal = CCSprite::create(buffer);
			pMedal->setPosition(ccp(12, 27));
			pSprite->addChild(pMedal);
		}
		float sclae = 1.0f;
		int xdist = 0;
		int ydist = 0;
		if ( rank_rank[i] < 10 )
		{
			xdist = 0;
		}
		else if ( rank_rank[i] < 100 )
		{
			xdist = -14;
		}
		else if ( rank_rank[i] < 1000 )
		{
			sclae = 0.8f;
			xdist = -18;
			ydist = 1;
		}
		else if ( rank_rank[i] < 10000 )
		{
			sclae = 0.7f;
			xdist = -20;
			ydist = 4;
		}
		else if ( rank_rank[i] < 100000 )
		{
			sclae = 0.5f;
			xdist = -16;
			ydist = 6;
		}
		common::ShowNumber(pSprite, rank_rank[i], 26, 30, 32+xdist, 15+ydist, "tu7/paihangbang/paiming.png", 888, 0, sclae);
		if ( rank_name[i] != "" )
		{
			CCLabelTTF* pLabel = CCLabelTTF::create(rank_name[i].c_str(), "Arial", 27,
				CCSizeMake(170, 32), kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
			pLabel->setAnchorPoint(ccp(0,0));
			pLabel->setPosition(ccp(97, 15));
			pSprite->addChild(pLabel);
		}
		common::ShowNumber(pSprite, rank_score[i], 26, 30, 290, 16, "tu7/paihangbang/paiming.png", 889);
	}

	//if ( rank_rank[5] != 0 )
	//{
		float sclae = 1.0f;
		int xdist = 0;
		int ydist = 0;
		if ( rank_rank[5] < 10 )
		{
			xdist = 0;
		}
		else if ( rank_rank[5] < 100 )
		{
			xdist = -14;
		}
		else if ( rank_rank[5] < 1000 )
		{
			sclae = 0.8f;
			xdist = -18;
			ydist = 0;
		}
		else if ( rank_rank[5] < 10000 )
		{
			sclae = 0.7f;
			xdist = -20;
			ydist = 3;
		}
		else if ( rank_rank[5] < 100000 )
		{
			sclae = 0.5f;
			xdist = -16;
			ydist = 5;
		}
		common::ShowNumber(m_pRankList, rank_rank[5], 26, 30, 40+xdist, 5+ydist, "tu7/paihangbang/paiming.png", 888, 0, sclae);
		common::ShowNumber(m_pRankList, rank_score[5], 26, 30, 300, 5, "tu7/paihangbang/paiming.png", 889);
	//}
}


void paihangbangScene::ShowRank( int _type )
{
	if ( _type < 0 )
		return;
	//AppDelegate::AudioPlayEffect("MS2/rankPress.mp3");
	for ( int i = 0; i < 6; i++ )
	{
		rank_rank[i] = i + 1;
		rank_name[i] = "SSSSS";
		rank_score[i] = 2000 - i *100;
	}
	ShowRank();
}