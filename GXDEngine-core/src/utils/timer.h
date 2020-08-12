#pragma once
#pragma optimize( "f", on )

#include <chrono>

namespace GXDEngine {

	class Timer {
	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> m_Start;
	public:
		Timer() 
		{
			reset();
		}

		void reset() 
		{
			m_Start = std::chrono::high_resolution_clock::now();
		}

		float elapsed() 
		{
			return std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(std::chrono::high_resolution_clock::now() - m_Start).count() / 1000.0f;
		}

	};

}