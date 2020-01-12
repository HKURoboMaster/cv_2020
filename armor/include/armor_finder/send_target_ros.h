#include <armor_finder/armor_finder.h>
#include <ros/ros.h>
#include <roborts/GimbalAngle.h>
#include <roborts/ArmorDetectionAction.h>
#include "armor_detection_base.h"
#include "proto/armor_detection.pb.h"
#include "gimbal_control.h"

namespace roborts_detection{

using roborts_common::NodeState;
using roborts_common::ErrorInfo;

class ArmorDetectionNode
{
    public:
        explicit ArmorDetectionNodeInit();
        ErrorInfo Init();
        // This function is used to respond to command sent by Decision maker
        // It will change a flag such that pass all the way back to detection code.
        // To start stop or suspension the mission.
        // The armor detection algorithm will be always running?
        void ActionCB(const roborts_msgs::ArmorDetectionGoal::ConstPtr &data);



}





}