#include "tensor3d.hpp"

template <typename T>
Tensor3D<T>::Tensor3D(const size_t nx, const size_t ny, const size_t nz) {
    this->nx_ = nx;
    this->ny_ = ny;
    this->nz_ = nz;
    this->data_ = new T[nx * ny * nz];
    this->owns_data_ = true;
}

template <typename T>
Tensor3D<T>::Tensor3D(const size_t nx, const size_t ny, const size_t nz, const T* data, const bool make_copy) {
    this->nx_ = nx;
    this->ny_ = ny;
    this->nz_ = nz;
    size_t size = nx * ny * nz;
    if (make_copy) {
        this->data_ = new T[size];
        std::memcpy(this->data_, data, size * sizeof(T));
        this->owns_data_ = true;
    }
    else {
        this->data_ = data;
        this->owns_data_ = false;
    }
}

template <typename T>
Tensor3D<T>::Tensor3D(const Tensor3D& tensor3d) {
    this->nx_ = tensor3d.GetLength(Dimension::X);
    this->ny_ = tensor3d.GetLength(Dimension::Y);
    this->nz_ = tensor3d.GetLength(Dimension::Z);
    this->data_ = new T[tensor3d.size()];
    if (tensor3d.data()) {
        std::memcpy(this->data_, tensor3d.data(), tensor3d.size() * sizeof(T));
        this->owns_data_ = true;
    }
}

template <typename T>
Tensor3D<T>::~Tensor3D() {
    if (this->owns_data_) {
        delete this->data_;
    }
}

template <typename T>
size_t Tensor3D<T>::size() const{
    return this->nx_ * this->ny_ * this->nz_;
}

template <typename T>
T* Tensor3D<T>::data() const{
    return this->data_;
}

template <typename T>
size_t Tensor3D<T>::GetLength(Dimension dimension) const{
    switch (dimension){
        case Dimension::X:
            return this->nx_;
        case Dimension::Y:
            return this->ny_;
        case Dimension::Z:
            return this->nz_;
    }
    return 0;
}

template <typename T>
Tensor3D<T> Tensor3D<T>::Transpose(Dimension dim1, Dimension dim2, Dimension dim3) {
    assert(dim1 != dim2 && dim1 != dim3 && dim2 != dim3 &&
        "Expected distinct dimentions for transpose");
    auto transposed_value = [&](int i, int j, int k) -> T& {
        // XYZ -> XYZ
        if (dim1 == Dimension::X && dim2 == Dimension::Y && dim3 == Dimension::Z)
            return (*this)(i,j,k);
        // XYZ -> XZY
        if (dim1 == Dimension::X && dim2 == Dimension::Z && dim3 == Dimension::Y)
            return (*this)(i,k,j);
        // XYZ -> YXZ
        if (dim1 == Dimension::Y && dim2 == Dimension::X && dim3 == Dimension::Z)
            return (*this)(j,i,k);
        // XYZ -> YZX
        if (dim1 == Dimension::Y && dim2 == Dimension::Z && dim3 == Dimension::X)
            return (*this)(j,k,i);
        // XYZ -> ZXY
        if (dim1 == Dimension::Z && dim2 == Dimension::X && dim3 == Dimension::Y)
            return (*this)(k,i,j);
        // XYZ -> ZYX
        if (dim1 == Dimension::Z && dim2 == Dimension::Y && dim3 == Dimension::X)
            return (*this)(k,j,i);
    };

    Tensor3D tensor(GetLength(dim1), GetLength(dim2), GetLength(dim3));
    for (int i=0; i<tensor.GetLength(Dimension::X); i++) {
        for (int j=0; j<tensor.GetLength(Dimension::Y); j++) {
            for (int k=0; k<tensor.GetLength(Dimension::Z); k++) {
                tensor(i,j,k) = transposed_value(i,j,k);
            }
        }
    }
}

template <typename T>
T& Tensor3D<T>::operator() (size_t i, size_t j, size_t k) {
    assert(i < this->nx_ && j < this->ny_ && k < this->nz_ &&
        "tensor(i,j,k) access operation failed due to index/es going out-of-bounds");
    return this->data_[i + j * nx_ + k * nx_ * ny_];
}