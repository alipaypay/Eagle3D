#ifndef TOOLS_H
#define TOOLS_H

#include "Vertex.h"
#include "EagleLog.h"
#include <GLES2/gl2.h>
#include <math.h>
#include <vector>
#include <string>

using namespace std;
class Tools{
public:
	static GLfloat* GetFloatBuffer(vector<Vertex> vertices);


	static GLfloat* GetVertexFloatBuffer(vector<Vertex> vertices);

	static GLfloat* GetTextureCoordFloatBuffer(vector<Vertex> vertices);

	static GLuint* GetIntBuffer(vector<int> indics);

	//Split String char
	static void SplitString(string strTarget,string splitSymbol,vector<string>& outputData);

	static GLfloat* GetFloatBuffer(Vertex *vertices);

	static void RemoveEmptyStrings(vector<string> data,vector<string>& outPutData);

	/**
	 ** �ַ���ƴ�ӷ���
	 **/
	static const char * Str_Contact(const char *str1,const char *str2);

	static vector<char*> GetStrLines(char * destination);
};
#endif
