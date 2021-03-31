// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include <algorithm>

#include "Mathf.h"
#include "Vector3.h"

namespace Reality {
	struct AABB {
		Vector3 Min, Max;

		constexpr AABB() = default;
		constexpr AABB(const Vector3& min, const Vector3& max);
		constexpr AABB(float minX, float minY, float minZ, float maxX, float maxY, float maxZ);
		constexpr AABB(const Vector3& point);

		constexpr bool operator==(const AABB& otherAABB) const;
		constexpr bool operator!=(const AABB& otherAABB) const;

		constexpr AABB& Set(float x, float y, float z);
		constexpr AABB& Set(float data);
		constexpr AABB& AddPoint(const Vector3& point);
		constexpr AABB& AddPoint(float x, float y, float z);
		constexpr AABB& AddAABB(const AABB& aabb);
		constexpr Vector3 GetCenter() const;
		constexpr float GetArea() const;
		constexpr Vector3 GetExtremePoint(const Vector3& direction) const;
		constexpr Vector3 GetClosestPoint(const Vector3& targetPoint) const;
		float GetDistance(const Vector3& point) const;
		constexpr float GetVolume() const;
		constexpr Vector3 GetSize() const;
		constexpr Vector3 GetHalfSize() const;
		constexpr void GetEdges(Vector3* edges) const;
		constexpr bool IsEmpty() const;
		constexpr bool IsAABBFullInside(const AABB& otherAABB) const;
		constexpr bool BoxColision(const AABB& otherAABB) const;
		constexpr bool IsPointFullInside(const Vector3& point) const;
		constexpr bool IsPointInside(const Vector3& point) const;
		constexpr AABB& Restore();
		constexpr AABB& Translate(const Vector3& translation);
		constexpr AABB& Scale(const Vector3& center, float scale);

		static constexpr bool BoxBoxColision(const AABB& aabb1, const AABB& aabb2);
		static constexpr AABB Lerp(const AABB& start, const AABB& destination, float t);
		static constexpr bool Equals(const AABB& aabb1, const AABB& aabb2, float epsilon = Mathf::Epsilon);
	};
}

constexpr Reality::AABB::AABB(const Vector3& min, const Vector3& max) 
	: Min{ min }, Max{ max }
{}

constexpr Reality::AABB::AABB(const Vector3& point) 
	: Min{ point }, Max{ point }
{}

constexpr Reality::AABB::AABB(float minX, float minY, float minZ, float maxX, float maxY, float maxZ) :
	Min(minX, minY, minZ), Max(maxX, maxY, maxZ)
{}

constexpr bool Reality::AABB::operator==(const AABB& otherAABB) const {
	return (Min == otherAABB.Min && otherAABB.Max == Max);
}

constexpr bool Reality::AABB::operator!=(const AABB& otherAABB) const {
	return !((*this) == otherAABB);
}

constexpr Reality::AABB& Reality::AABB::Set(float x, float y, float z) {
	Max.Set(x, y, z);
	Min = Max;
	return *this;
}

constexpr Reality::AABB& Reality::AABB::Set(float data) {
	Max.Set(data, data, data);
	Min = Max;
	return *this;
}

constexpr Reality::AABB& Reality::AABB::AddPoint(const Vector3& point) {
	AddPoint(point.X, point.Y, point.Z);
	return *this;
}

constexpr Reality::AABB& Reality::AABB::AddPoint(float x, float y, float z) {
	if (x < Min.X) {
		Min.X = x;
	}
	if (y < Min.Y) {
		Min.Y = y;
	}
	if (z < Min.Z) {
		Min.Z = z;
	}

	if (x > Max.X) {
		Max.X = x;
	}
	if (y > Max.Y) {
		Max.Y = y;
	}
	if (z > Max.Z) {
		Max.Z = z;
	}
	return *this;
}

constexpr Reality::AABB& Reality::AABB::AddAABB(const AABB& otherAABB) {
	AddPoint(otherAABB.Min);
	AddPoint(otherAABB.Max);
	return *this;
}

constexpr Reality::Vector3 Reality::AABB::GetCenter() const {
	return (Min + Max) * 0.5f;
}

constexpr float Reality::AABB::GetArea() const {
	const auto extend{ GetSize() };
	return 2.f * (extend.X * extend.Y + extend.X * extend.Z + extend.Y * extend.Z);
}

constexpr Reality::Vector3 Reality::AABB::GetExtremePoint(const Vector3& direction) const {
	return { direction.X >= 0.f ? Max.X : Min.X, direction.Y >= 0.f ? Max.Y : Min.Y, direction.Z >= 0.f ? Max.Z : Min.Z };
}

constexpr Reality::Vector3 Reality::AABB::GetClosestPoint(const Vector3& targetPoint) const {
	return { std::clamp(targetPoint.X, Min.X, Max.X), std::clamp(targetPoint.Y, Min.Y, Max.Y), 
		std::clamp(targetPoint.Z, Min.Z, Max.Z) };
}

inline float Reality::AABB::GetDistance(const Vector3& point) const {
	return Vector3::Distance(GetClosestPoint(point), point);
}

constexpr float Reality::AABB::GetVolume() const {
	const auto extend{ GetSize() };
	return (extend.X * extend.Y * extend.Z);
}

constexpr Reality::Vector3 Reality::AABB::GetSize() const {
	return { Max - Min };
}

constexpr Reality::Vector3 Reality::AABB::GetHalfSize() const {
	return { (Max - Min) * 0.5f };
}

constexpr void Reality::AABB::GetEdges(Vector3* edges) const {
	const auto middle{ GetCenter() }, diagonal{ middle - Max };

	// left side (0, 1, 2, 3 in trigo sens, begin bottom left)
	edges[0].Set(middle.X + diagonal.X, middle.Y + diagonal.Y, middle.Z + diagonal.Z);
	edges[1].Set(middle.X + diagonal.X, middle.Y - diagonal.Y, middle.Z + diagonal.Z);
	edges[2].Set(middle.X + diagonal.X, middle.Y + diagonal.Y, middle.Z - diagonal.Z);
	edges[3].Set(middle.X + diagonal.X, middle.Y - diagonal.Y, middle.Z - diagonal.Z);

	// right side (4, 5, 6, 7 in trigo sens, begin bottom left)
	edges[4].Set(middle.X - diagonal.X, middle.Y + diagonal.Y, middle.Z + diagonal.Z);
	edges[5].Set(middle.X - diagonal.X, middle.Y - diagonal.Y, middle.Z + diagonal.Z);
	edges[6].Set(middle.X - diagonal.X, middle.Y + diagonal.Y, middle.Z - diagonal.Z);
	edges[7].Set(middle.X - diagonal.X, middle.Y - diagonal.Y, middle.Z - diagonal.Z);
}

constexpr bool Reality::AABB::IsEmpty() const {
	return Min == Max;
}

constexpr bool Reality::AABB::IsAABBFullInside(const AABB& otherAABB) const {
	return Min.X >= otherAABB.Min.X && Min.Y >= otherAABB.Min.Y && Min.Z >= otherAABB.Min.Z
		&& Max.X <= otherAABB.Max.X && Max.Y <= otherAABB.Max.Y && Max.Z <= otherAABB.Max.Z;
}

constexpr bool Reality::AABB::BoxColision(const AABB& otherAABB) const {
	return Min.X <= otherAABB.Max.X && Min.Y <= otherAABB.Max.Y && Min.Z <= otherAABB.Max.Z
		&& Max.X >= otherAABB.Min.X && Max.Y >= otherAABB.Min.Y && Max.Z >= otherAABB.Min.Z;
}

constexpr bool Reality::AABB::IsPointFullInside(const Vector3& point) const {
	return point.X > Min.X && point.X < Max.X&& point.Y > Min.Y && point.Y < Max.Y&& point.Z > Min.Z && point.Z < Max.Z;
}

constexpr bool Reality::AABB::IsPointInside(const Vector3& point) const {
	return point.X >= Min.X && point.X <= Max.X && point.Y >= Min.Y && point.Y <= Max.Y && point.Z >= Min.Z && point.Z <= Max.Z;
}

constexpr Reality::AABB& Reality::AABB::Restore() {
	auto value{ 0.f };

	if (Min.X > Max.X) {
		value = Min.X;
		Min.X = Max.X;
		Max.X = value;
	}
	if (Min.Y > Max.Y) {
		value = Min.Y;
		Min.Y = Max.Y;
		Max.Y = value;
	}
	if (Min.Z > Max.Z) {
		value = Min.Z;
		Min.Z = Max.Z;
		Max.Z = value;
	}
	return *this;
}

constexpr Reality::AABB& Reality::AABB::Translate(const Vector3& translation) {
	Min += translation;
	Max += translation;
	return *this;
}

constexpr Reality::AABB& Reality::AABB::Scale(const Vector3& center, float scale) {
	Min = (Min - center) * scale + center;
	Max = (Max - center) * scale + center;
	return *this;
}

constexpr bool Reality::AABB::BoxBoxColision(const AABB& aabb1, const AABB& aabb2) {
	return aabb1.Min.X <= aabb2.Max.X && aabb1.Min.Y <= aabb2.Max.Y && aabb1.Min.Z <= aabb2.Max.Z
		&& aabb1.Max.X >= aabb2.Min.X && aabb1.Max.Y >= aabb2.Min.Y && aabb1.Max.Z >= aabb2.Min.Z;
}

constexpr Reality::AABB Reality::AABB::Lerp(const AABB& start, const AABB& destination, float t) {
	return { Vector3::Lerp(start.Min, destination.Min, t), Vector3::Lerp(start.Max, destination.Max, t) };
}

constexpr bool Reality::AABB::Equals(const AABB& aabb1, const AABB& aabb2, float epsilon) {
	return Vector3::Equals(aabb1.Min, aabb2.Min, epsilon) && Vector3::Equals(aabb1.Max, aabb2.Max, epsilon);
}