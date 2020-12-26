// Copyright Reality Engine. All Rights Reserved.

#include "Gameplay/Component/Transform.h"

#include "Gameplay/GameObject.h"

void reality::CTransform::SetParent(CTransform* parent) {
	if (parent == m_Parent || parent == this || std::find(m_Children.cbegin(), m_Children.cend(), parent) != m_Children.cend()) {
		return;
	}

	std::function<void(CTransform&, unsigned)> UpdateLevel = [&UpdateLevel](auto& root, unsigned level) {
		root.m_Level = level;

		for (auto child : root.m_Children) {
			UpdateLevel(*child, root.m_Level + 1);
		}
	};

	if (m_Parent) {
		m_Parent->m_Children.erase(std::remove(m_Parent->m_Children.begin(), m_Parent->m_Children.end(), this),
			m_Parent->m_Children.end());
	}

	if (parent) {
		parent->m_Children.emplace_back(this);
		m_ParentId = parent->GetGameObject().GetId();
		UpdateLevel(*this, parent->m_Level + 1);

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