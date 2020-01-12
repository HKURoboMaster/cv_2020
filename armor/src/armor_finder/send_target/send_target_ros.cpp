/**  
    This module get Input of CV detection with enemy position
    and Publish conduct Gimbal Transform and Publish Enemy Info through ROS
    It has three Mode:
        CAMERA_WITH_PITCH
        CAMERA_WITH_YAW
        CAMERA_WITH_CHASSIS
    It will become a ros Node and Publish Information As soon as target has
    been passed to it.
**/

#include <send_target_ros.h>