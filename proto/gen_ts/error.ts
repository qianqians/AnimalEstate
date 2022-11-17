import * as client_handle from "./client_handle";
/*this enum code is codegen by abelkhan codegen for ts*/

export enum error{
    timeout = -2,
    db_error = -1,
    success = 0,
    invalid_team = 2,
    not_leader = 3,
    more_team_members = 4,
    in_game = 5,
    not_in_match = 6,
    wait_into_game = 7,
    is_in_match = 8,
    is_ready = 9,
    not_all_ready = 10,
    drop_box_too_far = 11,
    invalid_drop_box = 12,
    box_is_occupied = 13,
    not_open_drop_box = 14,
    drop_box_not_have_this_item = 15,
    invalid_drop_team = 16,
    not_at_door = 17,
    battle_is_end = 18,
    team_is_full = 19,
    invalid_role = 20
}

/*this struct code is codegen by abelkhan codegen for typescript*/
/*this module code is codegen by abelkhan codegen for typescript*/
export class error_code_ntf_module extends client_handle.imodule {
    public _client_handle:client_handle.client;
    constructor(_client_handle_:client_handle.client){
        super();
        this._client_handle = _client_handle_;
        this._client_handle._modulemng.add_method("error_code_ntf_error_code", this.error_code.bind(this));

        this.cb_error_code = null;
    }

    public cb_error_code : (error:number)=>void | null;
    error_code(inArray:any[]){
        let _argv_:any[] = [];
        _argv_.push(inArray[0]);
        if (this.cb_error_code){
            this.cb_error_code.apply(null, _argv_);
        }
    }

}
