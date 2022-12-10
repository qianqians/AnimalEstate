import { _decorator, Component, Node, Button, Sprite, Label, director } from 'cc';
const { ccclass, property } = _decorator;

import * as singleton from '../netDriver/netSingleton';
import { playground } from '../serverSDK/common';

@ccclass('match_interface')
export class match_interface extends Component {
    @property(Button)
    start_match_game:Button = null;
    @property(Button)
    left:Button = null;
    @property(Button)
    right:Button = null;
    @property(Label)
    countdown:Label = null;
    @property(Sprite)
    random_sprite:Sprite = null;
    @property(Sprite)
    lakside_sprite:Sprite = null;

    enum_playground:playground = playground.random;
    countdown_count:number = 5;

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

        this.countdown.node.active = false;

        this.start_match_game.node.on(Node.EventType.MOUSE_DOWN, this.start_match_game_callback, this);
        this.left.node.on(Node.EventType.MOUSE_DOWN, this.left_callback, this);
        this.right.node.on(Node.EventType.MOUSE_DOWN, this.right_callback, this);

        singleton.netSingleton.game.cb_game_wait_start_info = () => {
            console.log("start match!");

            this.unschedule(this.countdown_callback);

            if (singleton.netSingleton.game.Playground == playground.lakeside){
                director.loadScene("lakeside_game");
            }

            this.node.active = false;
        };
    }

    update(deltaTime: number) {
    }
    
    countdown_callback() {
        this.countdown.string = (--this.countdown_count).toString();
    }

    start_match_game_callback() {
        singleton.netSingleton.match.start_match(this.enum_playground);

        this.countdown.node.active = true;
        this.schedule(this.countdown_callback, 1);
    }

    left_callback() {
        this.enum_playground--;
        if (this.enum_playground < 0) {
            this.enum_playground = playground.lakeside;
        }
        this.set_thumbnail();
    }

    right_callback() {
        this.enum_playground++;
        if (this.enum_playground > playground.lakeside) {
            this.enum_playground = playground.random;
        }
        this.set_thumbnail();
    }
}


