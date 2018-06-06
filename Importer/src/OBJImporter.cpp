#include "../include/OBJImporter.h"

CE::Imp::OBJData* CE::Imp::OBJImporter::ReadObjFile(const std::string& filePath)
{
	OBJData* data = new OBJData();
	std::fstream objFile;
	objFile.open(filePath, std::ios::in);
	if (!objFile.is_open())
		return nullptr;
	objFile.seekg(0, objFile.end);
	size_t size = objFile.tellg();
	objFile.seekg(0, objFile.beg);

	int gIndex = 0;

	char* buffer = (char*)malloc(size);
	while (!objFile.eof())
	{
		objFile.getline(buffer, size);
		std::string strBuffer = buffer;
		// read out the Material lib
		if (strBuffer[0] == 'm')
		{
			data->MtlLib = strBuffer.substr(7, strBuffer.size() - 7);
		}
		// read out the name of the obj
		if (strBuffer[0] == 'o')
		{
			data->ObjName = strBuffer.substr(2, strBuffer.size() - 2);
		}
		// read out vertex data
		if (strBuffer[0] == 'v' && strBuffer[1] == ' ')
		{
			std::vector<std::string> tempStr = cutStr(strBuffer.substr(3, strBuffer.size()));

			Nash::FVector4 vec;
			char coord = 0;
			for (int i = 0; i < 3; i++)
			{
				switch (coord)
				{
				case 0:
					vec.X = atof(parse(tempStr[0]).c_str());
					coord++;
					break;
				case 1:
					vec.Y = atof(parse(tempStr[1]).c_str());
					coord++;
					break;
				case 2:
					vec.Z = atof(parse(tempStr[2]).c_str());
					coord++;
					break;
				case 3:
					vec.W = atof(parse(tempStr[3]).c_str());
					coord++;
					break;
				}
			}
			data->Vertices.push_back(vec);
		}
		// read out vertex normals
		if (strBuffer[0] == 'v' && strBuffer[1] == 'n')
		{

			std::vector<std::string> tempStr = cutStr(strBuffer.substr(3, strBuffer.size()));

			Nash::FVector3 vec;
			char coord = 0;
			for (int i = 0; i < 3; i++)
			{
				switch (coord)
				{
				case 0:
					vec.X = atof(parse(tempStr[0]).c_str());
					coord++;
					break;
				case 1:
					vec.Y = atof(parse(tempStr[1]).c_str());
					coord++;
					break;
				case 2:
					vec.Z = atof(parse(tempStr[2]).c_str());
					coord++;
					break;
				}
			}
			data->Normals.push_back(vec);
		}
		// read out texture coordinates
		if (strBuffer[0] == 'v' && strBuffer[1] == 't')
		{
			std::vector<std::string> tempStr = cutStr(strBuffer.substr(3, strBuffer.size()));

			Nash::FVector3 vec;
			char coord = 0;
			for (int i = 0; i < 3; i++)
			{
				if (i == tempStr.size())
				{
					break;
				}
				switch (coord)
				{
				case 0:
					vec.X = atof(parse(tempStr[0]).c_str());
					coord++;
					break;
				case 1:
					vec.Y = atof(parse(tempStr[1]).c_str());
					coord++;
					break;
				case 2:
					vec.Z = atof(parse(tempStr[2]).c_str());
					coord++;
					break;
				}
			}
			data->TextureCoords.push_back(vec);
		}
		//read out the groupname
		if (strBuffer[0] == 'g')
		{
			FaceGroup group;
			group.Groupname = strBuffer.substr(2, strBuffer.size());
			data->FaceGroups.push_back(group);
			gIndex++;
		}
		// read out smoothing
		if (strBuffer[0] == 's' && strBuffer[3] != 'o')
		{
			data->FaceGroups[gIndex - 1].smoothShading = atoi(strBuffer.substr(3, strBuffer.size()).c_str());
		}
		// read out used material
		if (strBuffer[0] == 'u')
		{
			data->FaceGroups[gIndex - 1].UseMaterial = strBuffer.substr(7, strBuffer.size());
		}
		// read out faces
		if (strBuffer[0] == 'f')
		{
			std::string tempStr = strBuffer.substr(2, strBuffer.size());
			Nash::FVector3 vec;
			Face f;
			int beg = 0;
			char coord = 0;
			for (int i = 0; i < tempStr.size(); i++)
			{
				if (tempStr[i] == ' ' || i == tempStr.size())
				{
					vec.Z = atoi(tempStr.substr(beg, i - beg).c_str());
					beg = i + 1;
					coord = 0;
					f.push_back(vec);
				}
				if (tempStr[i] == '/' && tempStr[i + 1] == '/')
				{
					vec.Y = 0;
					i++;
					coord = 2;
				}
				if (tempStr[i] == '/')
				{
					switch (coord)
					{
					case 0:
						vec.X = atoi(tempStr.substr(beg, i - beg).c_str());
						beg = i + 1;
						coord++;
						break;
					case 1:
						vec.Y = atoi(tempStr.substr(beg, i - beg).c_str());
						beg = i + 1;
						coord++;
						break;
					}
				}
			}
			data->FaceGroups[gIndex - 1].Faces.push_back(f);
		}
	}
	return data;
}

std::string CE::Imp::OBJImporter::parse(const std::string & str)
{
	int len = 0;
	while (len != str.size())
	{
		len++;
	}
	return str.substr(0, len);
}

std::vector<std::string> CE::Imp::OBJImporter::cutStr(const std::string & str)
{
	int beg = 0;
	int len = 0;
	std::vector<std::string> tempStr;
	while (len != str.size() + 1)
	{
		if (str[len] == ' ')
		{
			tempStr.push_back(str.substr(beg, len - beg));
			beg = len + 1;
		}
		if (len == str.size())
		{
			tempStr.push_back(str.substr(beg, len - beg));
		}
		len++;
	}
	return tempStr;
}


