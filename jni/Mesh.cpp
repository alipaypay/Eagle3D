#include "Mesh.h"


Mesh::Mesh(){
	resource=NULL;
}

Mesh::Mesh(const char* fileName){
	string str(fileName);
	fileNameStr=str;
	loadModels_iter=loadModels.find(fileNameStr);
	if(loadModels_iter!=loadModels.end()){

		resource=loadModels[fileNameStr];
		resource->AddReference();
	}
	else{

		LoadMeshInAssets(fileName);
		loadModels[fileNameStr]=resource;
	}
}
Mesh::Mesh(vector<Vertex> vertices,vector<int> indics){

	AddVertices(vertices,indics);

}

Mesh::Mesh(vector<Vertex> vertices,vector<int> indics,bool calcNormal){

	AddVertices(vertices,indics,calcNormal);
}



Mesh::~Mesh(){

	//Finalize();
}

void Mesh::AddVertices(vector<Vertex> vertices,vector<int> indics,bool calcNormal){

		if(calcNormal){

			vertices=CalcNormals(vertices,indics);
		}

		resource=new MeshResource(vertices.size(),indics.size(),sizeof(GLfloat) * 3);

		//vbo

		GLfloat* vertexBuffer=Tools::GetFloatBuffer(vertices);//Tools::GetVertexFloatBuffer(vertices);

		glBindBuffer(GL_ARRAY_BUFFER,resource->GetVbo());
		glBufferData(GL_ARRAY_BUFFER,resource->GetNumVerticeSize()*Vertex::TOTAL_SIZE*sizeof(GLfloat),vertexBuffer,GL_STATIC_DRAW);

		//ibo
		if(resource->GetIndicsSize()>0){

			GLuint* indicsBuffer=Tools::GetIntBuffer(indics);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,resource->GetIbo());

			glBufferData(GL_ELEMENT_ARRAY_BUFFER,resource->GetIndicsSize()*sizeof(GLuint),indicsBuffer,GL_STATIC_DRAW);

			delete []indicsBuffer;

		}

		delete []vertexBuffer;

}


void Mesh::AddVertices(vector<Vertex> vertices,vector<int> indics){
	AddVertices(vertices,indics,false);
}

void Mesh::Draw(){

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER,resource->GetVbo());
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(GLfloat)*Vertex::TOTAL_SIZE,0);
	glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,sizeof(GLfloat)*Vertex::TOTAL_SIZE,(void*)(sizeof(GLfloat) * 3));
	glVertexAttribPointer(2,3,GL_FLOAT,GL_FALSE,sizeof(GLfloat)*Vertex::TOTAL_SIZE,(void*)(sizeof(GLfloat) * 5));
	if(resource->GetIndicsSize()>0){
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,resource->GetIbo());
		glDrawElements(GL_TRIANGLES,resource->GetIndicsSize(),GL_UNSIGNED_INT,0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	}else{
		glDrawArrays(GL_TRIANGLES,0,3);
	}
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);


}

vector<Vertex> Mesh::CalcNormals(vector<Vertex> vertices,vector<int> indics){
	for(int i=0;i<indics.size();i+=3){
		int i0=indics[i];
		int i1=indics[i+1];
		int i2=indics[i+2];
		Vector3 v1= vertices[i1].Position-vertices[i0].Position;
		Vector3 v2= vertices[i2].Position-vertices[i0].Position;
		Vector3 normal=v1.CrossProduct(v2);
		normal.Normalize();
		vertices[i0].Normal=vertices[i0].Normal+normal;
		vertices[i1].Normal=vertices[i1].Normal+normal;
		vertices[i2].Normal=vertices[i2].Normal+normal;
		//vertices[i0].normal
	}

	for(int i=0;i<vertices.size();i++){
		Vector3 normalR=vertices[i].Normal;
		normalR.Normalize();
		vertices[i].Normal=normalR;
	}
	return vertices;

}



//Read mesh resource in assets folder
Mesh  Mesh::LoadMeshInAssets(const char* fileName){
		 vector<string> spliteArr;
		 Tools::SplitString(fileName,".",spliteArr);
		 string ext=spliteArr[spliteArr.size()-1];
		 if(strcmp(ext.c_str(),"obj")!=0){

			 LOGE("Import file error:.obj?");
		 }

		 OBJModel objModel(fileName,false);
		 //LOGI("ToIndexedModel start ~~~~~~~~~~~~~~~~~");
		 IndexedModel indexedMode=objModel.ToIndexedModel();
		 LOGI("ToIndexedModel end ~~~~~~~~~~~~~~~~~1");
		 indexedMode.CalcNormals();
		 vector<Vertex> vertices;
		 vector<int> indics;
		 for(int i=0;i<indexedMode.GetPositions().size();i++){

			 vertices.push_back(Vertex(indexedMode.GetPositions()[i],
					 indexedMode.GetTextureCoords()[i],
					 indexedMode.GetNormals()[i]
			 	 	 ));

		 }


		 indics=indexedMode.GetIndices();

		// LOGI("indics count ~~~~~~~~~~~~~~~~~:%i",indics.size());
		 AddVertices(vertices,indics,false);

		 return *this;

}

//Read mesh resource in external sd card
Mesh  Mesh::LoadMesh(const char* fileName){
	 vector<string> spliteArr;
	 Tools::SplitString(fileName,".",spliteArr);

	// OBJModel objModel(fileName);
	 string ext=spliteArr[spliteArr.size()-1];
	 if(strcmp(ext.c_str(),"obj")!=0){

		 LOGE("Import file error:.obj?");
	 }

	 OBJModel objModel(fileName,true);
	 IndexedModel indexedMode=objModel.ToIndexedModel();
	 vector<Vertex> vertices;
	 vector<int> indics;
	 for(int i=0;i<indexedMode.GetPositions().size();i++){
	 	vertices.push_back(Vertex(indexedMode.GetPositions()[i],
	 					 indexedMode.GetTextureCoords()[i],
	 					 indexedMode.GetNormals()[i]
	 			 	 	 ));

	 	}
	 indics=indexedMode.GetIndices();
	 AddVertices(vertices,indics,true);
	 return *this;

}

char* Mesh::ReadResource(const char* fileName){
	AAsset *assets= AAssetManager_open(CoreActivity::GetActivity()->assetManager, fileName, AASSET_MODE_BUFFER);
	size_t length = AAsset_getLength(assets);
	char* buffer =new char[length+1];
	AAsset_read(assets, buffer, length);
	buffer[length]='\0';
	AAsset_close(assets);
	return	buffer;
}

void Mesh::Finalize(){
	//LOGI("Mesh FINALIZE");
	if(resource->RemoveReference()){
		loadModels_iter=loadModels.find(fileNameStr);
		if(loadModels_iter!=loadModels.end() && fileNameStr.length()!=0){

			loadModels.erase(loadModels_iter);
		}


	}

}

