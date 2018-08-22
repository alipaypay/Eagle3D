#include "CoreActivity.h"

ANativeActivity* CoreActivity::activity;

void CoreActivity::SetActivity(ANativeActivity* activity){

	CoreActivity::activity=activity;
}


ANativeActivity* CoreActivity::GetActivity(){

	return CoreActivity::activity;

}
