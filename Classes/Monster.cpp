#include "Monster.h"
USING_NS_CC; 
Monster::Monster(void)
{
	IsRunning=false;//û�ڷŶ���
	MonsterDirecton=TRUE;//�����˶�
	Monster_name=NULL;
	IsAttack=false;
	Monster_xue=NULL;
	my_hero=NULL;//��ǰӢ��
	my_map=NULL;//��ǰ��ͼ
	dis=10000;
	IsHurt=false;
	Isdead=false;
}

Monster::~ Monster(void)
{

}
CCSprite* Monster::GetSprite()
{
	return m_MonsterSprite;
}
void  Monster::InitMonsterSprite(char *name)
{
	Monster_name=name;
	this->m_MonsterSprite=CCSprite::create(name);
		m_MonsterSprite->setFlipX(MonsterDirecton);
	this->addChild(m_MonsterSprite);
}
void Monster::InitMonsterSprite(char *name,char *xue_back,char* xue_fore)
{
	InitMonsterSprite(name);

	//���ù����Ѫ�� 
	Monster_xue = new ProgressView();  
	if(MonsterDirecton)//��Ϊ�������Ĳ���ͼƬ���ģ�����ֻ�ܸ��ݹ��������������Ѫ���ĺ�����
		Monster_xue->setPosition(ccp(m_MonsterSprite->getPositionX()+20, m_MonsterSprite->getPositionY()+50));//�����ڹ�����ͷ  
	else
		Monster_xue->setPosition(ccp(m_MonsterSprite->getPositionX()-20, m_MonsterSprite->getPositionY()+50));  

	Monster_xue->setBackgroundTexture(xue_back);  
	Monster_xue->setForegroundTexture(xue_fore);  
	Monster_xue->setTotalProgress(300.0f);//������Ѫ��
	Monster_xue->setCurrentProgress(300.0f); //���ó�ʼѪ��

	this->addChild(Monster_xue);
}

//�����߶��Ķ���
void  Monster::SetAnimation(const char *name_each,unsigned int num,bool run_directon)
{
	//���÷���
	if(MonsterDirecton!=run_directon)
	{   MonsterDirecton=run_directon;
	    m_MonsterSprite->setFlipX(run_directon);
	}

	//�����߶������������˻����������ͷ���
	if(IsRunning||IsAttack||IsHurt||Isdead)
		return;

	//���ö���
	CCAnimation* animation = CCAnimation::create();  
	for( int i=1;i<=num;i++)  
	{  
		char szName[100] = {0};  
		sprintf(szName,"%s%d.png",name_each,i);  
		animation->addSpriteFrameWithFileName(szName); //���ض�����֡  
	}  
	animation->setDelayPerUnit(0.1f);//ÿ����ͼƬ��ʱ���� 
	animation->setRestoreOriginalFrame(true);  
	animation->setLoops(-1); //����ѭ��

	//��������װ��һ������
	CCAnimate* act=CCAnimate::create(animation);
	m_MonsterSprite->runAction(act);
	IsRunning=true;

}

//ֹͣ�߶���
void  Monster::StopAnimation()
{
	if(!IsRunning)
		return;

	m_MonsterSprite->stopAllActions();//��ǰ����ֹͣ���ж���
	//�ָ�����ԭ���ĳ�ʼ����ͼ 
	this->removeChild(m_MonsterSprite,TRUE);//��ԭ���ľ���ɾ����
	m_MonsterSprite=CCSprite::create(Monster_name);//�ָ�����ԭ������ͼ����
	m_MonsterSprite->setFlipX(MonsterDirecton);

	this->addChild(m_MonsterSprite);
	IsRunning=false;

	//����Ѫ��
	if(Monster_xue!=NULL)
	{
		if(MonsterDirecton)//��Ϊ�������Ĳ���ͼƬ���ģ�����ֻ�ܸ��ݹ��������������Ѫ���ĺ�����
			Monster_xue->setPosition(ccp(m_MonsterSprite->getPositionX()+20, m_MonsterSprite->getPositionY()+50));//�����ڹ�����ͷ  
		else
			Monster_xue->setPosition(ccp(m_MonsterSprite->getPositionX()-20, m_MonsterSprite->getPositionY()+50)); 
	}
}

//��������
void  Monster::AttackAnimation(const char *name_each,const unsigned int num,bool run_directon)
{
	//�����߶������������˻����������ͷ���
	if(IsRunning||IsAttack||IsHurt||Isdead)
		return;

	CCAnimation* animation = CCAnimation::create();  
	for( int i=1;i<=num;i++)  
	{  
		char szName[100] = {0};  
		sprintf(szName,"%s%d.png",name_each,i);  
		animation->addSpriteFrameWithFileName(szName); //���ض�����֡  
	}  
	animation->setDelayPerUnit(0.1f);  
	animation->setRestoreOriginalFrame(true);  
	animation->setLoops(1); //����ѭ��1��  

	//��������װ��һ������
	CCAnimate* act=CCAnimate::create(animation);
	//�����ص��������������������AttackEnd()
	CCCallFunc* callFunc=CCCallFunc::create(this,callfunc_selector(Monster::AttackEnd));
	//������������
	CCActionInterval* attackact=CCSequence::create(act,callFunc,NULL);

	m_MonsterSprite->runAction(attackact);  
	IsAttack=true;

}
void Monster::AttackEnd()
{
	//�ָ�����ԭ���ĳ�ʼ����ͼ 
	this->removeChild(m_MonsterSprite,TRUE);//��ԭ���ľ���ɾ����
	m_MonsterSprite=CCSprite::create(Monster_name);//�ָ�����ԭ������ͼ����
	m_MonsterSprite->setFlipX(MonsterDirecton);
	this->addChild(m_MonsterSprite);
	IsAttack=false;
}


void Monster::FollowRun(CCNode* m_hero,CCNode* m_map)
{

	//�õ�����x�ľ���,�ǵù��������Ҫ���ϵ�ͼ��
	float x = m_hero->getPositionX()-(this->getPositionX()+m_map->getPositionX());
	//�õ�����y�ľ��룬�ǵù��������Ҫ���ϵ�ͼ��
	float y = m_hero->getPositionY()-(this->getPositionY()+m_map->getPositionY());

   //�ȼ�������Ӣ�۵ľ���
	dis = sqrt(pow(x,2) + pow(y,2));

	if(dis>=300)//��������Ӣ�۾��볬��300
		return;
	if(dis<=100)//�ڹ��﹥����Χ�ڣ�����ֹͣ�ƶ�
	{
		this->StopAnimation();//ֹͣ�ܶ�
		JudegeAttack();//��һ���ĸ����ж����Ƿ��������
		return;
	}

	if(x<-100)//�жϹ���������Ӣ�۵ľ���
		{
			
			MonsterDirecton=true;
			m_MonsterSprite->setFlipX(MonsterDirecton);//���÷���
			if(IsAttack)
				return;
			 this->setPosition(this->getPositionX()-1,this->getPositionY());//������Ӣ���ƶ�
			 this->SetAnimation("monster_run",6,MonsterDirecton);//���Ŷ���

	}
	else if(x>100)
		{
			
			MonsterDirecton=false;
			m_MonsterSprite->setFlipX(MonsterDirecton);//���÷���
			if(IsAttack)
				return;
			this->setPosition(this->getPositionX()+1,this->getPositionY());
			 this->SetAnimation("monster_run",6,MonsterDirecton);//���Ŷ���
    }
	else if(x<=100)//����M���˺�Ӣ�������100����ʱ����ʼ�ƶ�����������
	{

		if(m_hero->getPositionY()>this->getPositionY())
		{
			m_MonsterSprite->setFlipX(MonsterDirecton);//���÷���
			if(IsAttack)
				return;
			this->setPosition(this->getPositionX(),this->getPositionY()+1);
			 this->SetAnimation("monster_run",6,MonsterDirecton);//���Ŷ���
		}
		else if(m_hero->getPositionY()<this->getPositionY())
		{
			m_MonsterSprite->setFlipX(MonsterDirecton);//���÷���
			if(IsAttack)
				return;
			this->setPosition(this->getPositionX(),this->getPositionY()-1);
			this->SetAnimation("monster_run",6,MonsterDirecton);//���Ŷ���
		}
	}

}
void Monster::JudegeAttack()
{
	srand((UINT)GetCurrentTime());
	int x = rand()%100;
	if(x>98)
	{
	this->AttackAnimation("monster_attack",5,MonsterDirecton);
	}

}
void  Monster::MonsterSeeRun()
{

	if(dis<300)
		return;
	 this->SetAnimation("monster_run",6,MonsterDirecton);//���Ŷ���
	 CCMoveBy *moveby1;

	 //��������Ѳ��
	 if(MonsterDirecton==true)
	 {	
     moveby1=CCMoveBy::create(2,ccp(-100,0));
	  MonsterDirecton=false;
	 }
	 else
	 {
     moveby1=CCMoveBy::create(2,ccp(100,0));
	  MonsterDirecton=true;
	 }

	//�����ص�������Ѳ��·�����
	CCCallFunc* callFunc=CCCallFunc::create(this,callfunc_selector(Monster::StopAnimation));
	//������������
	CCActionInterval* xunluo=CCSequence::create(moveby1,callFunc,NULL);
	this->runAction(xunluo);
}
//��������
void Monster::StartListen(CCNode* m_hero,CCNode* m_map)
{
	 my_hero=m_hero;
	 my_map=m_map;
	this->schedule(schedule_selector(Monster::updateMonster),3.0f);//ÿ��3��������
	this->scheduleUpdate();//Ӣ��һ��������ӷ�Χ������׷��Ӣ�۴�
}
//��������,ÿ��3������
void Monster::updateMonster(float delta)
{
	//���������ͷ���
	if(Isdead)
		return;
	//�õ�����x�ľ���,�ǵù��������Ҫ���ϵ�ͼ��
	float x = my_hero->getPositionX()-(this->getPositionX()+my_map->getPositionX());
	//�õ�����y�ľ��룬�ǵù��������Ҫ���ϵ�ͼ��
	float y = my_hero->getPositionY()-(this->getPositionY()+my_map->getPositionY());
	//�ȼ�������Ӣ�۵ľ���
	dis = sqrt(pow(x,2) + pow(y,2));
	if(dis>=300)
	{
		if(!IsRunning)
		MonsterSeeRun();
	}
}
void Monster::update(float delta)
{
	//���������ͷ���
	if(Isdead)
		return;
	if(dis<300)///��Ӣ�������Ŀ��ӷ�Χ�ڣ�����׷��Ӣ��
	FollowRun(my_hero,my_map);
}


//���˶���
void Monster::HurtAnimation(const char *name_each,const unsigned int num,bool run_directon)
{
	if(IsHurt||Isdead)
		return;
	//��������
	if(IsRunning||IsAttack)
	{
		m_MonsterSprite->stopAllActions();//��ǰ����ֹͣ���ж���
	   //�ָ�����ԭ���ĳ�ʼ����ͼ 
	  this->removeChild(m_MonsterSprite,TRUE);//��ԭ���ľ���ɾ����
	  m_MonsterSprite=CCSprite::create(Monster_name);//�ָ�����ԭ������ͼ����
	  m_MonsterSprite->setFlipX(MonsterDirecton);
	  this->addChild(m_MonsterSprite);
	  IsRunning=false;
	  IsAttack=false;
	}
	

	CCAnimation* animation = CCAnimation::create();  
	for( int i=1;i<=num;i++)  
	{  
		char szName[100] = {0};  
		sprintf(szName,"%s%d.png",name_each,i);  
		animation->addSpriteFrameWithFileName(szName); //���ض�����֡  
	}  
	animation->setDelayPerUnit(2.8f/14.0f);  
	animation->setRestoreOriginalFrame(true);  
	animation->setLoops(1); //����ѭ��1��  
	//��������װ��һ������
	CCAnimate* act=CCAnimate::create(animation);
	//�����ص����������˶�����������HurtEnd()
	CCCallFunc* callFunc=CCCallFunc::create(this,callfunc_selector(Monster::HurtEnd));
	//������������
	CCActionInterval* hurtackact=CCSequence::create(act,callFunc,NULL);

	m_MonsterSprite->runAction(hurtackact);  
	IsHurt=true;


}
//���˶�������
void Monster::HurtEnd()
{
	IsHurt=false;
	Monster_xue->setCurrentProgress(Monster_xue->getCurrentProgress()-10);
	if(Monster_xue->getCurrentProgress()==0)
	{
		//���Ź�����������
		DeadAnimation("monster_dead",2,MonsterDirecton);
	}	
}
//��������
void Monster::DeadAnimation(const char *name_each,const unsigned int num,bool run_directon)
{
	Isdead=true;
	CCAnimation* animation = CCAnimation::create();  
	for( int i=1;i<=num;i++)  
	{  
		char szName[100] = {0};  
		sprintf(szName,"%s%d.png",name_each,i);  
		animation->addSpriteFrameWithFileName(szName); //���ض�����֡  
	}  
	animation->setDelayPerUnit(2.8f/14.0f);  
	animation->setRestoreOriginalFrame(true);  
	animation->setLoops(1); //����ѭ��1��  
	//��������װ��һ������
	CCAnimate* act=CCAnimate::create(animation);
	//�����ص��������������������deadact()
	CCCallFunc* callFunc=CCCallFunc::create(this,callfunc_selector(Monster::DeadEnd));
	//������������
	CCActionInterval* deadact=CCSequence::create(act,callFunc,NULL);
	m_MonsterSprite->runAction(deadact);  

}
//������������
void Monster::DeadEnd()
{
	//�ָ�����������
	this->removeChild(m_MonsterSprite,TRUE);//��ԭ���ľ���ɾ����
	m_MonsterSprite=CCSprite::create("monster_dead2.png");//�ָ�����������
	m_MonsterSprite->setFlipX(MonsterDirecton);
	this->addChild(m_MonsterSprite);
	//����Ѫ��
	if(Monster_xue!=NULL)
	{
		if(MonsterDirecton)//��Ϊ�������Ĳ���ͼƬ���ģ�����ֻ�ܸ��ݹ��������������Ѫ���ĺ�����
			Monster_xue->setPosition(ccp(m_MonsterSprite->getPositionX()+60, m_MonsterSprite->getPositionY()));//�����ڹ�����ͷ  
		else
			Monster_xue->setPosition(ccp(m_MonsterSprite->getPositionX()-60, m_MonsterSprite->getPositionY())); 
	}
	//����������������
	CCBlink* blinkact=CCBlink::create(3,6);//3�ǳ���ʱ�䣬6�����Ĵ���
		
	//�����ص���������˸���������BlinkEnd()
	CCCallFunc* callFunc=CCCallFunc::create(this,callfunc_selector(Monster::BlinkEnd));
	//������������
	CCActionInterval* deadact=CCSequence::create(blinkact,callFunc,NULL);
	m_MonsterSprite->runAction(deadact);

}
//��˸����
void Monster::BlinkEnd()
{
this->removeAllChildren();//�ѹ����Ѫ����ɾ����;
}

