#include "Camera2D.h"

namespace GE2D {

	Camera2D::Camera2D() : _position(0.0f, 0.0f)
		, _cameraMatrix(1.0f)
		, _orthoMatrix(1.0f)
		, _scale(1)
		, _needsMatrixUpdate(true)
		, _screenWidth(500)
		, _screenHeight(300)
	{
	}


	Camera2D::~Camera2D()
	{
	}

	void Camera2D::update() {

		if (_needsMatrixUpdate) {
			
			//for pos
			glm::vec3 translate(-_position.x + _screenWidth / 2, -_position.y + _screenHeight / 2, 0.0f);
			_cameraMatrix = glm::translate(_orthoMatrix, translate);
			
			//for scale
			glm::vec3 scale(_scale, _scale, 0.0f);
			_cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * _cameraMatrix;
			
			_needsMatrixUpdate = false;

		}

	}

	void Camera2D::init(int screenWidth, int screenHeight) {

		_screenWidth = screenWidth;
		_screenHeight = screenHeight;
		_orthoMatrix = glm::ortho(0.0f, (float)_screenWidth, 0.0f, (float)_screenHeight);
	}

	glm::vec2 Camera2D::convertScreenToWorld(glm::vec2 screenCoords) {
		//invert y
		screenCoords.y = _screenHeight - screenCoords.y;
		//make it that 0 is center
		screenCoords -= glm::vec2(_screenWidth / 2, _screenHeight / 2);
		//scale the coords
		screenCoords /= _scale;
		//translate with the camera
		screenCoords += _position;

		return screenCoords;

	}

}