import { _decorator, Component, Node, Button, EditBox, find, director } from 'cc';
const { ccclass, property } = _decorator;

import * as singleton from '../netDriver/netSingleton';
import { playground, player_game_info } from '../serverSDK/common';

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

    start() {
        this.start_match_btn.node.on(Node.EventType.MOUSE_DOWN, this.start_match_callback, this);

        singleton.netSingleton.game.cb_game_wait_start_info = (countdown:number, _playground:playground, info:player_game_info[]) => {
            console.log("start game!");
            director.loadScene("game");
        };
    }

    update(deltaTime: number) {
    }

    start_match_callback() {
        console.log("start match!");
        singleton.netSingleton.match.start_match(playground.lakeside);
    }
}