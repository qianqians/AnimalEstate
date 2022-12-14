import { _decorator, Component, Node, Button, EditBox, find, director, Sprite, Camera, TiledLayer, TiledMap, Vec2, Prefab, instantiate } from 'cc';
const { ccclass, property } = _decorator;

import * as singleton from '../netDriver/netSingleton';
import { playground, player_game_info, animal } from '../serverSDK/common';

@ccclass('main_game')
export class main_game extends Component {
    @property(Camera)
    camera:Camera = null;
    @property(TiledMap)
    map:TiledMap = null;
    @property(Sprite)
    lake:Sprite = null;

    @property(Prefab)
    bear:Prefab = null;
    @property(Prefab)
    chicken:Prefab = null;
    @property(Prefab)
    duck:Prefab = null;
    @property(Prefab)
    lion:Prefab = null;
    @property(Prefab)
    monkey:Prefab = null;
    @property(Prefab)
    mouse:Prefab = null;
    @property(Prefab)
    rabbit:Prefab = null;
    @property(Prefab)
    tiger:Prefab = null;

    private mapPlayground:Map<number, Vec2> = new Map<number, Vec2>();

    start() {
        let playgroundLenght = singleton.netSingleton.game.get_playground_len();
        for(let i = 0; i < playgroundLenght; i++) {
            let layer_name = "跑道" + i;
            let layer = this.map.getLayer(layer_name);
            let tile_pos = new Vec2(layer.rightTop.col, layer.rightTop.row);
            this.mapPlayground.set(i, tile_pos);
        }

        this.set_animal_pos();
        
        if (!singleton.netSingleton.game.CurrentPlayerInfo) {
            this.set_camera_pos(0);
        }
        else {
            var current_animal = singleton.netSingleton.game.CurrentPlayerInfo.animal_info[singleton.netSingleton.game.CurrentPlayerInfo.current_animal_index];
            this.set_camera_pos(current_animal.current_pos);
        }
    }

    set_camera_pos(grid_index:number) {
        let tile_pos = this.mapPlayground.get(grid_index);
        let target_x = tile_pos.x * 64 + 32
        if (target_x < 320) {
            target_x = 320;
        }
        else if ((800 - target_x) < 320) {
            target_x = 800 - 320;
        }
        let view_center_x = 800 - target_x;
        let target_y = tile_pos.y * 64 + 32;
        if (target_y < 320) {
            target_y = 320;
        }
        else if ((800 - target_y) < 320) {
            target_y = 800 - 320;
        }
        let view_center_y = 800 + 160 - target_y;

        this.lake.node.setPosition(view_center_x, view_center_y);
        this.map.node.setPosition(view_center_x, view_center_y);
    }

    set_animal_pos() {
        for(let index in singleton.netSingleton.game.PlayerGameInfo) {
            let info = singleton.netSingleton.game.PlayerGameInfo[index];
            for(let animal_index in info.animal_info) {
                let animal_info = info.animal_info[animal_index];

                let layer_name = "出生点_" + index + "_" + animal_index;
                let layer = this.map.getLayer(layer_name);
                console.log(layer_name);
                console.log(layer);
                let target_x = layer.rightTop.col * 64 + 32 - 800;
                let target_y=  layer.rightTop.row * 64 + 32 - 800;

                let animal_prefab = null;
                switch(animal_info.animal_id) {
                    case animal.bear:
                        {
                            animal_prefab = this.bear;
                        }
                        break;

                    case animal.chicken:
                        {
                            animal_prefab = this.chicken;
                        }
                        break;

                    case animal.duck:
                        {
                            animal_prefab = this.duck;
                        }
                        break;
                    
                    case animal.lion:
                        {
                            animal_prefab = this.lion;
                        }
                        break;

                    case animal.monkey:
                        {
                            animal_prefab = this.monkey;
                        }
                        break;

                    case animal.mouse:
                        {
                            animal_prefab = this.mouse;
                        }
                        break;

                    case animal.rabbit:
                        {
                            animal_prefab = this.rabbit;
                        }
                        break;

                    case animal.tiger:
                        {
                            animal_prefab = this.tiger;
                        }
                        break;
                }

                let animal_instance = instantiate(animal_prefab);
                this.map.node.addChild(animal_instance);
                animal_instance.setPosition(target_x, target_y);
                console.log(animal_instance);
            }
        }
    }
}