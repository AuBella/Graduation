#ifndef _GAME_CONTROLER_H_
#define _GAME_CONTROLER_H_

#include "cocos2d.h"
#include "Background.h"
#include "Frontground.h"
//#include "Flash.h"
//#include "QuestionInfo.h"
////#include "CSizeLayer.h"

//////////////////
/****游戏数据****/
//////////////////
#define d_iMoneyS	5
#define d_iMoneyN	10
#define d_iMoneyL	50
#define d_iDropsDamage		10
#define d_iPoisonGasDamage	10
#define d_iGressDamage		10
#define d_iGressDist		50
#define d_iLandStayTime		15
#define d_iThunderDamage	3100

//////////////
/****主角****/
//////////////
#define d_fHeroSpeedX	3.8f
#define d_fHeroJump		14.0f
#define d_fHeroGravity	0.8f
#define d_fHeroCrashCX	0.0f
#define d_fHeroWidth	40.0f
#define d_fHeroHeight	88.0f
#define d_fHeroCenterY	0.0f
#define d_fScaleX		0.5f
#define d_fScaleY		0.7f
#define d_fHeroAnchorX	-0.0f
#define d_fHeroAnchorY	-18.0f

//////////////////
/****界面按钮****/
//////////////////
#define d_fStarMovieTime	0.1f
#define d_iStarW			139
#define	d_iStarH			135
#define d_fStarLocateX		300.0f
#define d_fStarLocateY		240.0f
#define d_fStarLocateX1		552.0f
#define d_fStarLocateY1		92.0f
#define d_fStarLocateX2		623.0f
#define d_fStarLocateY2		130.0f
#define d_fStarLocateX3		694.0f
#define d_fStarLocateY3		99.0f
#define d_iButtonSize		40
#define d_fBloodLocateX		107.0f
#define d_fBloodLocateY		71.0f
#define d_fBloodX			116.0f
#define d_fBloodY			71.0f
#define d_iActionNum		5
static const std::string g_sButtonPath[] =
{//按钮图片
	"tu4/zuo.png",		//左
	"tu4/you.png",		//右
	"tu4/gongji.png",	//打
	"tu4/tao.png",		//跳
	//"tu4/huanqiang.png",//切
	//"tu4/skillbtn1.png",	//技能
	//"tu4/shoulei.png",	//雷
	"tu4/zhanting1.png",//暂停
	//"tu4/an.png",//药瓶1
	//"tu4/an.png",//药瓶2
};
static const std::string g_sButtonPressPath[] =
{//按下图片
	"tu4/zuo2.png",		//左
	"tu4/you2.png",		//右
	"tu4/gongji2.png",	//打
	"tu4/tao2.png",		//跳
	//"tu4/huanqiang2.png",//切
	//"tu4/skillbtn2.png",	//技能
	//"tu4/shoulei2.png",	//雷
	"tu4/zhanting1.png",//暂停
	//"tu4/an.png",//药瓶1
	//"tu4/an.png",//药瓶2
};
static const float g_fButtonX[] =
{
	80,
	230,
	710,
	757,
	//650,
	//470,//520,
	//570,
	757.5,
	//404,
	//477,
};
static const float g_fButtonY[] =
{
	55,
	55,
	50,
	155,
	//444,
	//38,//33,
	//38,
	437,
	//446,
	//446,
};
static const float g_fButtonW[] =
{
	75.0,
	75.0,
	49.0,
	45.0,
	//80.0,
	//45.0,//45.0,
	//45.0,
	45.0,
	//40.0,
	//40.0,
};
static const float g_fButtonH[] =
{
	70.0,
	70.0,
	49.0,
	53.0,
	//25.0,
	//53,//53.0,
	//53.0,
	52.0,
	//40.0,
	//40.0,
};


//////////////////
/********按钮动作********/
//////////////////
enum e_ActionType
{
	eAT_MoveLeft = 0,
	eAT_MoveRight,
	eAT_Attack,
	eAT_Jump,
	//eAT_ChangeWeapon,
	//eAT_SKILL,
	//eAT_BOMB,
	eAT_PAUSE,
	//eAT_SKILL1,
	//eAT_SKILL2,
	eAT_NULL,
};

enum e_WeaponType
{
	eWT_Fire = -2,
	eWT_Grenade = -1,
	eWT_Knife /*= 2*/,
	eWT_Pistol,
	eWT_M4A1,
};

struct ItemObject
{
	cocos2d::CCSprite*	pSprite1;
	cocos2d::CCSprite*	pSprite2;
	float				x;
	float				y;
	int					time;
	int					type;
	int					num;

	ItemObject()
	{
		pSprite1	= NULL;
		pSprite2	= NULL;
		time		= 0;
		num			= 5;
	}
};

struct AttackingObject
{
	cocos2d::CCSprite*	pSprite;
	e_WeaponType		type;
	float				x;
	float				y;
	float				w;
	float				h;
	float				vx;
	float				vy;
	int					toward;
	float				speed;
	float				range;
	float				rotation;
	int					damage;
	int					time;
	int					life;
	int					index;
	int					isFirst;
	bool				wall;

	AttackingObject()
	{
		pSprite = NULL;
		life	= -1;
		isFirst	= 1;
		wall	= true;
	}
};

struct Shells
{
	cocos2d::CCSprite*	pSprite;
	float				x;
	float				y;
	float				vx;
	float				vy;
	float				rotate;
	int					life;

	Shells()
	{
		pSprite	= NULL;
		life	= 100;
	}
};

struct Chopper
{
	cocos2d::CCSprite*	pSprite;
	int					type;
	float				x;
	float				y;
	float				vx;
	float				vy;
	float				va;
	float				w;
	float				h;
	float				rotate;
	int					damage;
	int					time;
	int					clearTime;
	int					toward;
	bool				active;
	bool				bomb;
	bool				touchEarth;

	Chopper()
	{
		pSprite = NULL;
		time	= 16;
		rotate	= 0;
		active	= false;
		bomb	= false;
		touchEarth	= false;
	}
};

struct BoxDown
{
	cocos2d::CCSprite*	pSprite;
	float				x;
	float				y;
};

class CGameControler : public cocos2d::CCLayer
{
public:
	CGameControler();
	~CGameControler();
	CREATE_FUNC(CGameControler);
	virtual bool init();
	static CGameControler* NewGameControler(cocos2d::CCScene* _pScene, int _unLevel, int _difficult);
	static CGameControler* GetGameControler();
	void GameLoadingSecond();
	int		m_unLevel;
	int		m_iLevelType;
	int		m_iDifficult;
	int		m_iComboMax;
	int		m_iStateNumKill;
	int		m_iStateNumMedal;
	int		m_iStateNumGold;
	void Win(float _dt);
	void Lose(float _dt);
	void GameStart();
	void Timer(float _dt);
	void ButtonPressCheck();
	//显示血包
	void ShowHealBox();
	void ShowStar();
	void ShowStarMovie1(float _dt);
	void ShowStarMovie2(float _dt);
	void ShowStarMovie3(float _dt);
	void ShowStarBoss(float _dt);
	void ShowStarBoss1();
	void ShowOverBtn(float _dt);
	void MoveCheck(int _un, int _digit);
	void ShowScore();
	void PauseGame(int _type = 0);//暂停
	CBackground*			m_pCBackgroud;
	virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	cocos2d::CCSprite* m_pHero;
private:
	static CGameControler*	s_pGameControler;//controller
	cocos2d::CCNode*		m_pMenuNode;
	cocos2d::CCScene*		m_pScene;
	CFrontground*			m_pCFrontgroud;
	int m_iMapNum;//地图按钮数
	int		m_iHealBox;
	cocos2d::CCSprite*		m_pBG;
	int	m_iAllStar;
	cocos2d::CCNode*		m_pGameoverNode;
	cocos2d::CCNode*		m_pGameoverBtnNode;
	int	m_iStar;
	int*	m_pMoveActionArray;
	bool			m_bAttack;
	//CCSprite* m_pHero;
};

#endif
