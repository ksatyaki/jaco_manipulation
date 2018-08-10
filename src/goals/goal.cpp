//
// Created by julian on 04.08.18.
//

#include <jaco_manipulation/goals/goal.h>
#include <ros/console.h>

using namespace jaco_manipulation::goals;

Goal::Goal() : planning_frame_("root") {
  goal_.goal_type = "goal";
  description_ = goal_.goal_type;
}

jaco_manipulation::PlanAndMoveArmGoal Goal::goal() const {
  return goal_;
}

const std::string Goal::info() const {
  return description_ + " [goal_type=\"" + goal_.goal_type + "\"]";
}