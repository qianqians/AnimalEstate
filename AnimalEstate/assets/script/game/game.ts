import { _decorator, Component, director, Sprite, Camera, Animation, AnimationClip, TiledMap, Vec2, Prefab, instantiate } from 'cc';
const { ccclass, property } = _decorator;

import * as singleton from '../netDriver/netSingleton';
import { playground, player_game_info, animal } from '../serverSDK/common';

class move_info {
    public animal : any;
    public current : number;
    public to : number;
    public pos : Vec2;
    public speed : number;
}

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
    private moveList:move_info[] = [];
    private current_move_obj:move_info = null;

    start() {
        let playgroundLenght = singleton.netSingleton.game.get_playground_len();
        for(let i = 0; i < playgroundLenght; i++) {
            let layer_name = "跑道" + i;
            let layer = this.map.getLayer(layer_name);
            let tile_pos = new Vec2(layer.rightTop.col, layer.rightTop.row);
            this.mapPlayground.set(i, tile_pos);
        }

        this.set_animal_born_pos();
        
        if (!singleton.netSingleton.game.CurrentPlayerInfo) {
            this.set_camera_pos_grid(0);
        }
        else {
            var current_animal = singleton.netSingleton.game.CurrentPlayerInfo.animal_info[singleton.netSingleton.game.CurrentPlayerInfo.current_animal_index];
            this.set_camera_pos_grid(current_animal.current_pos);
        }

        singleton.netSingleton.game.cb_move = this.on_cb_move.bind(this);
    }

    private on_cb_move(guid:number, animal_index:number, from:number, to:number) {
        console.log("guid:" + guid + " animal_index:" + animal_index);

        let animal_map = singleton.netSingleton.game.PlayerAnimalMap.get(guid);
        let _animal = animal_map.get(animal_index);
        let animationComponent = _animal.getComponent(Animation);
        const [ idleClip, runClip ] = animationComponent.clips;
        const runState = animationComponent.getState(runClip.name);
        animationComponent.play(runClip.name);
        runState.wrapMode = AnimationClip.WrapMode.Loop;

        let _move_info = new move_info();
        _move_info.animal = _animal;
        _move_info.current = from;
        _move_info.to = to;
        let from_Pos = this.mapPlayground.get(from);
        _move_info.pos = new Vec2(from_Pos.x * 64 + 32 - 800, from_Pos.y * 64 + 32 - 800);
        _move_info.speed = 5 * 64 / 3;
        this.moveList.push(_move_info);

        this.current_move_obj = _move_info;
    }

    update(deltaTime: number) {
        let remove_list = [];
        for (let _info of this.moveList) {
            let target_grid = _info.current + 1;
            let target_config_pos = this.mapPlayground.get(target_grid);
            let target_pos = new Vec2(target_config_pos.x * 64 + 32 - 800, target_config_pos.y * 64 + 32 - 800);

            if (target_pos.x == _info.pos.x) {
                var _move = target_pos.y - _info.pos.y;
                if (_move > 0) {
                    _info.pos.y += deltaTime * _info.speed;
                    if (_info.pos.y >= target_pos.y) {
                        _info.pos.y = target_pos.y;
                        _info.current = target_grid;
                    }
                }
                else {
                    _info.pos.y -= deltaTime * _info.speed;
                    if (_info.pos.y <= target_pos.y) {
                        _info.pos.y = target_pos.y;
                        _info.current = target_grid;
                    }
                }
            }
            else if (target_pos.y == _info.pos.y) {
                var _move = target_pos.x - _info.pos.x;
                if (_move > 0) {
                    _info.pos.x += deltaTime * _info.speed;
                    if (_info.pos.x >= target_pos.x) {
                        _info.pos.x = target_pos.x;
                        _info.current = target_grid;
                    }
                }
                else {
                    _info.pos.x -= deltaTime * _info.speed;
                    if (_info.pos.x <= target_pos.x) {
                        _info.pos.x = target_pos.x;
                        _info.current = target_grid;
                    }
                }
            }

            _info.animal.setPosition(_info.pos.x, _info.pos.y);

            if (_info.current == _info.to) {
                remove_list.push(_info);
            }
        }

        for (let _remove of remove_list) {
            this.moveList.splice(this.moveList.indexOf(_remove), 1);

            let animationComponent = _remove.animal.getComponent(Animation);
            const [ idleClip, runClip ] = animationComponent.clips;
            const idleState = animationComponent.getState(idleClip.name);
            animationComponent.play(idleClip.name);
            idleState.wrapMode = AnimationClip.WrapMode.Loop;
        }

        if (this.current_move_obj) {
            this.set_camera_pos(this.current_move_obj.pos.x + 800, this.current_move_obj.pos.y + 800);
        }
    }

    set_camera_pos(x:number, y:number) {
        let target_x = x;
        if (target_x < 320) {
            target_x = 320;
        }
        else if ((1600 - target_x) < 320) {
            target_x = 1600 - 320;
        }
        let view_center_x = 800 - target_x;
        let target_y = y;
        if (target_y < 320) {
            target_y = 320;
        }
        else if ((1600 - target_y) < 320) {
            target_y = 1600 - 320;
        }
        let view_center_y = 800 + 160 - target_y;

        this.lake.node.setPosition(view_center_x, view_center_y);
        this.map.node.setPosition(view_center_x, view_center_y);
    }

    set_camera_pos_grid(grid_index:number) {
        let tile_pos = this.mapPlayground.get(grid_index);
        let target_x = tile_pos.x * 64 + 32;
        let target_y = tile_pos.y * 64 + 32;
        
        this.set_camera_pos(target_x, target_y);
    }

    set_animal_born_pos() {
        for(let index in singleton.netSingleton.game.PlayerGameInfo) {
            let info = singleton.netSingleton.game.PlayerGameInfo[index];

            let animal_map = new Map<number, any>();
            singleton.netSingleton.game.PlayerAnimalMap.set(info.guid, animal_map);

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
                let animationComponent = animal_instance.getComponent(Animation);
                const [ idleClip, runClip ] = animationComponent.clips;
                const idleState = animationComponent.getState(idleClip.name);
                animationComponent.play(idleClip.name);
                idleState.wrapMode = AnimationClip.WrapMode.Loop;

                animal_map.set(Number(animal_index), animal_instance);
            }
        }
    }
}