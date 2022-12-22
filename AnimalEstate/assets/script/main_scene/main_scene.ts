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

        
        singleton.netSingleton.game.cb_game_info = () => {
            console.log("start match!");

            if (singleton.netSingleton.game.Playground == playground.lakeside){
                director.loadScene("lakeside_game");
            }
        }
    }

    update(deltaTime: number) {
    }

    start_match_callback() {
        console.log("start match!");

        this.match_interface.node.active = true;
    }
}