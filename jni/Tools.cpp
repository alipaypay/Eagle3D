#include "Tools.h"

  GLfloat* Tools::GetFloatBuffer(vector<Vertex> vertices){
	  	  int totalSize=vertices.size()*Vertex::TOTAL_SIZE;

	  	  GLfloat* vertexBuffer=new GLfloat[totalSize];
	  				//LOGI("position start:\n");
	  				for(int i=0;i<totalSize;i++){
	  					if(i%Vertex::TOTAL_SIZE==0){
	  						vertexBuffer[i]=vertices[i/Vertex::TOTAL_SIZE].Position.x;
	  						//LOGI("position x:%f",vertexBuffer[i]);
	  						vertexBuffer[i+1]=vertices[i/Vertex::TOTAL_SIZE].Position.y;
	  						//LOGI("position y:%f",vertexBuffer[i+1]);
	  						vertexBuffer[i+2]=vertices[i/Vertex::TOTAL_SIZE].Position.z;
	  						//LOGI("position z:%f",vertexBuffer[i+2]);
	  						vertexBuffer[i+3]=vertices[i/Vertex::TOTAL_SIZE].TextureCoord.x;
	  						//LOGI("textureCoord x:%f",vertexBuffer[i+3]);
	  						vertexBuffer[i+4]=vertices[i/Vertex::TOTAL_SIZE].TextureCoord.y;
	  					//	LOGI("textureCoord y:%f",vertexBuffer[i+4]);
	  						vertexBuffer[i+5]=vertices[i/Vertex::TOTAL_SIZE].Normal.x;
	  					//	LOGI("Normal x:%f",vertexBuffer[i+5]);
	  						vertexBuffer[i+6]=vertices[i/Vertex::TOTAL_SIZE].Normal.y;
	  					//    LOGI("Normal y:%f",vertexBuffer[i+6]);
	  					    vertexBuffer[i+7]=vertices[i/Vertex::TOTAL_SIZE].Normal.z;
	  					//  	LOGI("Normal z:%f",vertexBuffer[i+7]);
	  					}
	  				}
	  				//LOGI("position end\n");
	  				return vertexBuffer;

  }


  GLfloat* Tools::GetVertexFloatBuffer(vector<Vertex> vertices){
	  	  	  	int totalSize=vertices.size()*Vertex::TOTAL_SIZE;
				int size=vertices.size()*Vertex::VERTEX_SIZE;
				GLfloat* vertexBuffer=new GLfloat[size];
				//LOGI("position start:\n");
				for(int i=0;i<totalSize;i++){
					if(i%Vertex::TOTAL_SIZE==0){
						vertexBuffer[i]=vertices[i/Vertex::TOTAL_SIZE].Position.x;
				//		LOGI("position x:%f",vertexBuffer[i]);
						vertexBuffer[i+1]=vertices[i/Vertex::TOTAL_SIZE].Position.y;
				//		LOGI("position y:%f",vertexBuffer[i+1]);
						vertexBuffer[i+2]=vertices[i/Vertex::TOTAL_SIZE].Position.z;
				//		LOGI("position z:%f",vertexBuffer[i+2]);

					}
				}
			//	LOGI("position end\n");
				return vertexBuffer;
			}

   GLfloat* Tools::GetTextureCoordFloatBuffer(vector<Vertex> vertices){
	   int totalSize=vertices.size()*Vertex::TOTAL_SIZE;
	   int size=vertices.size()*Vertex::TEXTURE_COORD_SIZE;
	   GLfloat* vertexBuffer=new GLfloat[size];

	   for(int i=0;i<totalSize;i++){
	   			if(i%Vertex::TOTAL_SIZE==0){
					vertexBuffer[i+3]=vertices[i/Vertex::TOTAL_SIZE].TextureCoord.x;

					vertexBuffer[i+4]=vertices[i/Vertex::TOTAL_SIZE].TextureCoord.y;

	   			}
	   		}

	   		return vertexBuffer;
   }


	 GLuint* Tools::GetIntBuffer(vector<int> indics){
		int size=indics.size();
		GLuint* intBuffer=new GLuint[size];
		for(int i=0;i<size;i++){
			intBuffer[i]=indics[i];
			//LOGI("INTBUFFER:%d",intBuffer[i]);
		}
		return intBuffer;
	}


	 void Tools::SplitString(string strTarget,string splitSymbol,vector<string>& outputData){
		  string::size_type pos;
		  strTarget+=splitSymbol;//锟斤拷展锟街凤拷锟斤拷锟皆凤拷锟斤拷锟斤拷锟�
		  int size=strTarget.size();

		  for(int i=0; i<size; i++)
		  {
		    pos=strTarget.find(splitSymbol,i);
		    if(pos<size)
		    {
		      string s=strTarget.substr(i,pos-i);
		      outputData.push_back(s);
		      i=pos+splitSymbol.size()-1;
		    }
		  }

		}

	 GLfloat* Tools::GetFloatBuffer(Vertex *vertices){

		int size=9;
		GLfloat* vertexBuffer=new GLfloat[size];
		for(int i=0;i<size;i++){
			if(i%3==0){
				vertexBuffer[i]=vertices[0].Position.x;
				vertexBuffer[i+1]=vertices[0].Position.y;
				vertexBuffer[i+2]=vertices[0].Position.z;
				vertices++;
			}

		}
		return vertexBuffer;
	}

	 void Tools::RemoveEmptyStrings(vector<string> data,vector<string>& outPutData){

		for(int i=0;i<data.size();i++){
			if(strcmp(data[i].c_str(),"")!=0){
				outPutData.push_back(data[i]);
		}
	}
}

const char * Tools::Str_Contact(const char *str1,const char *str2)
{
     char * result;
     result = (char*)malloc(strlen(str1) + strlen(str2) + 1); //str1的长度 + str2的长度 + \0;
     if(!result){ //如果内存动态分配失败
        printf("Error: malloc failed in concat! \n");
        exit(EXIT_FAILURE);
     }
     strcpy(result,str1);
     strcat(result,str2); //字符串拼接
     return result;
}

vector<char*> Tools::GetStrLines(char * destination){
		vector<char*> result;
		int len = strlen(destination);
	    for (int i = 0; i < len; ++i)
	    {
	    	char des=*(destination + i) = getchar();

	    	if( des=='\n')
	    	{
	    		LOGI("des enter~~~~~~~~~~~~:enter");
	    	        break;
	    	}

	    }



}



