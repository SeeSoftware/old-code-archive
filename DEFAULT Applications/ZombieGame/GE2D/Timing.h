#pragma once

namespace GE2D {

	class FpsLimiter {
	public:
		FpsLimiter();
		
		void init(float maxFPS);

		void setMaxFPS(float maxFPS);

		void begin();
		
		//end will return the current fps
		float end();

	private:
		
		void calculateFPS();

		float _fps;
		float _maxFPS;
		float _frameTime;
		unsigned int _startTicks;
		

	};

}