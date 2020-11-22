// This code is based on Jet framework.
// Copyright (c) 2018 Doyub Kim
// CubbyFlow is voxel-based fluid simulation engine for computer games.
// Copyright (c) 2020 CubbyFlow Team
// Core Part: Chris Ohk, Junwoo Hwang, Jihong Sin, Seungwoo Yoo
// AI Part: Dongheon Cho, Minseo Kim
// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef CUBBYFLOW_MPM_SOLVER2_HPP
#define CUBBYFLOW_MPM_SOLVER2_HPP

#include <Core/Emitter/ParticleEmitter2.hpp>
#include <Core/Solver/Grid/GridFluidSolver2.hpp>

namespace CubbyFlow
{
//!
//! \brief 2-D Material Point Method (MPM) implementation.
//!
//! This class implements 2-D Material Point Method (MPM) method by inheriting
//! GridFluidSolver2. Since it is a grid-particle hybrid method, the solver
//! also has a particle system to track fluid particles.
//!
//! \see Stomakhin et al. "A material point method for snow simulation."
//!     ACM Transactions on Graphics (TOG). Vol. 32. No. 4. ACM, 2013.
//!
class MPMSolver2 : public GridFluidSolver2
{
 public:
    class Builder;

    //! Default constructor.
    MPMSolver2();

    //! Constructs solver with initial grid size.
    MPMSolver2(const Size2& resolution, const Vector2D& gridSpacing,
               const Vector2D& gridOrigin);

    //! Deleted copy constructor.
    MPMSolver2(const MPMSolver2&) = delete;

    //! Deleted move constructor.
    MPMSolver2(MPMSolver2&&) noexcept = delete;

    //! Default virtual destructor.
    ~MPMSolver2() override = default;

    //! Deleted copy assignment operator.
    MPMSolver2& operator=(const MPMSolver2&) = delete;

    //! Deleted move assignment operator.
    MPMSolver2& operator=(MPMSolver2&&) noexcept = delete;

    //! Returns the particle system data.
    [[nodiscard]] const ParticleSystemData2Ptr& GetParticleSystemData() const;

    //! Returns the particle emitter.
    [[nodiscard]] const ParticleEmitter2Ptr& GetParticleEmitter() const;

    //! Sets the particle emitter.
    void SetParticleEmitter(const ParticleEmitter2Ptr& newEmitter);

    //! Returns builder for MPMSolver2.
    [[nodiscard]] static Builder GetBuilder();

 private:
    ParticleSystemData2Ptr m_particles;
    ParticleEmitter2Ptr m_particleEmitter;
};

//! Shared pointer type for the MPMSolver2.
using MPMSolver2Ptr = std::shared_ptr<MPMSolver2>;

//!
//! \brief Front-end to create MPMSolver2 objects step by step.
//!
class MPMSolver2::Builder final : public GridFluidSolverBuilderBase2<Builder>
{
 public:
    //! Builds MPMSolver2.
    [[nodiscard]] MPMSolver2 Build() const;

    //! Builds shared pointer of MPMSolver2 instance.
    [[nodiscard]] MPMSolver2Ptr MakeShared() const;
};
}  // namespace CubbyFlow

#endif