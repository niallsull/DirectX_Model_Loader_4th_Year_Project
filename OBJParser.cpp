#include "OBJParser.h"


OBJParser::OBJParser(string f)
{
	fileName=f;
	objectCount=0;
	point=0;
}

string OBJParser::Parse()
{
	ifstream myfile;
	myfile.open(fileName+".obj");

	while(myfile)
	{
		char buffer[100];
		//cout << "in loop" << endl;

		myfile.getline(buffer,100);
		string line=buffer;

		if((buffer[0]=='v') && (buffer[1]=='n'))
		{
			ParseNormal(line,buffer);
		}

		if((buffer[0]=='v') && (buffer[1]==' '))
		{
			ParseVertex(line,buffer);

		}


		if(buffer[0]=='f')
		{
			ParseFace(line,buffer);
		}


		if((buffer[0]=='v' ) && (buffer[1]=='t'))
		{
			ParseUV(line,buffer);
			
		}



		if(buffer[0]=='o')
		{
			

			if(objectCount>0)
			{
				mesh thisMesh;
				thisMesh.m=materials.at(objectCount-1);
				//thisMesh.vuvn=complete;
				thisMesh.faces=faces;

				Meshes.push_back(thisMesh);
			}
			faces.clear();
			objectCount++;
		}

		if(buffer[0]=='u')
		{
			ParseMaterial(line,buffer);
			
		}


	}

	mesh thisMesh;
	thisMesh.m=materials.at(objectCount-1);
	thisMesh.faces=faces;
	Meshes.push_back(thisMesh);

	//int count=0;
	

	

	ofstream outFile;

	outFile.open (fileName+"Test.txt");

	outFile << "Object Count: " << objectCount << "\n" <<endl;
	
	//outFile << "Data:" << "\n" << endl;
	
/*
	for(int i=0;i<triangles.size();i++)
	{
		outFile << triangles.at(i).pos.x << " " << triangles.at(i).pos.y << " " << triangles.at(i).pos.z << endl;
		outFile << triangles.at(i).pos2.x << " " << triangles.at(i).pos2.y << " " << triangles.at(i).pos2.z << endl;
		outFile << triangles.at(i).pos3.x << " " << triangles.at(i).pos3.y << " " << triangles.at(i).pos3.z << endl;
		//cout << endl;
	}
*/
	//for(int i=0;i<faces.size();i++)
	//{
	//	for(int j=0;j<faces.at(i).points.size()-2;j++)
	//	{
	//		/*
	//		outFile << vUV.at(faces.at(i).points.at(0)-1).v.x << " " << vUV.at(faces.at(i).points.at(0)-1).v.y<<" "<< vUV.at(faces.at(i).points.at(0)-1).v.z<<" "<< vUV.at(faces.at(i).points.at(0)-1).uv.u<<" "<<vUV.at(faces.at(i).points.at(0)-1).uv.v << endl;
	//		outFile << vUV.at(faces.at(i).points.at(j+1)-1).v.x << " " << vUV.at(faces.at(i).points.at(j+1)-1).v.y<<" "<< vUV.at(faces.at(i).points.at(j+1)-1).v.z<<" "<< vUV.at(faces.at(i).points.at(j+1)-1).uv.u<<" "<<vUV.at(faces.at(i).points.at(j+1)-1).uv.v << endl;
	//		outFile << vUV.at(faces.at(i).points.at(j+2)-1).v.x << " " << vUV.at(faces.at(i).points.at(j+2)-1).v.y<<" "<< vUV.at(faces.at(i).points.at(j+2)-1).v.z<<" "<< vUV.at(faces.at(i).points.at(j+2)-1).uv.u<<" "<<vUV.at(faces.at(i).points.at(j+2)-1).uv.v << endl;
	//		*/
	//		
	//		outFile << complete.at(faces.at(i).points.at(0)).v.x << "\t" << complete.at(faces.at(i).points.at(0)).v.y<<"\t"<< complete.at(faces.at(i).points.at(0)).v.z<<"\t"<< complete.at(faces.at(i).points.at(0)).uv.u<<"\t"<<complete.at(faces.at(i).points.at(0)).uv.v <<"\t"<< complete.at(faces.at(i).points.at(0)).n.x <<"\t"<< complete.at(faces.at(i).points.at(0)).n.y <<"\t"<< complete.at(faces.at(i).points.at(0)).n.z<< endl;
	//		
	//		outFile << complete.at(faces.at(i).points.at(j+1)).v.x << "\t" << complete.at(faces.at(i).points.at(j+1)).v.y<<"\t"<< complete.at(faces.at(i).points.at(j+1)).v.z<<"\t"<< complete.at(faces.at(i).points.at(j+1)).uv.u<<"\t"<<complete.at(faces.at(i).points.at(j+1)).uv.v<< "\t" <<complete.at(faces.at(i).points.at(j+1)).n.x <<"\t"<< complete.at(faces.at(i).points.at(j+1)).n.y <<"\t"<< complete.at(faces.at(i).points.at(j+1)).n.z<< endl;
	//		
	//		outFile << complete.at(faces.at(i).points.at(j+2)).v.x << "\t" << complete.at(faces.at(i).points.at(j+2)).v.y<<"\t"<< complete.at(faces.at(i).points.at(j+2)).v.z<<"\t"<< complete.at(faces.at(i).points.at(j+2)).uv.u<<"\t"<<complete.at(faces.at(i).points.at(j+2)).uv.v << "\t" << complete.at(faces.at(i).points.at(j+2)).n.x <<"\t"<< complete.at(faces.at(i).points.at(j+2)).n.y <<"\t"<< complete.at(faces.at(i).points.at(j+2)).n.z<< endl;
	//		
	//	}
	//}

	




	for(int o=0;o<Meshes.size();o++)
	{
		int count=0;
		//
		for(int i=0;i<Meshes.at(o).faces.size();i++)
		{
			count=count+((Meshes.at(o).faces.at(i).points.size() - 2) * 3);

		}

		outFile << "o " << o << endl;
		outFile << "count " << count << endl;
		for(int i=0;i<Meshes.at(o).faces.size();i++)
		{
		
			for(int j=0;j<Meshes.at(o).faces.at(i).points.size()-2;j++)
			{
			
			
			outFile << "v " << complete.at(Meshes.at(o).faces.at(i).points.at(0)).v.x << " " << complete.at(Meshes.at(o).faces.at(i).points.at(0)).v.y<<" "<< complete.at(Meshes.at(o).faces.at(i).points.at(0)).v.z<<" "<< complete.at(Meshes.at(o).faces.at(i).points.at(0)).uv.u<<" "<<complete.at(Meshes.at(o).faces.at(i).points.at(0)).uv.v <<" "<< complete.at(Meshes.at(o).faces.at(i).points.at(0)).n.x <<" "<< complete.at(Meshes.at(o).faces.at(i).points.at(0)).n.y <<" "<< complete.at(Meshes.at(o).faces.at(i).points.at(0)).n.z<< endl;
			
			outFile << "v " << complete.at(Meshes.at(o).faces.at(i).points.at(j+1)).v.x << " " << complete.at(Meshes.at(o).faces.at(i).points.at(j+1)).v.y<<" "<< complete.at(Meshes.at(o).faces.at(i).points.at(j+1)).v.z<<" "<< complete.at(Meshes.at(o).faces.at(i).points.at(j+1)).uv.u<<" "<<complete.at(Meshes.at(o).faces.at(i).points.at(j+1)).uv.v<< " " <<complete.at(Meshes.at(o).faces.at(i).points.at(j+1)).n.x <<" "<< complete.at(Meshes.at(o).faces.at(i).points.at(j+1)).n.y <<" "<< complete.at(Meshes.at(o).faces.at(i).points.at(j+1)).n.z<< endl;
			
			outFile << "v " << complete.at(Meshes.at(o).faces.at(i).points.at(j+2)).v.x << " " << complete.at(Meshes.at(o).faces.at(i).points.at(j+2)).v.y<<" "<< complete.at(Meshes.at(o).faces.at(i).points.at(j+2)).v.z<<" "<< complete.at(Meshes.at(o).faces.at(i).points.at(j+2)).uv.u<<" "<<complete.at(Meshes.at(o).faces.at(i).points.at(j+2)).uv.v << " " << complete.at(Meshes.at(o).faces.at(i).points.at(j+2)).n.x <<" "<< complete.at(Meshes.at(o).faces.at(i).points.at(j+2)).n.y <<" "<< complete.at(Meshes.at(o).faces.at(i).points.at(j+2)).n.z<< endl;
			
		}
	}
		outFile << "Material" << endl;

		outFile << "Am " << Meshes.at(o).m.ambient.red << " " << Meshes.at(o).m.ambient.green << " " << Meshes.at(o).m.ambient.blue << endl;
		outFile << "Di " << Meshes.at(o).m.diffuse.red << " " << Meshes.at(o).m.diffuse.green << " " << Meshes.at(o).m.diffuse.blue << endl;
		outFile << "Sp " << Meshes.at(o).m.specular.red << " " << Meshes.at(o).m.specular.green << " " << Meshes.at(o).m.specular.blue << endl;
		outFile << "Ot " << Meshes.at(o).m.other.red << " " <<Meshes.at(o).m.other.green << " " << Meshes.at(o).m.other.blue << endl;
		outFile << "Tx " << Meshes.at(o).m.mat << endl;
		outFile << "Ds " << Meshes.at(o).m.normal << endl;

	}





	outFile.close();

	return fileName+"Test";
}

OBJParser::~OBJParser(void)
{
}

void OBJParser::ParseVertex(string line, char* buffer)
{
	float f[3];
			vector3 vertex;
			int start=2;
			int end=0;
			end=start;
			for(int i=0;i<3;i++)
			{
				//while(buffer[end]!=' ')
				while(buffer[end]!=' ')
				{
					end++;

				}
				string pointString=line.substr(start,start-end);
				f[i] = stof(pointString);
				//cout << f[i] << endl;
				end++;
				start=end;
			}
			vertex.x=f[0];
			vertex.y=f[1];
			vertex.z=f[2];
			//cout << vertex.x << " " << vertex.y << " " << vertex.z << endl;
			
			vertices.push_back(vertex);
}


void OBJParser::ParseNormal(string line, char* buffer)
{
	float f[3];
			int start=3;
			int end=start;
			for(int i=0;i<3;i++)
			{
				while(buffer[end]!=' ')
				{
					end++;

				}
				end++;
			//	string pointString=line.substr(start,start-end);
				string pointString=line.substr(start,4);
				f[i] = stof(pointString);
				start=end;
			}
			normal n;
			n.x=f[0]; 
			n.y=f[1]; 
			n.z=f[2]*(-1);
			//cout << n.x << " "<<n.y<<" "<<n.z<< endl;
			normals.push_back(n);
}

void OBJParser:: ParseFace(string line, char* buffer)
{
	int start=2;
			int end=start;
			face fa;
			

			
			int i=start;
			for(;i<line.length();i++)
			{
				if(i==line.length()-1)
				{
					string num=line.substr(start,i);
					// check the number of slashes and shit
					int slashCount=0;
					for(int j=0;j<num.length();j++)
					{
						if(num[j]=='/')
							slashCount++;
					}

					if(slashCount==2)
					{
						int f[3];
						//chech slashes together
						// can do like verts then
						int s=0;
						int e=s;
						
						int slashes[2];
						int d=0;
						for(int i=0;i<num.length();i++)
						{
							if(num[i]=='/')
							{
								slashes[d]=i;
								d++;
							}
						}

						f[0]=stoi(num.substr(0,slashes[0]));
						f[1]=stoi(num.substr(slashes[0]+1,slashes[1]-slashes[0]+1));
						f[2]=stoi(num.substr(slashes[1]+1,num.length()));
						vertexUVNormal vuvn;
						vuvn.v.x=vertices.at(f[0]-1).x;
						vuvn.v.y=vertices.at(f[0]-1).y;
						vuvn.v.z=vertices.at(f[0]-1).z;
						vuvn.uv.u=textCoords.at(f[1]-1).u;
						vuvn.uv.v=textCoords.at(f[1]-1).v;
						vuvn.n.x=normals.at(f[2]-1).x;
						vuvn.n.y=normals.at(f[2]-1).y;
						vuvn.n.z=normals.at(f[2]-1).z;
						fa.points.push_back(point);
						complete.push_back(vuvn);
						point++;
					}
					if(slashCount==1)
					{
						for(int d=0;d<num.length();d++)
						{
							if(num[d]=='/')
							{
								int f=stoi(num.substr(0,d));
								fa.points.push_back(f);
								int uv=stoi(num.substr(d+1,num.length()));
								vertexAndUV thisvertex;
								//thisvertex.v=vertices.at(f-1);
								//thisvertex.uv=textCoords.at(uv-1);

								thisvertex.v.x=vertices.at(f-1).x;
								thisvertex.v.y=vertices.at(f-1).y;
								thisvertex.v.z=vertices.at(f-1).z;

								thisvertex.uv.u=textCoords.at(uv-1).u;
								thisvertex.uv.v=textCoords.at(uv-1).v;

								vUV.push_back(thisvertex);
							}
						}
					}
					start=i+1;
					
				}
			


				//if(buffer[i]==' ')
				if(line.at(i)==' ')
				{
					string num=line.substr(start,i-start);
					// check the number of slashes and shit
					int slashCount=0;
					for(int j=0;j<num.length();j++)
					{
						if(num[j]=='/')
							slashCount++;
					}

					if(slashCount==2)
					{
						int f[3];
						//chech slashes together
						// can do like verts then
						int s=0;
						int e=s;
						
						int slashes[2];
						int d=0;
						for(int i=0;i<num.length();i++)
						{
							if(num[i]=='/')
							{
								slashes[d]=i;
								d++;
							}
						}

						f[0]=stoi(num.substr(0,slashes[0]));
						f[1]=stoi(num.substr(slashes[0]+1,slashes[1]-slashes[0]+1));
						f[2]=stoi(num.substr(slashes[1]+1,num.length()));

						vertexUVNormal vuvn;
						vuvn.v.x=vertices.at(f[0]-1).x;
						vuvn.v.y=vertices.at(f[0]-1).y;
						vuvn.v.z=vertices.at(f[0]-1).z;
						vuvn.uv.u=textCoords.at(f[1]-1).u;
						vuvn.uv.v=textCoords.at(f[1]-1).v;
						vuvn.n.x=normals.at(f[2]-1).x;
						vuvn.n.y=normals.at(f[2]-1).y;
						vuvn.n.z=normals.at(f[2]-1).z;
						fa.points.push_back(point);
						complete.push_back(vuvn);
						point++;
					}

					if(slashCount==1)
					{
						for(int d=0;d<num.length();d++)
						{
							if(num[d]=='/')
							{
								int f=stoi(num.substr(0,d));
								fa.points.push_back(f);
								int uv=stoi(num.substr(d+1,num.length()));
								vertexAndUV thisvertex;
								//thisvertex.v=vertices.at(f-1);
								//thisvertex.uv=textCoords.at(uv-1);

								thisvertex.v.x=vertices.at(f-1).x;
								thisvertex.v.y=vertices.at(f-1).y;
								thisvertex.v.z=vertices.at(f-1).z;

								thisvertex.uv.u=textCoords.at(uv-1).u;
								thisvertex.uv.v=textCoords.at(uv-1).v;

								vUV.push_back(thisvertex);
							}
						}
					}
					start=i+1;
					
				}
			}	
			
			faces.push_back(fa);
}

void OBJParser::ParseUV(string line, char* buffer)
{
	vertexUV vert;
			int start=3;
			float f[3];
			int position=0;

			for(int i=start;i<line.length();i++)
			{
				//if(buffer[i]==' ')
				if(buffer[i]==' ')
				{
					string num=line.substr(start,i-start);
					f[position]=stof(num);
					start=i+1;
					position++;
				}

				if(i==line.length()-1)
				{
					string num=line.substr(start,i);
					f[position]=stof(num);
					position++;
				}

			}
			

			vert.u=f[0];
			//if(vert.u<0)
				//vert.u*=-1;

			vert.v=1-f[1];
			//if(vert.v<0)
				//vert.v*=-1;
			//cout << vert.u << " " << vert.v << endl;
			textCoords.push_back(vert);

}

void OBJParser::ParseMaterial(string line, char* buffer)
{
	ifstream materialFile;
			materialFile.open(fileName+".mtl");
			

			string materialName=line.substr(7);

			material m;

			bool foundMaterial=false;
			char Matbuffer[100];
			

			materialFile.getline(Matbuffer,100);
			string matline=Matbuffer;



			while(foundMaterial==false)
			{
				materialFile.getline(Matbuffer,100);
				matline=Matbuffer;

				if(matline.length() >= 7+materialName.length()){
					string findMaterial=matline.substr(7,materialName.length());

					if(findMaterial==materialName)
					foundMaterial=true;
				}

				
			}

			
			//while(Matbuffer[0]!=' ')
			while((Matbuffer[0]!=' ') && (matline!=""))
			{
				materialFile.getline(Matbuffer,100);
				matline=Matbuffer;

				if(Matbuffer[0]=='N')
				{
					if(Matbuffer[1]=='s')
					{
						int Ns=stoi(matline.substr(3));
						m.other.red=Ns;
					}
					if(Matbuffer[1]=='i')
					{
						int Ns=stoi(matline.substr(3));
						m.other.green=Ns;
					}
				}
				if(Matbuffer[0]=='d')
				{
					int d=stoi(matline.substr(2));
					m.other.green=d;
				}
				if(Matbuffer[0]=='i')
				{
					int ilium=stoi(matline.substr(6));
					m.other.blue=ilium;
				}

				if(Matbuffer[0]=='K')
				{
					if(Matbuffer[1]=='a')
					{
						float f[3];
						int start=3;
						int end=start;
						//cout << " matline.length " << matline.length() << endl;
						for(int i=0;i<3;i++)
						{
							while((Matbuffer[end]!=' ')  && (end<matline.length()))
							{
							end++;

							}
						end++;
						string pointString=matline.substr(start,end-start);
						f[i] = stof(pointString);
						start=end;
						}
						
						
						m.ambient.red=f[0]; 
						m.ambient.green=f[1]; 
						m.ambient.blue=f[2];
						
					}

					if(Matbuffer[1]=='d')
					{
						float f[3];
						int start=3;
						int end=start;
						for(int i=0;i<3;i++)
						{
							while((Matbuffer[end]!=' ')  && (end<matline.length()))
							{
							end++;

							}
						end++;
						string pointString=matline.substr(start,start-end);
						f[i] = stof(pointString);
						start=end;
						}
						
						
						m.diffuse.red=f[0]; 
						m.diffuse.green=f[1]; 
						m.diffuse.blue=f[2];
						
					}

					if(Matbuffer[1]=='s')
					{
						float f[3];
						int start=3;
						int end=start;
						for(int i=0;i<3;i++)
						{
							while((Matbuffer[end]!=' ')  && (end<matline.length()))
							{
							end++;

							}
						end++;
						string pointString=matline.substr(start,start-end);
						f[i] = stof(pointString);
						start=end;
						}
						
						
						m.specular.red=f[0]; 
						m.specular.green=f[1]; 
						m.specular.blue=f[2];
						
					}
				}

				if(Matbuffer[0]=='m')
				{
					if((Matbuffer[5]=='d') && (Matbuffer[4]=='K'))  // diffuse color texture
					{
						int start=7;
						int end=start;
						while(Matbuffer[end]!='.')
						{
							end++;
						}
						
						string mapDiffuse=matline.substr(start,end-start);
						m.mat=mapDiffuse+".dds";
					}

					if((Matbuffer[5]=='a') && (Matbuffer[4]=='K'))  // ambient colour texture
					{
						int start=7;
						int end=start;
						while(Matbuffer[end]!='.')
						{
							end++;
						}
						
						string mapAmbient=matline.substr(start,end-start);
					}

					if((Matbuffer[5]=='s') && (Matbuffer[4]=='K'))  // specular color texture
					{
						int start=7;
						int end=start;
						while(Matbuffer[end]!='.')
						{
							end++;
						}
						
						string mapSpecular=matline.substr(start,end-start);
					}

					if(Matbuffer[4]=='d')   // alpha texture
					{
						int start=6;
						int end=start;
						while(Matbuffer[end]!='.')
						{
							end++;
						}
						
						string mapAlpha=matline.substr(start,end-start);
					}

					if(Matbuffer[4]=='D')   // bump texture
					{
						int start=9;
						int end=start;
						while(Matbuffer[end]!='.')
						{
							end++;
						}
						
						string normal=matline.substr(start,end-start);
						m.normal=normal+".dds";
					}

				}

			}
			materials.push_back(m);
			materialFile.close();
}
