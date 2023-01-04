import { _decorator, Component, Node, Button, Widget, find, director } from 'cc';
const { ccclass, property } = _decorator;

import * as singleton from '../netDriver/netSingleton';
import { playground } from '../serverSDK/common';

@ccclass('main_scene')
export class main_scene extends Component {
    @property(Button)
    leaderboard:Button = null;
    @property(Button)
    setting:Button = null;
    @property(Button)
    start_match_btn:Button = null;
    @property(Button)
    invite_friend_btn:Button = null;

    @property(Widget)
    match_interface:Widget = null;

    start() {
        this.match_interface.node.active = false;
        this.start_match_btn.node.on(Node.EventType.MOUSE_DOWN, this.start_match_callback, this);

        this.check_reconnect();

        singleton.netSingleton.game.cb_game_info = () => {
            console.log("start match!");
            this.check_reconnect();
        }
    }

    update(deltaTime: number) {
    }

    check_reconnect() {
        if (singleton.netSingleton.game.game_hub_name) {
            console.log("start game!");
            console.log("Playground:", singleton.netSingleton.game.Playground);
            if (singleton.netSingleton.game.Playground == playground.lakeside){
                console.log("start game reconnect!");
                director.loadScene("lakeside_game");
            }
        }
    }

    start_match_callback() {
        console.log("start match!");

        this.match_interface.node.active = true;
    }
}