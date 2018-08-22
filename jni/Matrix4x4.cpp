#include <Matrix4x4.h>


Matrix4x4::Matrix4x4(float valMat[4][4]){
		SetMatrix(valMat);
	}

Matrix4x4::Matrix4x4(){
		for(int i=0;i<4;i++){
			for(int j=0;j<4;j++){
				mat[i][j]=0;
			}
		}

	}

Vector3 Matrix4x4::Transform(Vector3 r){

		return Vector3(mat[0][0]*r.x+mat[0][1]*r.y+mat[0][2]*r.z+mat[0][3],
					   mat[1][0]*r.x+mat[1][1]*r.y+mat[1][2]*r.z+mat[1][3],
					   mat[2][0]*r.x+mat[2][1]*r.y+mat[2][2]*r.z+mat[2][3]
						);

	}
	//opengl
	//	|m00 m10 m20 m30|
	//  |m01 m11 m21 m31|
	//  |m02 m12 m22 m32|
	//  |m03 m13 m23 m33|
Matrix4x4& Matrix4x4::InitRotation(float x,float y,float z){
		Matrix4x4 rx;
		Matrix4x4 ry;
		Matrix4x4 rz;
		x=EagleMath::ToRadians(x);
		y=EagleMath::ToRadians(y);
		z=EagleMath::ToRadians(z);

		rx.mat[0][0]=1.0f; rx.mat[0][1]=0.0f;  rx.mat[0][2]=0.0f;  rx.mat[0][3]=0.0f;
		rx.mat[1][0]=0.0f; rx.mat[1][1]=cos(x);  rx.mat[1][2]=-sin(x);  rx.mat[1][3]=0.0f;
		rx.mat[2][0]=0.0f; rx.mat[2][1]=sin(x);  rx.mat[2][2]=cos(x);  rx.mat[2][3]=0.0f;
		rx.mat[3][0]=0.0f; rx.mat[3][1]=0.0f;  rx.mat[3][2]=0.0f;  rx.mat[3][3]=1.0f;

		ry.mat[0][0]=cos(y); ry.mat[0][1]=0.0f;  ry.mat[0][2]=sin(y);  ry.mat[0][3]=0.0f;
		ry.mat[1][0]=0.0f; ry.mat[1][1]=1.0f;  ry.mat[1][2]=0.0f;  ry.mat[1][3]=0.0f;
		ry.mat[2][0]=-sin(y); ry.mat[2][1]=0.0f;  ry.mat[2][2]=cos(y);  ry.mat[2][3]=0.0f;
		ry.mat[3][0]=0.0f; ry.mat[3][1]=0.0f;  ry.mat[3][2]=0.0f;  ry.mat[3][3]=1.0f;

		rz.mat[0][0]=cos(z); rz.mat[0][1]=-sin(z);  rz.mat[0][2]=0.0f;  rz.mat[0][3]=0.0f;
		rz.mat[1][0]=sin(z); rz.mat[1][1]=cos(z);  rz.mat[1][2]=0.0f;  rz.mat[1][3]=0.0f;
		rz.mat[2][0]=0.0f; rz.mat[2][1]=0.0f;  rz.mat[2][2]=1.0f;  rz.mat[2][3]=0.0f;
		rz.mat[3][0]=0.0f; rz.mat[3][1]=0.0f;  rz.mat[3][2]=0.0f;  rz.mat[3][3]=1.0f;

		SetMatrix((rz*(ry*rx)).mat);

		return *this;
	}

void Matrix4x4::InitScale(float x,float y,float z){
		this->mat[0][0]=x;    this->mat[0][1]=0.0f;  this->mat[0][2]=0.0f;  this->mat[0][3]=0.0f;
		this->mat[1][0]=0.0f; this->mat[1][1]=y;     this->mat[1][2]=0.0f;  this->mat[1][3]=0.0f;
		this->mat[2][0]=0.0f; this->mat[2][1]=0.0f;  this->mat[2][2]=z;     this->mat[2][3]=0.0f;
		this->mat[3][0]=0.0f; this->mat[3][1]=0.0f;  this->mat[3][2]=0.0f;  this->mat[3][3]=1.0f;

	}

void Matrix4x4::InitPerspective(float fov,float aspectRatio,float zNear,float zFar){
		//float ratio=aspectRatio;
		float tanHalfFOV=tan(fov/2.0f);
		float zRange=zNear-zFar;
		this->mat[0][0]=1.0f/(tanHalfFOV*aspectRatio);   this->mat[0][1]=0.0f;  			 this->mat[0][2]=0.0f;  				this->mat[0][3]=0.0f;
		this->mat[1][0]=0.0f;              		   this->mat[1][1]=1.0f/tanHalfFOV;  this->mat[1][2]=0.0f;  			    this->mat[1][3]=0.0f;
		this->mat[2][0]=0.0f;              		   this->mat[2][1]=0.0f;  			 this->mat[2][2]=(-zNear-zFar)/zRange;  this->mat[2][3]=2.0f*zFar*zNear/zRange;
		this->mat[3][0]=0.0f;              		   this->mat[3][1]=0.0f;  			 this->mat[3][2]=1.0f;  				this->mat[3][3]=0.0f;
	}

void Matrix4x4::InitTranslation(float x,float y,float z){
			this->mat[0][0]=1.0f; this->mat[0][1]=0.0f;  this->mat[0][2]=0.0f;  this->mat[0][3]=x;
			this->mat[1][0]=0.0f; this->mat[1][1]=1.0f;  this->mat[1][2]=0.0f;  this->mat[1][3]=y;
			this->mat[2][0]=0.0f; this->mat[2][1]=0.0f;  this->mat[2][2]=1.0f;  this->mat[2][3]=z;
			this->mat[3][0]=0.0f; this->mat[3][1]=0.0f;  this->mat[3][2]=0.0f;  this->mat[3][3]=1.0f;

	}

void Matrix4x4::InitRotation(Vector3 forward,Vector3 up){
		Vector3 f=forward;
		f.Normalize();

		Vector3 r=up;
		r.Normalize();
		r=r.CrossProduct(f);

		Vector3 u=f.CrossProduct(r);

		InitRotation(f,u,r);

//		this->mat[0][0]=r.x;  this->mat[0][1]=r.y;   this->mat[0][2]=r.z;  this->mat[0][3]=0.0f;
//		this->mat[1][0]=u.x; this->mat[1][1]=u.y;  this->mat[1][2]=u.z;  this->mat[1][3]=0.0f;
//		this->mat[2][0]=f.x; this->mat[2][1]=f.y;  this->mat[2][2]=f.z;  this->mat[2][3]=0.0f;
//		this->mat[3][0]=0.0f; this->mat[3][1]=0.0f;  this->mat[3][2]=0.0f;  this->mat[3][3]=1.0f;
		//return *this;


	}

void Matrix4x4::InitRotation(Vector3 forward,Vector3 up,Vector3 right){
			Vector3 f=forward;
			//f.Normalize();

			Vector3 r=right;
			//r.Normalize();

			Vector3 u=up;
			//u.Normalize();
			this->mat[0][0]=r.x;  this->mat[0][1]=r.y;   this->mat[0][2]=r.z;  this->mat[0][3]=0.0f;
			this->mat[1][0]=u.x; this->mat[1][1]=u.y;  this->mat[1][2]=u.z;  this->mat[1][3]=0.0f;
			this->mat[2][0]=f.x; this->mat[2][1]=f.y;  this->mat[2][2]=f.z;  this->mat[2][3]=0.0f;
			this->mat[3][0]=0.0f; this->mat[3][1]=0.0f;  this->mat[3][2]=0.0f;  this->mat[3][3]=1.0f;
			//return *this;


		}

float* Matrix4x4::GetMatLinearArray(){
		float *value=new float[16];
		for(int i=0;i<4;i++){
			int sum=i*4;
			for(int j=0;j<4;j++){
				value[sum+j]=mat[i][j];
				}
			}
		return value;
	}


void Matrix4x4::SetMatrix(float copMat[4][4]){
		for(int i=0;i<4;i++){
			for(int j=0;j<4;j++){
				mat[i][j]=copMat[i][j];
			}
		}
	}

Matrix4x4 Matrix4x4::operator*(Matrix4x4 tarM){
		Matrix4x4 matResult;
		for(int i=0;i<4;i++){
			for(int j=0;j<4;j++){
				matResult.SetValue(i,j,mat[i][0]*tarM.mat[0][j]+
							 mat[i][1]*tarM.mat[1][j]+
							 mat[i][2]*tarM.mat[2][j]+
							 mat[i][3]*tarM.mat[3][j]
							);
			}
		}

		return matResult;
	}


float Matrix4x4::GetValue(int x,int y){

		return this->mat[x][y];
	}

void Matrix4x4::SetValue(int x,int y,float value){

		this->mat[x][y]=value;
	}

Matrix4x4& Matrix4x4::Identity(){
		this->mat[0][0]=1.0f; this->mat[0][1]=0.0f;  this->mat[0][2]=0.0f;  this->mat[0][3]=0.0f;
		this->mat[1][0]=0.0f; this->mat[1][1]=1.0f;  this->mat[1][2]=0.0f;  this->mat[1][3]=0.0f;
		this->mat[2][0]=0.0f; this->mat[2][1]=0.0f;  this->mat[2][2]=1.0f;  this->mat[2][3]=0.0f;
		this->mat[3][0]=0.0f; this->mat[3][1]=0.0f;  this->mat[3][2]=0.0f;  this->mat[3][3]=1.0f;
		return *this;
	}

Matrix4x4& Matrix4x4::InitOrthoGraphic(float left,float right,float top,float bottom,float near,float far){
		float width=right-left;
		float height=top-bottom;
		float depth=far-near;
		this->mat[0][0]=2.0f/width; this->mat[0][1]=0.0f;         this->mat[0][2]=0.0f; 	   this->mat[0][3]=-(left+right)/width;
		this->mat[1][0]=0.0f;       this->mat[1][1]=2.0f/height;  this->mat[1][2]=0.0f;  	   this->mat[1][3]=-(top+bottom)/height;
		this->mat[2][0]=0.0f;       this->mat[2][1]=0.0f;         this->mat[2][2]=-2.0f/depth;  this->mat[2][3]=-(near+far)/depth;
		this->mat[3][0]=0.0f;       this->mat[3][1]=0.0f;         this->mat[3][2]=0.0f; 	   this->mat[3][3]=1.0f;
		return *this;
		}

void Matrix4x4::Print(){
		LOGI("Matrix start print out");
		LOGI("mat[0][0]=%f",this->mat[0][0]);
		LOGI("mat[0][1]=%f",this->mat[0][1]);
		LOGI("mat[0][2]=%f",this->mat[0][2]);
		LOGI("mat[0][3]=%f",this->mat[0][3]);
		LOGI("mat[1][0]=%f",this->mat[1][0]);
		LOGI("mat[1][1]=%f",this->mat[1][1]);
		LOGI("mat[1][2]=%f",this->mat[1][2]);
		LOGI("mat[1][3]=%f",this->mat[1][3]);
		LOGI("mat[2][0]=%f",this->mat[2][0]);
		LOGI("mat[2][1]=%f",this->mat[2][1]);
		LOGI("mat[2][2]=%f",this->mat[2][2]);
		LOGI("mat[2][3]=%f",this->mat[2][3]);
		LOGI("mat[3][0]=%f",this->mat[3][0]);
		LOGI("mat[3][1]=%f",this->mat[3][1]);
		LOGI("mat[3][2]=%f",this->mat[3][2]);
		LOGI("mat[3][3]=%f",this->mat[3][3]);
		LOGI("Matrix end print out");
	}
