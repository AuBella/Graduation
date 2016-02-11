#include"Ogre.h"

Ogre::Ogre(){
	faceDirecton = true;
	leftInTheMonster = true;
};

Ogre::~Ogre(){};
CCSprite* Ogre::GetSprite()
{
	return m_MonsterSprite;
}
bool Ogre::init(){
	
		if( !Role::init())
			return false;
		


		//���þ���
		m_MonsterSprite = CCSprite::create( "$kingslime_1.png", CCRect( 0, 0, 155, 162 ) );


		Monster_xue = new ProgressView();  
		if(faceDirecton)//��Ϊ�������Ĳ���ͼƬ���ģ�����ֻ�ܸ��ݹ��������������Ѫ���ĺ�����
			Monster_xue->setPosition(ccp(m_MonsterSprite->getPositionX()+20, m_MonsterSprite->getPositionY()+50));//�����ڹ�����ͷ  
		else
			Monster_xue->setPosition(ccp(m_MonsterSprite->getPositionX()-20, m_MonsterSprite->getPositionY()+50));  
		Monster_xue->setBackgroundTexture("xue_back.png");  
		Monster_xue->setForegroundTexture("xue_fore.png");  
		Monster_xue->setTotalProgress(300.0f);//������Ѫ��
		Monster_xue->setCurrentProgress(300.0f); //���ó�ʼѪ��

		this->addChild(Monster_xue);



		this->setSprite( m_MonsterSprite );
		this->addChild( getSprite() );
		this->setPosition(240, 200);
		//��ʼ�����ֶ���
		/*CCAnimation* standAnimn = AnimationUtil::getAnimation( "$maouox_1.png", 2, 2 );
		setStandAnimation( CCRepeatForever::create( CCAnimate::create( standAnimn ) ) );

		CCAnimation* runAnimn = AnimationUtil::getAnimation( "$maouox_forward.png", 6, 6 );
		setRunAnimation( CCRepeatForever::create( CCAnimate::create( runAnimn ) ) );

		CCAnimation* deadAnimn = AnimationUtil::getAnimation( "$maouox_dead.png", 3, 3 );
		setDeadAnimation( CCRepeatForever::create( CCAnimate::create( deadAnimn ) ) );

		CCAnimation* hurtAnimn = AnimationUtil::getAnimation( "$maouox_4.png", 2, 2 );
		setHurtAnimation( CCRepeatForever::create( CCAnimate::create( hurtAnimn ) ) );
		runStandAnimation();*/

		CCAnimation* standAnimn = AnimationUtil::getAnimation( "$shana_1.png", 4, 4 );
		setStandAnimation( CCRepeatForever::create( CCAnimate::create( standAnimn ) ) );

		CCAnimation* runAnimn = AnimationUtil::getAnimation( "$shana_forward.png", 8, 8 );
		setRunAnimation( CCRepeatForever::create( CCAnimate::create( runAnimn ) ) );

		CCAnimation* deadAnimn = AnimationUtil::getAnimation( "$shana_dead.png", 3, 3 );
		setDeadAnimation( CCRepeatForever::create( CCAnimate::create( deadAnimn ) ) );

		CCAnimation* hurtAnimn = AnimationUtil::getAnimation( "$shana_4.png", 2, 2 );
		setHurtAnimation( CCRepeatForever::create( CCAnimate::create( hurtAnimn ) ) );

		CCAnimation* skillA = AnimationUtil::getAnimation( "$shana_2.png", 7, 20 );
		CCAnimation* skillB = AnimationUtil::getAnimation( "$shana_2extra1.png", 9, 24 );
		setSkillA( CCRepeatForever::create(CCSequence::create( CCAnimate::create( standAnimn ),CCAnimate::create( skillA ),
			CCAnimate::create( skillB ),  nullptr )));
		runStandAnimation();
		
		//this->schedule(schedule_selector(Ogre::updateMonster),2.0f);//ÿ��3��������
		//this->scheduleUpdate();//Ӣ��һ��������ӷ�Χ������׷��Ӣ�۴�
	return true;
};

void Ogre::StartListen()
{
		shana = GlobalCtrl::getInstance()->shana;
		tileMap = GlobalCtrl::getInstance()->tilemap;
	this->schedule(schedule_selector(Ogre::updateMonster),2.0f);//ÿ��3��������
	this->scheduleUpdate();//Ӣ��һ��������ӷ�Χ������׷��Ӣ�۴�
}

void Ogre::enterSafeArea(){
	//CCLOG("enter Monster can see area");
	if(dis < 200)
		return;
	float width = getSprite()->getContentSize().width;
	float mapWidth = GlobalCtrl::getInstance()->tilemap->getContentSize().width;
	CCPoint curPos = this->getPosition();
	if(getSprite()->isFlipX());
	//faceDirecton = true;
	double distance = -min(curPos.x - width, 100);
	if(shana -> getSprite()->isFlipX()){
		//CCLOG("shana is face left");
		distance =min(mapWidth - width - curPos.x, 100);
		faceDirecton = false;
		//this->getSprite()->setFlipX( false );
	}
	else{
		//CCLOG("shana is face right");
		faceDirecton = true;
		//this->getSprite()->setFlipX( true );
	}
	CCCallFunc* callFuncRunAction = CCCallFunc::create(this, callfunc_selector(Role::runRunAnimation));
	CCMoveBy* move = CCMoveBy::create( 1.0f, CCPoint( distance, 0 ) );

	CCSpawn* moveAndRunAction = CCSpawn::create(callFuncRunAction, move, NULL);
	//������������
	CCCallFunc* callFuncStanAction = CCCallFunc::create(this, callfunc_selector(Role::runStandAnimation));
	CCActionInterval* xunluo=CCSequence::create(moveAndRunAction,callFuncStanAction,NULL);
	this->runAction(xunluo);
};

void Ogre::updateMonster(float delta){
	
	CCLOG("ENTER updateMonster dis ================>>>>>>>>>>>>>>>>> %f\n", dis);
	if(dis>=200){
		enterSafeArea();
	}
			//runSkillAAnimation();
};

void Ogre::update(float dt){
	if(faceDirecton != this->getSprite()->isFlipX())
		this->getSprite()->setFlipX( faceDirecton );
	CCLOG("ENTER update attack area ================>>>>>>>>>>>>>>>>> %f\n", dis);
	float x = shana->getPositionX()-(this->getPositionX()+tileMap->getPositionX());
	//�õ�����y�ľ��룬�ǵù��������Ҫ���ϵ�ͼ��
	float y = shana->getPositionY()-(this->getPositionY()+tileMap->getPositionY());
	//�ȼ�������Ӣ�۵ľ���
	dis = sqrt(pow(x,2) + pow(y,2));
	//����׷������
	if(dis > 200 &&dis <201){
		runStandAnimation();
	}
	if(dis <= 200){
		//���빥������
		//runStandAnimation();
		faceDirecton = shana->getPositionX()>this->getPositionX()? false:true;
		if(abs(x) <= 80){
			if(abs(y) < 10){
				runSkillAAnimation();
			}
		}
		if(abs(x) > 80 || abs(y) >= 10){
			if(abs(x) > 20 || abs(y) > 20){
				runRunAnimation();
			}
			enterAttackArea(x, y);
		}
	}/*
	else
		runStandAnimation();*/
};

void Ogre::enterAttackArea(float x, float y){
	//CCLOG("ENTER enterAttackArea ================>>>>>>>>>>>>>>>>> %f\n", dis);
	CCLOG("attackarea position : %f %f %f %f",this->getPositionX(), dis, x, y);
	float directionx = abs(x) <= 80? directionx = 0:(x > 0? 1: -1);
	float directiony = abs(y) <= 10? directiony = 0:y > 0? 1: -1;
	this->setPosition(this->getPositionX()+directionx*2,this->getPositionY()+directiony);
};