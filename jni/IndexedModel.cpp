#include "IndexedModel.h"

IndexedModel::IndexedModel(){



}


vector<Vector3>& IndexedModel::GetPositions(){


	   return positions;
}

vector<Vector2>& IndexedModel::GetTextureCoords(){



		return textureCoords;
}

vector<Vector3>& IndexedModel::GetNormals(){


		return normals;
}

vector<int>& IndexedModel::GetIndices(){

		return indices;
}

void IndexedModel::CalcNormals(){
	LOGI(" Start Calculate Normals");
	for(int i=0;i<indices.size();i+=3){
		int i0=indices[i];
		int i1=indices[i+1];
		int i2=indices[i+2];
		Vector3 v1= positions[i1]-positions[i0];
		Vector3 v2= positions[i2]-positions[i0];
		Vector3 normal=v1.CrossProduct(v2);
		normal.Normalize();
		normals[i0]=normals[i0]+normal;
		normals[i1]=normals[i1]+normal;
		normals[i2]=normals[i2]+normal;
		//vertices[i0].normal
	}

	for(int i=0;i<normals.size();i++){
		Vector3 normalR=normals[i];
		normalR.Normalize();
		normals[i]=normalR;
	}
}
