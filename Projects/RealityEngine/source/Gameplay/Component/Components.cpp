// Copyright Reality Engine. All Rights Reserved.

#include <rttr/registration>

#include "Gameplay/Component/Components.h"

RTTR_REGISTRATION
{
    using namespace rttr;
    using namespace reality;

    registration::class_<CLight>("Light")
        .method("Instantiate", &CLight::Instantiate);

    registration::class_<CCamera>("Camera")
        .method("Instantiate", &CCamera::Instantiate);

    registration::class_<CMeshFilter>("MeshFilter")
        .method("Instantiate", &CMeshFilter::Instantiate);

    registration::class_<CMeshRenderer>("MeshRenderer")
        .method("Instantiate", &CMeshRenderer::Instantiate);

    registration::class_<CParticleSystem>("ParticleSystem")
        .method("Instantiate", &CParticleSystem::Instantiate);
}