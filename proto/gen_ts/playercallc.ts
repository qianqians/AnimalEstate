import * as client_handle from "./client_handle";
import * as common from "./common";
/*this enum code is codegen by abelkhan codegen for ts*/

/*this struct code is codegen by abelkhan codegen for typescript*/
/*this module code is codegen by abelkhan codegen for typescript*/
export class player_client_module extends client_handle.imodule {
    public _client_handle:client_handle.client;
    constructor(_client_handle_:client_handle.client){
        super();
        this._client_handle = _client_handle_;
        this._client_handle._modulemng.add_method("player_client_be_displacement", this.be_displacement.bind(this));

        this.cb_be_displacement = null;
    }

    public cb_be_displacement : ()=>void | null;
    be_displacement(inArray:any[]){
        let _argv_:any[] = [];
        if (this.cb_be_displacement){
            this.cb_be_displacement.apply(null, _argv_);
        }
    }

}
export class player_game_client_module extends client_handle.imodule {
    public _client_handle:client_handle.client;
    constructor(_client_handle_:client_handle.client){
        super();
        this._client_handle = _client_handle_;
        this._client_handle._modulemng.add_method("player_game_client_game_svr", this.game_svr.bind(this));
        this._client_handle._modulemng.add_method("player_game_client_room_svr", this.room_svr.bind(this));
        this._client_handle._modulemng.add_method("player_game_client_settle", this.settle.bind(this));

        this.cb_game_svr = null;
        this.cb_room_svr = null;
        this.cb_settle = null;
    }

    public cb_game_svr : (game_hub_name:string)=>void | null;
    game_svr(inArray:any[]){
        let _argv_:any[] = [];
        _argv_.push(inArray[0]);
        if (this.cb_game_svr){
            this.cb_game_svr.apply(null, _argv_);
        }
    }

    public cb_room_svr : (room_hub_name:string)=>void | null;
    room_svr(inArray:any[]){
        let _argv_:any[] = [];
        _argv_.push(inArray[0]);
        if (this.cb_room_svr){
            this.cb_room_svr.apply(null, _argv_);
        }
    }

    public cb_settle : (settle_info:common.game_settle_info)=>void | null;
    settle(inArray:any[]){
        let _argv_:any[] = [];
        _argv_.push(common.protcol_to_game_settle_info(inArray[0]));
        if (this.cb_settle){
            this.cb_settle.apply(null, _argv_);
        }
    }

}
export class player_room_client_module extends client_handle.imodule {
    public _client_handle:client_handle.client;
    constructor(_client_handle_:client_handle.client){
        super();
        this._client_handle = _client_handle_;
        this._client_handle._modulemng.add_method("player_room_client_invite_role_join_room", this.invite_role_join_room.bind(this));

        this.cb_invite_role_join_room = null;
    }

    public cb_invite_role_join_room : (room_id:string, invite_role_name:string)=>void | null;
    invite_role_join_room(inArray:any[]){
        let _argv_:any[] = [];
        _argv_.push(inArray[0]);
        _argv_.push(inArray[1]);
        if (this.cb_invite_role_join_room){
            this.cb_invite_role_join_room.apply(null, _argv_);
        }
    }

}
export class player_friend_client_invite_role_friend_rsp {
    private uuid_f4abe68d_823d_33d5_a6f6_9ebff8eb6e18 : number;
    private hub_name_7b2d0e53_b589_37f7_a9bc_31fcce44d278:string;
    private _client_handle:client_handle.client ;

    constructor(_client_handle_:client_handle.client, current_hub:string, _uuid:number){
        this._client_handle = _client_handle_;
        this.hub_name_7b2d0e53_b589_37f7_a9bc_31fcce44d278 = current_hub;
        this.uuid_f4abe68d_823d_33d5_a6f6_9ebff8eb6e18 = _uuid;
    }

    public rsp(){
        let _argv_7b2d0e53_b589_37f7_a9bc_31fcce44d278:any[] = [this.uuid_f4abe68d_823d_33d5_a6f6_9ebff8eb6e18];
        this._client_handle.call_hub(this.hub_name_7b2d0e53_b589_37f7_a9bc_31fcce44d278, "player_friend_client_rsp_cb_invite_role_friend_rsp", _argv_7b2d0e53_b589_37f7_a9bc_31fcce44d278);
    }

    public err(){
        let _argv_7b2d0e53_b589_37f7_a9bc_31fcce44d278:any[] = [this.uuid_f4abe68d_823d_33d5_a6f6_9ebff8eb6e18];
        this._client_handle.call_hub(this.hub_name_7b2d0e53_b589_37f7_a9bc_31fcce44d278, "player_friend_client_rsp_cb_invite_role_friend_err", _argv_7b2d0e53_b589_37f7_a9bc_31fcce44d278);
    }

}

export class player_friend_client_agree_role_friend_rsp {
    private uuid_8d09e4bc_e374_3918_b734_2a4508dc1ab9 : number;
    private hub_name_1f120946_a2d8_34bf_a794_941de0d70f98:string;
    private _client_handle:client_handle.client ;

    constructor(_client_handle_:client_handle.client, current_hub:string, _uuid:number){
        this._client_handle = _client_handle_;
        this.hub_name_1f120946_a2d8_34bf_a794_941de0d70f98 = current_hub;
        this.uuid_8d09e4bc_e374_3918_b734_2a4508dc1ab9 = _uuid;
    }

    public rsp(){
        let _argv_1f120946_a2d8_34bf_a794_941de0d70f98:any[] = [this.uuid_8d09e4bc_e374_3918_b734_2a4508dc1ab9];
        this._client_handle.call_hub(this.hub_name_1f120946_a2d8_34bf_a794_941de0d70f98, "player_friend_client_rsp_cb_agree_role_friend_rsp", _argv_1f120946_a2d8_34bf_a794_941de0d70f98);
    }

    public err(){
        let _argv_1f120946_a2d8_34bf_a794_941de0d70f98:any[] = [this.uuid_8d09e4bc_e374_3918_b734_2a4508dc1ab9];
        this._client_handle.call_hub(this.hub_name_1f120946_a2d8_34bf_a794_941de0d70f98, "player_friend_client_rsp_cb_agree_role_friend_err", _argv_1f120946_a2d8_34bf_a794_941de0d70f98);
    }

}

export class player_friend_client_module extends client_handle.imodule {
    public _client_handle:client_handle.client;
    constructor(_client_handle_:client_handle.client){
        super();
        this._client_handle = _client_handle_;
        this._client_handle._modulemng.add_method("player_friend_client_invite_role_friend", this.invite_role_friend.bind(this));
        this._client_handle._modulemng.add_method("player_friend_client_agree_role_friend", this.agree_role_friend.bind(this));

        this.cb_invite_role_friend = null;

        this.cb_agree_role_friend = null;

    }

    public cb_invite_role_friend : (invite_player:common.player_friend_info)=>void | null;
    invite_role_friend(inArray:any[]){
        let _cb_uuid = inArray[0];
        let _argv_:any[] = [];
        _argv_.push(common.protcol_to_player_friend_info(inArray[1]));
        this.rsp = new player_friend_client_invite_role_friend_rsp(this._client_handle, this._client_handle.current_hub, _cb_uuid);
        if (this.cb_invite_role_friend){
            this.cb_invite_role_friend.apply(null, _argv_);
        }
        this.rsp = null;
    }

    public cb_agree_role_friend : (target_player:common.player_friend_info)=>void | null;
    agree_role_friend(inArray:any[]){
        let _cb_uuid = inArray[0];
        let _argv_:any[] = [];
        _argv_.push(common.protcol_to_player_friend_info(inArray[1]));
        this.rsp = new player_friend_client_agree_role_friend_rsp(this._client_handle, this._client_handle.current_hub, _cb_uuid);
        if (this.cb_agree_role_friend){
            this.cb_agree_role_friend.apply(null, _argv_);
        }
        this.rsp = null;
    }

}
