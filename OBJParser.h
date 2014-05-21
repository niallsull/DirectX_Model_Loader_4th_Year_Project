#ifndef OBJPARSER_H
#define OBJPARSER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;


struct vector3
{
	float x;
	float y;
	float z;
};

struct normal
{
	float x;
	float y;
	float z;
};

struct triangle    // gonna have to make triangle of vertexUV as well
{
	vector3 pos;
	vector3 pos2;
	vector3 pos3;
};

struct face
{
	vector<int> points;
};


struct vertexUV
{
	float u;
	float v;
};

struct vertexAndUV
{
	vector3 v;
	vertexUV uv;
};

struct vertexUVNormal
{
	vector3 v;
	vertexUV uv;
	normal n;
};

struct float3
{
	float red;
	float green;
	float blue;
	
};

struct material
{
	float3 ambient;
	float3 diffuse;
	float3 specular;
	float3 other;
	string mat;
	string normal;
};

struct mesh
{
	material m;
	vector<vertexUVNormal> vuvn;
	vector<face> faces;
};


class OBJParser
{
public:
	OBJParser(string);

	~OBJParser(void);

	string Parse();
	void ParseVertex(string, char*);
	void ParseNormal(string , char*);
	void ParseFace(string ,char*);

	void ParseUV(string, char*);
	void ParseMaterial(string, char*);

	vector<normal> normals;
	int point;
	vector<vector3> vertices;
	vector<triangle> triangles;
	vector<face> faces;
	vector<vertexUV> textCoords;
	
	vector<vertexAndUV> vUV;
	vector<vertexUVNormal> complete;
	vector<material> materials;
	vector<mesh> Meshes;
	int objectCount;
	string fileName;
};
#endif
