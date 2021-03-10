#ifndef CAMERA_H
#define CAMERA_H
#include "../pch.h"
#include "../core.h"
#include "Entity3d.h"
class Camera : public Entity3d
{
	public:
		Camera();
		Camera(float _fov_angle, float ratio);
		void setProjection(float angle, float screen_ratio, float near, float far);
		void setFovAngle(float _angle);
		void setScreenRatio(float _ratio);
		float fov_angle = 45.0f;
		float screen_ratio = 16.0/9.0;
		float near = 0.01f; 
		float far = 100.0f;
		
		// glm::vec3 position;
		glm::vec3 target_position;
		glm::vec3 up_vector;
		
		glm::mat4 projection;
	private:
		/* add your private declarations */
};

#endif /* CAMERA_H */ 