#pragma once

#include <string>
#include <iostream>

using std::cout, std::cerr, std::endl;

class AudioClip;

class SoundSystem
{
public:
	SoundSystem();
	virtual ~SoundSystem();

	SoundSystem(const SoundSystem& other) = delete;
	SoundSystem& operator=(const SoundSystem& other) = delete;
	SoundSystem(SoundSystem&& other) noexcept = delete;
	SoundSystem& operator=(SoundSystem&& other) noexcept = delete;

	virtual void Play(int clipId, bool looping = false);
	virtual void Stop(int clipId);
	virtual int AddClip(const std::string& clipFilePath);

protected:
	class SoundSystemImpl;
	SoundSystemImpl* m_pSoundSystem;

};

class NULL_SoundSystem final : public SoundSystem
{
public:
	NULL_SoundSystem() = default;
	~NULL_SoundSystem() override = default;

	NULL_SoundSystem(const NULL_SoundSystem& other) = delete;
	NULL_SoundSystem& operator=(const NULL_SoundSystem& other) = delete;
	NULL_SoundSystem(NULL_SoundSystem&& other) noexcept = delete;
	NULL_SoundSystem& operator=(NULL_SoundSystem&& other) noexcept = delete;


	void Play(int, bool = false) override {}
	void Stop(int) override {}
	int AddClip(const std::string&) override { return 0; }

};

class Logged_SoundSystem final : public SoundSystem
{
public:
	Logged_SoundSystem() = default;
	~Logged_SoundSystem() override = default;

	Logged_SoundSystem(const Logged_SoundSystem& other) = delete;
	Logged_SoundSystem& operator=(const Logged_SoundSystem& other) = delete;
	Logged_SoundSystem(Logged_SoundSystem&& other) noexcept = delete;
	Logged_SoundSystem& operator=(Logged_SoundSystem&& other) noexcept = delete;

	void Play(int clipId, bool looping = false) override;
	void Stop(int clipId) override;
	int AddClip(const std::string& clipFilePath) override;
};


