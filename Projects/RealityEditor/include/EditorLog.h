// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include <imgui/imgui.h>
#include <string_view>

#include "EditorWindow.h"
#include "Core/Tools/Logger.h"

namespace Reality::Editor {
    class EditorLog : public EditorWindow {
    public:
        void AddLog(std::string_view msg);
        void Clear();
        void Draw();

    private:
        ImGuiTextBuffer m_Buffer;
        ImGuiTextFilter m_Filter;
        ImVector<int> m_LineOffsets;
        bool m_ScrollToBottom{ true };
    };
}

inline void Reality::Editor::EditorLog::AddLog(std::string_view msg) {
    auto oldSize{ m_Buffer.size() };
    m_Buffer.append(msg.data());
    for (auto newSize{ m_Buffer.size() }; oldSize < newSize; ++oldSize) {
        if (m_Buffer[oldSize] == '\n') {
            m_LineOffsets.push_back(oldSize);
        }
    }
    m_ScrollToBottom = true;
}

inline void Reality::Editor::EditorLog::Clear() {
    m_Buffer.clear();
    m_LineOffsets.clear();
}

inline void Reality::Editor::EditorLog::Draw() {
    ImGui::Begin("Console");
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

    if (ImGui::Button("Clear")) {
        Clear();
    }

    ImGui::SameLine();
    const auto copy{ ImGui::Button("Copy") };
    ImGui::SameLine();
    m_Filter.Draw("Filter", -100.f);
    ImGui::Separator();
    ImGui::BeginChild("scrolling");
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.f, 1.f));

    if (copy) {
        ImGui::LogToClipboard();
    }

    if (m_Filter.IsActive()) {
        const auto bufferBegin{ m_Buffer.begin() };
        auto line{ bufferBegin };

        for (auto lineNb{ 0 }; line; ++lineNb) {
            auto lineEnd{ (lineNb < m_LineOffsets.Size) ? bufferBegin + m_LineOffsets[lineNb] : nullptr };
            if (m_Filter.PassFilter(line, lineEnd)) {
                ImGui::TextUnformatted(line, lineEnd);
            }
            line = lineEnd && lineEnd[1] ? lineEnd + 1 : nullptr;
        }
    }
    else {
        ImGui::TextUnformatted(m_Buffer.begin());
    }

    if (m_ScrollToBottom) {
        ImGui::SetScrollHere(1.f);
    }
    m_ScrollToBottom = false;
    ImGui::PopStyleVar();
    ImGui::EndChild();
    ImGui::End();
}