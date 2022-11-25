import * as client_handle from "./client_handle";
import * as common from "./common";
/*this enum code is codegen by abelkhan codegen for ts*/

/*this struct code is codegen by abelkhan codegen for typescript*/
/*this module code is codegen by abelkhan codegen for typescript*/
export class game_client_module extends client_handle.imodule {
    public _client_handle:client_handle.client;
    constructor(_client_handle_:client_handle.client){
        super();
        this._client_handle = _client_handle_;
        this._client_handle._modulemng.add_method("game_client_game_info", this.game_info.bind(this));
        this._client_handle._modulemng.add_method("game_client_move", this.move.bind(this));

        this.cb_game_info = null;
        this.cb_move = null;
    }

    public cb_game_info : (info:common.player_game_info[])=>void | null;
    game_info(inArray:any[]){
        let _argv_:any[] = [];
        let _array_:any[] = [];
        for(let v_ of inArray[0]){
            _array_.push(common.protcol_to_player_game_info(v_));
        }
        _argv_.push(_array_);
        if (this.cb_game_info){
            this.cb_game_info.apply(null, _argv_);
        }
    }

    public cb_move : (guid:number, from:number, to:number)=>void | null;
    move(inArray:any[]){
        let _argv_:any[] = [];
        _argv_.push(inArray[0]);
        _argv_.push(inArray[1]);
        _argv_.push(inArray[2]);
        if (this.cb_move){
            this.cb_move.apply(null, _argv_);
        }
    }

}
