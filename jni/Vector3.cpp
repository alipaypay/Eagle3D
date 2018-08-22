#include "Vector3.h"
#include "Quaternion.h"

	//Constructor
	Vector3::Vector3():x(0.0f),y(0.0f),z(0.0f){};

	//澶嶅埗鏋勯�犲嚱鏁�
	Vector3::Vector3(const Vector3 &copy) : x(copy.x) , y(copy.y) , z(copy.z){};
	//鐢眡锛寉锛寊涓変釜鍊煎畬鎴愬垵濮嬪寲
	Vector3::Vector3(float vx,float vy,float vz):x(vx),y(vy),z(vz){};
	//璧嬪�尖�滐紳鈥濊繍绠楃
	Vector3 &Vector3::operator=(const Vector3 &v){
		x=v.x;
		y=v.y;
		z=v.z;
		return *this;
	}


	//姣旇緝"=="杩愮畻绗�
	bool Vector3::operator ==(const Vector3 &v) const{

		return x==v.x && y==v.y && z==v.z;
	}

	bool Vector3::operator !=(const Vector3 &v) const{

		return x!=v.x || y!=v.y || z!=v.z;
	}
	//闆跺悜閲�
	void Vector3::Zero(){x=y=z=0.0f;}

	//涓�鍏冭繍绠楃鈥滐紞鈥�
	Vector3 Vector3::operator -() const{

		return Vector3(-x,-y,-z);
	}
	//閲嶈浇鈥滐紜鈥濃�滐紞鈥濊繍绠楃
	Vector3 Vector3::operator +(const Vector3 &v)const{
		return Vector3(x+v.x,y+v.y,z+v.z);
	}

	Vector3 Vector3::Add(float addTarget){

		return Vector3(x+addTarget,y+addTarget,z+addTarget);
	}

	Vector3 Vector3::operator -(const Vector3 &v)const{
			return Vector3(x-v.x,y-v.y,z-v.z);
	}
	//鏍囬噺涔橀櫎娉�
	Vector3 Vector3::operator *(float value)const{
		return Vector3(x*value,y*value,z*value);
	}
	Vector3 Vector3::operator /(float value)const{
			float v=1.0f/value;
			return Vector3(x,y,z)*v;
	}
	//鑷弽杩愮畻绗�
	Vector3 &Vector3::operator +=(const Vector3 &v){
		x+=v.x;
		y+=v.y;
		z+=v.z;
		return *this;
	}
	Vector3 &Vector3::operator -=(const Vector3 &v){
			x-=v.x;
			y-=v.y;
			z-=v.z;
			return *this;
	}
	Vector3 &Vector3::operator *=(float value){
				x*=value;
				y*=value;
				z*=value;
				return *this;
	}
	Vector3 &Vector3::operator /=(float value){
		float v=1.0f/float(value);
		x*=v;
		y*=v;
		z*=v;
		return *this;
	}
	//褰掍竴鍖�
	void Vector3::Normalize(){
		float magSq=float(x*x+y*y+z*z);
		if(magSq>0.0f){
			float oneOverMag=1.0f/sqrt(magSq);
			x*=oneOverMag;
			y*=oneOverMag;
			z*=oneOverMag;
		}
	}
	//鐐逛箻
	float Vector3::Dot(const Vector3 &v) const{

		return x*v.x+y*v.y+z*v.z;
	}
	//鍚戦噺鐨勬ā闀�
	float Vector3::Length(const Vector3 &v){

		return sqrt(v.x*v.x+v.y*v.y+v.z*v.z);
	}
	//Cross product
	Vector3 Vector3::CrossProduct(const Vector3 &v)const{
		Vector3 vecResult(
				y*v.z-z*v.y,
				z*v.x-x*v.z,
				x*v.y-y*v.x
				);
		return vecResult;
	  }
	//Axis rotate
	Vector3 Vector3::Rotate(Vector3 axis,float angle){
		//1.
		float sinAngle=sin(-angle);
		float cosAngle=cos(-angle);
		Vector3 crossResult=this->CrossProduct(axis*sinAngle);
		crossResult+=((*this*cosAngle)+(axis*(this->Dot(axis*(1-cosAngle)))));
		return crossResult;
		//2.
		//Quaternion rotation;
		//rotation=rotation.;
		//Quaternion *q=new Quaternion();

		//return Rotate(q->InitRotation(axis,angle));

	}

	Vector3 Vector3::Rotate(Quaternion &rotation){

		Quaternion conjugate=rotation.Conjugate();
		Quaternion w=rotation.Mul(this->x,this->y,this->z).Mul(conjugate);
		return Vector3(w.x,w.y,w.z);
	}


	//v1 vector and v2 vector distance
	 float Vector3::Distance(const Vector3 &v1,const Vector3 &v2){
		float dx=v2.x-v1.x;
		float dy=v2.y-v1.y;
		float dz=v2.z-v1.z;

		return sqrt(dx*dx+dy*dy+dz*dz);

	}

	 Vector2 Vector3::GetXY(){


		 return Vector2(x,y);
	 }

	 Vector2 Vector3::GetYZ(){

		 return Vector2(y,z);
	 }

	 Vector2 Vector3::GetZX(){

		 return Vector2(z,x);
	 }

	 Vector2 Vector3::GetYX(){

		 return Vector2(y,x);
	 }

	 Vector2 Vector3::GetZY(){

		 return Vector2(z,y);
	 }

	 Vector2 Vector3::GetXZ(){

		 return Vector2(x,z);
	 }

	 Vector3 Vector3::Lerp(Vector3 dest,float lerpFactor){

		return (((dest-*this)*lerpFactor)+*this);
	 }

	 float Vector3::Max(){

		return max(x,max(y,z));
	 }

	 void Vector3::Set(float xCopy,float yCopy,float zCopy){

		x=xCopy;
		y=yCopy;
		z=zCopy;
	 }


	 void Vector3::Set(Vector3 copy){

		 x=copy.x;
		 y=copy.y;
		 z=copy.z;

	 }
