#include "LevelComponent.h"
#include <fstream>
#include <iostream>
#include <sstream>

#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"

using std::ifstream, std::cerr, std::endl, std::stringstream, std::string;
using namespace dae;

dae::LevelComponent::LevelComponent(const std::string& filename) noexcept
{
	LoadLevelFromFile(filename);

	m_Textures[0] = ResourceManager::GetInstance().LoadTexture("Level/wall.png");
	m_Textures[1] = ResourceManager::GetInstance().LoadTexture("Level/void.png");
	m_Textures[2] = ResourceManager::GetInstance().LoadTexture("Level/path.png");
	m_Textures[3] = ResourceManager::GetInstance().LoadTexture("Level/teleport.png");

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

		// P2 start pos
		std::getline(file, line);
		lineStream << line;
		lineStream >> token;
		m_Player2Start.x = std::stof(token);
		lineStream >> token;
		m_Player2Start.y = std::stof(token);

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
		cerr << "[ERROR] Unable to open file " << filename << " in " << __FILE__ << ":" << __LINE__ << endl;
	}
}
