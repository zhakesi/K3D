#include "KFile/KPNGFile.h"
#include <png.h>
#include <zlib.h>

using namespace KCore;

namespace KFile 
{
	int KPNGFile::Read(KCore::KImage &img, const char* filePath)
	{
		png_image image;
		memset(&image, 0, (sizeof image));
		image.version = PNG_IMAGE_VERSION;
		int ret = png_image_begin_read_from_file(&image, filePath);
		if (!ret)
			return KR_FAILED;

		img.m_width = image.width;
		img.m_height = image.height;
		
		switch (image.format) {
		case PNG_COLOR_TYPE_GRAY:
			img.m_format = K_PIXEL_FORMAT_GRAY;
			break;
		case PNG_COLOR_TYPE_RGBA:
			img.m_format = K_PIXEL_FORMAT_RGBA;
			break;
		case PNG_COLOR_TYPE_RGB:
			img.m_format = K_PIXEL_FORMAT_RGB;
			break;
		default:
			img.m_format = K_PIXEL_FORMAT_RGB;
			break;
		}

		if (img.pixels)
			delete img.pixels;

		png_bytep buffer = (png_bytep)malloc(PNG_IMAGE_SIZE(image));

		png_image_finish_read(&image, NULL/*background*/, buffer,
			0/*row_stride*/, NULL/*colormap*/);

		img.pixels = buffer;

		return KR_SUCCESS;
	}
}