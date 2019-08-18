#include "KGraphic/KTexture.h"
#include "KFile/KPNGFile.h"
using namespace KCore;
using namespace KFile;

namespace KGraphic 
{
	KTexture::KTexture(const char *path)
	{
		KImage image;
		int ret = KPNGFile::Read(image, path);
		glGenTextures(1, &txtID);
		glBindTexture(GL_TEXTURE_2D, txtID);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		int format = TEXTURE_PIXEL_FORMAT(image.m_format);
		glTexImage2D(GL_TEXTURE_2D, 0, format,
			image.m_width, image.m_height,
			0, format, GL_UNSIGNED_BYTE, image.pixels);

		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 4);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	KTexture::~KTexture()
	{

	}

	GLenum KTexture::TEXTURE_PIXEL_FORMAT(int pixel_format)
	{
		GLenum format = GL_RGB;
		switch (pixel_format)
		{
		case K_PIXEL_FORMAT_GRAY:
			format = GL_R8;
			break;
		case K_PIXEL_FORMAT_RGB:
			format = GL_RGB;
			break;
		case K_PIXEL_FORMAT_RGBA:
			format = GL_RGBA;
			break;
		default:
			break;
		}
		return format;
	}
}
