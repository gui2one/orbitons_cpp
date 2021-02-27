#ifndef CAMERA_H
#define CAMERA_H
#include "../pch.h"
#include "../core.h"
class Camera
{
	public:

		Camera(float _fov_angle, float ratio);
		void setProjection(glm::mat4 _proj);
		float fov_angle = 45.0f;
		float near = 0.01f; 
		float far = 100.0f;
		
		glm::vec3 position;
		glm::vec3 target_position;
		glm::vec3 up_vector;
		
		glm::mat4 projection;
	private:
		/* add your private declarations */
};

#endif /* CAMERA_H */ 