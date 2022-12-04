import { _decorator, Component, Node, Button, EditBox, find, director, Sprite, Camera, TiledLayer, TiledMap, Vec2 } from 'cc';
const { ccclass, property } = _decorator;

import * as singleton from '../netDriver/netSingleton';
import { playground, player_game_info } from '../serverSDK/common';

@ccclass('main_game')
export class main_game extends Component {
    @property(Camera)
    camera:Camera = null;
    @property(TiledMap)
    map:TiledMap = null;
    @property(Sprite)
    lake:Sprite = null;

    private mapPlayground:Map<number, Vec2> = new Map<number, Vec2>();

    start() {
        let playgroundLenght = singleton.netSingleton.game.get_playground_len();
        for(let i = 0; i < playgroundLenght; i++) {
            let layer_name = "跑道" + i;
            let layer = this.map.getLayer(layer_name);
            console.log(layer_name);
            console.log(layer);
            let tile_pos = new Vec2(layer.rightTop.col, layer.rightTop.row);
            this.mapPlayground.set(i, tile_pos);
        }
        
        if (!singleton.netSingleton.game.CurrentPlayerInfo) {
            this.set_camera_pos(0);
        }
        else {
            this.set_camera_pos(singleton.netSingleton.game.CurrentPlayerInfo.current_pos);
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
}