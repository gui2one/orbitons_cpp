#include "Camera.h"

Camera::Camera(){
	
}

Camera::Camera(float _fov_angle, float ratio)
{
	fov_angle = _fov_angle;
	screen_ratio = ratio;
	near = 0.01f;
	far = 100.0f;
	position = glm::vec3(5.0f, 0.0f, 0.0f);
	target_position = glm::vec3(0.0f, 0.0f, 0.0f);
	up_vector = glm::vec3(0.0f, 0.0f, 1.0f);
	setProjection(fov_angle, screen_ratio, near, far);
}

void Camera::setProjection(float _angle, float _screen_ratio, float _near = 0.01f, float _far = 100.0f)
{
	projection = glm::mat4(1.0f) * glm::perspective(_angle, _screen_ratio, _near, _far);;
}

void Camera::setFovAngle(float _angle){
	projection = glm::mat4(1.0f) * glm::perspective(_angle, screen_ratio, near, far);;
}

void Camera::setScreenRatio(float _ratio){
	projection = glm::mat4(1.0f) * glm::perspective(fov_angle, _ratio, near, far);;
}

