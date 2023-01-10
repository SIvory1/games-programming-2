#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

struct MainCamera
{
public:

	float fov = 70;

	void InitializeCamera(const glm::vec3& pos, float fov, float aspect, float nearClip, float farClip)
	{
		this->pos = pos;
		// shoudl be -1
		this->forward = glm::vec3(0.0f, 0.0f, 1.0f);
		this->up = glm::vec3(0.0f, 1.0f, 0.0f);
		this->projection = glm::perspective(fov, aspect, nearClip, farClip);	 
	}

	glm::vec3 getPos()
	{
		return this->pos;
	}

	inline glm::mat4 GetViewProjection() const
	{
		return projection * glm::lookAt(pos, pos + forward, up);
	}

	// dont want to use inline, as it is called loads of times and that woudfl cause big memeoray footprint???
	void ChangeFOV(float fov, float aspect, float nearClip, float farClip) 
	{
	   this->projection = glm::perspective(fov, aspect, nearClip, farClip);
	}

	inline glm::mat4 GetView() const
	{
		return glm::lookAt(pos, pos + forward, up);
	}

	inline glm::mat4 GetProjection() const
	{
		return projection;
	}

	inline glm::vec3 getPosition() const
	{
		return pos;
	}
	
	void Zoom(int zoomForce)
	{
		fov += zoomForce;
	}
	
    void MoveForward(float cameraSPD)
    {
	     pos += forward * cameraSPD;
    }

	void MoveHoriz(float cameraSPD)
	{
		pos += glm::cross(up, forward) * -cameraSPD;
	}

	void MoveVertical(float cameraSPD)
	{
		pos += up * cameraSPD;
	}
	
	void RotateY(float angle)
    {
		glm::vec3 right = glm::normalize(glm::cross(up, forward));

		forward = glm::vec3(glm::normalize(glm::rotate(angle, right) * glm::vec4(forward, 0.0)));
		up = glm::normalize(glm::cross(forward, right));
	}

	void RotateX(float angle)
	{
		static const glm::vec3 UP(0.0f, 1.0f, 0.0f);

		glm::mat4 rotation = glm::rotate(angle, UP);

		forward = glm::vec3(glm::normalize(rotation * glm::vec4(forward, 0.0)));
		up = glm::vec3(glm::normalize(rotation * glm::vec4(up, 0.0)));
	}
private:
	glm::mat4 projection;
	glm::vec3 pos;
	glm::vec3 forward;
	glm::vec3 up;
};


