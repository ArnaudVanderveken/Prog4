#pragma once
#include <glm/glm.hpp>

namespace dae
{
	struct Transform final
	{
		Transform() = default;
		Transform(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scale);

		Transform operator+(const Transform& other) const;
		Transform operator-(const Transform& other) const;

		glm::vec3 position{};
		glm::vec3 rotation{};
		glm::vec3 scale{};
	};
}
