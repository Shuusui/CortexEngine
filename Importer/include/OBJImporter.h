#pragma once
#pragma region Internal Includes
#pragma endregion 
#pragma region External Includes
#include "Vector4.h"
#include <string>
#include <fstream>
#include <vector>
#include <cstdint>
#pragma endregion 


namespace CE
{
	namespace Imp
	{
		__declspec(dllexport) typedef std::vector<Nash::FVector3> Face;

		struct __declspec(dllexport)FaceGroup
		{
		
			std::string Groupname;
			uint_fast32_t smoothShading = 0;
			std::string UseMaterial;
			std::vector<Face> Faces;
		};
		struct __declspec(dllexport)OBJData
		{
			std::string MtlLib; 
			std::string ObjName;
			std::vector<FaceGroup> FaceGroups;
			std::vector<Nash::FVector4> Vertices;
			std::vector<Nash::FVector3> Normals;
			std::vector<Nash::FVector3> TextureCoords;
		};
		class __declspec(dllexport) OBJImporter
		{
		public:
			static OBJData* ReadObjFile(const std::string& filePath); //TODO: Turn into const std::string& after testing
		private: 
			static std::string parse(const std::string& str);
			static std::vector<std::string> cutStr(const std::string& str);
		};
	}
}