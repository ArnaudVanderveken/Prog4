#pragma once
#include <string>

struct Mix_Chunk;

class AudioClip final
{
public:
	AudioClip(const std::string& filepath);
	~AudioClip();
	AudioClip(const AudioClip& other) = delete;
	AudioClip& operator=(const AudioClip& other) = delete;
	AudioClip(AudioClip&& other) noexcept = delete;
	AudioClip& operator=(AudioClip&& other) noexcept = delete;

	void Play(bool looping);
	void Stop() const;
	void SetVolume(int volume) const;
	int GetVolume() const;

private:
	std::string m_FilePath;
	Mix_Chunk* m_pChunk;
	int m_Channel{};
};

