#include "LevelComponent.h"

#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>

#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"

using std::ifstream, std::cerr, std::endl, std::stringstream, std::string;
using namespace dae;

dae::LevelComponent::LevelComponent(const std::string& filename) noexcept
{
	const std::regex txtRegex(R"(\.\./Data/[a-zA-Z0-9]+\.txt)");
	const std::regex binRegex(R"(\.\./Data/[a-zA-Z0-9]+\.bin)");
	
	if (std::regex_match(filename, binRegex))
		LoadLevelFromFileBin(filename);
	else if (std::regex_match(filename, txtRegex))
		LoadLevelFromFile(filename);
	else
		cerr << "[WARNING] Invalid file extension in file " << filename << " in " << __FILE__ << ":" << __LINE__ << "." << endl;

	m_Textures[0] = ResourceManager::GetInstance().LoadTexture("Level/wall.png");
	m_Textures[1] = ResourceManager::GetInstance().LoadTexture("Level/void.png");
	m_Textures[2] = ResourceManager::GetInstance().LoadTexture("Level/path.png");
	m_Textures[3] = ResourceManager::GetInstance().LoadTexture("Level/teleport.png");

}

const glm::vec2& LevelComponent::GetPlayer1Start() const
{
	return m_Player1Start;
}

const glm::vec2& LevelComponent::GetPlayer2Start() const
{
	return m_Player2Start;
}

const std::vector<glm::vec2>& LevelComponent::GetNormalEnemiesStarts() const
{
	return m_NormalEnemyStarts;
}

const std::vector<glm::vec2>& LevelComponent::GetRecognizersStarts() const
{
	return m_RecognizerEnemyStarts;
}

void LevelComponent::QueryLevelForMovement(const glm::vec2& xyPos, glm::vec2& movement) const
{
	// Prioritize main movement direction.
	if (abs(movement.x) >= abs(movement.y))
	{
		QueryLevelForMovementX(xyPos, movement.x);
		QueryLevelForMovementY(xyPos, movement.y);
	}
	else
	{
		QueryLevelForMovementY(xyPos, movement.y);
		QueryLevelForMovementX(xyPos, movement.x);
	}
}

void LevelComponent::Update()
{
}

void LevelComponent::Render() const
{
	for (size_t i{}; i < LEVEL_ROWS; ++i)
	{
		for (size_t j{}; j < LEVEL_COLS; ++j)
		{
			const size_t index = i * LEVEL_COLS + j;
			const float x = GetOwner()->GetWorldTransform().position.x + static_cast<float>(j) * SPRITE_SIZE;
			const  float y = GetOwner()->GetWorldTransform().position.y + static_cast<float>(i) * SPRITE_SIZE;
			Renderer::GetInstance().RenderTexture(*m_Textures[m_LevelLayout[index]], x, y);
		}
	}
}

void dae::LevelComponent::LoadLevelFromFile(const std::string& filename)
{
	ifstream file(filename);
	if(file.is_open())
	{
		for (size_t i{}; i < LEVEL_TOTAL_TILES; ++i)
		{
			m_LevelLayout[i] = static_cast<uint8_t>(file.get() - '0');
		}
		file.get(); //\n

		stringstream lineStream;
		string line;
		string token;

		// P1 start pos
		std::getline(file, line);
		lineStream << line;
		lineStream >> token;
		m_Player1Start.x = std::stof(token);
		lineStream >> token;
		m_Player1Start.y = std::stof(token);
		lineStream.str("");
		lineStream.clear();

		// P2 start pos
		std::getline(file, line);
		lineStream << line;
		lineStream >> token;
		m_Player2Start.x = std::stof(token);
		lineStream >> token;
		m_Player2Start.y = std::stof(token);
		lineStream.str("");
		lineStream.clear();

		// Enemies count + start pos
		std::getline(file, line);
		lineStream << line;
		lineStream >> token;
		int enemyCount = std::stoi(token);
		m_NormalEnemyStarts.resize(enemyCount);
		for (int i{}; i < enemyCount; ++i)
		{
			lineStream >> token;
			m_NormalEnemyStarts[i].x = std::stof(token);
			lineStream >> token;
			m_NormalEnemyStarts[i].y = std::stof(token);
		}
		lineStream.str("");
		lineStream.clear();

		// Recognizer count + start pos
		std::getline(file, line);
		lineStream << line;
		lineStream >> token;
		enemyCount = std::stoi(token);
		m_RecognizerEnemyStarts.resize(enemyCount);
		for (int i{}; i < enemyCount; ++i)
		{
			lineStream >> token;
			m_RecognizerEnemyStarts[i].x = std::stof(token);
			lineStream >> token;
			m_RecognizerEnemyStarts[i].y = std::stof(token);
		}

		file.close();
	}
	else
	{
		cerr << "[ERROR] Unable to open file " << filename << " in " << __FILE__ << ":" << __LINE__ << "." << endl;
	}
}

void LevelComponent::LoadLevelFromFileBin(const std::string& filename)
{
	ifstream file(filename, std::ios::binary);
	if (file.is_open())
	{
		// Level Layout
		constexpr size_t BIN_BYTES{ LEVEL_TOTAL_TILES / BIN_TILES_PER_BYTE };
		uint8_t data[BIN_BYTES];
		file.read(reinterpret_cast<char*>(&data), BIN_BYTES);

		constexpr uint8_t MASK{ 0b00000011 };
		for (size_t i{}; i < BIN_BYTES; ++i)
		{
			auto var = data[i];
			m_LevelLayout[4 * i + 3] = var & MASK;
			var = var >> 2;
			m_LevelLayout[4 * i + 2] = var & MASK;
			var = var >> 2;
			m_LevelLayout[4 * i + 1] = var & MASK;
			var = var >> 2;
			m_LevelLayout[4 * i] = var & MASK;
		}

		// Player 1 start pos
		uint16_t p1Start[2];
		file.read(reinterpret_cast<char*>(&p1Start), sizeof p1Start);
		m_Player1Start.x = static_cast<float>(p1Start[0]);
		m_Player1Start.y = static_cast<float>(p1Start[1]);

		// Player 2 start pos
		uint16_t p2Start[2];
		file.read(reinterpret_cast<char*>(&p2Start), sizeof p2Start);
		m_Player2Start.x = static_cast<float>(p2Start[0]);
		m_Player2Start.y = static_cast<float>(p2Start[1]);

		// Normal enemies count and start pos
		uint8_t normalEnemiesCount;
		file.read(reinterpret_cast<char*>(&normalEnemiesCount), sizeof normalEnemiesCount);
		m_NormalEnemyStarts.resize(normalEnemiesCount);
		for (uint8_t i{}; i < normalEnemiesCount; ++i)
		{
			uint16_t enemyStart[2];
			file.read(reinterpret_cast<char*>(&enemyStart), sizeof enemyStart);
			m_NormalEnemyStarts[i].x = static_cast<float>(enemyStart[0]);
			m_NormalEnemyStarts[i].y = static_cast<float>(enemyStart[1]);
		}

		// Recognizer count and start pos
		uint8_t recognizerEnemiesCount;
		file.read(reinterpret_cast<char*>(&recognizerEnemiesCount), sizeof recognizerEnemiesCount);
		m_RecognizerEnemyStarts.resize(recognizerEnemiesCount);
		for (uint8_t i{}; i < recognizerEnemiesCount; ++i)
		{
			uint16_t enemyStart[2];
			file.read(reinterpret_cast<char*>(&enemyStart), sizeof enemyStart);
			m_RecognizerEnemyStarts[i].x = static_cast<float>(enemyStart[0]);
			m_RecognizerEnemyStarts[i].y = static_cast<float>(enemyStart[1]);
		}
	}
}

bool LevelComponent::IsWalkableAtPixel(const glm::vec2& pixelPos) const
{
	const auto relativePos = pixelPos - glm::vec2{ GetOwner()->GetWorldTransform().position.x, GetOwner()->GetWorldTransform().position.y };
	const auto tileX = static_cast<uint8_t>(std::round(relativePos.x)) / SPRITE_SIZE;
	const auto tileY = static_cast<uint8_t>(std::round(relativePos.y)) / SPRITE_SIZE;
	return m_LevelLayout[tileY * LEVEL_COLS + tileX]; // only tiles of type 0 are non walkable.
}

void LevelComponent::QueryLevelForMovementX(const glm::vec2& xyPos, float& dx) const
{
	if (IsWalkableAtPixel({ xyPos.x + dx, xyPos.y }))
		return;

	const float tileOffset{ xyPos.x - static_cast<float>(SPRITE_SIZE * (static_cast<uint16_t>(xyPos.x) % SPRITE_SIZE)) };
	if (dx > 0.0f)
		dx = SPRITE_SIZE - tileOffset; // distance to the right border of the tile
	else
		dx = SPRITE_SIZE; // distance to the left border of the tile
}

void LevelComponent::QueryLevelForMovementY(const glm::vec2& xyPos, float& dy) const
{
	if (IsWalkableAtPixel({ xyPos.y + dy, xyPos.y }))
		return;

	const float tileOffset{ xyPos.y - static_cast<float>(SPRITE_SIZE * (static_cast<uint16_t>(xyPos.y) % SPRITE_SIZE)) };
	if (dy > 0.0f)
		dy = SPRITE_SIZE - tileOffset; // distance to the right border of the tile
	else
		dy = SPRITE_SIZE; // distance to the left border of the tile
}
