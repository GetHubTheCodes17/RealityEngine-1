// Copyright Reality Engine. All Rights Reserved.

#include "Audio/AudioSource.h"

#include <irrklang/irrKlang.h>

#include "Audio/AudioEngine.h"

Reality::AudioClip::AudioClip(AudioClipSettings settings) {
	m_Clip = g_AudioEngine->m_Engine->addSoundSourceFromFile(settings.Path.c_str());
}

void Reality::AudioSource::Play(Vector3 position) {
	if (CurrentClip) {
		if (Is3D) {
			m_CurrentSound = g_AudioEngine->m_Engine->play3D(CurrentClip->m_Clip, { position.X, position.Y, position.Z },
				false, false, true);
		}
		else {
			m_CurrentSound = g_AudioEngine->m_Engine->play2D(CurrentClip->m_Clip, false, false, true);
		}
	}
}

void Reality::AudioSource::Stop() const {
	if (m_CurrentSound) {
		m_CurrentSound->stop();
	}
}

bool Reality::AudioSource::IsPaused() const {
	return m_CurrentSound ? m_CurrentSound->getIsPaused() : false;
}

bool Reality::AudioSource::IsFinish() const {
	return m_CurrentSound ? m_CurrentSound->isFinished() : false;
}

bool Reality::AudioSource::IsLooped() const {
	return m_CurrentSound ? m_CurrentSound->isLooped() : false;
}

float Reality::AudioSource::GetMaxDistance() const {
	return m_CurrentSound ? m_CurrentSound->getMaxDistance() : 0.f;
}

float Reality::AudioSource::GetMinDistance() const {
	return m_CurrentSound ? m_CurrentSound->getMinDistance() : 0.f;
}

float Reality::AudioSource::GetPan() const {
	return m_CurrentSound ? m_CurrentSound->getPan() : 0.f;
}

float Reality::AudioSource::GetSpeed() const {
	return m_CurrentSound ? m_CurrentSound->getPlaybackSpeed() : 0.f;
}

unsigned Reality::AudioSource::GetLengthInMs() const {
	return m_CurrentSound ? m_CurrentSound->getPlayLength() : 0;
}

Reality::Vector3 Reality::AudioSource::GetPosition() const {
	if (m_CurrentSound) {
		const auto position{ m_CurrentSound->getPosition() };
		return { position.X, position.Y, position.Z };
	}
	return {};
}

Reality::Vector3 Reality::AudioSource::GetVelocity() const {
	if (m_CurrentSound) {
		const auto velocity{ m_CurrentSound->getVelocity() };
		return { velocity.X, velocity.Y, velocity.Z };
	}
	return {};
}

float Reality::AudioSource::GetVolume() const {
	return m_CurrentSound ? m_CurrentSound->getVolume() : 0.f;
}

void Reality::AudioSource::SetPaused(bool paused) const {
	if (m_CurrentSound) {
		m_CurrentSound->setIsPaused(paused);
	}
}

void Reality::AudioSource::SetLooped(bool looped) const {
	if (m_CurrentSound) {
		m_CurrentSound->setIsLooped(looped);
	}
}

void Reality::AudioSource::SetMaxDistance(float distance) const {
	if (m_CurrentSound) {
		m_CurrentSound->setMaxDistance(distance);
	}
}

void Reality::AudioSource::SetMinDistance(float distance) const {
	if (m_CurrentSound) {
		m_CurrentSound->setMinDistance(distance);
	}
}

void Reality::AudioSource::SetPan(float pan) const {
	if (m_CurrentSound) {
		m_CurrentSound->setPan(pan);
	}
}

void Reality::AudioSource::SetSpeed(float speed) const {
	if (m_CurrentSound) {
		m_CurrentSound->setPlaybackSpeed(speed);
	}
}

void Reality::AudioSource::SetPosition(Vector3 position) const {
	if (m_CurrentSound) {
		m_CurrentSound->setPosition({ position.X, position.Y, position.Z });
	}
}

void Reality::AudioSource::SetVelocity(Vector3 velocity) const {
	if (m_CurrentSound) {
		m_CurrentSound->setVelocity({ velocity.X, velocity.Y, velocity.Z });
	}
}

void Reality::AudioSource::SetVolume(float volume) const {
	if (m_CurrentSound) {
		m_CurrentSound->setVolume(volume);
	}
}

void Reality::AudioSource::PlayOneShot(const AudioClip& sound, Vector3 position, bool is3D) {
	if (is3D) {
		g_AudioEngine->m_Engine->play3D(sound.m_Clip, { position.X, position.Y, position.Z });
	}
	else {
		g_AudioEngine->m_Engine->play2D(sound.m_Clip);
	}
}