// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include <string>

#include "Core/Platform.h"
#include "Core/Maths/Vector3.h"

namespace irrklang { class ISound; class ISoundSource; }

namespace reality {
	struct AudioClipSettings {
		std::string Path;
	};

	class RE_CORE AudioClip {
		friend class AudioSource;

	public:
		explicit AudioClip(AudioClipSettings settings);

	private:
		irrklang::ISoundSource* m_Clip{};
	};

	class RE_CORE AudioSource {
	public:
		AudioClip* CurrentClip{};
		bool Is3D{ true };

		void Play(Vector3 position = {});
		void Stop() const;
		bool IsPaused() const;
		bool IsFinish() const;
		bool IsLooped() const;
		float GetMaxDistance() const;
		float GetMinDistance() const;
		float GetPan() const;
		float GetSpeed() const;
		unsigned GetLengthInMs() const;
		Vector3 GetPosition() const;
		Vector3 GetVelocity() const;
		float GetVolume() const;
		void SetPaused(bool paused) const;
		void SetLooped(bool looped) const;
		void SetMaxDistance(float distance) const;
		void SetMinDistance(float distance) const;
		void SetPan(float pan) const;
		void SetSpeed(float speed) const;
		void SetPosition(Vector3 position) const;
		void SetVelocity(Vector3 velocity) const;
		void SetVolume(float volume) const;
		static void PlayOneShot(const AudioClip& sound, Vector3 position = {}, bool is3D = true);

	private:
		irrklang::ISound* m_CurrentSound{};
	};
}