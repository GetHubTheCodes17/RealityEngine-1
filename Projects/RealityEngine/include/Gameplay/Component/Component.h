// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include <cereal/cereal.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>
#include <rttr/type>

namespace reality {
	class GameObject;

	struct Component {
	public:
		friend GameObject;

		virtual	~Component() = default;

		GameObject& GetGameObject() const;

	protected:
		GameObject* m_GameObject{};

		virtual Component* Clone() const = 0;

		RTTR_ENABLE()
	};
}

inline reality::GameObject& reality::Component::GetGameObject() const {
	return *m_GameObject;
}

#define RE_COMPONENT(T, Base)					\
private:										\
	RTTR_ENABLE(Base)							\
public:											\
	virtual Component* Clone() const override {	\
		return new T{ *this };					\
	}											\
	void Reset() {								\
		auto owner{ m_GameObject };				\
		*this = T{};							\
		m_GameObject = owner;					\
	}											\
	static Component* Instantiate() {			\
		return new T;							\
	}											