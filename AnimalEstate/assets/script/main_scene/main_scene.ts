import { _decorator, Component, Node, Button, Widget, find, director } from 'cc';
const { ccclass, property } = _decorator;

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
    }

    update(deltaTime: number) {
    }

    start_match_callback() {
        console.log("start match!");

        this.match_interface.node.active = true;
    }
}