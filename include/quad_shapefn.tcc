// 4-node Quadrilateral Element
//! 3 0----------0 2
//!   |          |
//!   |          |
//!   |          |
//!   |          |
//! 0 0----------0 1

//! Return shape functions of a 4-node Quadrilateral Element at a given local
//! coordinate
template <>
inline Eigen::VectorXd mpm::QuadrilateralShapeFn<2, 4>::shapefn(
    const Eigen::Matrix<double, 2, 1>& xi) {
  Eigen::Matrix<double, 4, 1> shapefn;
  shapefn(0) = 0.25 * (1 - xi(0)) * (1 - xi(1));
  shapefn(1) = 0.25 * (1 + xi(0)) * (1 - xi(1));
  shapefn(2) = 0.25 * (1 + xi(0)) * (1 + xi(1));
  shapefn(3) = 0.25 * (1 - xi(0)) * (1 + xi(1));
  return shapefn;
}

//! Return gradient of shape functions of a 4-node Quadrilateral Element at a
//! given local coordinate
template <>
inline Eigen::MatrixXd mpm::QuadrilateralShapeFn<2, 4>::grad_shapefn(
    const Eigen::Matrix<double, 2, 1>& xi) {
  Eigen::Matrix<double, 4, 2> grad_shapefn;
  grad_shapefn(0, 0) = -0.25 * (1 - xi(1));
  grad_shapefn(1, 0) = 0.25 * (1 - xi(1));
  grad_shapefn(2, 0) = 0.25 * (1 + xi(1));
  grad_shapefn(3, 0) = -0.25 * (1 + xi(1));

  grad_shapefn(0, 1) = -0.25 * (1 - xi(0));
  grad_shapefn(1, 1) = -0.25 * (1 + xi(0));
  grad_shapefn(2, 1) = 0.25 * (1 + xi(0));
  grad_shapefn(3, 1) = 0.25 * (1 - xi(0));

  return grad_shapefn;
}

// 8-node Quadrilateral Element
//!  3      6       2
//!   0-----0-----0
//!   |           |
//!   |           |
//! 7 0           0 5
//!   |           |
//!   |           |
//!   0-----0-----0
//! 0       4       1

//! Return shape functions of a 8-node Quadrilateral Element at a given local
//! coordinate
template <>
inline Eigen::VectorXd mpm::QuadrilateralShapeFn<2, 8>::shapefn(
    const Eigen::Matrix<double, 2, 1>& xi) {
  Eigen::Matrix<double, 8, 1> shapefn;
  shapefn(0) = -0.25 * (1. - xi(0)) * (1. - xi(1)) * (xi(0) + xi(1) + 1.);
  shapefn(1) = 0.25 * (1. + xi(0)) * (1. - xi(1)) * (xi(0) - xi(1) - 1.);
  shapefn(2) = 0.25 * (1. + xi(0)) * (1. + xi(1)) * (xi(0) + xi(1) - 1.);
  shapefn(3) = -0.25 * (1. - xi(0)) * (1. + xi(1)) * (xi(0) - xi(1) + 1.);
  shapefn(4) = 0.5 * (1. - (xi(0) * xi(0))) * (1. - xi(1));
  shapefn(5) = 0.5 * (1. - (xi(1) * xi(1))) * (1. + xi(0));
  shapefn(6) = 0.5 * (1. - (xi(0) * xi(0))) * (1. + xi(1));
  shapefn(7) = 0.5 * (1. - (xi(1) * xi(1))) * (1. - xi(0));
  return shapefn;
}

//! Return gradient of shape functions of a 8-node Quadrilateral Element at a
//! given local coordinate
template <>
inline Eigen::MatrixXd mpm::QuadrilateralShapeFn<2, 8>::grad_shapefn(
    const Eigen::Matrix<double, 2, 1>& xi) {
  Eigen::Matrix<double, 8, 2> grad_shapefn;
  grad_shapefn(0, 0) = 0.25 * (2. * xi(0) + xi(1)) * (1. - xi(1));
  grad_shapefn(1, 0) = 0.25 * (2. * xi(0) - xi(1)) * (1. - xi(1));
  grad_shapefn(2, 0) = 0.25 * (2. * xi(0) + xi(1)) * (1. + xi(1));
  grad_shapefn(3, 0) = 0.25 * (2. * xi(0) - xi(1)) * (1. + xi(1));
  grad_shapefn(4, 0) = -xi(0) * (1. - xi(1));
  grad_shapefn(5, 0) = 0.5 * (1. - (xi(1) * xi(1)));
  grad_shapefn(6, 0) = -xi(0) * (1. + xi(1));
  grad_shapefn(7, 0) = -0.5 * (1. - (xi(1) * xi(1)));

  grad_shapefn(0, 1) = 0.25 * (2. * xi(1) + xi(0)) * (1. - xi(0));
  grad_shapefn(1, 1) = 0.25 * (2. * xi(1) - xi(0)) * (1. + xi(0));
  grad_shapefn(2, 1) = 0.25 * (2. * xi(1) + xi(0)) * (1. + xi(0));
  grad_shapefn(3, 1) = 0.25 * (2. * xi(1) - xi(0)) * (1. - xi(0));
  grad_shapefn(4, 1) = -0.5 * (1. - (xi(0) * xi(0)));
  grad_shapefn(5, 1) = -xi(1) * (1. + xi(0));
  grad_shapefn(6, 1) = 0.5 * (1 - (xi(0) * xi(0)));
  grad_shapefn(7, 1) = -xi(1) * (1. - xi(0));
  return grad_shapefn;
}

// 9-node Quadrilateral Element
//! 3       6       2
//!   0-----0-----0
//!   |           |
//!   |           |
//! 7 0   8 0     0 5
//!   |           |
//!   |           |
//!   0-----0-----0
//!  0      4       1

//! Return shape functions of a 9-node Quadrilateral Element at a given local
//! coordinate
template <>
inline Eigen::VectorXd mpm::QuadrilateralShapeFn<2, 9>::shapefn(
    const Eigen::Matrix<double, 2, 1>& xi) {
  Eigen::Matrix<double, 9, 1> shapefn;

  shapefn(0) = 0.25 * xi(0) * xi(1) * (xi(0) - 1.) * (xi(1) - 1.);
  shapefn(1) = 0.25 * xi(0) * xi(1) * (xi(0) + 1.) * (xi(1) - 1.);
  shapefn(2) = 0.25 * xi(0) * xi(1) * (xi(0) + 1.) * (xi(1) + 1.);
  shapefn(3) = 0.25 * xi(0) * xi(1) * (xi(0) - 1.) * (xi(1) + 1.);
  shapefn(4) = -0.5 * xi(1) * (xi(1) - 1.) * ((xi(0) * xi(0)) - 1.);
  shapefn(5) = -0.5 * xi(0) * (xi(0) + 1.) * ((xi(1) * xi(1)) - 1.);
  shapefn(6) = -0.5 * xi(1) * (xi(1) + 1.) * ((xi(0) * xi(0)) - 1.);
  shapefn(7) = -0.5 * xi(0) * (xi(0) - 1.) * ((xi(1) * xi(1)) - 1.);
  shapefn(8) = ((xi(0) * xi(0)) - 1.) * ((xi(1) * xi(1)) - 1.);

  return shapefn;
}

//! Return gradient of shape functions of a 9-node Quadrilateral Element at a
//! given local coordinate
template <>
inline Eigen::MatrixXd mpm::QuadrilateralShapeFn<2, 9>::grad_shapefn(
    const Eigen::Matrix<double, 2, 1>& xi) {
  Eigen::Matrix<double, 9, 2> grad_shapefn;
  // 9-noded
  grad_shapefn(0, 0) = 0.25 * xi(1) * (xi(1) - 1.) * (2 * xi(0) - 1.);
  grad_shapefn(1, 0) = 0.25 * xi(1) * (xi(1) - 1.) * (2 * xi(0) + 1.);
  grad_shapefn(2, 0) = 0.25 * xi(1) * (xi(1) + 1.) * (2 * xi(0) + 1.);
  grad_shapefn(3, 0) = 0.25 * xi(1) * (xi(1) + 1.) * (2 * xi(0) - 1.);
  grad_shapefn(4, 0) = -xi(0) * xi(1) * (xi(1) - 1.);
  grad_shapefn(5, 0) = -0.5 * (2. * xi(0) + 1.) * ((xi(1) * xi(1)) - 1.);
  grad_shapefn(6, 0) = -xi(0) * xi(1) * (xi(1) + 1.);
  grad_shapefn(7, 0) = -0.5 * (2. * xi(0) - 1.) * ((xi(1) * xi(1)) - 1.);
  grad_shapefn(8, 0) = 2. * xi(0) * ((xi(1) * xi(1)) - 1.);
  grad_shapefn(0, 1) = 0.25 * xi(0) * (xi(0) - 1.) * (2. * xi(1) - 1.);
  grad_shapefn(1, 1) = 0.25 * xi(0) * (xi(0) + 1.) * (2. * xi(1) - 1.);
  grad_shapefn(2, 1) = 0.25 * xi(0) * (xi(0) + 1.) * (2. * xi(1) + 1.);
  grad_shapefn(3, 1) = 0.25 * xi(0) * (xi(0) - 1.) * (2. * xi(1) + 1.);
  grad_shapefn(4, 1) = -0.5 * (2. * xi(1) - 1.) * ((xi(0) * xi(0)) - 1.);
  grad_shapefn(5, 1) = -xi(0) * xi(1) * (xi(0) + 1.);
  grad_shapefn(6, 1) = -0.5 * (2. * xi(1) + 1.) * ((xi(0) * xi(0)) - 1.);
  grad_shapefn(7, 1) = -xi(0) * xi(1) * (xi(0) - 1.);
  grad_shapefn(8, 1) = 2. * xi(1) * ((xi(0) * xi(0)) - 1.);
  return grad_shapefn;
}

//! Return the B-matrix of a Quadrilateral Element at a given local
//! coordinate
template <unsigned Tdim, unsigned Tnfunctions>
inline std::vector<Eigen::MatrixXd>
    mpm::QuadrilateralShapeFn<Tdim, Tnfunctions>::bmatrix(const VectorDim& xi) {

  Eigen::MatrixXd grad_shapefn = this->grad_shapefn(xi);

  // B-Matrix
  std::vector<Eigen::MatrixXd> bmatrix;
  bmatrix.reserve(Tnfunctions);

  for (unsigned i = 0; i < Tnfunctions; ++i) {
    Eigen::Matrix<double, 3, Tdim> bi;
    // clang-format off
    bi(0, 0) = grad_shapefn(i, 0); bi(0, 1) = 0.;
    bi(1, 0) = 0.;                 bi(1, 1) = grad_shapefn(i, 1);
    bi(2, 0) = grad_shapefn(i, 1); bi(2, 1) = grad_shapefn(i, 0);
    bmatrix.push_back(bi);
    // clang-format on
  }
  return bmatrix;
}

//! Return the corner indices of a cell to calculate the cell volume
template <unsigned Tdim, unsigned Tnfunctions>
inline Eigen::VectorXi
    mpm::QuadrilateralShapeFn<Tdim, Tnfunctions>::corner_indices() {
  Eigen::Matrix<int, 4, 1> indices;
  indices << 0, 1, 2, 3;
  return indices;
}

//! Return indices of a sub-tetrahedrons in a volume
template <unsigned Tdim, unsigned Tnfunctions>
inline Eigen::MatrixXi
    mpm::QuadrilateralShapeFn<Tdim, Tnfunctions>::inhedron_indices() {
  Eigen::Matrix<int, 4, Tdim, Eigen::RowMajor> indices;

  // clang-format off
  indices << 0, 1,
             1, 2,
             2, 3,
             3, 0;
  //clang-format on
  return indices;
}
  
