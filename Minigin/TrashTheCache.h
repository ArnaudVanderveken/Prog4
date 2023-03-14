#pragma once
#include "BaseComponent.h"

#include <thread>

#include "imgui.h"

namespace dae
{
	struct Tr
	{
		float matrix[16]
		{
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		};
	};

	struct OBJ
	{
		Tr t;
		int id{};
	};

	struct OBJ2
	{
		Tr* t{};
		int id{};
	};

	enum class TestState
	{
		Empty, Calculating, Done
	};

	class TrashTheCache : public dae::BaseComponent
	{
	public:
		TrashTheCache(dae::GameObject* attachedObj) noexcept;
		~TrashTheCache() override = default;

		TrashTheCache(const TrashTheCache& other) = delete;
		TrashTheCache& operator=(const TrashTheCache& other) noexcept = delete;
		TrashTheCache(TrashTheCache&& other) = delete;
		TrashTheCache& operator=(TrashTheCache&& other) noexcept = delete;

		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		void OnGUI() override;
		
	private:
		/* DATA MEMBERS */
		inline static TestState m_Trash1State{};
		inline static TestState m_Trash2State{};

		std::jthread m_Trash1Thread;
		std::jthread m_Trash2Thread;

		static constexpr int DATA_SIZE{ 1000000 };
		static constexpr int PASSES{ 10 };
		static constexpr int MAX_STEP_SIZE{ 1024 };

		static constexpr int VALUES_COUNT{ 11 };
		inline static constexpr float m_PlotXData[VALUES_COUNT] { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024 };
		inline static float m_Trash1Timings[VALUES_COUNT]{};
		inline static float m_Trash2Timings[VALUES_COUNT]{};
		inline static float m_Trash3Timings[VALUES_COUNT]{};
		inline static const float* m_Ex2Timings[]{ m_Trash2Timings, m_Trash3Timings };
		inline static ImU32 m_Colors[2] = { ImColor(255, 255, 0), ImColor(0, 255, 255) };

		/* PRIVATE METHODS */
		static void TrashV1();
		static void TrashV2();

	};
}


