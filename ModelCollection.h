#ifndef MODELCOLLECTION_H
#define MODELCOLLECTION_H

#include "Model.h"
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class ModelCollection
{
public:
	ModelCollection(void);
	ModelCollection(string );
	~ModelCollection(void);
	vector<Model*> modelMeshes;

	
	bool Render();
	bool ParseModelData();
	bool ParseMaterial();
	string fileName;
	Model* model;

};
#endif
