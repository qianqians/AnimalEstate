import * as client_handle from "./client_handle";
/*this enum code is codegen by abelkhan codegen for ts*/

/*this struct code is codegen by abelkhan codegen for typescript*/
/*this module code is codegen by abelkhan codegen for typescript*/
export class game_client_module extends client_handle.imodule {
    public _client_handle:client_handle.client;
    constructor(_client_handle_:client_handle.client){
        super();
        this._client_handle = _client_handle_;
        this._client_handle._modulemng.add_method("game_client_move", this.move.bind(this));

        this.cb_move = null;
    }

    public cb_move : (from:number, to:number)=>void | null;
    move(inArray:any[]){
        let _argv_:any[] = [];
        _argv_.push(inArray[0]);
        _argv_.push(inArray[1]);
        if (this.cb_move){
            this.cb_move.apply(null, _argv_);
        }
    }

}
