/*
 * qianqians
 * 2020-1-22
 * battle
 * map_data.h
 */
#ifndef _map_data_h
#define _map_data_h

#include <memory>
#include <list>
#include <vector>

namespace battle {

extern int32_t map_width;
extern int32_t map_height;
extern int32_t map_width_box;
extern int32_t map_height_box;

void map_primitive_data(std::string data_path);

class tiledmap {
public:
    int32_t x_offset_begin;
    int32_t x_offset_end;
    int32_t y_offset_begin;
    int32_t y_offset_end;
    std::string tiledmap_name;

};
extern std::vector<tiledmap> tiledmap_list;

enum class em_map_element_property {
    em_map_empty = 0,
    em_map_map = 1,
    em_map_wreck = 2,
};

class base_element {
public:
    em_map_element_property _property;

};

class empty_element : public base_element {
public:
    empty_element() {
        _property = em_map_element_property::em_map_empty;
    }
};

enum class em_map_element_groundlayer {
    em_map_groundlayer = 1, 
    em_map_house = 2,
    em_map_shared = 3,
};

class map_element : public base_element {
public:
    int32_t collision;
    int32_t groundlayer;
    int32_t hp;

public:
    map_element(int32_t _collision, int32_t _hp, int32_t _groundlayer) {
        _property = em_map_element_property::em_map_map;
        collision = _collision;
        groundlayer = _groundlayer;
        hp = _hp;
    }
};

class role;
class drop_box;
class box {
public:
    std::shared_ptr<base_element> map_elem = nullptr;
    std::list<std::weak_ptr<role> > role_list = {};

public:
    bool check_exist_enemy(std::shared_ptr<role> _self);

};

struct door{
    int32_t x_min;
    int32_t x_max;
    int32_t y_min;
    int32_t y_max;
};

struct ladder {
    int32_t x_min;
    int32_t x_max;
    int32_t y_min;
    int32_t y_max;
};

std::vector<std::shared_ptr<box> > create_map();
std::vector<std::shared_ptr<box> > create_house();
std::vector<door> create_door();
std::vector<ladder> create_ladder();

}

#endif //_map_data_h