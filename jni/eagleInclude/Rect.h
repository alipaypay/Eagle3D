#ifndef _RECT_H_
#define _RECT_H

class Rect{
public:
	float x;
	float y;
	float width;
	float height;
	Rect(float x,float y,float width,float height);
	Rect();
	void SetRect(float x,float y,float width,float height);
	Rect GetRect();
};
#endif
