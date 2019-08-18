//#include "KFile/KAssimpFile.h"
//#include <fstream>
//#include <string>
//#include <iostream>
//#include <sstream>
//#include <Importer.hpp>
//#include <scene.h>
//#include <postprocess.h>
//
//using namespace KCore;
//using namespace std;
//
//namespace KFile
//{
//	Mesh processMesh(aiMesh* mesh, const aiScene* scene)
//	{
//		// Data to fill
//		vector<Vertex> vertices;
//		vector<GLuint> indices;
//		vector<Texture> textures;
//
//		// Walk through each of the mesh's vertices
//		for (GLuint i = 0; i < mesh->mNumVertices; i++)
//		{
//			Vertex vertex;
//			glm::vec3 vector; // We declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
//			// Positions
//			vector.x = mesh->mVertices[i].x;
//			vector.y = mesh->mVertices[i].y;
//			vector.z = mesh->mVertices[i].z;
//			vertex.Position = vector;
//			// Normals
//			vector.x = mesh->mNormals[i].x;
//			vector.y = mesh->mNormals[i].y;
//			vector.z = mesh->mNormals[i].z;
//			vertex.Normal = vector;
//			// Texture Coordinates
//			if (mesh->mTextureCoords[0]) // Does the mesh contain texture coordinates?
//			{
//				glm::vec2 vec;
//				// A vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
//				// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
//				vec.x = mesh->mTextureCoords[0][i].x;
//				vec.y = mesh->mTextureCoords[0][i].y;
//				vertex.TexCoords = vec;
//			}
//			else
//				vertex.TexCoords = glm::vec2(0.0f, 0.0f);
//			vertices.push_back(vertex);
//		}
//		// Now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
//		for (GLuint i = 0; i < mesh->mNumFaces; i++)
//		{
//			aiFace face = mesh->mFaces[i];
//			// Retrieve all indices of the face and store them in the indices vector
//			for (GLuint j = 0; j < face.mNumIndices; j++)
//				indices.push_back(face.mIndices[j]);
//		}
//		// Process materials
//		if (mesh->mMaterialIndex >= 0)
//		{
//			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
//			// We assume a convention for sampler names in the shaders. Each diffuse texture should be named
//			// as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
//			// Same applies to other texture as the following list summarizes:
//			// Diffuse: texture_diffuseN
//			// Specular: texture_specularN
//			// Normal: texture_normalN
//
//			// 1. Diffuse maps
//			vector<Texture> diffuseMaps = this->loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
//			textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
//			// 2. Specular maps
//			vector<Texture> specularMaps = this->loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
//			textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
//		}
//
//		// Return a mesh object created from the extracted mesh data
//		return Mesh(vertices, indices, textures);
//	}
//
//	static void processNode(aiNode* node, const aiScene* scene)
//	{
//		// 添加当前节点中的所有Mesh
//		for (unsigned i = 0; i < node->mNumMeshes; i++)
//		{
//			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
//			//this->meshes.push_back(this->processMesh(mesh, scene));
//		}
//		// 递归处理该节点的子孙节点
//		for (unsigned i = 0; i < node->mNumChildren; i++)
//		{
//			processNode(node->mChildren[i], scene);
//		}
//	}
//
//	int KAssimpFile::Read(const char* path)
//	{
//		Assimp::Importer import;
//		const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
//
//		if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
//		{
//			cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
//			return KR_FAILED;
//		}
//		processNode(scene->mRootNode, scene);
//		return KR_SUCCESS;
//	}
//}