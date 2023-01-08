import { _decorator, Component, director, Button, Node, Sprite, Camera, Animation, AnimationClip, TiledMap, Vec2, Prefab, instantiate } from 'cc';
const { ccclass, property } = _decorator;

import * as singleton from '../netDriver/netSingleton';
import { playground, player_game_info, animal_game_info, animal } from '../serverSDK/common';

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

    @property(Sprite)
    dice_instance:Sprite = null;
    @property(Sprite)
    dice2_1_instance:Sprite = null;
    @property(Sprite)
    dice2_2_instance:Sprite = null;

    @property(Sprite)
    dice_1:Sprite = null;
    @property(Sprite)
    dice_2:Sprite = null;
    @property(Sprite)
    dice_3:Sprite = null;
    @property(Sprite)
    dice_4:Sprite = null;
    @property(Sprite)
    dice_5:Sprite = null;
    @property(Sprite)
    dice_6:Sprite = null;

    @property(Sprite)
    dice_1_1:Sprite = null;
    @property(Sprite)
    dice_1_2:Sprite = null;
    @property(Sprite)
    dice_1_3:Sprite = null;
    @property(Sprite)
    dice_1_4:Sprite = null;
    @property(Sprite)
    dice_1_5:Sprite = null;
    @property(Sprite)
    dice_1_6:Sprite = null;

    @property(Sprite)
    dice_2_1:Sprite = null;
    @property(Sprite)
    dice_2_2:Sprite = null;
    @property(Sprite)
    dice_2_3:Sprite = null;
    @property(Sprite)
    dice_2_4:Sprite = null;
    @property(Sprite)
    dice_2_5:Sprite = null;
    @property(Sprite)
    dice_2_6:Sprite = null;

    @property(Button)
    readyBtn:Button = null;
    @property(Button)
    diceBtn:Button = null;
    
    dice_result_instance:Sprite = null;
    dice_1_result_instance:Sprite = null;
    dice_2_result_instance:Sprite = null;

    private mapPlayground:Map<number, Vec2> = new Map<number, Vec2>();
    private moveList:move_info[] = [];
    private current_move_obj:move_info = null;

    start() {
        this.readyBtn.node.on(Node.EventType.MOUSE_DOWN, this.ready_callback, this);
        this.diceBtn.node.on(Node.EventType.MOUSE_DOWN, this.dice_callback, this);

        singleton.netSingleton.game.cb_turn_player_round = this.on_cb_turn_player_round.bind(this);
        singleton.netSingleton.game.cb_move = this.on_cb_move.bind(this);
        singleton.netSingleton.game.cb_start_dice = this.on_cb_start_dice.bind(this);
        singleton.netSingleton.game.cb_throw_dice = this.on_cb_throw_dice.bind(this);
        singleton.netSingleton.game.cb_rabbit_choose_dice = this.on_cb_rabbit_choose_dice.bind(this);

        let playgroundLenght = singleton.netSingleton.game.get_playground_len();
        for(let i = 0; i < playgroundLenght; i++) {
            let layer_name = "跑道" + i;
            let layer = this.map.getLayer(layer_name);
            let tile_pos = new Vec2(layer.rightTop.col, layer.rightTop.row);
            this.mapPlayground.set(i, tile_pos);
        }

        this.set_animal_born_pos();
        this.init_dice();
        
        if (!singleton.netSingleton.game.CurrentPlayerInfo) {
            this.set_camera_pos_grid(0);
        }
        else {
            this.readyBtn.node.active = false;

            var current_animal = singleton.netSingleton.game.CurrentPlayerInfo.animal_info[singleton.netSingleton.game.CurrentPlayerInfo.current_animal_index];
            if (current_animal.current_pos < 0) {
                this.set_camera_pos_grid(0);
            }
            else {
                this.set_camera_pos_grid(current_animal.current_pos);
            }
        }
    }

    private init_dice() {
        this.dice_instance.node.setPosition(0, 0);
        this.dice_instance.node.active = false;
        
        this.dice2_1_instance.node.setPosition(-96, 0);
        this.dice2_1_instance.node.active = false;
        this.dice2_2_instance.node.setPosition(96, 0);
        this.dice2_2_instance.node.active = false;

        this.dice_1.node.setPosition(0, 0);
        this.dice_1.node.active = false;
        this.dice_2.node.setPosition(0, 0);
        this.dice_2.node.active = false;
        this.dice_3.node.setPosition(0, 0);
        this.dice_3.node.active = false;
        this.dice_4.node.setPosition(0, 0);
        this.dice_4.node.active = false;
        this.dice_5.node.setPosition(0, 0);
        this.dice_5.node.active = false;
        this.dice_6.node.setPosition(0, 0);
        this.dice_6.node.active = false;
        
        this.dice_1_1.node.setPosition(-96, 0);
        this.dice_1_1.node.active = false;
        this.dice_1_2.node.setPosition(-96, 0);
        this.dice_1_2.node.active = false;
        this.dice_1_3.node.setPosition(-96, 0);
        this.dice_1_3.node.active = false;
        this.dice_1_4.node.setPosition(-96, 0);
        this.dice_1_4.node.active = false;
        this.dice_1_5.node.setPosition(-96, 0);
        this.dice_1_5.node.active = false;
        this.dice_1_6.node.setPosition(-96, 0);
        this.dice_1_6.node.active = false;

        this.dice_2_1.node.setPosition(96, 0);
        this.dice_2_1.node.active = false;
        this.dice_2_2.node.setPosition(96, 0);
        this.dice_2_2.node.active = false;
        this.dice_2_3.node.setPosition(96, 0);
        this.dice_2_3.node.active = false;
        this.dice_2_4.node.setPosition(96, 0);
        this.dice_2_4.node.active = false;
        this.dice_2_5.node.setPosition(96, 0);
        this.dice_2_5.node.active = false;
        this.dice_2_6.node.setPosition(96, 0);
        this.dice_2_6.node.active = false;
    }

    private ready_callback() {
        console.log("ready!");

        singleton.netSingleton.game.ready();
        this.readyBtn.node.active = false;
    }

    private dice_callback() {
        singleton.netSingleton.game.throw_dice();
    }

    private on_cb_turn_player_round(guid:number) {
        this.readyBtn.node.active = false;
        if (guid == singleton.netSingleton.login.player_info.guid) {
            let player_game_info = singleton.netSingleton.game.get_player_game_info(guid);
            let pos = player_game_info.animal_info[player_game_info.current_animal_index].current_pos;
            pos = pos >= 0 ? pos : 0;
            this.set_camera_pos_grid(pos);

            console.log("on_cb_turn_player_round guid:", guid);
        }
    }

    private on_cb_start_dice(guid:number, animal_index:number) {
        let _current_animal:animal_game_info = null;
        for(let info of singleton.netSingleton.game.PlayerGameInfo) {
            if (info.guid == guid) {
                _current_animal = info.animal_info[animal_index];
            }
        }

        console.log("on_cb_start_dice guid:" + guid + " _current_animal.animal_id:", _current_animal.animal_id);

        if (_current_animal.animal_id != animal.rabbit) {
            this.dice_instance.node.active = true;
            let animationComponent = this.dice_instance.getComponent(Animation);
            const [ diceClip ] = animationComponent.clips;
            const diceState = animationComponent.getState(diceClip.name);
            animationComponent.play(diceState.name);
            diceState.wrapMode = AnimationClip.WrapMode.Loop;
        }
        else {
            {
                this.dice2_1_instance.node.active = true;
                let animationComponent = this.dice2_1_instance.getComponent(Animation);
                const [ diceClip ] = animationComponent.clips;
                const diceState = animationComponent.getState(diceClip.name);
                animationComponent.play(diceState.name);
                diceState.wrapMode = AnimationClip.WrapMode.Loop;
            }

            {
                this.dice2_2_instance.node.active = true;
                let animationComponent = this.dice2_2_instance.getComponent(Animation);
                const [ diceClip ] = animationComponent.clips;
                const diceState = animationComponent.getState(diceClip.name);
                animationComponent.play(diceState.name);
                diceState.wrapMode = AnimationClip.WrapMode.Loop;
            }
        }
    }

    private on_cb_throw_dice(guid:number, dice:number[]) {
        this.dice_instance.node.active = false;
        this.dice2_1_instance.node.active = false;
        this.dice2_2_instance.node.active = false;

        console.log("guid: " + guid + " on_cb_throw_dice dice:", dice);

        if (dice.length == 1) {
            let dice_num = dice[0];
            switch(dice_num){
                case 1:
                    this.dice_result_instance = this.dice_1;
                    break;
                case 2:
                    this.dice_result_instance = this.dice_2;
                    break;
                case 3:
                    this.dice_result_instance = this.dice_3;
                    break;
                case 4:
                    this.dice_result_instance = this.dice_4;
                    break;
                case 5:
                    this.dice_result_instance = this.dice_5;
                    break;
                case 6:
                    this.dice_result_instance = this.dice_6;
                    break;
            }
            this.dice_result_instance.node.active = true;
        }
        else {
            let dice_1_num = dice[0];
            let dice_2_num = dice[1];
            switch(dice_1_num){
                case 1:
                    this.dice_1_result_instance = this.dice_1_1;
                    break;
                case 2:
                    this.dice_1_result_instance = this.dice_1_2;
                    break;
                case 3:
                    this.dice_1_result_instance = this.dice_1_3;
                    break;
                case 4:
                    this.dice_1_result_instance = this.dice_1_4;
                    break;
                case 5:
                    this.dice_1_result_instance = this.dice_1_5;
                    break;
                case 6:
                    this.dice_1_result_instance = this.dice_1_6;
                    break;
            } 
            switch(dice_2_num){
                case 1:
                    this.dice_2_result_instance = this.dice_2_1;
                    break;
                case 2:
                    this.dice_2_result_instance = this.dice_2_2;
                    break;
                case 3:
                    this.dice_2_result_instance = this.dice_2_3;
                    break;
                case 4:
                    this.dice_2_result_instance = this.dice_2_4;
                    break;
                case 5:
                    this.dice_2_result_instance = this.dice_2_5;
                    break;
                case 6:
                    this.dice_2_result_instance = this.dice_2_6;
                    break;
            }
            this.dice_1_result_instance.node.active = true;
            this.dice_2_result_instance.node.active = true;

            if (guid == singleton.netSingleton.login.player_info.guid) {
                this.dice_1_result_instance.node.on(Node.EventType.MOUSE_DOWN, this.dice_1_callback, this);
                this.dice_2_result_instance.node.on(Node.EventType.MOUSE_DOWN, this.dice_2_callback, this);
            }
        }
    }

    private dice_1_callback() {
        if (singleton.netSingleton.game.choose_dice_rsp) {
            this.dice_1_result_instance.node.off(Node.EventType.MOUSE_DOWN, this.dice_1_callback, this);
            this.dice_2_result_instance.node.off(Node.EventType.MOUSE_DOWN, this.dice_2_callback, this);

            singleton.netSingleton.game.choose_dice_rsp.rsp(0);
            singleton.netSingleton.game.choose_dice_rsp = null;
        }
    }

    private dice_2_callback() {
        if (singleton.netSingleton.game.choose_dice_rsp) {
            this.dice_1_result_instance.node.off(Node.EventType.MOUSE_DOWN, this.dice_1_callback, this);
            this.dice_2_result_instance.node.off(Node.EventType.MOUSE_DOWN, this.dice_2_callback, this);

            singleton.netSingleton.game.choose_dice_rsp.rsp(1);
            singleton.netSingleton.game.choose_dice_rsp = null;
        }
    }

    private on_cb_rabbit_choose_dice(dice:number) {
        this.dice_1_result_instance.node.active = false;
        this.dice_2_result_instance.node.active = false;

        switch(dice){
            case 1:
                this.dice_result_instance = this.dice_1;
                break;
            case 2:
                this.dice_result_instance = this.dice_2;
                break;
            case 3:
                this.dice_result_instance = this.dice_3;
                break;
            case 4:
                this.dice_result_instance = this.dice_4;
                break;
            case 5:
                this.dice_result_instance = this.dice_5;
                break;
            case 6:
                this.dice_result_instance = this.dice_6;
                break;
        }
        this.dice_result_instance.node.active = true;
    }

    private on_cb_move(guid:number, animal_index:number, from:number, to:number) {
        console.log("guid:" + guid + " animal_index:" + animal_index);

        if (this.dice_result_instance) {
            this.dice_result_instance.node.active = false;
        }

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
            if (target_grid >= singleton.netSingleton.game.get_playground_len()) {
                continue;
            }
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
        if (target_y < 500) {
            target_y = 500;
        }
        else if ((1600 - target_y) < 480) {
            target_y = 1600 - 480;
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
                if (animal_info.current_pos != -1) {
                    let pos = this.mapPlayground.get(animal_info.current_pos);
                    target_x = pos.x * 64 + 32 - 800;
                    target_y=  pos.y * 64 + 32 - 800;
                }

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