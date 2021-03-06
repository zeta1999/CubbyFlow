// This code is based on Jet framework.
// Copyright (c) 2018 Doyub Kim
// CubbyFlow is voxel-based fluid simulation engine for computer games.
// Copyright (c) 2020 CubbyFlow Team
// Core Part: Chris Ohk, Junwoo Hwang, Jihong Sin, Seungwoo Yoo
// AI Part: Dongheon Cho, Minseo Kim
// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef CUBBYFLOW_BOUNDING_BOX_HPP
#define CUBBYFLOW_BOUNDING_BOX_HPP

#include <Core/Vector/Vector.hpp>

namespace CubbyFlow
{
//!
//! \brief Generic N-D axis-aligned bounding box class.
//!
//! \tparam T - Real number type.
//! \tparam N - Dimension.
//!
template <typename T, size_t N>
class BoundingBox
{
 public:
    static_assert(N > 0,
                  "Size of static-sized box should be greater than zero.");

    using VectorType = Vector<T, N>;

    //! Default constructor.
    BoundingBox();

    //! Constructs a box that tightly covers two points.
    BoundingBox(const VectorType& point1, const VectorType& point2);

    //! Copy constructor.
    BoundingBox(const BoundingBox& other);

    //! Move constructor.
    BoundingBox(BoundingBox&& other) noexcept;

    //! Default destructor.
    ~BoundingBox() = default;

    //! Copy assignment operator.
    BoundingBox& operator=(const BoundingBox& other);

    //! Move assignment operator.
    BoundingBox& operator=(BoundingBox&& other) noexcept;

    //! Returns true of this box and other box overlaps.
    [[nodiscard]] bool Overlaps(const BoundingBox& other) const;

    //! Returns true if the input point is inside of this box.
    [[nodiscard]] bool Contains(const VectorType& point) const;

    //! Returns the mid-point of this box.
    [[nodiscard]] VectorType MidPoint() const;

    //! Returns diagonal length of this box.
    [[nodiscard]] T DiagonalLength() const;

    //! Returns squared diagonal length of this box.
    [[nodiscard]] T DiagonalLengthSquared() const;

    //! Resets this box to initial state (min=infinite, max=-infinite).
    void Reset();

    //! Merges this and other point.
    void Merge(const VectorType& point);

    //! Merges this and other boxes.
    void Merge(const BoundingBox& other);

    //! Expands this box by given delta to all direction.
    //! If the width of the box was x, expand(y) will result a box with
    //! x+y+y width.
    void Expand(T delta);

    //! Lower corner of the bounding box.
    VectorType lowerCorner;

    //! Upper corner of the bounding box.
    VectorType upperCorner;
};
}  // namespace CubbyFlow

#include <Core/Geometry/BoundingBox-Impl.hpp>

#endif