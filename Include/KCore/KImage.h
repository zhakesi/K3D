#pragma once
#include "KCore/KDef.h"

namespace KCore {
	enum {
		K_PIXEL_FORMAT_GRAY,
		K_PIXEL_FORMAT_RGB,
		K_PIXEL_FORMAT_RGBA
	};

	class KLIB_EXPORT KImage
	{
	public:
		KImage();
		~KImage();
	public:
		int m_width;
		int m_height;
		int m_stride;
		int m_format;
		void *pixels;
	};
}