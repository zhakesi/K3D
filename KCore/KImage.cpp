#include "KCore/KImage.h"

namespace KCore 
{
	KImage::KImage() 
	{
		m_width = 0;
		m_height = 0;
		pixels = nullptr;
	}

	KImage::~KImage() 
	{
		m_width = 0;
		m_height = 0;
		if (pixels) {
			delete pixels;
			pixels = nullptr;
		}
	}
}