// Copyright Reality Engine. All Rights Reserved.

#include "Gameplay/Component/Transform.h"

#include <functional>

#include "Gameplay/GameObject.h"

void Reality::CTransform::SetParent(CTransform* parent) {
	if (parent == m_Parent || parent == this || std::ranges::any_of(m_Children, [parent](auto child) { return child == parent; })) {
		return;
	}

	std::function<void(CTransform&, unsigned)> UpdateLevel = [&UpdateLevel](auto& root, unsigned level) {
		root.m_Level = level;

		for (auto child : root.m_Children) {
			UpdateLevel(*child, root.m_Level + 1);
		}
	};

	if (m_Parent) {
		std::erase(m_Parent->m_Children, this);
	}

	if (parent) {
		parent->m_Children.emplace_back(this);
		m_ParentId = parent->GetGameObject().GetId();
		UpdateLevel(*this, parent->m_Level + 1);

		// TODO : Update world position
		//m_Position = (m_Trs * Matrix4::Inverse(parent->GetTrs())).GetRow3(3);
		//m_Scale = Matrix4::GetScale(m_Trs * Matrix4::Inverse(parent->GetTrs()));
		//m_Rotation = Quaternion(m_Trs * Matrix4::Inverse(parent->GetTrs()));
	}
	else {
		UpdateLevel(*this, 0);
		m_ParentId = 0;
	}

	m_Parent = parent;
	SetHasChanged(true);
}