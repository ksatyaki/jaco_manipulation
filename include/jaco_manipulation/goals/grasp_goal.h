//
// Created by chitt on 8/6/18.
//

#ifndef PROJECT_GRASPGOAL_HPP
#define PROJECT_GRASPGOAL_HPP
#include "kinect_goal.h"

namespace jaco_manipulation {
namespace goals {

/*!
 * GraspGoal
 * Represent a severely limited pose for grasping objects
 * Limited in height, and rotation around x and y axis
 */
class GraspGoal: public KinectGoal {
 public:

  /**
   * deleted default constructor
  */
  GraspGoal() = delete;

  /**
   * Constructor
   * @param grasp_pose_goal grasp pose goal
   * @param description descritpion with additional info
   */
  explicit GraspGoal(const goal_input::LimitedPose &grasp_pose_goal,
                     jaco_manipulation::grasps::GraspType grasp,
                     const std::string &description = "grasp goal");

  /**
   * Constructor
   * @param bounding_box_goal bounding box to drop something at
   * @param description descritpion with additional info
   */
  explicit GraspGoal(const jaco_manipulation::BoundingBox&bounding_box_goal,
                     jaco_manipulation::grasps::GraspType grasp,
                     const std::string &description = "grasp box goal");

  /**
   * default destructor
   */
  ~GraspGoal() final = default;

  /**
   * get created goal
   */
  jaco_manipulation::PlanAndMoveArmGoal goal() const final;
};

} // namespace goals
} // namespace jaco_manipulation

#endif //PROJECT_GRASPGOAL_HPP
