// This code is based on Jet framework.
// Copyright (c) 2018 Doyub Kim
// CubbyFlow is voxel-based fluid simulation engine for computer games.
// Copyright (c) 2020 CubbyFlow Team
// Core Part: Chris Ohk, Junwoo Hwang, Jihong Sin, Seungwoo Yoo
// AI Part: Dongheon Cho, Minseo Kim
// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef CUBBYFLOW_ARRAY2_HPP
#define CUBBYFLOW_ARRAY2_HPP

#include <Core/Array/Array.hpp>
#include <Core/Array/ArrayAccessor2.hpp>
#include <Core/Geometry/Size2.hpp>

#include <vector>

namespace CubbyFlow
{
//!
//! \brief 2-D array class.
//!
//! This class represents 2-D array data structure. Internally, the 2-D data is
//! mapped to a linear array such that (i, j) element is actually stored at
//! (i + (width * j))th element of the linear array. This mapping means
//! iterating i first and j next will give better performance such as:
//!
//! \code{.cpp}
//! Array<int, 2> array;
//! for (size_t j = 0; j < array.height(); ++j)
//! {
//!     for (size_t i = 0; i < array.width(); ++i)
//!     {
//!         // Read or write array(i, j)
//!     }
//! }
//! \endcode
//!
//! \tparam T - Type to store in the array.
//!
template <typename T>
class Array<T, 2> final
{
 public:
    using ContainerType = std::vector<T>;
    using Iterator = typename ContainerType::iterator;
    using ConstIterator = typename ContainerType::const_iterator;

    //! Default constructor.
    Array() = default;

    //! Constructs 2-D array with given \p size and fill it with \p initVal.
    //! \param size Initial size of the array.
    //! \param initVal Initial value of each array element.
    explicit Array(const Size2& size, const T& initVal = T());

    //! Constructs 2-D array with size \p width x \p height and fill it with
    //! \p initVal.
    //! \param width Initial width of the array.
    //! \param height Initial height of the array.
    //! \param initVal Initial value of each array element.
    Array(size_t width, size_t height, const T& initVal = T());

    //!
    //! \brief Constructs 2-D array with given initializer list \p list.
    //!
    //! This constructor will build 2-D array with given initializer list \p
    //! list such as
    //!
    //! \code{.cpp}
    //! Array<int, 2> arr =
    //! {
    //!     {1, 2, 4},
    //!     {9, 3, 5}
    //! };
    //! \endcode
    //!
    //! Note the initializer also has 2-D structure. The code above will
    //! construct 3 x 2 array.
    //!
    //! \param list Initializer list that should be copy to the new array.
    //!
    Array(const std::initializer_list<std::initializer_list<T>>& list);

    //! Copy constructor.
    Array(const Array& other);

    //! Move constructor.
    Array(Array&& other) noexcept;

    //! Default destructor.
    ~Array() = default;

    //! Sets entire array with given \p value.
    void Set(const T& value);

    //! Copies given array \p other to this array.
    void Set(const Array& other);

    //!
    //! Copies given initializer list \p list to this array.
    //!
    //! This function copies given initializer list \p list to the array such as
    //!
    //! \code{.cpp}
    //! Array<int, 2> arr;
    //! arr =
    //! {
    //!     {1, 2, 4},
    //!     {9, 3, 5}
    //! };
    //! \endcode
    //!
    //! Note the initializer also has 2-D structure. The code above will
    //! build 3 x 2 array.
    //!
    //! \param list Initializer list that should be copy to the new array.
    //!
    void Set(const std::initializer_list<std::initializer_list<T>>& list);

    //! Clears the array and resizes to zero.
    void Clear();

    //! Resizes the array with \p size and fill the new element with \p initVal.
    void Resize(const Size2& size, const T& initVal = T());

    //! Resizes the array with size \p width x \p height and fill the new
    //! element with \p initVal.
    void Resize(size_t width, size_t height, const T& initVal = T());

    //!
    //! \brief Returns the reference to the i-th element.
    //!
    //! This function returns the reference to the i-th element of the array
    //! where i is the index of linearly mapped elements such that
    //! i = x + (width * y) (x and y are the 2-D coordinates of the element).
    //!
    T& At(size_t i);

    //!
    //! \brief Returns the const reference to the i-th element.
    //!
    //! This function returns the const reference to the i-th element of the
    //! array where i is the index of linearly mapped elements such that
    //! i = x + (width * y) (x and y are the 2-D coordinates of the element).
    //!
    [[nodiscard]] const T& At(size_t i) const;

    //! Returns the reference to the element at (pt.x, pt.y).
    T& At(const Point2UI& pt);

    //! Returns the const reference to the element at (pt.x, pt.y).
    [[nodiscard]] const T& At(const Point2UI& pt) const;

    //! Returns the reference to the element at (i, j).
    T& At(size_t i, size_t j);

    //! Returns the const reference to the element at (i, j).
    [[nodiscard]] const T& At(size_t i, size_t j) const;

    //! Returns the size of the array.
    [[nodiscard]] Size2 size() const;

    //! Returns the width of the array.
    [[nodiscard]] size_t Width() const;

    //! Returns the height of the array.
    [[nodiscard]] size_t Height() const;

    //! Returns the raw pointer to the array data.
    T* data();

    //! Returns the const raw pointer to the array data.
    const T* data() const;

    //! Returns the begin iterator of the array.
    Iterator begin();

    //! Returns the begin const iterator of the array.
    [[nodiscard]] ConstIterator begin() const;

    //! Returns the end iterator of the array.
    Iterator end();

    //! Returns the end const iterator of the array.
    [[nodiscard]] ConstIterator end() const;

    //! Returns the array accessor.
    ArrayAccessor2<T> Accessor();

    //! Returns the const array accessor.
    ConstArrayAccessor2<T> ConstAccessor() const;

    //! Swaps the content of the array with \p other array.
    void Swap(Array& other);

    //!
    //! \brief Iterates the array and invoke given \p func for each index.
    //!
    //! This function iterates the array elements and invoke the callback
    //! function \p func. The callback function takes array's element as its
    //! input. The order of execution will be the same as the nested for-loop
    //! below:
    //!
    //! \code{.cpp}
    //! Array<int, 2> array;
    //! for (size_t j = 0; j < array.height(); ++j)
    //! {
    //!     for (size_t i = 0; i < array.width(); ++i)
    //!     {
    //!         func(array(i, j));
    //!     }
    //! }
    //! \endcode
    //!
    //! Below is the sample usage:
    //!
    //! \code{.cpp}
    //! Array<int, 2> array(100, 200, 4);
    //! array.ForEach([](int elem)
    //! {
    //!     printf("%d\n", elem);
    //! });
    //! \endcode
    //!
    template <typename Callback>
    void ForEach(Callback func) const;

    //!
    //! \brief Iterates the array and invoke given \p func for each index.
    //!
    //! This function iterates the array elements and invoke the callback
    //! function \p func. The callback function takes two parameters which are
    //! the (i, j) indices of the array. The order of execution will be the same
    //! as the nested for-loop below:
    //!
    //! \code{.cpp}
    //! Array<int, 2> array;
    //! for (size_t j = 0; j < array.height(); ++j)
    //! {
    //!     for (size_t i = 0; i < array.width(); ++i)
    //!     {
    //!         func(i, j);
    //!     }
    //! }
    //! \endcode
    //!
    //! Below is the sample usage:
    //!
    //! \code{.cpp}
    //! Array<int, 2> array(10, 20, 4);
    //! array.ForEachIndex([&](size_t i, size_t j)
    //! {
    //!     array(i, j) = 4.f * i + 7.f * j + 1.5f;
    //! });
    //! \endcode
    //!
    template <typename Callback>
    void ForEachIndex(Callback func) const;

    //!
    //! \brief Iterates the array and invoke given \p func for each index in
    //!     parallel.
    //!
    //! This function iterates the array elements and invoke the callback
    //! function \p func. The callback function takes array's element as its
    //! input. The order of execution will be non-deterministic since it runs in
    //! parallel. Below is the sample usage:
    //!
    //! \code{.cpp}
    //! Array<int, 2> array(100, 200, 4);
    //! array.ParallelForEach([](int& elem)
    //! {
    //!     elem *= 2;
    //! });
    //! \endcode
    //!
    //! The parameter type of the callback function doesn't have to be T&, but
    //! const T& or T can be used as well.
    //!
    template <typename Callback>
    void ParallelForEach(Callback func);

    //!
    //! \brief Iterates the array and invoke given \p func for each index in
    //!     parallel using multi-threading.
    //!
    //! This function iterates the array elements and invoke the callback
    //! function \p func in parallel using multi-threading. The callback
    //! function takes two parameters which are the (i, j) indices of the array.
    //! The order of execution will be non-deterministic since it runs in
    //! parallel. Below is the sample usage:
    //!
    //! \code{.cpp}
    //! Array<int, 2> array(100, 200, 4);
    //! array.ParallelForEachIndex([&](size_t i, size_t j)
    //! {
    //!     array(i, j) *= 2;
    //! });
    //! \endcode
    //!
    template <typename Callback>
    void ParallelForEachIndex(Callback func) const;

    //!
    //! \brief Returns the reference to the i-th element.
    //!
    //! This function returns the reference to the i-th element of the array
    //! where i is the index of linearly mapped elements such that
    //! i = x + (width * y) (x and y are the 2-D coordinates of the element).
    //!
    //! \see Array<T, 2>::at
    //!
    T& operator[](size_t i);

    //!
    //! \brief Returns the const reference to the i-th element.
    //!
    //! This function returns the const reference to the i-th element of the
    //! array where i is the index of linearly mapped elements such that
    //! i = x + (width * y) (x and y are the 2-D coordinates of the element).
    //!
    //! \see Array<T, 2>::at
    //!
    const T& operator[](size_t i) const;

    //! Returns the reference to the element at (pt.x, pt.y).
    T& operator()(const Point2UI& pt);

    //! Returns the const reference to the element at (pt.x, pt.y).
    const T& operator()(const Point2UI& pt) const;

    //! Returns the reference to the element at (i, j).
    T& operator()(size_t i, size_t j);

    //! Returns the const reference to the element at (i, j).
    const T& operator()(size_t i, size_t j) const;

    //! Sets entire array with given \p other.
    Array& operator=(const T& other);

    //! Copies given array \p other to this array.
    Array& operator=(const Array& other);

    //! Moves given array \p other to this array.
    Array& operator=(Array&& other) noexcept;

    //!
    //! Copies given initializer list \p list to this array.
    //!
    //! This function copies given initializer list \p list to the array such as
    //!
    //! \code{.cpp}
    //! Array<int, 2> arr;
    //! arr =
    //! {
    //!     {1, 2, 4},
    //!     {9, 3, 5}
    //! };
    //! \endcode
    //!
    //! Note the initializer also has 2-D structure. The code above will
    //! build 3 x 2 array.
    //!
    //! \param list Initializer list that should be copy to the new array.
    //!
    Array& operator=(
        const std::initializer_list<std::initializer_list<T>>& list);

    //! Casts to array accessor.
    operator ArrayAccessor2<T>();

    //! Casts to const array accessor.
    operator ConstArrayAccessor2<T>() const;

 private:
    Size2 m_size;
    std::vector<T> m_data;
};

//! Type alias for 2-D array.
template <typename T>
using Array2 = Array<T, 2>;
}  // namespace CubbyFlow

#include <Core/Array/Array2-Impl.hpp>

#endif