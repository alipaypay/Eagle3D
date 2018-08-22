#include "OBJModel.h"
OBJModel::OBJModel(const char* fileName,bool isOutSideModel){


		 hasTextureCoord=false;
		 hasNormals=false;
		 if(isOutSideModel){

			 OutSideModelLoad(fileName);
		 }else{

			 InSideModelLoad(fileName);

		 }
	//	 Mesh mesh(vertices,indics,true);
		// return mesh;
}

void  OBJModel::OutSideModelLoad(const char* fileName){
			 ifstream infile(fileName);
			 string line;
			 while(getline(infile,line))
			 {
				 vector<string> tokens;
				 Tools::SplitString(line.c_str()," ",tokens);
				 vector<string> tokensResult;
				 Tools::RemoveEmptyStrings(tokens,tokensResult);
				 if(tokensResult.size()==0 || strcmp(tokensResult[0].c_str(),"#")==0)
				 {
					 continue;
				 }else if(strcmp(tokensResult[0].c_str(),"v")==0){

					 positions.push_back(Vector3(atof(tokensResult[1].c_str()),atof(tokensResult[2].c_str()),atof(tokensResult[3].c_str())));
				 }else if(strcmp(tokensResult[0].c_str(),"vt")==0){

					 textureCoords.push_back(Vector2(atof(tokensResult[1].c_str()),atof(tokensResult[2].c_str())));
				 }else if(strcmp(tokensResult[0].c_str(),"vn")==0){

					 normals.push_back(Vector3(atof(tokensResult[1].c_str()),atof(tokensResult[2].c_str()),atof(tokensResult[3].c_str())));
				 }else if(strcmp(tokensResult[0].c_str(),"f")==0){
					 for(int i=0;i<tokensResult.size()-3;i++){
					 indices.push_back(ParseOBJIndex(tokensResult[1]));
					 indices.push_back(ParseOBJIndex(tokensResult[2+i]));
					 indices.push_back(ParseOBJIndex(tokensResult[3+i]));
				 }

				 }
			 }


}

void  OBJModel::InSideModelLoad(const char* fileName){

			//Split Array
			 vector<string> tokens;

			 const char* sourceInfo=ReadResource(fileName);
			 Tools::SplitString(sourceInfo,"\n",tokens);
			 int t=tokens.size();
			 for(int i=0;i<tokens.size();i++){
				 vector<string> tokensLine;
				 Tools::SplitString(tokens[i].c_str()," ",tokensLine);
				 vector<string> tokensLineResult;
				 Tools::RemoveEmptyStrings(tokensLine,tokensLineResult);
				 if(tokensLineResult.size()==0 || strcmp(tokensLineResult[0].c_str(),"#")==0){

					 continue;
				 }else if(strcmp(tokensLineResult[0].c_str(),"v")==0){

					 positions.push_back(Vector3(atof(tokensLineResult[1].c_str()),atof(tokensLineResult[2].c_str()),atof(tokensLineResult[3].c_str())));

				 }else if(strcmp(tokensLineResult[0].c_str(),"vt")==0){

					 textureCoords.push_back(Vector2(atof(tokensLineResult[1].c_str()),atof(tokensLineResult[2].c_str())));
				 }else if(strcmp(tokensLineResult[0].c_str(),"vn")==0){

					 normals.push_back(Vector3(atof(tokensLineResult[1].c_str()),atof(tokensLineResult[2].c_str()),atof(tokensLineResult[3].c_str())));
				 }else if(strcmp(tokensLineResult[0].c_str(),"f")==0){
					 for(int i=0;i<tokensLineResult.size()-3;i++){
						indices.push_back(ParseOBJIndex(tokensLineResult[1]));
						indices.push_back(ParseOBJIndex(tokensLineResult[2+i]));
						indices.push_back(ParseOBJIndex(tokensLineResult[3+i]));
					 }
				 }
			 }

	}



OBJIndex OBJModel::ParseOBJIndex(string token){
	vector<string> values;
	Tools::SplitString(token.c_str(),"/",values);
	OBJIndex resultObjIndex;
	resultObjIndex.VectexIndex=atoi(values[0].c_str())-1;

	if(values.size()>1){

		hasTextureCoord=true;
		resultObjIndex.TextureCoordIndex=atoi(values[1].c_str())-1;
		if(values.size()>2){

			hasNormals=true;
			resultObjIndex.NormalIndex=atoi(values[2].c_str())-1;
		}
	}
	return resultObjIndex;
}

char* OBJModel::ReadResource(const char* fileName){
	AAsset *assets= AAssetManager_open(CoreActivity::GetActivity()->assetManager, fileName, AASSET_MODE_BUFFER);
	size_t length = AAsset_getLength(assets);
	char* buffer =new char[length+1];
	AAsset_read(assets, buffer, length);
	buffer[length]='\0';
	AAsset_close(assets);
	return	buffer;
}

IndexedModel OBJModel::ToIndexedModel(){


	IndexedModel indexedModel;
	IndexedModel normalModel;

	//vector<OBJIndex> resultVec;
	map<OBJIndex,int> resultMap;
	map<OBJIndex,int>::iterator l_itResultMap;
	map<int,int> normalIndexMap;
	map<int,int>::iterator l_itNormalIndexMap;
	map<int,int> indexMap;
	map<int,int>::iterator l_itIndexMap;
	int modelVertexIndex=-1;
	int normalModelIndex=-1;

	for(int i=0;i<indices.size();i++){
		//LOGI("indices size ~~~~~~~~~:%i",indices.size());
		OBJIndex objIndex=indices[i];
		Vector3 currentPos=positions[objIndex.VectexIndex];

		Vector2 currentTex;
		Vector3 currentNor;
		if(hasTextureCoord){
			currentTex=textureCoords[objIndex.TextureCoordIndex];

		}

		if(hasNormals){

			currentNor=normals[objIndex.NormalIndex];

		}


		l_itResultMap=resultMap.find(objIndex);
		if(l_itResultMap==resultMap.end()){

			modelVertexIndex=indexedModel.GetPositions().size();


			resultMap.insert(make_pair(objIndex,modelVertexIndex));
			indexedModel.GetPositions().push_back(currentPos);

			indexedModel.GetTextureCoords().push_back(currentTex);
			if(hasNormals){
				indexedModel.GetNormals().push_back(currentNor);
			}
		}



		l_itNormalIndexMap=normalIndexMap.find(objIndex.VectexIndex);

		if(l_itNormalIndexMap==normalIndexMap.end()){
			normalModelIndex=normalModel.GetPositions().size();
			normalIndexMap.insert(make_pair(objIndex.VectexIndex,normalModelIndex));

			normalModel.GetPositions().push_back(currentPos);
			normalModel.GetNormals().push_back(currentNor);
			normalModel.GetTextureCoords().push_back(currentTex);
		}


		indexedModel.GetIndices().push_back(modelVertexIndex);
		normalModel.GetIndices().push_back(normalModelIndex);
		indexMap.insert(make_pair(modelVertexIndex,normalModelIndex));
	}
	if(!hasNormals){
		normalModel.CalcNormals();
		for(int k=0;k<indexedModel.GetPositions().size();k++){
			//l_itIndexMap=indexMap.find(k);
			//if(l_itIndexMap!=indexMap.end()){
			indexedModel.GetNormals().push_back(normalModel.GetNormals()[indexMap[k]]);//[l_itIndexMap->second]);
			//}
		}
	}

	//LOGI("indexedModel.GetPositions().size():%i",indexedModel.GetPositions().size());
	//LOGI("indexedModel.GetTextureCoords().size():%i",indexedModel.GetTextureCoords().size());
//	LOGI("indexedModel.GetIndices().size():%i",indexedModel.GetIndices().size());
	return indexedModel;
}

bool OBJModel::FindOBJIndex(vector <OBJIndex>::iterator beg,
             vector <OBJIndex>::iterator end,OBJIndex val)//�����������ĳ��intԪ���Ƿ���ڵĺ���
{
    while (beg!=end)
    {
        if (*beg==val)//�ҵ����˳�while
            break;
        else
            ++beg;
    }

    if (beg!=end)//�ҵ������سɹ�
        return true;
    else//�Ҳ���������ʧ��
        return false;
}
