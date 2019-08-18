#include "KGraphic/KShader.h"
#include "KFile/KStringFile.h"
#include <iostream>


namespace KGraphic
{
	KShader::KShader()
	{
		m_program = 0;
	}

	KShader::KShader(const char* vpath, const char* fpath)
	{
		GLint success;
		GLchar infoLog[512];

		GLuint vshader = CompileShaderFile(vpath, GL_VERTEX_SHADER);
		GLuint fshader = CompileShaderFile(fpath, GL_FRAGMENT_SHADER);

		m_program = glCreateProgram();
		glAttachShader(m_program, vshader);
		glAttachShader(m_program, fshader);
		glLinkProgram(m_program);

		glGetProgramiv(m_program, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(m_program, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}
		glDeleteShader(vshader);
		glDeleteShader(fshader);
	}

	KShader::~KShader() 
	{
		//if (m_program) {
		//	glDeleteProgram(m_program);
		//	m_program = 0;
		//}
	}

	void KShader::Use() 
	{
		glUseProgram(m_program);
	}

	GLuint KShader::CompileShaderFile(const char* path, GLenum type)
	{
		GLint success;
		GLchar infoLog[512];
		std::string str_buff;

		KFile::KSringFile::Read(str_buff, path);
		const char *char_sh = str_buff.c_str();
		GLuint shader = glCreateShader(type);
		glShaderSource(shader, 1, &char_sh, NULL);
		glCompileShader(shader);
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			std::cout << "error::Graphic::shader compilation failed.\n" <<
				path << "\n" << infoLog << std::endl;
			return 0;
		};
		return shader;
	}
}