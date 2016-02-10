#include "GlobalCtrl.h"


GlobalCtrl* GlobalCtrl::_instance = nullptr;

GlobalCtrl::GlobalCtrl() {}


GlobalCtrl::~GlobalCtrl() {}


GlobalCtrl* GlobalCtrl::getInstance() {
	if ( _instance == nullptr ) {
		_instance = new GlobalCtrl();
	}
	return _instance;
}


void GlobalCtrl::destroyInstance() {
	CC_SAFE_DELETE( _instance );
}