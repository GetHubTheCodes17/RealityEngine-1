// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include <vector>
#include <span>

#include "Core/Platform.h"
#include "Core/Maths/MathsSerializer.h"
#include "Component.h"

namespace Reality {
	struct RE_CORE CTransform : Component {
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
		std::span<CTransform*> GetChildren();
		CTransform* GetChild(unsigned index) const;
		unsigned GetChildrenSize() const;
		unsigned GetLevel() const;
		uint64 GetParentId() const;
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

	private:
		Matrix4 m_Trs{ Matrix4::Identity };
		Quaternion m_Rotation;
		Vector3 m_Position;
		Vector3 m_Scale{ Vector3::One };
		std::vector<CTransform*> m_Children;
		CTransform* m_Parent{};
		uint64 m_ParentId{};
		unsigned m_Level{};
		bool m_HasChanged{};

	public:
		virtual Component* Clone() const override {
			return new CTransform{ *this };
		}
		void Reset() {
			auto owner{ m_GameObject };
			*this = {};
			m_GameObject = owner;
		}

	private:
		friend class cereal::access;
		template <class Archive>
		void serialize(Archive& archive);
	};
}

inline Reality::CTransform::CTransform(const CTransform& other) :
	m_Trs{ other.m_Trs }, m_Rotation{ other.m_Rotation }, m_Position{ other.m_Position }, m_Scale{ other.m_Scale }
{
	SetHasChanged(true);
	SetParent(other.m_Parent);
}

inline Reality::CTransform& Reality::CTransform::operator=(const CTransform& other) {
	SetHasChanged(true);
	m_Trs = other.m_Trs;
	m_Rotation = other.m_Rotation;
	m_Position = other.m_Position;
	m_Scale = other.m_Scale;
	SetParent(other.m_Parent);
	return *this;
}

inline Reality::CTransform::~CTransform() {
	if (m_Parent && !m_Parent->m_Children.empty()) {
		std::erase(m_Parent->m_Children, this);
	}
}

inline Reality::Vector3 Reality::CTransform::TransformPoint(const Vector3& position) const {
	return {
		m_Trs[0] * position.X + m_Trs[4] * position.Y + m_Trs[8] * position.Z + m_Trs[12],
		m_Trs[1] * position.X + m_Trs[5] * position.Y + m_Trs[9] * position.Z + m_Trs[13],
		m_Trs[2] * position.X + m_Trs[6] * position.Y + m_Trs[10] * position.Z + m_Trs[14]
	};
}

inline Reality::Vector3 Reality::CTransform::InverseTransformPoint(const Vector3& position) const {
	const auto pos{ position - m_Position };
	return {
		m_Trs[0] * pos.X + m_Trs[1] * pos.Y + m_Trs[2] * pos.Z + m_Trs[4],
		m_Trs[4] * pos.X + m_Trs[5] * pos.Y + m_Trs[6] * pos.Z + m_Trs[7],
		m_Trs[8] * pos.X + m_Trs[9] * pos.Y + m_Trs[10] * pos.Z + m_Trs[11]
	};
}

inline void Reality::CTransform::Rotate(const Vector3& eulerAngles) {
	m_Rotation = Quaternion::Normalize(m_Rotation * Quaternion{ eulerAngles * Mathf::Deg2Rad });
	SetHasChanged(true);
}

inline void Reality::CTransform::Translate(const Vector3& translation) {
	m_Position += translation;
	SetHasChanged(true);
}

inline bool Reality::CTransform::IsRoot() const {
	return !m_Level;
}

inline bool Reality::CTransform::HasChanged() const {
	return m_Parent ? m_Parent->HasChanged() : m_HasChanged;
}

inline Reality::CTransform* Reality::CTransform::GetRoot() {
	return m_Parent ? m_Parent->GetRoot() : this;
}

inline Reality::CTransform* Reality::CTransform::GetParent() const {
	return m_Parent;
}

inline std::span<Reality::CTransform*> Reality::CTransform::GetChildren() {
	return m_Children;
}

inline Reality::CTransform* Reality::CTransform::GetChild(unsigned index) const {
	return index < m_Children.size() ? m_Children[index] : nullptr;
}

inline unsigned Reality::CTransform::GetChildrenSize() const {
	return (unsigned)m_Children.size();
}

inline unsigned Reality::CTransform::GetLevel() const {
	return m_Level;
}

inline Reality::uint64 Reality::CTransform::GetParentId() const {
	return m_ParentId;
}

inline const Reality::Vector3& Reality::CTransform::GetPosition() const {
	return m_Position;
}

inline const Reality::Quaternion& Reality::CTransform::GetRotation() const {
	return m_Rotation;
}

inline const Reality::Vector3& Reality::CTransform::GetScale() const {
	return m_Scale;
}

inline Reality::Quaternion Reality::CTransform::GetLocalRotation() const {
	return m_Parent ? Quaternion::Inverse(m_Parent->m_Rotation * m_Rotation) : m_Rotation;
}

inline Reality::Vector3 Reality::CTransform::GetLocalPosition() const {
	return m_Parent ? m_Parent->TransformPoint(m_Position) : m_Position;
}

inline Reality::Matrix4 Reality::CTransform::GetWorldToLocalMatrix() const {
	return Matrix4::Inverse(m_Trs);
}

inline const Reality::Matrix4& Reality::CTransform::GetTrs() const {
	return m_Trs;
}

inline Reality::Vector3 Reality::CTransform::GetRight() const {
	return m_Trs.GetRow3(0);
}

inline Reality::Vector3 Reality::CTransform::GetUp() const {
	return m_Trs.GetRow3(1);
}

inline Reality::Vector3 Reality::CTransform::GetForward() const {
	return m_Trs.GetRow3(2);
}

inline void Reality::CTransform::SetHasChanged(bool hasChanged) {
	m_HasChanged = hasChanged;
	if (m_Parent && hasChanged) {
		m_Parent->SetHasChanged(m_HasChanged);
	}
}

inline void Reality::CTransform::SetPosition(Vector3 position) {
	m_Position = std::move(position);
	SetHasChanged(true);
}

inline void Reality::CTransform::SetRotation(Vector3 eulerAngles) {
	m_Rotation = Quaternion{ eulerAngles * Mathf::Deg2Rad };
	SetHasChanged(true);
}

inline void Reality::CTransform::SetRotation(Quaternion rotation) {
	m_Rotation = std::move(rotation);
	SetHasChanged(true);
}

inline void Reality::CTransform::SetScale(Vector3 scale) {
	m_Scale = std::move(scale);
	SetHasChanged(true);
}

inline void Reality::CTransform::SetTrs(const Matrix4& trs) {
	m_Trs = trs;
	SetHasChanged(true);
}

template <class Archive>
void Reality::CTransform::serialize(Archive& archive) {
	archive(CEREAL_NVP(m_Trs));
	archive(CEREAL_NVP(m_Rotation));
	archive(CEREAL_NVP(m_Position));
	archive(CEREAL_NVP(m_Scale));
	archive(CEREAL_NVP(m_Level));
	archive(CEREAL_NVP(m_HasChanged));
	archive(CEREAL_NVP(m_ParentId));
}

CEREAL_REGISTER_TYPE_WITH_NAME(Reality::CTransform, "Transform");
CEREAL_REGISTER_POLYMORPHIC_RELATION(Reality::Component, Reality::CTransform)