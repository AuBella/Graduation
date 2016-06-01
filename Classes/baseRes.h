#pragma warning (disable:4068)

#define GameTypeA 

////////////
//**平台**//
////////////
#define Plat_Telecom
//#define Plat_Telecom_Logo
 #define Plat_Telecom_Demo
//#define Plat_91
//#define Plat_Unicom	//适合三网
//#define Plat_MM


#define Pay_GOC_Can

//正常地图总关数
#define LevelLimit	6   

//挑战关开启
#define ChallengeLevel	

//正版验证只有2处而非原始的4处
#define PayGOCTwo

//无新手引导关
#define No_Trans

//商店和其他地方无购买金钱
#define NoGetMoney

//无关于内容
//#define No_About

//关卡全开
#define All_Level_Open

//BOSS关全卡
#define Boss_Level_Open


#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#define CCLogError(...) __android_log_print(ANDROID_LOG_ERROR,"TaijiLog", __VA_ARGS__)
#endif

#ifndef _BASE_RESOUCE_H_
#define _BASE_RESOUCE_H_

#define WINSIZE         CCDirector::sharedDirector()->getWinSize()//([[CCDirector sharedDirector] winSize])

#define WINSIZE_W       (WINSIZE.width)
#define WINSIZE_H       (WINSIZE.height)
#define S_WINSIZE_W     800
#define S_WINSIZE_H     480
#define Scale_X         ((WINSIZE_W)/S_WINSIZE_W)
#define Scale_Y         ((WINSIZE_H)/S_WINSIZE_H)

#define SetScale(object) \
	object->setAnchorPoint(ccp(0.0f, 0.0f)); \
	object->setScaleX(Scale_X);\
	object->setScaleY(Scale_Y);

#define SetScaleY(object) \
	object->setAnchorPoint(ccp(0.5f, 0.5f)); \
	object->setScaleX(Scale_X);\
	object->setScaleY(Scale_Y);
//////////////
/****主角****/
//////////////
#pragma mark 主角
#define d_unHeroFrame	40
#define d_iRotateObjectNum 3
static std::string d_sRotateObject[] =
{
	"tou",
	"shou1",
	"shou2",
};
#define d_iRotateFireNum 16
static std::string d_sRotateFire[] =
{
	"qhuohua11",
	"qhuohua110",
	"qhuohua130",
	"qhuohua131",
	"qhuohua13",
	"sdhuo 1",
	"qhuohua14",
	"qhuohua1402",
	"qhuohua9",
	"qhuohua8",
	"qhuohua82",
	"qhuohua148",
	"qhuohua1408",
	"qhuohua",
	"qhuoguang15",
	"qhuoguang150",
};

static std::string g_sHeroAction[] = 
{
	"",
	"chuanqidz",
	"paobudz",
};

//////////////
/****Tile****/
//////////////
#pragma mark Tile
#define d_fMapSizeX		800.0f
#define d_fSpan			25.0f
#define d_fCantMove		20.0f
#define d_fActiveLength 800.0f
#define d_fStairFix		16.0f
#define d_iShowDepth	3
#define d_iGraviTime	4
#define	d_fRampHeight	8.0
#define d_fReleaseLength 1000.0f
#define d_iWinTime		20
static int g_iHideLevelY[] =
{
	1440,
	1440,
	1440,
};

static int g_unWaveNum[] =
{
	3,
	0,
	3,
	4,
	3,
};

static int g_unMapNum[] =
{
	3,3,1,3,4,4,
	3,1,3,1,4,4,
	3,1,3,1,4,4,
	3,1,3,1,4,4,
	0,0,0,0,0,0,
	1,
	0,0,0,0,
	0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,
	1,1,1,1,1,1,
	1,1,1,1,1,1,
};
static std::string g_sBGPath[] =
{
	"Tile/beijing1.png",
	"Tile/beijing2.png",
	"Tile/beijing3.png",
	"Tile/beijing4.png",
	"Tile/beijing1.png",
	"Tile/beijing1.png",

	"Tile/beijing2.png",
	"Tile/beijing2.png",
	"Tile/beijing2.png",
	"Tile/beijing2.png",
	"Tile/beijing2.png",
	"Tile/beijing2.png",

	"Tile/beijing3.png",
	"Tile/beijing3.png",
	"Tile/beijing3.png",
	"Tile/beijing3.png",
	"Tile/beijing3.png",
	"Tile/beijing3.png",

	"Tile/beijing4.png",//4
	"Tile/beijing4.png",
	"Tile/beijing4.png",
	"Tile/beijing4.png",
	"Tile/beijing4.png",
	"Tile/beijing4.png",

	"Tile/beijing3.png",//5
	"Tile/beijing3.png",
	"Tile/beijing3.png",
	"Tile/beijing3.png",
	"Tile/beijing3.png",
	"Tile/beijing3.png",

	"Tile/beijing1.png",//6
	"Tile/beijing1.png",
	"Tile/beijing3.png",
	"Tile/beijing3.png",
	"Tile/beijing3.png",
	"Tile/beijing3.png",

	"Tile/beijing3.png",
	"Tile/beijing3.png",
	"Tile/beijing3.png",
	"Tile/beijing3.png",
	"Tile/beijing3.png",
	"Tile/beijing3.png",

	"Tile/beijing1.png",
	"Tile/beijing2.png",
	"Tile/beijing3.png",
	"Tile/beijing3.png",
	"Tile/beijing3.png",
	"Tile/beijing3.png",
	"Tile/beijing3.png",

	"Tile/beijing1.png",//挑战
	"Tile/beijing2.png",
	"Tile/beijing3.png",
	"Tile/beijing3.png",
	"Tile/beijing3.png",
	"Tile/beijing3.png",

	"Tile/beijing1.png",//BOSS
	"Tile/beijing2.png",
	"Tile/beijing3.png",
	"Tile/beijing4.png",
	"Tile/beijing3.png",
	"Tile/beijing1.png",
};
static std::string g_sMGPath[] =
{
	"Tile/a1levmg.tmx",
	"Tile/a2levmg.tmx",
	"Tile/a1levmg.tmx",
	"Tile/a2levmg.tmx",
	"Tile/a1levmg.tmx",
	"Tile/a2levmg.tmx",

	"Tile/b1levmg.tmx",
	"Tile/b2levmg.tmx",
	"Tile/b1levmg.tmx",
	"Tile/b2levmg.tmx",
	"Tile/b1levmg.tmx",
	"Tile/b2levmg.tmx",

	"Tile/c1levmg.tmx",
	"Tile/c2levmg.tmx",
	"Tile/c1levmg.tmx",
	"Tile/c2levmg.tmx",
	"Tile/c1levmg.tmx",
	"Tile/c2levmg.tmx",

	"Tile/d1levmg.tmx",
	"Tile/d2levmg.tmx",
	"Tile/d1levmg.tmx",
	"Tile/d2levmg.tmx",
	"Tile/d1levmg.tmx",
	"Tile/d2levmg.tmx",

	"Tile/a1levmg.tmx",
	"Tile/a2levmg.tmx",
	"Tile/a1levmg.tmx",
	"Tile/a2levmg.tmx",
	"Tile/a1levmg.tmx",
	"Tile/a2levmg.tmx",

	"Tile/a1levmg.tmx",
	"Tile/a2levmg.tmx",
	"Tile/a1levmg.tmx",
	"Tile/a2levmg.tmx",
	"Tile/a1levmg.tmx",
	"Tile/a2levmg.tmx",

	"Tile/a1levmg.tmx",
	"Tile/a2levmg.tmx",
	"Tile/a1levmg.tmx",
	"Tile/a2levmg.tmx",
	"Tile/a1levmg.tmx",
	"Tile/a2levmg.tmx",

	"Tile/a1levmg.tmx",
	"Tile/b1levmg.tmx",
	"Tile/c1levmg.tmx",
	"Tile/a1levmg.tmx",
	"Tile/a1levmg.tmx",
	"Tile/a1levmg.tmx",
	"Tile/a1levmg.tmx",

	"Tile/a2levmg.tmx",//挑战
	"Tile/b2levmg.tmx",
	"Tile/c2levmg.tmx",
	"Tile/c2levmg.tmx",
	"Tile/c2levmg.tmx",
	"Tile/c2levmg.tmx",

	"Tile/a2levmg.tmx",//BOSS
	"Tile/b2levmg.tmx",
	"Tile/c2levmg.tmx",
	"Tile/d2levmg.tmx",
	"Tile/a2levmg.tmx",
	"Tile/a2levmg.tmx",
};
static std::string g_sNGPath[] =
{
	"Tile/a1levjg.tmx",
	"Tile/a2levjg.tmx",
	"Tile/a3levjg.tmx",
	"Tile/a4levjg.tmx",
	"Tile/a5levjg.tmx",
	"Tile/a6levjg.tmx",

	"Tile/b1levjg.tmx",
	"Tile/b2levjg.tmx",
	"Tile/b3levjg.tmx",
	"Tile/b4levjg.tmx",
	"Tile/b5levjg.tmx",
	"Tile/b6levjg.tmx",

	"Tile/c1levjg.tmx",
	"Tile/c2levjg.tmx",
	"Tile/c3levjg.tmx",
	"Tile/c4levjg.tmx",
	"Tile/c5levjg.tmx",
	"Tile/c6levjg.tmx",

	"Tile/d1levjg.tmx",
	"Tile/d2levjg.tmx",
	"Tile/d3levjg.tmx",
	"Tile/d4levjg.tmx",
	"Tile/d5levjg.tmx",
	"Tile/d6levjg.tmx",

	"Tile/c1levjg.tmx",
	"Tile/c2levjg.tmx",
	"Tile/c3levjg.tmx",
	"Tile/c4levjg.tmx",
	"Tile/c5levjg.tmx",
	"Tile/c6levjg.tmx",

	"Tile/c1levjg.tmx",
	"Tile/c2levjg.tmx",
	"Tile/c3levjg.tmx",
	"Tile/c4levjg.tmx",
	"Tile/c5levjg.tmx",
	"Tile/c6levjg.tmx",

	"Tile/c1levjg.tmx",
	"Tile/c2levjg.tmx",
	"Tile/c3levjg.tmx",
	"Tile/c4levjg.tmx",
	"Tile/c5levjg.tmx",
	"Tile/c6levjg.tmx",

	"Tile/a7levjg.tmx",
	"Tile/b7levjg.tmx",
	"Tile/c7levjg.tmx",
	"Tile/c7levjg.tmx",
	"Tile/c7levjg.tmx",
	"Tile/c7levjg.tmx",
	"Tile/c7levjg.tmx",

	"Tile/x-alevjg.tmx",//挑战
	"Tile/x-blevjg.tmx",
	"Tile/x-clevjg.tmx",
	"Tile/x-clevjg.tmx",
	"Tile/x-clevjg.tmx",
	"Tile/x-clevjg.tmx",

	"Tile/bjg.tmx",//BOSS
	"Tile/bjg.tmx",
	"Tile/bjg.tmx",
	"Tile/bjg.tmx",
	"Tile/bjg.tmx",
	"Tile/bjg.tmx",
};
static std::string g_sTilePath[] =
{
	"Tile/a1lev.tmx",
	"Tile/a2lev.tmx",
	"Tile/a3lev.tmx",
	"Tile/a4lev.tmx",
	"Tile/a5lev.tmx",
	"Tile/a6lev.tmx",

	"Tile/b1lev.tmx",
	"Tile/b2lev.tmx",
	"Tile/b3lev.tmx",
	"Tile/b4lev.tmx",
	"Tile/b5lev.tmx",
	"Tile/b6lev.tmx",

	"Tile/c1lev.tmx",
	"Tile/c2lev.tmx",
	"Tile/c3lev.tmx",
	"Tile/c4lev.tmx",
	"Tile/c5lev.tmx",
	"Tile/c6lev.tmx",

	"Tile/d1lev.tmx",
	"Tile/d2lev.tmx",
	"Tile/d3lev.tmx",
	"Tile/d4lev.tmx",
	"Tile/d5lev.tmx",
	"Tile/d6lev.tmx",

	"Tile/c1lev.tmx",
	"Tile/c2lev.tmx",
	"Tile/c3lev.tmx",
	"Tile/c4lev.tmx",
	"Tile/c5lev.tmx",
	"Tile/c6lev.tmx",

	"Tile/c1lev.tmx",
	"Tile/c2lev.tmx",
	"Tile/c3lev.tmx",
	"Tile/c4lev.tmx",
	"Tile/c5lev.tmx",
	"Tile/c6lev.tmx",

	"Tile/c1lev.tmx",
	"Tile/c2lev.tmx",
	"Tile/c3lev.tmx",
	"Tile/c4lev.tmx",
	"Tile/c5lev.tmx",
	"Tile/c6lev.tmx",

	"Tile/a7lev.tmx",
	"Tile/b7lev.tmx",
	"Tile/c7lev.tmx",
	"Tile/c7lev.tmx",
	"Tile/c7lev.tmx",
	"Tile/c7lev.tmx",
	"Tile/c7lev.tmx",

	"Tile/x-alev.tmx",
	"Tile/x-blev.tmx",
	"Tile/x-clev.tmx",
	"Tile/x-clev.tmx",
	"Tile/x-clev.tmx",
	"Tile/x-clev.tmx",

	"Tile/ab.tmx",
	"Tile/bb.tmx",
	"Tile/cb.tmx",

};
static std::string g_sBoxPath[] =
{
	"Tile/xiangzi.png",
	"Tile/xiangzi.png",
};
static std::string g_sStairPath[] =
{
	"Tile/a1.png",
	"Tile/a2.png",
	"Tile/b1.png",
	"Tile/b2.png",
	"",
	"",
	"",
	"Tile/a8.png"
};
static std::string g_sDefencePath[] =
{
	"Tile/a5.png",
	"Tile/a6.png",
	"Tile/a5.png",
	"Tile/a6.png",
};
static std::string g_sWallPath[] =
{
	"",
	"Tile/a7.png",
	"Tile/b7.png",
};
static std::string g_sDownStairPath[] =
{
	"Tile/b1.png",
	"Tile/b2.png",
};
#define g_iItemNum 10
//static const std::string g_sItemPath[] =
//{
//	"",
//};

//////////////////
/****武器相关****/
//////////////////
#pragma mark 武器相关
#define d_iHealBoxMax		3
#define d_iGrenadeMax		10
#define d_iWeaponNum		3
#define d_fShellsX			20.0f
#define d_fShellsY			70.0f
#define d_fShellsVX			4.0f
#define d_fShellsVY			4.0f
#define d_iShellsCooltime	50
#define d_fWeaponCenterX	0.0f
#define d_fWeaponCenterY	50.0f
#define d_fRunHigher		11.0f
#define d_fJumpHigher		12.0f
#define d_fJumpFire			18.0f
#define d_fGrenadeW			10
#define d_fGrenadeH			10
#define	d_fGrenadeRange		200
static int g_iWeaponBulletOnce[] =
{
	0,0,
	12,7,30,
	40,30,30,
	50,15,35,100,
	100, 100,
	0, 0, 45, 35,
};
static int g_iWeaponCooltime[] = 
{
	0,0,
	35,12,4,
	20,35,8,
	25,15,10,5,
	4, 35,
	35, 35, 20, 16,
};
static int g_iWeaponDamage[] = 
{
	8,300,
	50,30,15,40,
	150,30,90,60,
	40,25,
	25,300,
	60,100, 150, 100,
};
static int g_iWeaponUpgradeD[] =
{
	0, 0,
	10, 10, 10,
	10, 50, 10,
	20, 20, 10, 10,
	10, 100,
	20, 20, 30, 20,
};
static int g_iWeaponUpgradeS[] =
{
	0, 0,
	0, 0, 0,
	0, 0, 0,
	0, 0, 0, 0,
	0, 0,
	0, 0, 0, 0,
};

static float g_fWeaponStartLength[] =
{
	52.0,52.0,
	62.0,52.0,52.0,62.0,
	52.0,52.0,62.0,52.0,
	52.0,62.0,62.0,62.0,
};
static float g_fWeaponStartSpeed[] =
{
	//0,
	//0,
	30.0,
	10.0,
	10.0,
};
static float g_fFireX[] =
{
	0,0,
	0,55,51,
	57,0,54,
	58,50,60,72,44,44,
};
static float g_fFireY[] =
{
	0,0,
	0,59,54,
	53,0,56,
	46,41,59,44,20,20,
};
static float g_fFireX2[] =
{
	0,0,
	0,40,37,
	44,0,48,
	41,32,49,53,32,
	0,0,0,48,48,
};
static float g_fFireY2[] =
{
	0,0,
	0,59,54,
	53,0,56,
	51,46,59,51,20,
	0,0,0,53,56,
};
static int g_fFireX3 = 42;
static int g_fFireY3 = 60;
static int g_fFireX3S = 38;
static int g_fFireY3S = 60;
//////////////
/****怪物****/
//////////////
#pragma mark 怪物资源
#define g_fMonsterView	200.0f
#define g_fChopperW		52.0f
#define g_fChopperH		36.0f
#define g_iMonsterNum	12
static std::string g_cMonsterPath[] = 
{
	"Monster/js1dz.png",//1
	"Monster/js2dz.png",
	"Monster/js4dz.png",
	"Monster/js5dz.png",
	"Monster/js3dz.png",//5
	"Monster/jsboss1dz.png",
	"Monster/js9dz.png",
	"Monster/js10dz.png",
	"Monster/jsboss2_main.png",
	"Monster/js7dz.png",//10
	"Monster/js8dz.png",
	"Monster/js6dz.png",
	"Monster/jsboss3_1.png",
	"Monster/jsboss4_1.png",
	"Monster/jsboss5_1.png",
	"Monster/js11dz.png",
	"Monster/jsboss5_fj.png",
	"Monster/jsboss6_1.png",
};
static std::string g_cMonsterPlist[] = 
{
	"Monster/js1dz.plist",
	"Monster/js2dz.plist",
	"Monster/js4dz.plist",
	"Monster/js5dz.plist",
	"Monster/js3dz.plist",
	"Monster/jsboss1dz.plist",
	"Monster/js9dz.plist",
	"Monster/js10dz.plist",
	"Monster/jsboss2_main.plist",
	"Monster/js7dz.plist",
	"Monster/js8dz.plist",
	"Monster/js6dz.plist",
	"Monster/jsboss3_1.plist",
	"Monster/jsboss4_1.plist",
	"Monster/jsboss5_1.plist",
	"Monster/js11dz.plist",
	"Monster/jsboss5_fj.plist",
	"Monster/jsboss6_1.plist",
};
static std::string g_cMonsterXML[] = 
{
	"Monster/js1dz.json",
	"Monster/js2dz.json",
	"Monster/js4dz.json",
	"Monster/js5dz.json",
	"Monster/js3dz.json",
	"Monster/jsboss1dz.json",
	"Monster/js9dz.json",
	"Monster/js10dz.json",
	"Monster/jsboss2_main.json",
	"Monster/js7dz.json",
	"Monster/js8dz.json",
	"Monster/js6dz.json",
	"Monster/jsboss3.json",
	"Monster/jsboss4.json",
	"Monster/jsboss5.json",
	"Monster/js11dz.json",
	"Monster/jsboss5_fj.json",
	"Monster/jsboss6.json",
};
static std::string g_sMonsterName[] = 
{
	"js1dz",
	"js2dz",
	"js4dz",
	"js5dz",
	"js3dz",
	"jsboss1dz",
	"js9dz",
	"js10dz",
	"jsboss2_shenti",
	"js7dz",
	"js8dz",
	"js6dz",
	"jsboss3",
	"jsboss4",
	"jsboss5",
	"js11dz",
	"jsboss5_feiji",
	"jsboss6",
};

#pragma mark 其他
//////////////
/****参数****/
//////////////

#define PI_FIX (3.14159265/180.0)

////////////////
/****方法宏****/
////////////////
#define DELETEITERATORFROMVECTOR(_VEC_, _IT_) \
delete *_IT_;\
_VEC_.erase(_IT_)

#define DELETESPRITEFROMFATHER(_FATHER_, _CHILD_) \
if ( _CHILD_ ) \
{ \
	_FATHER_->removeChild(_CHILD_); \
	delete _CHILD_; \
	_CHILD_ = NULL; \
}

#define SAFEDELETE(_P_) \
if ( _P_ ) \
{ \
	delete _P_;\
	_P_ = NULL;\
}

#define SAFEDELETEARRAY(_P_) \
if ( _P_ ) \
{ \
	delete[] _P_;\
	_P_ = NULL;\
}

#define REMOVE_SELF(_P_) \
	if ( _P_ ) \
{ \
	_P_->removeFromParentAndCleanup(true); \
	_P_ = NULL; \
}

#define VECTORCLEAN(_VEC_, _TEMPLATE_) \
if ( _VEC_.size() ) \
{ \
	for ( std::vector<_TEMPLATE_*>::iterator it = _VEC_.begin(); \
	it != _VEC_.end(); it++ ) \
	SAFEDELETE( *it ); \
	_VEC_.clear(); \
}

#define DIS_SELF(_NUM_) \
	if ( _NUM_ > 0 ) \
		_NUM_--

#endif
