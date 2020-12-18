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
	class ResourceManager final {
	public:
		explicit ResourceManager(const char* path);

		void Update();
		const Resource& Load(const char* key, const Settings& settings, const Properties& properties = {});
		const Resource* Get(const char* key) const;

	private:
		std::fstream m_File;
		std::unique_ptr<cereal::JSONOutputArchive> m_Archive;
		std::unordered_map<std::string, Resource> m_Resources;
		std::unordered_map<std::string, std::pair<Properties, std::future<TmpResource>>> m_TmpResources;
	};
}

template <class Resource, class Settings, class Properties, class TmpResource>
reality::ResourceManager<Resource, Settings, Properties, TmpResource>::ResourceManager(const char* path) :
	m_File{ path }
{
	// If the file exist but is empty, cereal cannot open the file
	if (m_File.peek() == std::fstream::traits_type::eof()) {
		return;
	}

	std::istream fileInputBuffer{ m_File.rdbuf() };
	cereal::JSONInputArchive archive{ fileInputBuffer };

	m_File = { path, std::fstream::out | std::fstream::trunc };
	m_Archive = std::make_unique<cereal::JSONOutputArchive>(m_File);

	Settings settings;
	Properties properties;
	while (const auto key{ archive.getNodeName() }) {
		archive.startNode();
		archive(settings, properties);
		Load(key, settings, properties);
		archive.finishNode();
	}
}

template <class Resource, class Settings, class Properties, class TmpResource>
const Resource& reality::ResourceManager<Resource, Settings, Properties, TmpResource>::Load(const char* key,
	const Settings& settings, const Properties& properties)
{
	if (const auto it{ m_Resources.find(key) }; it != m_Resources.cend()) {
		return it->second;
	}

	m_Archive->setNextName(key);
	m_Archive->startNode();
	m_Archive->operator()(CEREAL_NVP(settings), CEREAL_NVP(properties));
	m_Archive->finishNode();

	m_TmpResources.emplace(key, std::make_pair(properties, std::future<TmpResource>{})).first->second.second =
		std::async(std::launch::async, [settings] { return TmpResource{ settings }; });
	return m_Resources.emplace(key, Resource{}).first->second;
}

template <class Resource, class Settings, class Properties, class TmpResource>
const Resource* reality::ResourceManager<Resource, Settings, Properties, TmpResource>::Get(const char* key) const {
	if (const auto it{ m_Resources.find(key) }; it != m_Resources.cend()) {
		return &it->second;
	}
	return nullptr;
}

template <class Resource, class Settings, class Properties, class TmpResource>
void reality::ResourceManager<Resource, Settings, Properties, TmpResource>::Update() {
	for (auto it{ m_TmpResources.begin() }; it != m_TmpResources.cend(); ) {
		auto& [settings, resource] { it->second };
		if (resource._Is_ready()) {
			m_Resources.at(it->first) = loader::Convert<Resource>(settings, resource.get());
			it = m_TmpResources.erase(it);
		}
		else {
			++it;
		}
	}
}