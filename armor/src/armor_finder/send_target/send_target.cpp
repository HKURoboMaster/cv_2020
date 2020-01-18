//
// Created by xinyang on 19-7-11.
//

#include <armor_finder/armor_finder.h>
#include <armor_finder/protocol.h>
#include <config/setconfig.h>
#include <log.h>
#include <list>
#define SPEED_CALC_LEN 5
using namespace std;

bool ArmorFinder::sendBoxPosition(float &last_yaw, float &last_pitch, bool shoot) {
    static list<float> yaw_buffer;
    static list<float> pitch_buffer;
    if (target_box.rect == cv::Rect2d()) return false;
    auto rect = target_box.rect;
    float dx = rect.x + rect.width / 2 - IMAGE_CENTER_X;
    float dy = rect.y + rect.height / 2 - IMAGE_CENTER_Y;
    float yaw = atan(dx / FOCUS_PIXAL) * 180 / PI;
    float pitch = atan(dy / FOCUS_PIXAL) * 180 / PI;
    float yaw_speed = (yaw - last_yaw) * 120;
    yaw_buffer.push_front(yaw_speed);
    if(yaw_buffer.size()>SPEED_CALC_LEN)
        yaw_buffer.pop_back();
    float pitch_speed = (pitch - last_pitch) * 120;
    pitch_buffer.push_front(pitch_speed); // Angular speed per second 
    if(pitch_buffer.size()>SPEED_CALC_LEN)
        pitch_buffer.pop_back();
    list<float>::iterator yaw_iter=yaw_buffer.begin(),pitch_iter=pitch_buffer.begin();
    int counter = 1;
    for(;yaw_iter!=yaw_buffer.end();yaw_iter++)
    {
        yaw_speed += 2.588*(*yaw_iter)*exp(-counter*counter); // 2.588 Normalize constant has almost no effect when changing length
    }
    counter=1;
    for(;pitch_iter!=pitch_buffer.end();pitch_iter++)
    {
        pitch_speed += 2.588*(*yaw_iter)*exp(-counter*counter);
    }
    last_yaw = yaw;
    last_pitch = pitch;
    return protocol::SendGimbalAngle(yaw, pitch, yaw_speed, pitch_speed, shoot);
}

