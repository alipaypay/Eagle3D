#include <Rect.h>

Rect::Rect():x(0),y(0),width(0),height(0){

}

Rect::Rect(float x,float y,float width,float height):
		x(x),y(y),width(width),height(height)
{
}

void Rect::SetRect(float x,float y,float width,float height){
	this->x=x;
	this->y=y;
	this->width=width;
	this->height=height;

}
Rect Rect::GetRect(){

	return Rect(x,y,width,height);

}
