// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include "Core/Maths/Vector3.h"

namespace irrklang { class ISoundEngine; }

namespace reality {
	class RE_CORE AudioEngine {
		friend class AudioClip;
		friend class AudioSource;
	public:
		AudioEngine();

		void PauseSounds(bool paused = true) const;
		void StopSounds() const;
		float GetVolume() const;
		void SetListenerTransform(const Vector3& position, const Vector3& direction, const Vector3& velocity = {},
			const Vector3& up = Vector3::Up) const;                                  
		void SetVolume(float volume) const;

	private:
		irrklang::ISoundEngine* m_Engine{};
	};

	RE_CORE extern AudioEngine* g_AudioEngine;
}