// This code is based on Jet framework.
// Copyright (c) 2018 Doyub Kim
// CubbyFlow is voxel-based fluid simulation engine for computer games.
// Copyright (c) 2020 CubbyFlow Team
// Core Part: Chris Ohk, Junwoo Hwang, Jihong Sin, Seungwoo Yoo
// AI Part: Dongheon Cho, Minseo Kim
// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Core/Solver/Hybrid/MPM/MPMSolver2.hpp>

namespace CubbyFlow
{
MPMSolver2::MPMSolver2() : MPMSolver2{ { 1, 1 }, { 1, 1 }, { 0, 0 } }
{
    // Do nothing
}

MPMSolver2::MPMSolver2(const Size2& resolution, const Vector2D& gridSpacing,
                       const Vector2D& gridOrigin)
    : GridFluidSolver2{ resolution, gridSpacing, gridOrigin }
{
    m_particles = std::make_shared<ParticleSystemData2>();
}

const ParticleSystemData2Ptr& MPMSolver2::GetParticleSystemData() const
{
    return m_particles;
}

const ParticleEmitter2Ptr& MPMSolver2::GetParticleEmitter() const
{
    return m_particleEmitter;
}

void MPMSolver2::SetParticleEmitter(const ParticleEmitter2Ptr& newEmitter)
{
    m_particleEmitter = newEmitter;
    newEmitter->SetTarget(m_particles);
}

MPMSolver2::Builder MPMSolver2::GetBuilder()
{
    return Builder{};
}

MPMSolver2 MPMSolver2::Builder::Build() const
{
    return MPMSolver2{ m_resolution, GetGridSpacing(), m_gridOrigin };
}

MPMSolver2Ptr MPMSolver2::Builder::MakeShared() const
{
    return std::shared_ptr<MPMSolver2>(
        new MPMSolver2{ m_resolution, GetGridSpacing(), m_gridOrigin },
        [](MPMSolver2* obj) { delete obj; });
}
}  // namespace CubbyFlow