import * as client_handle from "./client_handle";
import * as common from "./common";
/*this enum code is codegen by abelkhan codegen for ts*/

/*this struct code is codegen by abelkhan codegen for typescript*/
export class effect_info
{
    public grids : number[];
    public effect_id : common.effect;

    constructor(){
    }
}

export function effect_info_to_protcol(_struct:effect_info){
    return _struct;
}

export function protcol_to_effect_info(_protocol:any){
    let _struct = new effect_info();
    for (const [key, val] of Object.entries(_protocol))        if (key === "grids"){
            _struct.grids = [];
            for(let v_ of val){
                _struct.grids.push(v_);
    }
        }
        else if (key === "effect_id"){
            _struct.effect_id = val as common.effect;
        }
    return _struct;
}

/*this module code is codegen by abelkhan codegen for typescript*/
export class game_client_module extends client_handle.imodule {
    public _client_handle:client_handle.client;
    constructor(_client_handle_:client_handle.client){
        super();
        this._client_handle = _client_handle_;
        this._client_handle._modulemng.add_method("game_client_game_info", this.game_info.bind(this));
        this._client_handle._modulemng.add_method("game_client_move", this.move.bind(this));
        this._client_handle._modulemng.add_method("game_client_relay", this.relay.bind(this));
        this._client_handle._modulemng.add_method("game_client_effect", this.effect.bind(this));
        this._client_handle._modulemng.add_method("game_client_use_skill", this.use_skill.bind(this));
        this._client_handle._modulemng.add_method("game_client_effect_move", this.effect_move.bind(this));

        this.cb_game_info = null;
        this.cb_move = null;
        this.cb_relay = null;
        this.cb_effect = null;
        this.cb_use_skill = null;
        this.cb_effect_move = null;
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

    public cb_relay : (guid:number, new_animal_index:number)=>void | null;
    relay(inArray:any[]){
        let _argv_:any[] = [];
        _argv_.push(inArray[0]);
        _argv_.push(inArray[1]);
        if (this.cb_relay){
            this.cb_relay.apply(null, _argv_);
        }
    }

    public cb_effect : (info:effect_info)=>void | null;
    effect(inArray:any[]){
        let _argv_:any[] = [];
        _argv_.push(protcol_to_effect_info(inArray[0]));
        if (this.cb_effect){
            this.cb_effect.apply(null, _argv_);
        }
    }

    public cb_use_skill : (guid:number)=>void | null;
    use_skill(inArray:any[]){
        let _argv_:any[] = [];
        _argv_.push(inArray[0]);
        if (this.cb_use_skill){
            this.cb_use_skill.apply(null, _argv_);
        }
    }

    public cb_effect_move : (guid:number, effect_id:common.effect, from:number, to:number)=>void | null;
    effect_move(inArray:any[]){
        let _argv_:any[] = [];
        _argv_.push(inArray[0]);
        _argv_.push(inArray[1]);
        _argv_.push(inArray[2]);
        _argv_.push(inArray[3]);
        if (this.cb_effect_move){
            this.cb_effect_move.apply(null, _argv_);
        }
    }

}
