// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include <vector>

#include "Component.h"
#include "Core/Maths/Quaternion.h"

namespace reality {
	struct CTransform : Component {
		RE_COMPONENT(CTransform, Component)

		bool HasChanged{};

		CTransform() = default;
		CTransform(const CTransform&);
		CTransform& operator=(const CTransform&);

		Vector3 TransformPoint(const Vector3& position) const;
		Vector3 InverseTransformPoint(const Vector3& position) const;
		void Rotate(const Vector3& eulerAngles);
		void Translate(const Vector3& translation);
		bool IsRoot() const;
		CTransform* GetRoot();
		CTransform* GetParent() const;
		const std::vector<CTransform*>& GetChildren() const;
		CTransform* GetChild(unsigned index) const;
		unsigned GetChildrenSize() const;
		unsigned GetLevel() const;
		const Vector3& GetPosition() const;
		const Quaternion& GetRotation() const;
		const Vector3& GetScale() const;
		Quaternion GetLocalRotation() const;
		Vector3 GetLocalPosition() const;
		Matrix4 GetWorldToLocalMatrix() const;
		const Matrix4& GetTrs() const;
		Vector3 GetRight() const;
		Vector3 GetUp() const;
		Vector3 GetForward() const;
		void SetParent(CTransform* parent);
		void SetPosition(Vector3 position);
		void SetRotation(Vector3 eulerAngles);
		void SetRotation(Quaternion rotation);
		void SetScale(Vector3 scale);
		void SetTrs(const Matrix4& trs);

	private:
		Matrix4 m_Trs{ Matrix4::Identity };
		Quaternion m_Rotation;
		Vector3 m_Position;
		Vector3 m_Scale{ Vector3::One };
		std::vector<CTransform*> m_Children;
		CTransform* m_Parent{};
		unsigned m_Level{};
	};
}

inline reality::CTransform::CTransform(const CTransform& other) :
	HasChanged{ other.HasChanged }, m_Trs{ other.m_Trs }, m_Rotation{ other.m_Rotation },
	m_Position{ other.m_Position }, m_Scale{ other.m_Scale }
{
	SetParent(other.m_Parent);
}

inline reality::CTransform& reality::CTransform::operator=(const CTransform& other) {
	HasChanged = other.HasChanged;
	m_Trs = other.m_Trs;
	m_Rotation = other.m_Rotation;
	m_Position = other.m_Position;
	m_Scale = other.m_Scale;
	SetParent(other.m_Parent);
	return *this;
}

inline reality::Vector3 reality::CTransform::TransformPoint(const Vector3& position) const {
	return { 
		m_Trs[0] * position.X + m_Trs[4] * position.Y + m_Trs[8] * position.Z + m_Trs[12],
		m_Trs[1] * position.X + m_Trs[5] * position.Y + m_Trs[9] * position.Z + m_Trs[13],
		m_Trs[2] * position.X + m_Trs[6] * position.Y + m_Trs[10] * position.Z + m_Trs[14] 
	};
}

inline reality::Vector3 reality::CTransform::InverseTransformPoint(const Vector3& position) const {
	const auto pos{ position - m_Position };
	return { 
		m_Trs[0] * pos.X + m_Trs[1] * pos.Y + m_Trs[2] * pos.Z + m_Trs[4],
		m_Trs[4] * pos.X + m_Trs[5] * pos.Y + m_Trs[6] * pos.Z + m_Trs[7],
		m_Trs[8] * pos.X + m_Trs[9] * pos.Y + m_Trs[10] * pos.Z + m_Trs[11] 
	};
}

inline void reality::CTransform::Rotate(const Vector3& eulerAngles) {
	m_Rotation = Quaternion::Normalize(m_Rotation * Quaternion{ eulerAngles * Mathf::Deg2Rad });
	HasChanged = true;
}

inline void reality::CTransform::Translate(const Vector3& translation) {
	m_Position += translation;
	HasChanged = true;
}

inline bool reality::CTransform::IsRoot() const {
	return !m_Level;
}

inline reality::CTransform* reality::CTransform::GetRoot() {
	return m_Parent ? m_Parent->GetRoot() : this;
}

inline reality::CTransform* reality::CTransform::GetParent() const {
	return m_Parent;
}

inline const std::vector<reality::CTransform*>& reality::CTransform::GetChildren() const {
	return m_Children;
}

inline reality::CTransform* reality::CTransform::GetChild(unsigned index) const {
	return index < m_Children.size() ? m_Children[index] : nullptr;
}

inline unsigned reality::CTransform::GetChildrenSize() const {
	return (unsigned)(m_Children.size());
}

inline unsigned reality::CTransform::GetLevel() const {
	return m_Level;
}

inline const reality::Vector3& reality::CTransform::GetPosition() const {
	return m_Position;
}

inline const reality::Quaternion& reality::CTransform::GetRotation() const {
	return m_Rotation;
}

inline const reality::Vector3& reality::CTransform::GetScale() const {
	return m_Scale;
}

inline reality::Quaternion reality::CTransform::GetLocalRotation() const {
	return m_Parent ? Quaternion::Inverse(m_Parent->m_Rotation * m_Rotation) : m_Rotation;
}

inline reality::Vector3 reality::CTransform::GetLocalPosition() const {
	return m_Parent ? m_Parent->TransformPoint(m_Position) : m_Position;
}

inline reality::Matrix4 reality::CTransform::GetWorldToLocalMatrix() const {
	return Matrix4::Inverse(m_Trs);
}

inline const reality::Matrix4& reality::CTransform::GetTrs() const {
	return m_Trs;
}

inline reality::Vector3 reality::CTransform::GetRight() const {
	return m_Trs.GetRow3(0);
}

inline reality::Vector3 reality::CTransform::GetUp() const {
	return m_Trs.GetRow3(1);
}

inline reality::Vector3 reality::CTransform::GetForward() const {
	return m_Trs.GetRow3(2);
}

inline void reality::CTransform::SetParent(CTransform* parent) {
	if (parent == m_Parent) {
		return;
	}

	std::function<void(CTransform&, unsigned)> UpdateLevel = [&UpdateLevel](auto& parent, unsigned level) {
		parent.m_Level = level;
		parent.HasChanged = true;

		for (auto& child : parent.m_Children) {
			UpdateLevel(*child, child->m_Parent->m_Level + 1);
		}
	};

	if (m_Parent) {
		m_Parent->m_Children.erase(std::find(m_Parent->m_Children.cbegin(), m_Parent->m_Children.cend(), this));
	}

	if (parent) {
		parent->m_Children.emplace_back(this);
		UpdateLevel(*this, parent->m_Level + 1);
	}
	else {
		UpdateLevel(*this, 0);
	}

	m_Parent = parent;
}

inline void reality::CTransform::SetPosition(Vector3 position) {
	m_Position = std::move(position);
	HasChanged = true;
}

inline void reality::CTransform::SetRotation(Vector3 eulerAngles) {
	m_Rotation = Quaternion{ eulerAngles * Mathf::Deg2Rad };
	HasChanged = true;
}

inline void reality::CTransform::SetRotation(Quaternion rotation) {
	m_Rotation = std::move(rotation);
	HasChanged = true;
}

inline void reality::CTransform::SetScale(Vector3 scale) {
	m_Scale = std::move(scale);
	HasChanged = true;
}

inline void reality::CTransform::SetTrs(const Matrix4& trs) {
	m_Trs = trs;
	HasChanged = true;
}