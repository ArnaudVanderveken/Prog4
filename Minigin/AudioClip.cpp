#include "AudioClip.h"

#include <iostream>

#include "SDL_mixer.h"

using std::cerr, std::endl;

AudioClip::AudioClip(const std::string& filepath)
	: m_FilePath{ filepath }
{
	m_pChunk = Mix_LoadWAV(m_FilePath.c_str());
	if (m_pChunk == nullptr)
	{
		cerr << "Unable to load file: " << Mix_GetError() << endl;
	}
}

AudioClip::~AudioClip()
{
	if (m_pChunk)
		Mix_FreeChunk(m_pChunk);
}

void AudioClip::Play() const
{
	if (m_pChunk)
		Mix_PlayChannel(-1, m_pChunk, 0);
}

void AudioClip::SetVolume(int volume) const
{
	if (m_pChunk)
		Mix_VolumeChunk(m_pChunk, volume);
}

int AudioClip::GetVolume() const
{
	// If less than 0 then chunk volume will not be set
	if (m_pChunk)
		return Mix_VolumeChunk(m_pChunk, -1);
	return 0;
}