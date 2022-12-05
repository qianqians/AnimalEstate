/*
 * qianqians
 * 2020-1-22
 * battle
 * map.h
 */
#ifndef _map_h
#define _map_h

#include <vector>
#include <memory>
#include <string>
#include <random>

#include <crossguid/guid.hpp>

#include <hub.h>

#include <common.h>

#include "map_data.h"

namespace battle {

class role;
class item;
class drop_box {
public:
    std::string uuid;
    int32_t x;
    int32_t y;
    std::vector<std::shared_ptr<item> > item_list;

    std::shared_ptr<role> opener;

public:
    drop_box() {
        uuid = xg::newGuid().str();
        opener = nullptr;
    }

    bool open(std::shared_ptr<role> _role) {
        if (opener != nullptr) {
            return false;
        }
        opener = _role;

        return true;
    }

    void close() {
        opener = nullptr;
    }

};

class box_pos {
public:
    int32_t x_box;
    int32_t y_box;
};

class sub_map {
private:
    static int count;

public:
    sub_map();

    virtual ~sub_map();

    std::vector<std::weak_ptr<role> > field_roles = {};
    std::vector<box_pos> be_wreck_box = {};
    std::vector<box_pos> be_wreck_house = {};
    std::list<std::shared_ptr<item> > item_box_list = {};

public:
    void leave_sub_map(std::weak_ptr<role> _role);

    void into_sub_map(std::weak_ptr<role> _role);

    std::vector<std::string> get_field_roles_uuid();
};

class battle;
class map {
public:
    std::vector<std::shared_ptr<box> > map_data;
    std::vector<std::shared_ptr<box> > house_data;
    std::vector<door> door_data;
    std::vector<ladder> ladder_data;
    std::vector<std::shared_ptr<sub_map> > sub_maps;
    std::vector<int32_t> born_point;

    int32_t _map_width;
    int32_t _map_height;
    int32_t _map_width_box;
    int32_t _map_height_box;

private:
    static int count;

public:
    map();

    virtual ~map();

    int32_t random_born();

    void check_and_init(bool is_in_house, int32_t & x, int32_t & y);

    void into_map(std::shared_ptr<role> _role);

    void leave_map(std::shared_ptr<role> _role);

    int32_t hit_box(int32_t x, int32_t y, int32_t collision, int32_t hit_terrain, std::vector<std::shared_ptr<item> >& downitems);

    void check_item_dowm(std::shared_ptr<battle> _battle, std::vector<std::shared_ptr<item> > downitems);

    int32_t get_sub_map_index(int32_t x);

    std::shared_ptr<sub_map> get_sub_map(int32_t x);

    std::vector<std::shared_ptr<sub_map> > get_field_sub_map(int32_t x);

    std::vector<std::shared_ptr<role> > get_field_roles(int32_t x);

    std::vector<std::string> get_field_roles_uuid(int32_t x);

    std::vector<std::shared_ptr<role> > get_range_field_roles(int32_t start_x, int32_t end_x);

    std::vector<std::string> get_range_field_roles_uuid(int32_t start_x, int32_t end_x);

    std::vector<abelkhan::role_info> get_filed_roles_info(int32_t x);

    std::shared_ptr<box> get_box_list(int32_t x, int32_t y);

    std::shared_ptr<box> get_house_box(int32_t x, int32_t y);

    bool check_in_same_layer(bool is_in_house, int32_t _x_box, int32_t _y_box);

};

}

#endif //_map_h