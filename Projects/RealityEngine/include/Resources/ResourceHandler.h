// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include <cereal/archives/json.hpp>
#include <unordered_map>
#include <fstream>
#include <future>

#include "ResourceSerialize.h"
#include "ResourceConverter.h"

namespace reality {
	template <class Resource, class Settings, class Properties, class TmpResource>
	class ResourceHandler final {
	public:
		explicit ResourceHandler(std::string_view path);

		void Update();
		const Resource& Load(std::string_view key, const Settings& settings, const Properties& properties = {});
		bool Remove(std::string_view key);
		const Resource* Get(std::string_view key) const;
		std::string_view GetPath() const;
		const std::unordered_map<std::string, Resource>& GetResources() const;

	private:
		std::string m_Path;
		std::unordered_map<std::string, Resource> m_Resources;
		std::unordered_map<std::string, std::pair<Properties, std::future<TmpResource>>> m_TmpResources;
	};
}

template <class Resource, class Settings, class Properties, class TmpResource>
reality::ResourceHandler<Resource, Settings, Properties, TmpResource>::ResourceHandler(std::string_view path) :
	m_Path{ path }
{
	std::fstream file{ m_Path };
	if (file.peek() == std::fstream::traits_type::eof()) {
		file.seekg(std::ios_base::beg);
		file << "{}";
		return;
	}

	std::istream fileInputBuffer{ file.rdbuf() };
	cereal::JSONInputArchive inArchive{ fileInputBuffer };

	Settings settings;
	Properties properties;
	while (const auto key{ inArchive.getNodeName() }) {
		inArchive.startNode();
		inArchive(settings, properties);
		m_TmpResources.emplace(key, std::make_pair(properties, std::future<TmpResource>{})).first->second.second =
			std::async(std::launch::async, [settings] { return TmpResource{ settings }; });
		m_Resources.emplace(key, Resource{});
		inArchive.finishNode();
	}
}

template <class Resource, class Settings, class Properties, class TmpResource>
void reality::ResourceHandler<Resource, Settings, Properties, TmpResource>::Update() {
	for (auto it{ m_TmpResources.begin() }; it != m_TmpResources.cend(); ) {
		auto& [settings, resource] { it->second };
		if (resource.wait_for(std::chrono::seconds{ 0 }) == std::future_status::ready) {
			m_Resources.at(it->first) = loader::Convert<Resource>(settings, resource.get());
			it = m_TmpResources.erase(it);
		}
		else {
			++it;
		}
	}
}

template <class Resource, class Settings, class Properties, class TmpResource>
const Resource& reality::ResourceHandler<Resource, Settings, Properties, TmpResource>::Load(std::string_view key,
	const Settings& settings, const Properties& properties)
{
	if (const auto it{ m_Resources.find(key.data()) }; it != m_Resources.cend()) {
		return it->second;
	}

	std::fstream file{ m_Path };
	std::istream fileInputBuffer{ file.rdbuf() };
	cereal::JSONInputArchive inArchive{ fileInputBuffer };
	file = std::fstream{ m_Path, std::fstream::out | std::fstream::trunc };
	cereal::JSONOutputArchive outArchive{ file };

	auto WriteResourceToArchive{ [](auto& archive, auto key, auto& settings, auto& properties) {
		archive.setNextName(key);
		archive.startNode();
		archive(CEREAL_NVP(settings), CEREAL_NVP(properties));
		archive.finishNode();
	} };

	Settings oldSettings;
	Properties oldProperties;
	while (const auto oldKey{ inArchive.getNodeName() }) {
		inArchive.startNode();
		inArchive(oldSettings, oldProperties);
		WriteResourceToArchive(outArchive, oldKey, oldSettings, oldProperties);
		inArchive.finishNode();
	}
	WriteResourceToArchive(outArchive, key.data(), settings, properties);

	m_TmpResources.emplace(key, std::make_pair(properties, std::future<TmpResource>{})).first->second.second =
		std::async(std::launch::async, [settings] { return TmpResource{ settings }; });
	return m_Resources.emplace(key, Resource{}).first->second;
}

template<class Resource, class Settings, class Properties, class TmpResource>
bool reality::ResourceHandler<Resource, Settings, Properties, TmpResource>::Remove(std::string_view key) {
	if (const auto it{ m_Resources.find(key.data()) }; it == m_Resources.cend()) {
		return false;
	}

	std::fstream file{ m_Path };
	std::istream fileInputBuffer{ file.rdbuf() };
	cereal::JSONInputArchive inArchive{ fileInputBuffer };
	file = std::fstream{ m_Path, std::fstream::out | std::fstream::trunc };
	cereal::JSONOutputArchive outArchive{ file };

	Settings settings;
	Properties properties;
	while (const auto oldKey{ inArchive.getNodeName() }) {
		inArchive.startNode();
		inArchive(settings, properties);
		if (oldKey != key) {
			outArchive.setNextName(oldKey);
			outArchive.startNode();
			outArchive(CEREAL_NVP(settings), CEREAL_NVP(properties));
			outArchive.finishNode();
		}
		inArchive.finishNode();
	}
	m_Resources.erase(key.data());
	return true;
}

template <class Resource, class Settings, class Properties, class TmpResource>
const Resource* reality::ResourceHandler<Resource, Settings, Properties, TmpResource>::Get(std::string_view key) const {
	if (const auto it{ m_Resources.find(key.data()) }; it != m_Resources.cend()) {
		return &it->second;
	}
	return nullptr;
}

template<class Resource, class Settings, class Properties, class TmpResource>
std::string_view reality::ResourceHandler<Resource, Settings, Properties, TmpResource>::GetPath() const {
	return m_Path;
}

template <class Resource, class Settings, class Properties, class TmpResource>
const std::unordered_map<std::string, Resource>& 
reality::ResourceHandler<Resource, Settings, Properties, TmpResource>::GetResources() const {
	return m_Resources;
}