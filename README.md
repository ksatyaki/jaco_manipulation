# Jaco Manipulation

Provides ROS Actionlib Server and Client interface to Jaco Robotic Arm.

Depends on [wpi_jaco](https://github.com/ksatyaki/wpi_jaco), a custom driver for the robotic arm and [rail_manipulation_msgs](https://github.com/GT-RAIL/rail_manipulation_msgs). Just drop the repos in your catkin workspace, or use the provided `.rosinstall` file in to start a fresh workspace.

Depends on installation of [MoveIt!](https://moveit.ros.org/) and it's [visual tools](https://github.com/ros-planning/moveit_visual_tools)
Test the installation 
```
cd <workspace_root>
catkin_make -j8
source devel/setup.<bash/zsh>
roslaunch manipulation_launch manipulation.launch use_rviz:=true
```

An RViz window should open with Moveit! ready to be used

*Note*: If you have any problems with dependencies, try running `rosdep install --from-paths src -i -y`

## Server: jaco\_manipulation_server
### Config
Define these ROS parameters in the [launch file](launch/jaco_manipulation.launch)
* `planner_id type`: e.g. RRTConnectkConfigDefault, RRTstarkConfigDefault, etc. **Default**: RRTConnectkConfigDefault
* `planning_time`: time in seconds **Default**: 1.5
* `planning_attempts`: number of planning attempts **Default**: 10
* `allow_replanning`: true/false **Default**: true
* `allow_looking`: true/false **Default**: true
* `publish_debug`: true/false. **Default**: true. If true, [this message](msg/JacoDebug.msg) is published on topic `/jaco_manipulation/debug`

Messages defined in [action/PlanAndMoveArm.action](action/PlanAndMoveArm.action)

### Input
* `geometry_msgs/PoseStamped` or 
* `sensor_msgs/JointState` and when used with vision system:
* `jaco_manipulation/BoundingBox bounding_box` defined [here](msg/BoundingBox.msg)

**Note**: the bounding box should be defined with a centroid and dimensions. If your bounding box is defined differently, e.g. by the the position of the lower left corner and dimensions, this code will still assume this to be a centroid. Adjust your definition of a bounding box accordingly.

## Client: jaco\_manipulation_client
Simple but convenient wrapper around ROS action server SimpleActionClient, tuned for Jaco Robot Arm

### Possible MoveIt Goal States
 * [JointGoal](include/jaco_manipulation/goals/joint_goal.h) : Joint state goal state
 * [PoseGoal](include/jaco_manipulation/goals/pose_goal.h) : Pose goal state
 * [MoveItGoal](include/jaco_manipulation/goals/move_it_goal.h) : Goal state from MoveIt config file ([jaco.srdf](https://github.com/ksatyaki/wpi_jaco/blob/develop/jaco_moveit_config/config/jaco.srdf)) 
 * [DropGoal](include/jaco_manipulation/goals/drop_goal.h) : Bounding Box to be dropped
 * [GraspGoal](include/jaco_manipulation/goals/grasp_goal.h) : Bounding Box to be grasped
 * All goals are defined [here](include/jaco_manipulation/goals) 

### Usage
Start with

```cpp
#include <jaco_manipulation/client/jaco_manipulation_client.h>

using namespace jaco_manipulation::client;

int main(int argn, char *args[]) {

  ros::init(argn, args, "pam_client");

  JacoManipulationClient jmc;
```
MoveIt! Config file goal "home"

```go
jmc.moveTo("home");
```

Joint state goal

```go
sensor_msgs::JointState joint_state;
joint_state.position.push_back(-2.6435937802859897);
joint_state.position.push_back(2.478897506888874);
joint_state.position.push_back(1.680057969995632);
joint_state.position.push_back(-2.0813597278055846);
joint_state.position.push_back(1.451960752633381);
joint_state.position.push_back(1.0931317536782839);
jmc.moveTo(joint_state);
```
Pose goal

```go
geometry_msgs::PoseStamped pose;
pose.pose.position.x = 0.063846;
pose.pose.position.y = -0.193645;
pose.pose.position.z = 0.509365;
pose.pose.orientation.x = 0.369761;
pose.pose.orientation.y = -0.555344;
pose.pose.orientation.z = -0.661933;
pose.pose.orientation.w = 0.341635;
jmc.moveTo(pose);
```

Grasp goal
```go
jaco_manipulation::BoundingBox b;
b.header.frame_id = "base_link";
b.description = "bottle";
b.point.x = 0.695;
b.point.y = 0.3;
b.point.z = 0.105;
b.dimensions.x = 0.06;
b.dimensions.y = 0.06;
b.dimensions.z = 0.21;
jmc.graspAt(b);
```

Drop goal
```go
jaco_manipulation::BoundingBox b;
b.header.frame_id = "base_link";
b.description = "bottle";
b.point.x = 0.55;
b.point.y = 0.0;
b.point.z = 0.105;
b.dimensions.x = 0.06;
b.dimensions.y = 0.06;
b.dimensions.z = 0.21;
jmc.dropAt(b);
```

Examples can be found [here](test/).


## TODO
- [x] seperate action: pre-grasp pose
- [ ] define file as input arg python scripts
- [ ] grasp pose generator configurable
- [ ] call analyser when shutting down test: destructor?
- [ ] accepts labels as list
- [ ] no whitespace in individual label!
- [ ] catch file not found

For tests: disable wall and front grasp
