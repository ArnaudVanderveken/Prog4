#include "SoundSystem.h"

#include <mutex>
#include <queue>
#include <thread>

#include "AudioClip.h"
#include "SDL_mixer.h"

class SoundSystem::SoundSystemImpl
{
public:
	SoundSystemImpl();
	virtual ~SoundSystemImpl();
	SoundSystemImpl(const SoundSystemImpl& other) = delete;
	SoundSystemImpl& operator=(const SoundSystemImpl& other) = delete;
	SoundSystemImpl(SoundSystemImpl&& other) noexcept = delete;
	SoundSystemImpl& operator=(SoundSystemImpl&& other) noexcept = delete;

	void Play(int clipId, bool looping);
	void Stop(int clipId) const;
	void Mute();
	int AddClip(const std::string& clipFilePath);

	void RunEventQueue();

private:
	std::vector<std::pair<std::string, std::unique_ptr<AudioClip>>> m_pClips;
	std::queue<std::pair<AudioClip*, bool>> m_SoundsToPlay;

	std::jthread m_Thread;
	std::mutex m_Mutex;
	std::condition_variable m_CV;
	std::atomic<bool> m_StopThread;

	int m_Volume{ 64 };
};

SoundSystem::SoundSystemImpl::SoundSystemImpl()
{
	int result = Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 512);
	if (result < 0)
	{
		cerr << "Unable to open audio: " << SDL_GetError() << endl;
		return;
	}

	result = Mix_AllocateChannels(16);
	if (result < 0)
	{
		cerr << "Unable to allocate mixing channels: " << SDL_GetError() << endl;
		return;
	}

	m_Thread = std::jthread(&SoundSystemImpl::RunEventQueue, this);
	Mix_MasterVolume(m_Volume);
}

SoundSystem::SoundSystemImpl::~SoundSystemImpl()
{
	Mix_CloseAudio();
	m_StopThread.store(true);
	m_CV.notify_all();
}

void SoundSystem::SoundSystemImpl::Play(int clipId, bool looping)
{
	std::unique_lock lock(m_Mutex);
	m_SoundsToPlay.emplace(m_pClips[clipId].second.get(), looping);
	lock.unlock();
	m_CV.notify_all();
}

void SoundSystem::SoundSystemImpl::Stop(int clipId) const
{
	m_pClips[clipId].second->Stop();
}

void SoundSystem::SoundSystemImpl::Mute()
{
	m_Volume = Mix_MasterVolume(m_Volume);
}

int SoundSystem::SoundSystemImpl::AddClip(const std::string& clipFilePath)
{
	for (size_t i{}; i < m_pClips.size(); ++i)
	{
		if (m_pClips[i].first == clipFilePath)
			return static_cast<int>(i);
	}

	m_pClips.emplace_back(clipFilePath, std::make_unique<AudioClip>(clipFilePath));
	return static_cast<int>(m_pClips.size()) - 1;
}

void SoundSystem::SoundSystemImpl::RunEventQueue()
{
	while (true)
	{
		// Wait for a sound to be played or for the thread to be stopped
		std::unique_lock lock(m_Mutex);
		m_CV.wait(lock, [&]() { return !m_SoundsToPlay.empty() || m_StopThread.load(); });

		// Check if thread needs to be stopped
		if (m_StopThread.load())
			break;

		// Get sound to play
		const auto clip = m_SoundsToPlay.front();

		// Remove the sound from the queue
		m_SoundsToPlay.pop();

		// Release lock
		lock.unlock();

		//Play sound
		clip.first->Play(clip.second);
	}
}


SoundSystem::SoundSystem()
	: m_pSoundSystem{ new SoundSystemImpl() }
{
}

SoundSystem::~SoundSystem()
{
	delete m_pSoundSystem;
}

void SoundSystem::Play(int clipId, bool looping)
{
	m_pSoundSystem->Play(clipId, looping);
}

void SoundSystem::Stop(int clipId)
{
	m_pSoundSystem->Stop(clipId);
}

void SoundSystem::Mute()
{
	m_pSoundSystem->Mute();
}

int SoundSystem::AddClip(const std::string& clipFilePath)
{
	return m_pSoundSystem->AddClip(clipFilePath);
}

void Logged_SoundSystem::Play(int clipId, bool looping)
{
	cout << "Playing Sound: \tId: " << clipId << endl;
	SoundSystem::Play(clipId, looping);
}

void Logged_SoundSystem::Stop(int clipId)
{
	cout << "Stopping Sound: \tId: " << clipId << endl;
	SoundSystem::Stop(clipId);
}

void Logged_SoundSystem::Mute()
{
	cout << "Toggling mute." << endl;
	SoundSystem::Mute();
}

int Logged_SoundSystem::AddClip(const std::string& clipFilePath)
{
	cout << "Loading Clip..." << endl;
	return SoundSystem::AddClip(clipFilePath);
}
