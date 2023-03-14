#include "TrashTheCache.h"

#include <chrono>
#include <numeric>
#include <vector>

#include "imgui.h"
#include "imgui_plot.h"

using std::vector;
using namespace std::chrono;

dae::TrashTheCache::TrashTheCache(dae::GameObject* attachedObj) noexcept
	: BaseComponent(attachedObj)
{

}

void dae::TrashTheCache::Update()
{
}

void dae::TrashTheCache::FixedUpdate()
{
}

void dae::TrashTheCache::Render() const
{
}

void dae::TrashTheCache::OnGUI()
{
    ImGui::Begin("Exercise 1");
    if (m_Trash1State == TestState::Done || m_Trash1State == TestState::Empty)
    {
        if (ImGui::Button("Trash the cache"))
        {
            m_Trash1State = TestState::Calculating;
            m_Trash1Thread = std::jthread(TrashV1);
        }

        if (m_Trash1State == TestState::Done)
        {
            ImGui::PlotConfig conf;
            conf.values.xs = m_PlotXData;
            conf.values.ys = m_Trash1Timings;
            conf.values.count = VALUES_COUNT;
            conf.scale.min = 0;
            conf.scale.max = m_Trash1Timings[0];
            conf.scale.type = ImGui::PlotConfig::Scale::Linear;
            conf.tooltip.show = true;
            conf.tooltip.format = "x=%.f, y=%.f ms";
            conf.frame_size = ImVec2(280, 280);
            conf.line_thickness = 1.f;
            conf.v_lines.show = false;
            conf.values.color = ImColor(255, 255, 0);
            ImGui::Plot("plot1", conf);
        }

    }
    else
    {
        ImGui::Text("Calculating...");
    }
    
    ImGui::End();

    ImGui::Begin("Exercise 2");
    if (m_Trash2State == TestState::Done || m_Trash2State == TestState::Empty)
    {
        if (ImGui::Button("Trash the cache with OBJ and OBJ2"))
        {
            m_Trash2State = TestState::Calculating;
            m_Trash2Thread = std::jthread(TrashV2);
        }

        if (m_Trash2State == TestState::Done)
        {
            ImGui::PlotConfig conf;
            conf.values.xs = m_PlotXData;
            conf.values.ys = m_Trash2Timings;
            conf.values.count = VALUES_COUNT;
            conf.scale.min = 0;
            conf.scale.max = m_Trash2Timings[0];
            conf.scale.type = ImGui::PlotConfig::Scale::Linear;
            conf.tooltip.show = true;
            conf.tooltip.format = "x=%.f, y=%.f ms";
            conf.frame_size = ImVec2(280, 280);
            conf.line_thickness = 1.f;
            conf.v_lines.show = false;
            conf.values.color = m_Colors[0];
            ImGui::Plot("plot2", conf);

            ImGui::PlotConfig conf2;
            conf2.values.xs = m_PlotXData;
            conf2.values.ys = m_Trash3Timings;
            conf2.values.count = VALUES_COUNT;
            conf2.scale.min = 0;
            conf2.scale.max = m_Trash3Timings[0];
            conf2.scale.type = ImGui::PlotConfig::Scale::Linear;
            conf2.tooltip.show = true;
            conf2.tooltip.format = "x=%.f, y=%.f ms";
            conf2.frame_size = ImVec2(280, 280);
            conf2.line_thickness = 1.f;
            conf2.v_lines.show = false;
            conf2.values.color = m_Colors[1];
            ImGui::Plot("plot3", conf2);

            ImGui::PlotConfig conf3;
            conf3.values.xs = m_PlotXData;
            conf3.values.ys_list = m_Ex2Timings;
            conf3.values.ys_count = 2;
            conf3.values.count = VALUES_COUNT;
            conf3.scale.min = 0;
            conf3.scale.max = m_Trash2Timings[0] > m_Trash3Timings[0] ? m_Trash2Timings[0] : m_Trash3Timings[0];
            conf3.scale.type = ImGui::PlotConfig::Scale::Linear;
            conf3.tooltip.show = true;
            conf3.tooltip.format = "x=%.f, y=%.f ms";
            conf3.frame_size = ImVec2(280, 280);
            conf3.line_thickness = 1.f;
            conf3.v_lines.show = false;
            conf3.values.colors = m_Colors;
            ImGui::Plot("plot4", conf3);
        }

    }
    else
    {
        ImGui::Text("Calculating...");
    }
    ImGui::End();
}

void dae::TrashTheCache::TrashV1()
{
    int* data = new int[DATA_SIZE]{};
    int stepCounter{};
    for (int stepsize{ 1 }; stepsize <= MAX_STEP_SIZE; stepsize *= 2)
    {
        vector<long long> timings(PASSES);
        for (int pass{ 1 }; pass <= PASSES; ++pass)
        {
	        auto start = high_resolution_clock::now();
            for (int i{}; i < DATA_SIZE; i += stepsize)
                ++data[i];
            timings.emplace_back(duration_cast<nanoseconds>(high_resolution_clock::now() - start).count());
        }
    	m_Trash1Timings[stepCounter] = float(std::accumulate(timings.begin(), timings.end(), 0ll)) / float(timings.size());
        ++stepCounter;
    }

    delete[] data;

    m_Trash1State = TestState::Done;
}

void dae::TrashTheCache::TrashV2()
{
    OBJ* data = new OBJ[DATA_SIZE]{};
    int stepCounter{};
    for (int stepsize{ 1 }; stepsize <= MAX_STEP_SIZE; stepsize *= 2)
    {
        vector<long long> timings(PASSES);
        for (int pass{ 1 }; pass <= PASSES; ++pass)
        {
            auto start = high_resolution_clock::now();
            for (int i{}; i < DATA_SIZE; i += stepsize)
                ++data[i].id;
            timings.emplace_back(duration_cast<nanoseconds>(high_resolution_clock::now() - start).count());
        }
        m_Trash2Timings[stepCounter] = float(std::accumulate(timings.begin(), timings.end(), 0ll)) / float(timings.size());
        ++stepCounter;
    }

    delete[] data;

    OBJ2* data2 = new OBJ2[DATA_SIZE]{};
    stepCounter = 0;
    for (int stepsize{ 1 }; stepsize <= MAX_STEP_SIZE; stepsize *= 2)
    {
        vector<long long> timings(PASSES);
        for (int pass{ 1 }; pass <= PASSES; ++pass)
        {
            auto start = high_resolution_clock::now();
            for (int i{}; i < DATA_SIZE; i += stepsize)
                ++data2[i].id;
            timings.emplace_back(duration_cast<nanoseconds>(high_resolution_clock::now() - start).count());
        }
        m_Trash3Timings[stepCounter] = float(std::accumulate(timings.begin(), timings.end(), 0ll)) / float(timings.size());
        ++stepCounter;
    }

    delete[] data2;

    m_Trash2State = TestState::Done;
}
