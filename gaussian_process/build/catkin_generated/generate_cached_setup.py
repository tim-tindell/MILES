from __future__ import print_function
import argparse
import os
import stat
import sys

# find the import for catkin's python package - either from source space or from an installed underlay
if os.path.exists(os.path.join('/opt/ros/hydro/share/catkin/cmake', 'catkinConfig.cmake.in')):
    sys.path.insert(0, os.path.join('/opt/ros/hydro/share/catkin/cmake', '..', 'python'))
try:
    from catkin.environment_cache import generate_environment_script
except ImportError:
    # search for catkin package in all workspaces and prepend to path
    for workspace in "/home/slam/catkin_ws/devel_isolated/move_base;/home/slam/catkin_ws/devel_isolated/rotate_recovery;/home/slam/catkin_ws/devel_isolated/global_planner;/home/slam/catkin_ws/devel_isolated/navfn;/home/slam/catkin_ws/devel_isolated/move_slow_and_clear;/home/slam/catkin_ws/devel_isolated/dwa_local_planner;/home/slam/catkin_ws/devel_isolated/clear_costmap_recovery;/home/slam/catkin_ws/devel_isolated/carrot_planner;/home/slam/catkin_ws/devel_isolated/base_local_planner;/home/slam/catkin_ws/devel_isolated/nav_core;/home/slam/catkin_ws/devel_isolated/costmap_2d;/home/slam/catkin_ws/devel_isolated/voxel_grid;/home/slam/catkin_ws/devel_isolated/slam_gmapping;/home/slam/catkin_ws/devel_isolated/rosaria;/home/slam/catkin_ws/devel_isolated/robot_pose_ekf;/home/slam/catkin_ws/devel_isolated/pointcloud_to_laserscan;/home/slam/catkin_ws/devel_isolated/pioneer2dx_Gazebo;/home/slam/catkin_ws/devel_isolated/pioneer2dx;/home/slam/catkin_ws/devel_isolated/perception_pcl;/home/slam/catkin_ws/devel_isolated/pcl_ros;/home/slam/catkin_ws/devel_isolated/openni_launch;/home/slam/catkin_ws/devel_isolated/openni_camera;/home/slam/catkin_ws/devel_isolated/navigation;/home/slam/catkin_ws/devel_isolated/move_base_msgs;/home/slam/catkin_ws/devel_isolated/amcl;/home/slam/catkin_ws/devel_isolated/map_server;/home/slam/catkin_ws/devel_isolated/gmapping;/home/slam/catkin_ws/devel_isolated/fake_localization;/home/slam/catkin_ws/devel;/opt/ros/hydro".split(';'):
        python_path = os.path.join(workspace, 'lib/python2.7/dist-packages')
        if os.path.isdir(os.path.join(python_path, 'catkin')):
            sys.path.insert(0, python_path)
            break
    from catkin.environment_cache import generate_environment_script

code = generate_environment_script('/home/slam/catkin_ws/src/gaussian_process/build/devel/env.sh')

output_filename = '/home/slam/catkin_ws/src/gaussian_process/build/catkin_generated/setup_cached.sh'
with open(output_filename, 'w') as f:
    #print('Generate script for cached setup "%s"' % output_filename)
    f.write('\n'.join(code))

mode = os.stat(output_filename).st_mode
os.chmod(output_filename, mode | stat.S_IXUSR)
