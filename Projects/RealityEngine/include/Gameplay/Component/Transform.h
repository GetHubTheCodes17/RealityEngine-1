// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include <functional>
#include <vector>

#include "Component.h"
#include "Core/Maths/Quaternion.h"

namespace reality {
	struct CTransform : Component {
		CTransform() = default;
		CTransform(const CTransform&);
		CTransform& operator=(const CTransform&);
		~CTransform();

		Vector3 TransformPoint(const Vector3& position) const;
		Vector3 InverseTransformPoint(const Vector3& position) const;
		void Rotate(const Vector3& eulerAngles);
		void Translate(const Vector3& translation);
		bool IsRoot() const;
		bool HasChanged() const;
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
		void SetHasChanged(bool hasChanged);
		void SetParent(CTransform* parent);
		void SetPosition(Vector3 position);
		void SetRotation(Vector3 eulerAngles);
		void SetRotation(Quaternion rotation);
		void SetScale(Vector3 scale);
		void SetTrs(const Matrix4& trs);

	public:
		virtual Component* Clone() const override;
		void Reset();
		static Component* Instantiate();

	private:
		Matrix4 m_Trs{ Matrix4::Identity };
		Quaternion m_Rotation;
		Vector3 m_Position;
		Vector3 m_Scale{ Vector3::One };
		std::vector<CTransform*> m_Children;
		CTransform* m_Parent{};
		unsigned m_Level{};		
		bool m_HasChanged{};
	};
}

inline reality::CTransform::CTransform(const CTransform& other) :
	m_Trs{ other.m_Trs }, m_Rotation{ other.m_Rotation }, m_Position{ other.m_Position }, m_Scale{ other.m_Scale }
{
	SetHasChanged(true);
	SetParent(other.m_Parent);
}

inline reality::CTransform& reality::CTransform::operator=(const CTransform& other) {
	SetHasChanged(true);
	m_Trs = other.m_Trs;
	m_Rotation = other.m_Rotation;
	m_Position = other.m_Position;
	m_Scale = other.m_Scale;
	SetParent(other.m_Parent);
	return *this;
}

inline reality::CTransform::~CTransform() {
	if (m_Parent && !m_Parent->m_Children.empty()) {
		m_Parent->m_Children.erase(std::remove(m_Parent->m_Children.begin(), m_Parent->m_Children.end(), this),
			m_Parent->m_Children.end());
	}
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
	SetHasChanged(true);
}

inline void reality::CTransform::Translate(const Vector3& translation) {
	m_Position += translation;
	SetHasChanged(true);
}

inline bool reality::CTransform::IsRoot() const {
	return !m_Level;
}

inline bool reality::CTransform::HasChanged() const {
	auto parent{ m_Parent };
	while (parent) {
		if (parent->m_HasChanged) {
			return true;
		}
		parent = parent->m_Parent;
	}
	return m_HasChanged;
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

inline void reality::CTransform::SetHasChanged(bool hasChanged) {
	m_HasChanged = hasChanged;

	if (hasChanged) {
		auto parent{ m_Parent };
		while (parent) {
			parent->m_HasChanged = true;
			parent = parent->m_Parent;
		}
	}
}

inline void reality::CTransform::SetParent(CTransform* parent) {
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
		UpdateLevel(*this, parent->m_Level + 1);
		
		//m_Position = (m_Trs * Matrix4::Inverse(parent->GetTrs())).GetRow3(3);
		//m_Scale = Matrix4::GetScale(m_Trs * Matrix4::Inverse(parent->GetTrs()));
		//m_Rotation = Quaternion(m_Trs * Matrix4::Inverse(parent->GetTrs()));
	}
	else {
		UpdateLevel(*this, 0);
	}

	m_Parent = parent;
	SetHasChanged(true);
}

inline void reality::CTransform::SetPosition(Vector3 position) {
	m_Position = std::move(position);
	SetHasChanged(true);
}

inline void reality::CTransform::SetRotation(Vector3 eulerAngles) {
	m_Rotation = Quaternion{ eulerAngles * Mathf::Deg2Rad };
	SetHasChanged(true);
}

inline void reality::CTransform::SetRotation(Quaternion rotation) {
	m_Rotation = std::move(rotation);
	SetHasChanged(true);
}

inline void reality::CTransform::SetScale(Vector3 scale) {
	m_Scale = std::move(scale);
	SetHasChanged(true);
}

inline void reality::CTransform::SetTrs(const Matrix4& trs) {
	m_Trs = trs;
	SetHasChanged(true);
}

inline reality::Component* reality::CTransform::Clone() const {
	return new CTransform{ *this };
}

inline void reality::CTransform::Reset() {
	auto owner{ m_GameObject };
	*this = CTransform{};
	m_GameObject = owner;
}

inline reality::Component* reality::CTransform::Instantiate() {
	return new CTransform;
}