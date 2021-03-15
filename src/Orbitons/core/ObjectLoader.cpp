#include "ObjectLoader.h"

namespace Orbitons{
	ObjLoader::ObjLoader(){
		// std::cout << "ObjLoader initiatied ----\n";
	}

	// ObjLoader::~ObjLoader(){
	// 	std::cout << "ObjLoader DELETED ----\n";
	// }


	Mesh ObjLoader::assimp_load(std::string file_path){
		// printf("FILE PATH : %s\n", file_path.c_str());
		Assimp::Importer importer;

		const aiScene* scene = importer.ReadFile( file_path,
			aiProcess_CalcTangentSpace |
			aiProcess_Triangulate |
			//aiProcess_JoinIdenticalVertices |
			//aiProcess_SortByPType |
			aiProcess_GenNormals 
		);

		if(scene){
			
			// std::cout << "ObjLoader assimp loading V2 : " << file_path << "\n";
			// std::cout << "----------------------------\n";
			
			// printf("num vertices : %d\n", scene->mMeshes[0]->mNumVertices);
			
			std::vector<Vertex> vertices;
			for (int i = 0; i < scene->mMeshes[0]->mNumVertices; i++){
				Vertex vertex;
				vertex.position.x = scene->mMeshes[0]->mVertices[i].x;
				vertex.position.y = scene->mMeshes[0]->mVertices[i].y;
				vertex.position.z = scene->mMeshes[0]->mVertices[i].z;
				
				if (scene->mMeshes[0]->HasNormals()) {

					vertex.normal.x = scene->mMeshes[0]->mNormals[i].x;
					vertex.normal.y = scene->mMeshes[0]->mNormals[i].y;
					vertex.normal.z = scene->mMeshes[0]->mNormals[i].z;
				}
				else {
					vertex.normal.x = 0.0f;
					vertex.normal.y = 0.0f;
					vertex.normal.z = 1.0f;
				}
				
				if(scene->mMeshes[0]->HasTextureCoords(0)){
					
					vertex.t_coords.x = scene->mMeshes[0]->mTextureCoords[0][i].x;
					vertex.t_coords.y = scene->mMeshes[0]->mTextureCoords[0][i].y;
				}else{
					vertex.t_coords.x = 0.0f;
					vertex.t_coords.y = 0.0f;
				}
				vertices.push_back(vertex);

			
			}
			
			std::vector<unsigned int> indices;
			for (int i = 0; i < scene->mMeshes[0]->mNumFaces; i++)
			{
				//~ std::cout << "Face : "<< i << "\n";
				for (int j = 0; j < scene->mMeshes[0]->mFaces[i].mNumIndices; j++)
				{
					unsigned int index = scene->mMeshes[0]->mFaces[i].mIndices[j];
					indices.push_back(index);

				}
			}
			
			
			Mesh mesh;
			mesh.vertices = vertices;
			mesh.indices = indices;
			
			
			return mesh;
		}
		std::cout<< "problem loading " << file_path << "\n";
		Mesh empty_mesh;
		return empty_mesh;
	}
}
