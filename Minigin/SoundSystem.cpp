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
	~SoundSystemImpl();
	SoundSystemImpl(const SoundSystemImpl& other) = delete;
	SoundSystemImpl& operator=(const SoundSystemImpl& other) = delete;
	SoundSystemImpl(SoundSystemImpl&& other) noexcept = delete;
	SoundSystemImpl& operator=(SoundSystemImpl&& other) noexcept = delete;

	void Play(int clipId);
	int AddClip(const std::string& clipFilePath);

	void RunEventQueue();

private:
	std::vector<std::pair<std::string, AudioClip*>> m_pClips;
	std::queue<AudioClip*> m_SoundsToPlay;

	std::jthread m_Thread;
	std::mutex m_Mutex;
	std::condition_variable m_CV;
	std::atomic<bool> m_StopThread;
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
}

SoundSystem::SoundSystemImpl::~SoundSystemImpl()
{
	Mix_CloseAudio();
	m_StopThread.store(true);
	m_CV.notify_all();

	for (const auto clip : m_pClips)
		delete clip.second;
}

void SoundSystem::SoundSystemImpl::Play(int clipId)
{
	std::lock_guard lock(m_Mutex);
	m_SoundsToPlay.emplace(m_pClips[clipId].second);
	m_CV.notify_all();
}

int SoundSystem::SoundSystemImpl::AddClip(const std::string& clipFilePath)
{
	for (int i{}; i < m_pClips.size(); ++i)
	{
		if (m_pClips[i].first == clipFilePath)
			return i;
	}

	m_pClips.emplace_back(std::pair{ clipFilePath, new AudioClip{ clipFilePath } });
	return int(m_pClips.size()) - 1;
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

		// Play the sound
		const auto clip = m_SoundsToPlay.front();
		clip->Play();

		// Remove the sound from the queue
		m_SoundsToPlay.pop();
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

void SoundSystem::Play(int clipId)
{
	m_pSoundSystem->Play(clipId);
}

int SoundSystem::AddClip(const std::string& clipFilePath)
{
	return m_pSoundSystem->AddClip(clipFilePath);
}

void Logged_SoundSystem::Play(int clipId)
{
	cout << "Playing Sound: \tId: " << clipId << endl;
	m_pSoundSystem->Play(clipId);
}

int Logged_SoundSystem::AddClip(const std::string& clipFilePath)
{
	cout << "Loading Clip..." << endl;
	return m_pSoundSystem->AddClip(clipFilePath);
}