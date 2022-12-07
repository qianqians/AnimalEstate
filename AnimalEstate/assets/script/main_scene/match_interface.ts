import { _decorator, Component, Node, Button, Sprite, director } from 'cc';
const { ccclass, property } = _decorator;

import * as singleton from '../netDriver/netSingleton';
import { playground } from '../serverSDK/common';

@ccclass('match_interface')
export class match_interface extends Component {
    @property(Button)
    start_match_game:Button = null;
    @property(Sprite)
    random_sprite:Sprite = null;
    @property(Sprite)
    lakside_sprite:Sprite = null;

    enum_playground:playground = playground.random;

    set_thumbnail() {
        this.random_sprite.node.active = false;
        this.lakside_sprite.node.active = false;

        switch(this.enum_playground) {
            case playground.random:
                this.random_sprite.node.active = true;
                break;
            case playground.lakeside:
                this.lakside_sprite.node.active = true;
                break;
        }
    }

    start() {
        this.set_thumbnail();

        this.start_match_game.node.on(Node.EventType.MOUSE_DOWN, this.start_match_game_callback, this);

        singleton.netSingleton.game.cb_game_wait_start_info = () => {
            console.log("start match!");

            if (singleton.netSingleton.game.Playground == playground.lakeside){
                director.loadScene("lakeside_game");
            }

            this.node.active = false;
        };
    }

    update(deltaTime: number) {
    }
    
    start_match_game_callback() {
        singleton.netSingleton.match.start_match(this.enum_playground);
    }
}


