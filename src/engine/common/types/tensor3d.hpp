#ifndef __TYPE_TENSOR3D__
#define __TYPE_TENSOR3D__

#include <string>
#include <cassert>

template <typename T>
class Tensor3D {
public:
    enum Dimension{X,Y,Z};

    Tensor3D(const size_t nx, const size_t ny, const size_t nz);
    Tensor3D(const size_t nx, const size_t ny, const size_t nz, const T* data, const bool make_copy = true);
    Tensor3D(const Tensor3D& tensor3d);
    ~Tensor3D();

    size_t size() const;
    T* data() const;
    size_t GetLength(Dimension dimension) const;

    Tensor3D<T> Transpose(Dimension dim1, Dimension dim2, Dimension dim3);

    T& operator() (size_t i, size_t j, size_t k);

private:
    T* data_;
    bool owns_data_;
    size_t nx_, ny_, nz_;
};
#endif //__TYPE_TENSOR3D__
