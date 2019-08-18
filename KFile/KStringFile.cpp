#include "KFile/KStringFile.h"
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

namespace KFile 
{
	int KSringFile::Read(std::string &strbuff, const char* filePath)
	{
		std::ifstream ifile;

		ifile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			ifile.open(filePath);
			std::stringstream s_stream;
			s_stream << ifile.rdbuf();
			ifile.close();
			strbuff = s_stream.str();
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "error::FILE::file read failed! path: " << filePath << std::endl;
			return KR_FAILED;
		}
		return KR_SUCCESS;
	}
}