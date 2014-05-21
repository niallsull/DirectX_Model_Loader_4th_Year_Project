#include "OBJParser.h"
#include "ModelCollection.h"
#include "systemclass.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	//char* filename;
	
	SystemClass* System;
	bool result;

	
	//string file;	
	//cout << " enter obj model name, i.e. no extension " << endl;
	//std::cin >> file;

	//OBJParser parser=OBJParser("3box");
	
	//string model;
	//model=parser.Parse();

	//ModelCollection models=ModelCollection(model);

	//models.ParseModelData();
	

	// Create the system object.
	System = new SystemClass;
	if(!System)
	{
		return 0;
	}

	// Initialize and run the system object.
	result = System->Initialize();
	if(result)
	{
		System->Run();
	}

	// Shutdown and release the system object.
	System->Shutdown();
	delete System;
	System = 0;

	return 0;



	//cout << models.modelMeshes.size() << endl;

	string name;
	cin >> name;







	std::cin.get();
	cout << "done" << endl;
	return 0;
}







