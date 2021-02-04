// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include <cereal/cereal.hpp>

#include "Quaternion.h"
#include "Matrix4.h"
#include "Vector4.h"
#include "Vector3.h"
#include "Vector2.h"

namespace reality {
	template <class Archive>
	void serialize(Archive& archive, Vector2& v);
	template <class Archive>
	void serialize(Archive& archive, Vector3& v);
	template <class Archive>
	void serialize(Archive& archive, Vector4& v);
	template <class Archive>
	void serialize(Archive& archive, Matrix4& m);
	template <class Archive>
	void serialize(Archive& archive, Quaternion& q);
}

template<class Archive>
void reality::serialize(Archive& archive, Vector2& v) {
	archive(cereal::make_nvp("X", v.X), cereal::make_nvp("Y", v.Y));
}

template<class Archive>
void reality::serialize(Archive& archive, Vector3& v) {
	archive(cereal::make_nvp("X", v.X), cereal::make_nvp("Y", v.Y), cereal::make_nvp("Z", v.Z));
}

template<class Archive>
void reality::serialize(Archive& archive, Vector4& v) {
	archive(cereal::make_nvp("X", v.X), cereal::make_nvp("Y", v.Y), cereal::make_nvp("Z", v.Z), cereal::make_nvp("W", v.W));
}

template<class Archive>
void reality::serialize(Archive& archive, Matrix4& m) {
	archive(cereal::make_nvp("Array Row Major", m.Array));
}

template<class Archive>
void reality::serialize(Archive& archive, Quaternion& q) {
	archive(cereal::make_nvp("X", q.X), cereal::make_nvp("Y", q.Y), cereal::make_nvp("Z", q.Z), cereal::make_nvp("W", q.W));
}