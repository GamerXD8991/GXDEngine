#pragma once
#pragma optimize( "f", on )
#include "../stdafx.h"

namespace GXDEngine {

	static std::string read_file(const char* filepath) {
		FILE* file = fopen(filepath, "rt");
		_fseeki64(file, 0, SEEK_END);
		const unsigned long length = _ftelli64(file);
		const unsigned long lengthPlus1 = length + 1;
		char* data = new char[(size_t)lengthPlus1];
		A_memset(data, 0, (size_t)lengthPlus1);
		_fseeki64(file, 0, SEEK_SET);
		fread(data, 1, (size_t)length, file);
		fclose(file);

		std::string result(data);
		delete[] data;
		return result;
	}
}