#include "OBJIndex.h"

OBJIndex::OBJIndex(){
	VectexIndex=0;
	TextureCoordIndex=0;
	NormalIndex=0;
}


bool OBJIndex::operator==(const OBJIndex &objI){


	return this->VectexIndex==objI.VectexIndex &&
		   this->TextureCoordIndex==objI.TextureCoordIndex &&
		   this->NormalIndex==objI.NormalIndex;
}


int OBJIndex::HashCode(){
	const int BASE=17;
	const int MULTIPLIER=31;
	int result=BASE;
	result=MULTIPLIER*result+VectexIndex;
	result=MULTIPLIER*result+TextureCoordIndex;
	result=MULTIPLIER*result+NormalIndex;

	return result;
}

bool OBJIndex::operator < (const  OBJIndex& oJI) const{

	//LOGI("OBJIndex Can't Compare");
	return !(this->VectexIndex==oJI.VectexIndex &&
			   this->TextureCoordIndex==oJI.TextureCoordIndex &&
			   this->NormalIndex==oJI.NormalIndex);
}
