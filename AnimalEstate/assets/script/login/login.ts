import { _decorator, Component, Node, Button, EditBox, director } from 'cc';
const { ccclass, property } = _decorator;

import * as singleton from '../netDriver/netSingleton';

@ccclass('login')
export class login extends Component {
    @property(Node)
    netBode:Node = null;
    @property(Button)
    loginBtn:Button = null;
    @property(EditBox)
    account:EditBox = null;
    
    start() {
        this.account.node.active = false;
        this.loginBtn.node.on(Node.EventType.MOUSE_DOWN, this.callback, this);

        singleton.netSingleton.login.cb_player_login_non_account = () => {
            console.log("login non_account create role");
            singleton.netSingleton.login.create_role(this._accountName);
        };

        singleton.netSingleton.login.cb_player_login_sucess = () => {
            console.log("login sucess!");
            director.loadScene("main");
        }

        this.netBode.on("connect",(e)=>{
            this.account.node.active = true;
        });
    }

    private _accountName = "";
    callback(){
        console.log(this.account.textLabel.string);
        this._accountName = this.account.textLabel.string;

        singleton.netSingleton.login.login_player_no_author(this._accountName);
    }

    update(deltaTime: number) {
    }
}

