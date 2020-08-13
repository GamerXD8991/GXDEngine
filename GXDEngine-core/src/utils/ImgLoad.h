#pragma once
#pragma optimize( "f", on )

#include "../stdafx.h"

namespace GXDEngine {
	class ImgLoad {
	public:
		static ImgLoad& instance() {

			FreeImage_Initialise();

			static ImgLoad m_instance;
			return m_instance;
		}

		~ImgLoad() { FreeImage_DeInitialise(); }

		static BYTE* loadImg(const char* path, int* width, int* height, unsigned int& bpp) {

			FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
			FIBITMAP* dib = nullptr;
			BYTE* result = nullptr;

			fif = FreeImage_GetFileType(path, 0);

			if (fif == FIF_UNKNOWN)
				fif = FreeImage_GetFIFFromFilename(path);
			if (fif == FIF_UNKNOWN)
				result = nullptr;

			if (FreeImage_FIFSupportsReading(fif))
				dib = FreeImage_Load(fif, path);

			if (!dib)
				result = nullptr;

			result = FreeImage_GetBits(dib);
			*width = FreeImage_GetWidth(dib);
			*height = FreeImage_GetHeight(dib);

			bpp = FreeImage_GetBPP(dib);
			const unsigned int w = (*width);
			const unsigned int h = (*height);

			size_t size = (size_t)w * (size_t)h * (bpp / 8);
			BYTE* res = new BYTE[size];

			if ((result == 0) || (w == 0) || (h == 0)) {
				delete[] res;
				res = nullptr;
			} else {
				A_memcpy(res, result, size);
			}
			FreeImage_Unload(dib);
			return res;
			
			/*

			Order of pixels read by FreeImage_Load(FIF_PNG, filename)

			/-----------\
			|3.		  4.|
			|		    |
			|   IMAGE   |
			|		    |
			|1.		  2.|
			\-----------/

			*/
		}

		ImgLoad& operator=(const ImgLoad& iL);
	private:
		ImgLoad()  {}

		ImgLoad(const ImgLoad&);
	};
	
}