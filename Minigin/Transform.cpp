#include "Transform.h"

dae::Transform::Transform(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scale)
	: position(pos)
	, rotation(rot)
	, scale(scale)
{
}

dae::Transform dae::Transform::operator+(const Transform& other) const
{
	Transform t;
	t.position = position + other.position;
	t.rotation = position + other.position;
	t.scale = glm::vec3{ scale.x * other.scale.x, scale.y * other.scale.y, scale.z * other.scale.z };

	return t;
}

dae::Transform dae::Transform::operator-(const Transform& other) const
{
	Transform t;
	t.position = position - other.position;
	t.rotation = position - other.position;
	t.scale = glm::vec3{ scale.x / other.scale.x, scale.y / other.scale.y, scale.z / other.scale.z };

	return t;
}