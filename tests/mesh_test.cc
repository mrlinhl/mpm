#include <limits>
#include <memory>

#include "Eigen/Dense"
#include "catch.hpp"

#include "hex_shapefn.h"
#include "mesh.h"
#include "node.h"
#include "quad_shapefn.h"
#include "shapefn.h"

//! \brief Check mesh class for 2D case
TEST_CASE("Mesh is checked for 2D case", "[mesh][2D]") {
  // Dimension
  const unsigned Dim = 2;
  // Degrees of freedom
  const unsigned Dof = 2;
  // Number of phases
  const unsigned Nphases = 1;
  // Number of nodes per cell
  const unsigned Nnodes = 4;
  // Tolerance
  const double Tolerance = 1.E-9;

  //! Check Mesh IDs
  SECTION("Check mesh ids") {
    //! Check for id = 0
    SECTION("Mesh id is zero") {
      unsigned id = 0;
      auto mesh = std::make_shared<mpm::Mesh<Dim>>(id);
      REQUIRE(mesh->id() == 0);
    }

    SECTION("Mesh id is positive") {
      //! Check for id is a positive value
      unsigned id = std::numeric_limits<unsigned>::max();
      auto mesh = std::make_shared<mpm::Mesh<Dim>>(id);
      REQUIRE(mesh->id() == std::numeric_limits<unsigned>::max());
    }
  }

  SECTION("Add neighbours") {
    auto mesh = std::make_shared<mpm::Mesh<Dim>>(0);
    auto neighbourmesh = std::make_shared<mpm::Mesh<Dim>>(1);
    REQUIRE(mesh->nneighbours() == 0);
    mesh->add_neighbour(0, neighbourmesh);
    REQUIRE(mesh->nneighbours() == 1);
  }

  // Check add / remove particle
  SECTION("Check add / remove particle functionality") {
    // Particle 1
    mpm::Index id1 = 0;
    Eigen::Vector2d coords;
    coords.setZero();
    std::shared_ptr<mpm::ParticleBase<Dim>> particle1 =
        std::make_shared<mpm::Particle<Dim, Nphases>>(id1, coords);

    // Particle 2
    mpm::Index id2 = 1;
    std::shared_ptr<mpm::ParticleBase<Dim>> particle2 =
        std::make_shared<mpm::Particle<Dim, Nphases>>(id2, coords);

    auto mesh = std::make_shared<mpm::Mesh<Dim>>(0);
    // Check mesh is active
    REQUIRE(mesh->status() == false);

    // Add particle 1 and check status
    bool status1 = mesh->add_particle(particle1);
    REQUIRE(status1 == true);
    // Add particle 2 and check status
    bool status2 = mesh->add_particle(particle2);
    REQUIRE(status2 == true);
    // Add particle 2 again and check status
    bool status3 = mesh->add_particle(particle2);
    REQUIRE(status3 == false);

    // Check mesh is active
    REQUIRE(mesh->status() == true);
    // Check number of particles in mesh
    REQUIRE(mesh->nparticles() == 2);

    // Update coordinates
    Eigen::Vector2d coordinates;
    coordinates << 1., 1.;
    // Check iterate over functionality
    mesh->iterate_over_particles(
        std::bind(&mpm::ParticleBase<Dim>::assign_coordinates,
                  std::placeholders::_1, coordinates));

    // Particle 1
    {
      // Check if nodal coordinate update has gone through
      auto check_coords = particle1->coordinates();
      // Check if coordinates for each particle is zero
      for (unsigned i = 0; i < check_coords.size(); ++i)
        REQUIRE(check_coords[i] == Approx(1.).epsilon(Tolerance));
    }
    // Particle 2
    {
      // Check if nodal coordinate update has gone through
      auto check_coords = particle2->coordinates();
      // Check if coordinates for each particle is zero
      for (unsigned i = 0; i < check_coords.size(); ++i)
        REQUIRE(check_coords[i] == Approx(1.).epsilon(Tolerance));
    }

    // Remove particle 2 and check status
    bool remove_status = mesh->remove_particle(particle2);
    REQUIRE(remove_status == true);
    // Check number of particles in mesh
    REQUIRE(mesh->nparticles() == 1);
  }

  // Check add / remove node
  SECTION("Check add / remove node functionality") {
    // Node 1
    mpm::Index id1 = 0;
    Eigen::Vector2d coords;
    coords.setZero();
    std::shared_ptr<mpm::NodeBase<Dim>> node1 =
        std::make_shared<mpm::Node<Dim, Dof, Nphases>>(id1, coords);

    // Node 2
    mpm::Index id2 = 1;
    std::shared_ptr<mpm::NodeBase<Dim>> node2 =
        std::make_shared<mpm::Node<Dim, Dof, Nphases>>(id2, coords);

    // Create a mesh
    auto mesh = std::make_shared<mpm::Mesh<Dim>>(0);
    // Check mesh is active
    REQUIRE(mesh->status() == false);

    // Add node 1 and check status
    bool status1 = mesh->add_node(node1);
    REQUIRE(status1 == true);
    // Add node 2 and check status
    bool status2 = mesh->add_node(node2);
    REQUIRE(status2 == true);
    // Add node 2 again and check status
    bool status3 = mesh->add_node(node2);
    REQUIRE(status3 == false);

    // Check number of nodes in mesh
    REQUIRE(mesh->nnodes() == 2);

    // Update coordinates
    Eigen::Vector2d coordinates;
    coordinates << 1., 1.;
    // Check iterate over functionality
    mesh->iterate_over_nodes(std::bind(&mpm::NodeBase<Dim>::assign_coordinates,
                                       std::placeholders::_1, coordinates));

    // Node 1
    {
      // Check if nodal coordinate update has gone through
      auto check_coords = node1->coordinates();
      // Check if coordinates for each node is zero
      for (unsigned i = 0; i < check_coords.size(); ++i)
        REQUIRE(check_coords[i] == Approx(1.).epsilon(Tolerance));
    }
    // Node 2
    {
      // Check if nodal coordinate update has gone through
      auto check_coords = node2->coordinates();
      // Check if coordinates for each node is zero
      for (unsigned i = 0; i < check_coords.size(); ++i)
        REQUIRE(check_coords[i] == Approx(1.).epsilon(Tolerance));
    }

    // Remove node 2 and check status
    bool remove_status = mesh->remove_node(node2);
    REQUIRE(remove_status == true);
    // Check number of nodes in mesh
    REQUIRE(mesh->nnodes() == 1);
  }

  // Check add / remove cell
  SECTION("Check add / remove cell functionality") {
    // Cell 1
    mpm::Index id1 = 0;
    Eigen::Vector2d coords;
    coords.setZero();
    auto cell1 = std::make_shared<mpm::Cell<Dim>>(id1, Nnodes);

    // Cell 2
    mpm::Index id2 = 1;
    auto cell2 = std::make_shared<mpm::Cell<Dim>>(id2, Nnodes);

    auto mesh = std::make_shared<mpm::Mesh<Dim>>(0);
    // Check mesh is active
    REQUIRE(mesh->status() == false);

    // Add cell 1 and check status
    bool status1 = mesh->add_cell(cell1);
    REQUIRE(status1 == true);
    // Add cell 2 and check status
    bool status2 = mesh->add_cell(cell2);
    REQUIRE(status2 == true);
    // Add cell 2 again and check status
    bool status3 = mesh->add_cell(cell2);
    REQUIRE(status3 == false);

    // Check number of cells in mesh
    REQUIRE(mesh->ncells() == 2);

    // Check iterate over functionality
    mesh->iterate_over_cells(
        std::bind(&mpm::Cell<Dim>::nnodes, std::placeholders::_1));

    // Remove cell 2 and check status
    bool remove_status = mesh->remove_cell(cell2);
    REQUIRE(remove_status == true);
    // Check number of cells in mesh
    REQUIRE(mesh->ncells() == 1);
  }

  SECTION("Check particle is in cell") {
    // Cell 1
    mpm::Index id1 = 0;
    Eigen::Vector2d coords;
    coords.setZero();

    // Mesh
    auto mesh = std::make_shared<mpm::Mesh<Dim>>(0);
    // Check mesh is inactive (false)
    REQUIRE(mesh->status() == false);

    // Define nodes
    std::shared_ptr<mpm::NodeBase<Dim>> node0 =
        std::make_shared<mpm::Node<Dim, Dof, Nphases>>(0, coords);

    // Add node 0 and check status
    bool node_status0 = mesh->add_node(node0);
    REQUIRE(node_status0 == true);

    coords << 2., 0.;
    std::shared_ptr<mpm::NodeBase<Dim>> node1 =
        std::make_shared<mpm::Node<Dim, Dof, Nphases>>(1, coords);

    // Add node 1 and check status
    bool node_status1 = mesh->add_node(node1);
    REQUIRE(node_status1 == true);

    coords << 2., 2.;
    std::shared_ptr<mpm::NodeBase<Dim>> node2 =
        std::make_shared<mpm::Node<Dim, Dof, Nphases>>(2, coords);

    // Add node 2 and check status
    bool node_status2 = mesh->add_node(node2);
    REQUIRE(node_status2 == true);

    coords << 0., 2.;
    std::shared_ptr<mpm::NodeBase<Dim>> node3 =
        std::make_shared<mpm::Node<Dim, Dof, Nphases>>(3, coords);

    // Add node 3 and check status
    bool node_status3 = mesh->add_node(node3);
    REQUIRE(node_status3 == true);

    // Create cell1
    coords.setZero();
    auto cell1 = std::make_shared<mpm::Cell<Dim>>(id1, Nnodes);

    // Add nodes to cell
    cell1->add_node(0, node0);
    cell1->add_node(1, node1);
    cell1->add_node(2, node2);
    cell1->add_node(3, node3);

    // Assign quadrilateral shapefn to cell
    std::shared_ptr<mpm::ShapeFn<Dim>> shapefn =
        std::make_shared<mpm::QuadrilateralShapeFn<Dim, 4>>();
    cell1->shapefn(shapefn);

    // Compute cell volume
    cell1->compute_volume();

    // Add cell 1 and check status
    bool cell_status1 = mesh->add_cell(cell1);
    REQUIRE(cell_status1 == true);

    // Particle 1
    coords << 1.0, 1.0;
    std::shared_ptr<mpm::ParticleBase<Dim>> particle1 =
        std::make_shared<mpm::Particle<Dim, Nphases>>(0, coords);

    // Particle 2
    coords << 1.5, 1.5;
    std::shared_ptr<mpm::ParticleBase<Dim>> particle2 =
        std::make_shared<mpm::Particle<Dim, Nphases>>(1, coords);

    // Add particle 1 and check status
    bool particle_status1 = mesh->add_particle(particle1);
    REQUIRE(particle_status1 == true);
    // Add particle 2 and check status
    bool particle_status2 = mesh->add_particle(particle2);
    REQUIRE(particle_status2 == true);

    // Check mesh is active
    REQUIRE(mesh->status() == true);

    // Locate particles in a mesh
    mesh->locate_particles_mesh();

    // Check location of particle 1
    REQUIRE(particle1->cell_id() == 0);
    // Check location of particle 2
    REQUIRE(particle2->cell_id() == 0);
  }
}

//! \brief Check mesh class for 3D case
TEST_CASE("Mesh is checked for 3D case", "[mesh][3D]") {
  // Dimension
  const unsigned Dim = 3;
  // Degrees of freedom
  const unsigned Dof = 6;
  // Number of phases
  const unsigned Nphases = 1;
  // Number of nodes per cell
  const unsigned Nnodes = 8;
  // Tolerance
  const double Tolerance = 1.E-9;

  //! Check Mesh IDs
  SECTION("Check mesh ids") {
    //! Check for id = 0
    SECTION("Mesh id is zero") {
      unsigned id = 0;
      auto mesh = std::make_shared<mpm::Mesh<Dim>>(id);
      REQUIRE(mesh->id() == 0);
    }

    SECTION("Mesh id is positive") {
      //! Check for id is a positive value
      unsigned id = std::numeric_limits<unsigned>::max();
      auto mesh = std::make_shared<mpm::Mesh<Dim>>(id);
      REQUIRE(mesh->id() == std::numeric_limits<unsigned>::max());
    }
  }

  SECTION("Add neighbours") {
    auto mesh = std::make_shared<mpm::Mesh<Dim>>(0);
    auto neighbourmesh = std::make_shared<mpm::Mesh<Dim>>(1);
    REQUIRE(mesh->nneighbours() == 0);
    mesh->add_neighbour(0, neighbourmesh);
    REQUIRE(mesh->nneighbours() == 1);
  }

  // Check add / remove particle
  SECTION("Check add / remove particle functionality") {
    // Particle 1
    mpm::Index id1 = 0;
    Eigen::Vector3d coords;
    coords.setZero();
    std::shared_ptr<mpm::ParticleBase<Dim>> particle1 =
        std::make_shared<mpm::Particle<Dim, Nphases>>(id1, coords);

    // Particle 2
    mpm::Index id2 = 1;
    std::shared_ptr<mpm::ParticleBase<Dim>> particle2 =
        std::make_shared<mpm::Particle<Dim, Nphases>>(id2, coords);

    auto mesh = std::make_shared<mpm::Mesh<Dim>>(0);
    // Check mesh is active
    REQUIRE(mesh->status() == false);

    // Add particle 1 and check status
    bool status1 = mesh->add_particle(particle1);
    REQUIRE(status1 == true);
    // Add particle 2 and check status
    bool status2 = mesh->add_particle(particle2);
    REQUIRE(status2 == true);
    // Add particle 2 again and check status
    bool status3 = mesh->add_particle(particle2);
    REQUIRE(status3 == false);

    // Check mesh is active
    REQUIRE(mesh->status() == true);
    // Check number of particles in mesh
    REQUIRE(mesh->nparticles() == 2);

    // Remove particle 2 and check status
    bool remove_status = mesh->remove_particle(particle2);
    REQUIRE(remove_status == true);
    // Check number of particles in mesh
    REQUIRE(mesh->nparticles() == 1);
  }

  // Check add / remove node
  SECTION("Check add / remove node functionality") {
    // Node 1
    mpm::Index id1 = 0;
    Eigen::Vector3d coords;
    coords.setZero();
    std::shared_ptr<mpm::NodeBase<Dim>> node1 =
        std::make_shared<mpm::Node<Dim, Dof, Nphases>>(id1, coords);

    // Node 2
    mpm::Index id2 = 1;
    std::shared_ptr<mpm::NodeBase<Dim>> node2 =
        std::make_shared<mpm::Node<Dim, Dof, Nphases>>(id2, coords);

    auto mesh = std::make_shared<mpm::Mesh<Dim>>(0);
    // Check mesh is active
    REQUIRE(mesh->status() == false);

    // Add node 1 and check status
    bool status1 = mesh->add_node(node1);
    REQUIRE(status1 == true);
    // Add node 2 and check status
    bool status2 = mesh->add_node(node2);
    REQUIRE(status2 == true);
    // Add node 2 again and check status
    bool status3 = mesh->add_node(node2);
    REQUIRE(status3 == false);

    // Check number of nodes in mesh
    REQUIRE(mesh->nnodes() == 2);

    // Update coordinates
    Eigen::Vector3d coordinates;
    coordinates << 7., 7., 7.;
    // Check iterate over functionality
    mesh->iterate_over_nodes(std::bind(&mpm::NodeBase<Dim>::assign_coordinates,
                                       std::placeholders::_1, coordinates));

    // Node 1
    {
      // Check if nodal coordinate update has gone through
      auto check_coords = node1->coordinates();
      // Check if coordinates for each node is zero
      for (unsigned i = 0; i < check_coords.size(); ++i)
        REQUIRE(check_coords[i] == Approx(7.).epsilon(Tolerance));
    }
    // Node 2
    {
      // Check if nodal coordinate update has gone through
      auto check_coords = node2->coordinates();
      // Check if coordinates for each node is zero
      for (unsigned i = 0; i < check_coords.size(); ++i)
        REQUIRE(check_coords[i] == Approx(7.).epsilon(Tolerance));
    }

    // Remove node 2 and check status
    bool remove_status = mesh->remove_node(node2);
    REQUIRE(remove_status == true);
    // Check number of nodes in mesh
    REQUIRE(mesh->nnodes() == 1);
  }

  // Check add / remove cell
  SECTION("Check add / remove cell functionality") {
    // Cell 1
    mpm::Index id1 = 0;
    Eigen::Vector3d coords;
    coords.setZero();
    auto cell1 = std::make_shared<mpm::Cell<Dim>>(id1, Nnodes);

    // Cell 2
    mpm::Index id2 = 1;
    auto cell2 = std::make_shared<mpm::Cell<Dim>>(id2, Nnodes);

    auto mesh = std::make_shared<mpm::Mesh<Dim>>(0);
    // Check mesh is active
    REQUIRE(mesh->status() == false);

    // Add cell 1 and check status
    bool status1 = mesh->add_cell(cell1);
    REQUIRE(status1 == true);
    // Add cell 2 and check status
    bool status2 = mesh->add_cell(cell2);
    REQUIRE(status2 == true);
    // Add cell 2 again and check status
    bool status3 = mesh->add_cell(cell2);
    REQUIRE(status3 == false);

    // Check number of cells in mesh
    REQUIRE(mesh->ncells() == 2);

    // Check iterate over functionality
    mesh->iterate_over_cells(
        std::bind(&mpm::Cell<Dim>::nnodes, std::placeholders::_1));

    // Remove cell 2 and check status
    bool remove_status = mesh->remove_cell(cell2);
    REQUIRE(remove_status == true);
    // Check number of cells in mesh
    REQUIRE(mesh->ncells() == 1);
  }

  SECTION("Check particle is in cell") {
    // Index
    mpm::Index id1 = 0;

    // Mesh
    auto mesh = std::make_shared<mpm::Mesh<Dim>>(0);
    // Check mesh is inactive (false)
    REQUIRE(mesh->status() == false);

    // Coordinates
    Eigen::Vector3d coords;
    coords.setZero();

    // Define nodes
    coords << 0, 0, 0;
    std::shared_ptr<mpm::NodeBase<Dim>> node0 =
        std::make_shared<mpm::Node<Dim, Dof, Nphases>>(0, coords);

    coords << 2, 0, 0;
    std::shared_ptr<mpm::NodeBase<Dim>> node1 =
        std::make_shared<mpm::Node<Dim, Dof, Nphases>>(1, coords);

    coords << 2, 2, 0;
    std::shared_ptr<mpm::NodeBase<Dim>> node2 =
        std::make_shared<mpm::Node<Dim, Dof, Nphases>>(2, coords);

    coords << 0, 2, 0;
    std::shared_ptr<mpm::NodeBase<Dim>> node3 =
        std::make_shared<mpm::Node<Dim, Dof, Nphases>>(3, coords);

    coords << 0, 0, 2;
    std::shared_ptr<mpm::NodeBase<Dim>> node4 =
        std::make_shared<mpm::Node<Dim, Dof, Nphases>>(4, coords);

    coords << 2, 0, 2;
    std::shared_ptr<mpm::NodeBase<Dim>> node5 =
        std::make_shared<mpm::Node<Dim, Dof, Nphases>>(5, coords);

    coords << 2, 2, 2;
    std::shared_ptr<mpm::NodeBase<Dim>> node6 =
        std::make_shared<mpm::Node<Dim, Dof, Nphases>>(6, coords);

    coords << 0, 2, 2;
    std::shared_ptr<mpm::NodeBase<Dim>> node7 =
        std::make_shared<mpm::Node<Dim, Dof, Nphases>>(7, coords);

    // Create cell1
    coords.setZero();
    auto cell1 = std::make_shared<mpm::Cell<Dim>>(id1, Nnodes);

    // Add nodes to cell
    cell1->add_node(0, node0);
    cell1->add_node(1, node1);
    cell1->add_node(2, node2);
    cell1->add_node(3, node3);
    cell1->add_node(4, node4);
    cell1->add_node(5, node5);
    cell1->add_node(6, node6);
    cell1->add_node(7, node7);

    REQUIRE(cell1->nnodes() == 8);

    // Assign quadrilateral shapefn to cell
    std::shared_ptr<mpm::ShapeFn<Dim>> shapefn =
        std::make_shared<mpm::HexahedronShapeFn<Dim, 8>>();
    cell1->shapefn(shapefn);

    // Compute cell volume
    cell1->compute_volume();

    // Add cell 1 and check status
    bool cell_status1 = mesh->add_cell(cell1);
    REQUIRE(cell_status1 == true);

    // Particle 1
    coords << 1.0, 1.0, 1.0;
    std::shared_ptr<mpm::ParticleBase<Dim>> particle1 =
        std::make_shared<mpm::Particle<Dim, Nphases>>(0, coords);

    // Particle 2
    coords << 1.5, 1.5, 1.5;
    std::shared_ptr<mpm::ParticleBase<Dim>> particle2 =
        std::make_shared<mpm::Particle<Dim, Nphases>>(1, coords);

    // Add particle 1 and check status
    bool particle_status1 = mesh->add_particle(particle1);
    REQUIRE(particle_status1 == true);
    // Add particle 2 and check status
    bool particle_status2 = mesh->add_particle(particle2);
    REQUIRE(particle_status2 == true);

    // Check mesh is active
    REQUIRE(mesh->status() == true);

    // Locate particles in a mesh
    mesh->locate_particles_mesh();

    // Check location of particle 1
    REQUIRE(particle1->cell_id() == 0);
    // Check location of particle 2
    REQUIRE(particle2->cell_id() == 0);
  }
}
