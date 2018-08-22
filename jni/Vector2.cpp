#include <Vector2.h>
	Vector2::Vector2():x(0.0f),y(0.0f){};

	Vector2::Vector2(const Vector2 &copy) : x(copy.x) , y(copy.y){};

	Vector2::Vector2(float vx,float vy):x(vx),y(vy){};

	Vector2 &Vector2::operator=(const Vector2 &v){
		x=v.x;
		y=v.y;

		return *this;
	}

	bool Vector2::operator ==(const Vector2 &v) const{

		return x==v.x && y==v.y;
	}
	Vector2 Vector2::Rotate(float angle){
		float radias=EagleMath::ToRadians(angle);
		float sinX=sin(radias);
		float cosX=cos(radias);
		Vector2 v(x*cosX-sinX*y,x*sinX+y*cosX);
		return v;
	}

	bool Vector2::operator !=(const Vector2 &v) const{

		return x!=v.x || y!=v.y;
	}

	void Vector2::Zero(){x=y=0;}


	Vector2 Vector2::operator -() const{

		return Vector2(-x,-y);
	}

	Vector2 Vector2::operator +(const Vector2 &v)const{
		return Vector2(x+v.x,y+v.y);
	}
	Vector2 Vector2::operator -(const Vector2 &v)const{
			return Vector2(x-v.x,y-v.y);
	}

	Vector2 Vector2::operator *(float value)const{
		return Vector2(x*value,y*value);
	}
	Vector2 Vector2::operator /(float value)const{
			float v=1.0f/float(value);
			return Vector2(x,y)*v;
	}

	Vector2 &Vector2::operator +=(const Vector2 &v){
		x+=v.x;
		y+=v.y;

		return *this;
	}
	Vector2 &Vector2::operator -=(const Vector2 &v){
			x-=v.x;
			y-=v.y;

			return *this;
	}
	Vector2 &Vector2::operator *=(float value){
				x*=value;
				y*=value;

				return *this;
	}
	Vector2 &Vector2::operator /=(float value){
		float v=1.0f/float(value);
		x*=v;
		y*=v;

		return *this;
	}

	void Vector2::Normalize(){
		float magSq=float(x*x+y*y);
		if(magSq>0.0f){
			float oneOverMag=1.0f/sqrt(magSq);
			x*=oneOverMag;
			y*=oneOverMag;
		}
	}

	float Vector2::Dot(const Vector2 &v) const{

		return x*v.x+y*v.y;
	}

	float Vector2::Length(const Vector2 &v){

		return float(sqrt(v.x*v.x+v.y*v.y));
	}

	float Vector2::Distance(const Vector2 &v1,const Vector2 &v2){
		float dx=v2.x-v1.x;
		float dy=v2.y-v1.y;


		return float(sqrt(dx*dx+dy*dy));

	}

	Vector2 Vector2::Lerp(Vector2 dest,float lerpFactor){

		return (((dest-*this)*lerpFactor)+*this);
	}


	//Cross product
	Vector2  Vector2::CrossProduct(const Vector2 &v)const{
		Vector2 vecResult(
				x*v.y-y*v.x,
				y*v.x-x*v.y
				);
		return vecResult;
	}
	float Vector2::Max(){

		return max(x,y);
	}
