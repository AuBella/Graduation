#ifndef __Monster_H__
#define __Monster_H__
#include "cocos2d.h"
#include "ProgressView.h"
USING_NS_CC;
class Monster:public cocos2d::CCNode
{
public:
	Monster(void);
	~Monster(void);
	//����ͼƬ�������������Ѫ���Ĺ���
	void InitMonsterSprite(char *name);
	//����ͼƬ�����������Ѫ���Ĺ���
	void InitMonsterSprite(char *name,char *xue_back,char* xue_fore);

	//�����߶�����,numΪͼƬ��Ŀ��run_directonΪ����������false����,name_eachΪname_png��ÿһС��ͼƬ�Ĺ������Ʋ���
	void SetAnimation(const char *name_each,const unsigned int num,bool run_directon);
	//ֹͣ�߶�����
	void StopAnimation();
	//�ж��Ƿ����ܶ���
	bool IsRunning;

	//��������
	void AttackAnimation(const char *name_each,const unsigned int num,bool run_directon);
	//������������
	void AttackEnd();
	//�ж��Ƿ��ڹ�������
	bool IsAttack;

	//���˶���
	void HurtAnimation(const char *name_each,const unsigned int num,bool run_directon);
	//���˶�������
	void HurtEnd();
	//�ж��Ƿ������˶���
	bool IsHurt;

	//��������
	void DeadAnimation(const char *name_each,const unsigned int num,bool run_directon);
	//������������
	void DeadEnd();
	//�ж��Ƿ�����
	bool Isdead;

	//����������˸����
	void BlinkEnd();

	//����Ӣ��
	CCSprite* GetSprite();
	//�����˶��ķ���
	bool MonsterDirecton;

	//�ڿ��ӷ�Χ�ڣ��������Ӣ���˶�
	void FollowRun(CCNode* m_hero,CCNode* m_map);
	//�ж��Ƿ񹥻�
	void JudegeAttack();
	//����Ѳ��·��
	void MonsterSeeRun();


	//������������Ӣ��
	void StartListen(CCNode* m_hero,CCNode* m_map);
	//��������,ÿ��3�����£�����Ӣ�������ľ���
	void updateMonster(float delta);
	//���º��������Ӣ���ڿ��ӷ�Χ�ڣ����ϴ���
	void update(float delta);

	CREATE_FUNC(Monster);

private:
	CCSprite* m_MonsterSprite;//���ﾫ��
	char *Monster_name;//���������ʼ״̬�ľ���ͼƬ����
	ProgressView*  Monster_xue;//����Ѫ��
	CCNode* my_hero;//��ǰӢ��
	CCNode* my_map;//��ǰ��ͼ
	float   dis;//��ǰ�����Ӣ�۵ľ���
	
};
#endif // 

