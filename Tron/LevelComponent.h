#pragma once

#include <array>
#include <memory>
#include <string>
#include <vector>

#include <glm/glm.hpp>
#include "BaseComponent.h"

namespace dae
{
	class Texture2D;
	
	class LevelComponent : public dae::BaseComponent
	{
	public:
		LevelComponent(const std::string& filename) noexcept;
		~LevelComponent() override = default;

		LevelComponent(const LevelComponent& other) noexcept = delete;
		LevelComponent(LevelComponent&& other) noexcept = delete;
		LevelComponent& operator=(const LevelComponent& other) noexcept = delete;
		LevelComponent& operator=(LevelComponent&& other) noexcept = delete;

		[[nodiscard]] const glm::vec2& GetPlayer1Start() const;
		[[nodiscard]] const glm::vec2& GetPlayer2Start() const;
		[[nodiscard]] const std::vector<glm::vec2>& GetNormalEnemiesStarts() const;
		[[nodiscard]] const std::vector<glm::vec2>& GetRecognizersStarts() const;

		void QueryLevelForMovement(const glm::vec2& xyPos, glm::vec2& movement) const;

	protected:
		void Update() override;
		void Render() const override;

	private:
		/* DATA MEMBERS */

		static constexpr uint8_t TEXTURE_COUNT{ 4 };
		static constexpr uint8_t SPRITE_SIZE{ 8 };
		static constexpr uint8_t LEVEL_COLS{ 58 };
		static constexpr uint8_t LEVEL_ROWS{ 54 };
		static constexpr uint8_t BIN_TILES_PER_BYTE{ 4 };
		static constexpr size_t LEVEL_TOTAL_TILES{ static_cast<size_t>(LEVEL_COLS) * LEVEL_ROWS };

		std::array<uint8_t, LEVEL_TOTAL_TILES> m_LevelLayout{};
		glm::vec2 m_Player1Start{};
		glm::vec2 m_Player2Start{};
		std::vector<glm::vec2> m_NormalEnemyStarts;
		std::vector<glm::vec2> m_RecognizerEnemyStarts;
		std::array<std::shared_ptr<Texture2D>, TEXTURE_COUNT> m_Textures{};

		/* PRIVATE METHODS */

		void LoadLevelFromFile(const std::string& filename);
		void LoadLevelFromFileBin(const std::string& filename);

		[[nodiscard]] bool IsWalkableAtPixel(const glm::vec2& pixelPos) const;
		void QueryLevelForMovementX(const glm::vec2& xyPos, float& dx) const;
		void QueryLevelForMovementY(const glm::vec2& xyPos, float& dy) const;

	};
}


