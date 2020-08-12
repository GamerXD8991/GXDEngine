#pragma once
#pragma optimize( "f", on )
#include <asmlib.h>
#include <string>

namespace GXDEngine {

	static std::string read_file(const char* filepath) {
		FILE* file = fopen(filepath, "rt");
		fseek(file, 0, SEEK_END);
		const unsigned long length = ftell(file);
		const unsigned long lengthPlus1 = length + 1;
		char* data = new char[lengthPlus1];
		A_memset(data, 0, lengthPlus1);
		fseek(file, 0, SEEK_SET);
		fread(data, 1, length, file);
		fclose(file);

		std::string result(data);
		delete[] data;
		return result;
	}
}