#include "GlobalCtrl.h"


GlobalCtrl* GlobalCtrl::_instance = NULL;

GlobalCtrl::GlobalCtrl() {
	shana = NULL;
	joyStick = NULL;
	skillButton = NULL;
	operatorLayer = NULL;
	menu = NULL;
	tilemap = NULL;
}


GlobalCtrl::~GlobalCtrl() {}


GlobalCtrl* GlobalCtrl::getInstance() {
	if ( _instance == NULL ) {
		_instance = new GlobalCtrl();
	}
	return _instance;
}


void GlobalCtrl::destroyInstance() {
	CC_SAFE_DELETE( _instance );
}