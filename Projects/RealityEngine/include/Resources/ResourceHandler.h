// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include <cereal/archives/json.hpp>
#include <cereal/types/unordered_map.hpp>
#include <cereal/types/utility.hpp>
#include <fstream>
#include <future>

#include "ResourceSerializer.h"
#include "ResourceConverter.h"

namespace Reality {
	template <class Resource, class Settings, class Properties, class TmpResource>
	class ResourceHandler final {
		friend class ResourceManager;

	public:
		const Resource& Load(std::string_view key, const Settings& settings, const Properties& properties = {});
		bool Remove(std::string_view key);
		bool Exist(std::string_view key) const;
		const Resource* Get(std::string_view key) const;
		std::string_view GetPath() const;
		const std::unordered_map<std::string, Resource>& GetResources() const;

	private:
		std::string m_Path;
		std::unordered_map<std::string, Resource> m_Resources;
		std::unordered_map<std::string, std::pair<Settings, Properties>> m_Properties;
		std::unordered_map<std::string, std::future<TmpResource>> m_TmpResources;

		explicit ResourceHandler(std::string_view path);
		~ResourceHandler();

		void Update();
	};
}

template <class Resource, class Settings, class Properties, class TmpResource>
Reality::ResourceHandler<Resource, Settings, Properties, TmpResource>::ResourceHandler(std::string_view path) :
	m_Path{ path }
{
	if (std::ifstream file{ m_Path }) {
		cereal::JSONInputArchive archive{ file };
		archive(m_Properties);

		for (auto& [key, value] : m_Properties) {
			auto& [settings, properties] { value };
			m_TmpResources.emplace(key, std::future<TmpResource>{}).first->second =
				std::async(std::launch::async, [settings] { return TmpResource{ settings }; });
			m_Resources.emplace(key, Resource{});
		}
	}
}

template<class Resource, class Settings, class Properties, class TmpResource>
Reality::ResourceHandler<Resource, Settings, Properties, TmpResource>::~ResourceHandler() {
	if (std::ofstream file{ m_Path }) {
		cereal::JSONOutputArchive archive{ file };
		archive(m_Properties);
	}
}

template <class Resource, class Settings, class Properties, class TmpResource>
void Reality::ResourceHandler<Resource, Settings, Properties, TmpResource>::Update() {
	for (auto it{ m_TmpResources.begin() }; it != m_TmpResources.cend(); ) {
		auto& resource{ it->second };
		if (resource.wait_for(std::chrono::seconds{ 0 }) == std::future_status::ready) {
			m_Resources.at(it->first) = loader::Convert<Resource>(m_Properties.at(it->first).second, resource.get());
			it = m_TmpResources.erase(it);
		}
		else {
			++it;
		}
	}
}

template <class Resource, class Settings, class Properties, class TmpResource>
const Resource& Reality::ResourceHandler<Resource, Settings, Properties, TmpResource>::Load(std::string_view key,
	const Settings& settings, const Properties& properties)
{
	if (const auto it{ m_Resources.find(key.data()) }; it != m_Resources.cend()) {
		return it->second;
	}

	m_Properties.emplace(key, std::pair{ settings, properties });
	m_TmpResources.emplace(key, std::future<TmpResource>{}).first->second =
		std::async(std::launch::async, [settings] { return TmpResource{ settings }; });
	return m_Resources.emplace(key, Resource{}).first->second;
}

template<class Resource, class Settings, class Properties, class TmpResource>
bool Reality::ResourceHandler<Resource, Settings, Properties, TmpResource>::Remove(std::string_view key) {
	if (const auto it{ m_Resources.find(key.data()) }; it == m_Resources.cend()) {
		return false;
	}

	m_Properties.erase(key.data());
	m_Resources.erase(key.data());
	return true;
}

template<class Resource, class Settings, class Properties, class TmpResource>
bool Reality::ResourceHandler<Resource, Settings, Properties, TmpResource>::Exist(std::string_view key) const {
	return m_Resources.contains(key.data());
}

template <class Resource, class Settings, class Properties, class TmpResource>
const Resource* Reality::ResourceHandler<Resource, Settings, Properties, TmpResource>::Get(std::string_view key) const {
	if (const auto it{ m_Resources.find(key.data()) }; it != m_Resources.cend()) {
		return &it->second;
	}
	return nullptr;
}

template<class Resource, class Settings, class Properties, class TmpResource>
std::string_view Reality::ResourceHandler<Resource, Settings, Properties, TmpResource>::GetPath() const {
	return m_Path;
}

template <class Resource, class Settings, class Properties, class TmpResource>
const std::unordered_map<std::string, Resource>& 
Reality::ResourceHandler<Resource, Settings, Properties, TmpResource>::GetResources() const {
	return m_Resources;
}