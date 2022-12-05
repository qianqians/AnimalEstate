/*
 * qianqians
 * 2020-1-22
 * battle
 * role_scene.h
 */
#ifndef _role_scene_h
#define _role_scene_h

#include <memory>

#include <hub.h>

#include "map.h"

namespace battle {

struct pos {
    int32_t x;
    int32_t y;
};

class obb {
public:
    int32_t down_left_x;
    int32_t down_left_y;
    int32_t up_right_x;
    int32_t up_right_y;

private:
    static int count;

public:
    obb(int32_t _down_left_x, int32_t _down_left_y, int32_t _up_right_x, int32_t _up_right_y) {
        down_left_x = _down_left_x;
        down_left_y = _down_left_y;
        up_right_x = _up_right_x;
        up_right_y = _up_right_y;

        ++count;
    }

    virtual ~obb() {
        spdlog::trace("obb destruction count:{0}", --count);
    }

    struct pos get_center_pos(){
        pos _pos;
        _pos.x = (down_left_x + up_right_x) / 2;
        _pos.y = down_left_y;
        return _pos;
    }

    struct pos get_shoot_pos() {
        pos _pos;
        _pos.x = (down_left_x + up_right_x) / 2;
        _pos.y = up_right_y - 16;

        spdlog::trace("obb get_shoot_pos down_left_x:{0}, down_left_y:{1}, up_right_x:{2}, up_right_y:{3}", down_left_x, down_left_y, up_right_x, up_right_y);

        return _pos;
    }

    void set_center_pos(int32_t x, int32_t y) {
        auto disp_x = x - (down_left_x + up_right_x) / 2;
        auto _height = up_right_y - down_left_y;

        down_left_x += disp_x;
        down_left_y = y;
        up_right_x += disp_x;
        up_right_y = y + _height;

        spdlog::trace("obb set_center_pos down_left_x:{0}, down_left_y:{1}, up_right_x:{2}, up_right_y:{3}", down_left_x, down_left_y, up_right_x, up_right_y);
        spdlog::trace("obb set_center_pos disp_x:{0}, _height:{1}", disp_x, _height);
    }

    void squat_down() {
        up_right_y -= 16;
    }

    void stand_up() {
        up_right_y += 16;
    }
};

enum class in_out_house_state{
    em_not_door = -1,
    em_in_house = 0,
    em_out_house = 1,
};

class role;
class role_scene {
public:
    
    bool is_squat = false;
    int32_t direction = 0;
    int32_t move_speed;
    int32_t move_speed_rate = 100;
    /*
     * jump_status -1 下落 1 跳起 0 地面
     */
    int32_t jump_status;
    int32_t jump_speed;
    int32_t jump_height;
    bool is_twostepjump = false;

    /*
     * ladder_state -1 向下 1 向上 0 静止
     */
    int32_t ladder_state = 0;
    int32_t last_rocker = 0;

    /*
     * 玩家在房子内，房子范围 
     */
    int32_t house_range_begin = -1;
    int32_t house_range_end = -1;

    uint64_t timetmp;

    /*
     * c_ladder 当前楼梯iterator
     */
    std::vector<ladder>::iterator c_ladder;

    std::weak_ptr<role> _role;
    std::weak_ptr<map> _map_handle;
    std::shared_ptr<obb> _obb;

private:
    static int count;

public:
    role_scene(std::weak_ptr<role> _role, int32_t x, int32_t y);

    virtual ~role_scene();

    abelkhan::role_scene_info cs_info();

    void check_and_init();

    void check_and_down();

    void check_and_move();

    void check_and_set_squat_obb(int32_t x_box, int32_t y_down_box_old, int32_t y_up_box_old, int32_t y_down_box_new, int32_t y_up_box_new);

    struct pos get_shoot_pos();

    int32_t get_scene_x();

    void set_rocker(int32_t rocker);

    void set_direction(int32_t direction);

    void force_set_direction(int32_t direction);

    void set_ladder(int32_t ladder_state);

    void set_jump();

    void set_squat(bool _squat);

    std::vector<std::string> get_role_field();

    int in_out_house();

    bool check_at_wreck();

private:
    void send_role_move_state();

    void check_change_sub_map(std::vector<std::shared_ptr<sub_map> > now_sub_map, std::vector<std::shared_ptr<sub_map> > new_sub_map);

    bool check_and_x(std::shared_ptr<role> _role_ptr, std::shared_ptr<map> _map, int32_t& _x, int32_t& _y, float current_move_speed, float step_time);

    void check_move_out_house();

    void check_and_y();

    bool check_and_y_down(std::shared_ptr<role> _role_ptr, std::shared_ptr<map> _map, int32_t& _x, int32_t& _y, float step_time);

    bool check_up_map_stop(std::shared_ptr<role> _role_ptr, std::shared_ptr<map> _map, int32_t _x);

    bool check_and_y_up(std::shared_ptr<role> _role_ptr, std::shared_ptr<map> _map, int32_t& _x, int32_t& _y, float step_time);

    void set_jump_done();

    void set_jump_down();

    bool check_ladder_move(int32_t& _x, int32_t& _y);

    std::vector<ladder>::iterator check_ladder_down(int32_t _x, int32_t _y);

    std::vector<ladder>::iterator check_ladder_up(int32_t _x, int32_t _y);

    bool check_in_same_house(std::shared_ptr<role_scene> self, std::shared_ptr<role_scene> target);

    void clear_house_range();

    void check_and_set_house_range();

    int wreck_in_out_house();

    int door_in_out_house();

    void sync_in_out_house_field(std::shared_ptr<role> _self, std::shared_ptr<map> _map, int ret);

    void check_sync_house_wreak_field(std::shared_ptr<role> _self, std::shared_ptr<map> _map, int32_t x_box_old, int32_t x_new_old, int32_t y_down_box_old, int32_t y_down_box_new, int32_t y_up_box_old, int32_t y_up_box_new);

    void check_shoot_direction(std::shared_ptr<role> _self);
};

}

#endif //_role_scene_h