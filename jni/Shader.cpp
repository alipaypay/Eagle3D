#include "Shader.h"
#include "RenderOfCamera.h"
Shader::Shader(){
	program=glCreateProgram();
	//renderCam=NULL;
	if(program==0){
		return;
	}
}

void Shader::AddVertexShader(const char* vert){

	AddProgram(vert,GL_VERTEX_SHADER);
}

void Shader::AddFragmentShader(const char* frag){

	AddProgram(frag,GL_FRAGMENT_SHADER);
}

void Shader::AddUniform(const char* uniform){
	int uniformLocation=glGetUniformLocation(program,uniform);
	if(uniformLocation==0xFFFFFFFF){
		LOGE("Eagle3D uniform error:could not find uniform");
		return;
	}
	uniforms[uniform]=uniformLocation;

}

int Shader::FindUniformLocation(const char* uniformName){
		map<const char*,int>::iterator l_it;;
		l_it=uniforms.find(uniformName);//���ص���һ��ָ��
		if(l_it==uniforms.end()){
			LOGE("Eagle3D Error:Not find uniform name:%s",uniformName);
			return -1;
		}
		else
		{
			return l_it->second;
		}

}

void Shader::SetUniformi(const char* uniformName,int val){
	int uniformId= FindUniformLocation(uniformName);
	if(uniformId!=-1){
		glUniform1i(uniformId,val);
	}

}

// void Shader::SetUniform(string uniformName,BaseLight  baseLight){
//
//
// }
//
// void Shader::SetUniform(string uniformName,DirectionalLight  directionalLight){
//
//
// }
//
//void Shader::SetUniform(std::string uniformName,PointLight *pointLight){
//
//
// }

void Shader::SetUniformf(const char* uniformName,float val){

			int uniformId= FindUniformLocation(uniformName);
			if(uniformId!=-1){
				glUniform1f(uniformId,val);
			}
}

void Shader::SetUniform3f(const char* uniformName,Vector3 val){
			int uniformId= FindUniformLocation(uniformName);
			if(uniformId!=-1){
				glUniform3f(uniformId,val.x,val.y,val.z);
			}
}

void Shader::SetUniformM(const char* uniformName,Matrix4x4 val){
			int uniformId= FindUniformLocation(uniformName);
			float *matArr=val.GetMatLinearArray();
			if(uniformId!=-1){
				glUniformMatrix4fv(uniformId,
				 	1,
				 	true,
				 	matArr);
			}
}


void Shader::AddProgram(const char* shader,int type){
	GLint compiled;
	GLuint shaderInfo=glCreateShader(type);
	if(shaderInfo==0){
		return;
	}

	glShaderSource(shaderInfo,1,&shader,NULL);
	glCompileShader(shaderInfo);
	glGetShaderiv(shaderInfo,GL_COMPILE_STATUS,&compiled);
	if(!compiled){
		GLint infoLen=0;
		glGetShaderiv(shaderInfo,GL_INFO_LOG_LENGTH,&infoLen);
		if(infoLen>1){
			char* infoLog=(char*)malloc(sizeof(char)*infoLen);
			glGetShaderInfoLog(shaderInfo,infoLen,NULL,infoLog);
			LOGE("Error compiling shader:\n%s\n",infoLog);
			free(infoLog);
		}
		glDeleteShader(shaderInfo);
		return;
	}
	glAttachShader(program,shaderInfo);

	glLinkProgram(program);

}

void Shader::CompileShader(){
	 GLint linkStatus;
	 glGetProgramiv(program,GL_LINK_STATUS,&linkStatus);
	    if (!linkStatus)
	    {
	       // LOGE("ERROR : link shader program failed");
	        GLint logLen;
	        glGetProgramiv(program,GL_INFO_LOG_LENGTH,
	            &logLen);
	        if (logLen > 1)
	        {
	            char *log = (char *)malloc(logLen);
	            GLsizei written;
	            glGetProgramInfoLog(program,logLen,
	                &written,log);
	            LOGE("shader program Error log :\n%s\n",log);
	            free(log);
	        }
	    }
}


void Shader::UpdateUniforms(Transform* trans,Material material,RenderOfCamera* renderCam){


}


void Shader::UnBind(){

	glDeleteProgram(program);
}

void Shader::Bind(){

	glUseProgram(program);
}

char* Shader::LoadShader(const char* fileName){
	FILE* fp=fopen(fileName,"r");
	fseek(fp,0,SEEK_END);
	long file_length=ftell(fp);
	fseek(fp,0,SEEK_SET);
	char* contents=new char[file_length+1];
	//zero out memory
	for(int i=0;i<file_length+1;i++){
		contents[i]=0;
	}

	//Here is the actual read
	fread(contents,1,file_length,fp);
	contents[file_length]='\0';
	fclose(fp);
	return contents;
}

char* Shader::ReadAssetsShader(const char* fileName){
	const char* INCLUDE_DIRECTORY="#include";
	char* fileContent=ReadResource(fileName);
	//Tools::GetStrLines(fileContent);

	return fileContent;
}

char* Shader::ReadResource(const char* fileName){
	AAsset *assets= AAssetManager_open(CoreActivity::GetActivity()->assetManager, fileName, AASSET_MODE_BUFFER);
	size_t length = AAsset_getLength(assets);
	char* buffer =new char[length+1];
	AAsset_read(assets, buffer, length);
	buffer[length]='\0';
	AAsset_close(assets);
	//LOGI("Shader Source:%s",buffer);
	return	buffer;
}

void Shader::AddVertexShaderFromFile(const char* vertFileName){
	AddProgram(ReadAssetsShader(vertFileName),GL_VERTEX_SHADER);

}

void Shader::AddFragmentShaderFromFile(const char* fragFileName){

	AddProgram(ReadAssetsShader(fragFileName),GL_FRAGMENT_SHADER);
}


//void Shader::SetRenderOfCamera(RenderOfCamera* renderCam){
//
//	this->renderCam=renderCam;
//}
//
//RenderOfCamera* Shader::GetRenderOfCamera(){
//
//	return this->renderCam;
//}

void Shader::SetAttribLocation(const char* attributeName,int location){

	glBindAttribLocation(program, location, attributeName);
}
