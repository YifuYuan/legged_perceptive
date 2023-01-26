//
// Created by qiayuan on 23-1-2.
//

#pragma once

#include <ocs2_core/reference/ModeSchedule.h>

#include <convex_plane_decomposition/PlanarRegion.h>
#include <convex_plane_decomposition/PolygonTypes.h>
#include <convex_plane_decomposition/SegmentedPlaneProjection.h>
#include <ocs2_centroidal_model/CentroidalModelInfo.h>
#include <ocs2_core/reference/TargetTrajectories.h>
#include <ocs2_legged_robot/common/Types.h>
#include <ocs2_pinocchio_interface/PinocchioEndEffectorKinematics.h>

namespace legged {
using namespace ocs2;
using namespace legged_robot;

class ConvexRegionSelector {
 public:
  ConvexRegionSelector(CentroidalModelInfo info, std::shared_ptr<convex_plane_decomposition::PlanarTerrain> PlanarTerrainPtr,
                       const EndEffectorKinematics<scalar_t>& endEffectorKinematics);

  void update(const ModeSchedule& modeSchedule, const vector_t& initState, TargetTrajectories& targetTrajectories);

  convex_plane_decomposition::PlanarTerrainProjection getProjection(size_t leg, scalar_t time) const;

  vector3_t getNominalFootholds(size_t leg, scalar_t time) const;

  std::vector<scalar_t> getMiddleTimes(size_t leg) const { return middleTimes_[leg]; }

  std::shared_ptr<convex_plane_decomposition::PlanarTerrain> getPlanarTerrainPtr() { return planarTerrainPtr_; }

 private:
  feet_array_t<std::vector<bool>> extractContactFlags(const std::vector<size_t>& phaseIDsStock) const;
  static std::pair<int, int> findIndex(size_t index, const std::vector<bool>& contactFlagStock);

  vector3_t getNominalFoothold(size_t leg, scalar_t time, const vector_t& initState, TargetTrajectories& targetTrajectories);

  feet_array_t<std::vector<convex_plane_decomposition::PlanarTerrainProjection>> feetProjections_;
  feet_array_t<std::vector<vector3_t>> nominalFootholds_;
  feet_array_t<std::vector<scalar_t>> middleTimes_;

  feet_array_t<std::vector<scalar_t>> timeEvents_;

  const CentroidalModelInfo info_;

  std::shared_ptr<convex_plane_decomposition::PlanarTerrain> planarTerrainPtr_;
  std::unique_ptr<EndEffectorKinematics<scalar_t>> endEffectorKinematicsPtr_;
};
}  // namespace legged
