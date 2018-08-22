#ifndef OBJ_INDEX_H
#define OBJ_INDEX_H
#include "EagleLog.h"
class OBJIndex{
public:
	OBJIndex();
	int VectexIndex;
	int TextureCoordIndex;
	int NormalIndex;

	bool operator==(const OBJIndex &objI);

	bool operator < (const  OBJIndex& oJI) const;

	int HashCode();
};
#endif
