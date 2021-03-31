// Copyright Reality Engine. All Rights Reserved.

#include "Audio/AudioEngine.h"

#include <irrklang/irrKlang.h>

Reality::AudioEngine::AudioEngine() {
	m_Engine = irrklang::createIrrKlangDevice(irrklang::ESOD_AUTO_DETECT, irrklang::ESEO_MULTI_THREADED |
		irrklang::ESEO_LOAD_PLUGINS | irrklang::ESEO_USE_3D_BUFFERS | irrklang::ESEO_PRINT_DEBUG_INFO_TO_DEBUGGER);
	RE_ASSERT(m_Engine, "Cannot load the Audio Engine");
}

void Reality::AudioEngine::PauseSounds(bool paused) const {
	m_Engine->setAllSoundsPaused(paused);
}

void Reality::AudioEngine::StopSounds() const {
	m_Engine->stopAllSounds();
}

float Reality::AudioEngine::GetVolume() const {
	return m_Engine->getSoundVolume();
}

void Reality::AudioEngine::SetListenerTransform(const Vector3& position, const Vector3& direction, const Vector3& velocity, 
	const Vector3& up) const 
{
	m_Engine->setListenerPosition({ position.X, position.Y, position.Z }, { direction.X, direction.Y, direction.Z },
		{ velocity.X, velocity.Y, velocity.Z }, { up.X, up.Y, up.Z });
}

void Reality::AudioEngine::SetVolume(float volume) const {
	m_Engine->setSoundVolume(volume);
}