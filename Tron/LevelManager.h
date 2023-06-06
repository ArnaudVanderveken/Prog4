#pragma once

class LevelManager final
{
public:
	LevelManager() noexcept = default;
	~LevelManager() = default;

	LevelManager(const LevelManager& other) noexcept = delete;
	LevelManager(LevelManager&& other) noexcept = delete;
	LevelManager& operator=(const LevelManager& other) noexcept = delete;
	LevelManager& operator=(LevelManager&& other) noexcept = delete;

private:
	/* DATA MEMBERS */


	/* PRIVATE METHODS */



};

