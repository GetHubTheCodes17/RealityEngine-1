// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include <rttr/type>

namespace reality {
	class GameObject;

	struct Component {
	public:
		friend GameObject;

		virtual	~Component() = default;

		GameObject& GetGameObject() const;

	private:
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
		return new T(*this);					\
	}
