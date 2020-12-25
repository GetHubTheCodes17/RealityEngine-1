// Copyright Reality Engine. All Rights Reserved.

#include <rttr/registration>

#include "Gameplay/Component/EngineComponents.h"

RTTR_REGISTRATION
{
    using namespace rttr;
    using namespace reality;

    registration::class_<CLight>("Light");
    registration::class_<CMeshRenderer>("MeshRenderer");
    registration::class_<CMeshFilter>("MeshFilter");
    registration::class_<CCamera>("Camera");
    registration::class_<CParticleSystem>("ParticleSystem");
}