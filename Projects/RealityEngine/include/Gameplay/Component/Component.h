// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include <cereal/cereal.hpp>
#include <cereal/types/memory.hpp>
#include <rttr/type>

namespace Reality {
	class GameObject;
	class Scene;

	struct Component {
		friend GameObject;
		friend Scene;

	public:
		virtual	~Component() = default;

		GameObject& GetGameObject() const;

	protected:
		GameObject* m_GameObject{};

		virtual Component* Clone() const = 0;

		RTTR_ENABLE()
	};
}

inline Reality::GameObject& Reality::Component::GetGameObject() const {
	return *m_GameObject;
}

#define RE_COMPONENT(T, Base)					\
private:										\
	RTTR_ENABLE(Base)							\
	friend class cereal::access;				\
public:											\
	virtual Component* Clone() const override {	\
		return new T{ *this };					\
	}											\
	void Reset() {								\
		auto owner{ m_GameObject };				\
		*this = T{};							\
		m_GameObject = owner;					\
	}											\
	static std::shared_ptr<T> Instantiate() {	\
		return std::make_shared<T>();			\
	}			

#define RE_INTERFACE(Base)						\
private:										\
	RTTR_ENABLE(Base)							\
	friend class cereal::access;				\
public:											\
	virtual Component* Clone() const override {	\
		return nullptr;							\
	}											\
