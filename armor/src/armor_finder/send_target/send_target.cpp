//
// Created by xinyang on 19-7-11.
//

#include <armor_finder/armor_finder.h>
#include <armor_finder/protocol.h>
#include <config/setconfig.h>
#include <log.h>

bool ArmorFinder::sendBoxPosition(float &last_yaw, float &last_pitch, bool shoot) {
    if (target_box.rect == cv::Rect2d()) return false;
    auto rect = target_box.rect;
    float dx = rect.x + rect.width / 2 - IMAGE_CENTER_X;
    float dy = rect.y + rect.height / 2 - IMAGE_CENTER_Y;
    float yaw = atan(dx / FOCUS_PIXAL) * 180 / PI;
    float pitch = atan(dy / FOCUS_PIXAL) * 180 / PI;
    float yaw_speed = (yaw - last_yaw) * 120;
    float pitch_speed = (pitch - last_pitch) * 120;
    last_yaw = yaw;
    last_pitch = pitch;
    return protocol::SendGimbalAngle(yaw, pitch, yaw_speed, pitch_speed, shoot);
}

