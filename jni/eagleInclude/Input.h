
#ifndef INPUT_H
#define INPUT_H
#include <jni.h>
class Input{
public:
	static void SetMoveEventAction(float x,float y);
	static void SetDownEventAction(float x,float y);
	static void SetUpEventAction(float x,float y);
};
#endif
