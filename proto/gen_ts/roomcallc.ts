import * as client_handle from "./client_handle";
import * as common from "./common";
/*this enum code is codegen by abelkhan codegen for ts*/

/*this struct code is codegen by abelkhan codegen for typescript*/
/*this module code is codegen by abelkhan codegen for typescript*/
export class room_client_module extends client_handle.imodule {
    public _client_handle:client_handle.client;
    constructor(_client_handle_:client_handle.client){
        super();
        this._client_handle = _client_handle_;
        this._client_handle._modulemng.add_method("room_client_refresh_room_info", this.refresh_room_info.bind(this));
        this._client_handle._modulemng.add_method("room_client_transfer_refresh_room_info", this.transfer_refresh_room_info.bind(this));
        this._client_handle._modulemng.add_method("room_client_room_is_free", this.room_is_free.bind(this));
        this._client_handle._modulemng.add_method("room_client_player_leave_room_success", this.player_leave_room_success.bind(this));
        this._client_handle._modulemng.add_method("room_client_be_kicked", this.be_kicked.bind(this));
        this._client_handle._modulemng.add_method("room_client_team_into_match", this.team_into_match.bind(this));

        this.cb_refresh_room_info = null;
        this.cb_transfer_refresh_room_info = null;
        this.cb_room_is_free = null;
        this.cb_player_leave_room_success = null;
        this.cb_be_kicked = null;
        this.cb_team_into_match = null;
    }

    public cb_refresh_room_info : (info:common.room_info)=>void | null;
    refresh_room_info(inArray:any[]){
        let _argv_:any[] = [];
        _argv_.push(common.protcol_to_room_info(inArray[0]));
        if (this.cb_refresh_room_info){
            this.cb_refresh_room_info.apply(null, _argv_);
        }
    }

    public cb_transfer_refresh_room_info : (room_hub_name:string, info:common.room_info)=>void | null;
    transfer_refresh_room_info(inArray:any[]){
        let _argv_:any[] = [];
        _argv_.push(inArray[0]);
        _argv_.push(common.protcol_to_room_info(inArray[1]));
        if (this.cb_transfer_refresh_room_info){
            this.cb_transfer_refresh_room_info.apply(null, _argv_);
        }
    }

    public cb_room_is_free : ()=>void | null;
    room_is_free(inArray:any[]){
        let _argv_:any[] = [];
        if (this.cb_room_is_free){
            this.cb_room_is_free.apply(null, _argv_);
        }
    }

    public cb_player_leave_room_success : ()=>void | null;
    player_leave_room_success(inArray:any[]){
        let _argv_:any[] = [];
        if (this.cb_player_leave_room_success){
            this.cb_player_leave_room_success.apply(null, _argv_);
        }
    }

    public cb_be_kicked : ()=>void | null;
    be_kicked(inArray:any[]){
        let _argv_:any[] = [];
        if (this.cb_be_kicked){
            this.cb_be_kicked.apply(null, _argv_);
        }
    }

    public cb_team_into_match : ()=>void | null;
    team_into_match(inArray:any[]){
        let _argv_:any[] = [];
        if (this.cb_team_into_match){
            this.cb_team_into_match.apply(null, _argv_);
        }
    }

}
export class room_match_client_module extends client_handle.imodule {
    public _client_handle:client_handle.client;
    constructor(_client_handle_:client_handle.client){
        super();
        this._client_handle = _client_handle_;
        this._client_handle._modulemng.add_method("room_match_client_role_into_game", this.role_into_game.bind(this));

        this.cb_role_into_game = null;
    }

    public cb_role_into_game : (game_hub_name:string)=>void | null;
    role_into_game(inArray:any[]){
        let _argv_:any[] = [];
        _argv_.push(inArray[0]);
        if (this.cb_role_into_game){
            this.cb_role_into_game.apply(null, _argv_);
        }
    }

}
