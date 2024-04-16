#pragma once

#include <glm/glm.hpp>

namespace Fountainhead {

	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);

		void SetProjection(float left, float right, float bottom, float top);

		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }

		float GetRotation() const { return m_Rotation; }
		void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }

		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
	private:
		void RecalculateViewMatrix();
	private:
		glm::mat4 m_ProjectionMatrix;//投影矩阵
		glm::mat4 m_ViewMatrix;//视图矩阵，相机实际变换矩阵的逆矩阵
		glm::mat4 m_ViewProjectionMatrix;//暂存视图矩阵

		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };//追踪位置
		float m_Rotation = 0.0f;//追踪旋转
	};

}