import * as client_handle from "./client_handle";
import * as common from "./common";
/*this enum code is codegen by abelkhan codegen for ts*/

export enum enum_add_props_type{
    pick_up = 1,
    gacha_add = 2
}

/*this struct code is codegen by abelkhan codegen for typescript*/
export class effect_info
{
    public grids : number[];
    public effect_id : common.effect;
    public continued_rounds : number;

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
        else if (key === "continued_rounds"){
            _struct.continued_rounds = val as number;
        }
    return _struct;
}

/*this module code is codegen by abelkhan codegen for typescript*/
export class game_client_choose_dice_rsp {
    private uuid_7ed84a95_822b_31ca_bfce_b880528f1fc1 : number;
    private hub_name_ffefe8e1_59c2_3292_8600_93dfa9b71e7f:string;
    private _client_handle:client_handle.client ;

    constructor(_client_handle_:client_handle.client, current_hub:string, _uuid:number){
        this._client_handle = _client_handle_;
        this.hub_name_ffefe8e1_59c2_3292_8600_93dfa9b71e7f = current_hub;
        this.uuid_7ed84a95_822b_31ca_bfce_b880528f1fc1 = _uuid;
    }

    public rsp(dice_index:number){
        let _argv_ffefe8e1_59c2_3292_8600_93dfa9b71e7f:any[] = [this.uuid_7ed84a95_822b_31ca_bfce_b880528f1fc1];
        _argv_ffefe8e1_59c2_3292_8600_93dfa9b71e7f.push(dice_index);
        this._client_handle.call_hub(this.hub_name_ffefe8e1_59c2_3292_8600_93dfa9b71e7f, "game_client_rsp_cb_choose_dice_rsp", _argv_ffefe8e1_59c2_3292_8600_93dfa9b71e7f);
    }

    public err(){
        let _argv_ffefe8e1_59c2_3292_8600_93dfa9b71e7f:any[] = [this.uuid_7ed84a95_822b_31ca_bfce_b880528f1fc1];
        this._client_handle.call_hub(this.hub_name_ffefe8e1_59c2_3292_8600_93dfa9b71e7f, "game_client_rsp_cb_choose_dice_err", _argv_ffefe8e1_59c2_3292_8600_93dfa9b71e7f);
    }

}

export class game_client_module extends client_handle.imodule {
    public _client_handle:client_handle.client;
    constructor(_client_handle_:client_handle.client){
        super();
        this._client_handle = _client_handle_;
        this._client_handle._modulemng.add_method("game_client_game_wait_start_info", this.game_wait_start_info.bind(this));
        this._client_handle._modulemng.add_method("game_client_game_info", this.game_info.bind(this));
        this._client_handle._modulemng.add_method("game_client_ntf_effect_info", this.ntf_effect_info.bind(this));
        this._client_handle._modulemng.add_method("game_client_ntf_new_effect_info", this.ntf_new_effect_info.bind(this));
        this._client_handle._modulemng.add_method("game_client_turn_player_round", this.turn_player_round.bind(this));
        this._client_handle._modulemng.add_method("game_client_throw_dice", this.throw_dice.bind(this));
        this._client_handle._modulemng.add_method("game_client_choose_dice", this.choose_dice.bind(this));
        this._client_handle._modulemng.add_method("game_client_rabbit_choose_dice", this.rabbit_choose_dice.bind(this));
        this._client_handle._modulemng.add_method("game_client_move", this.move.bind(this));
        this._client_handle._modulemng.add_method("game_client_relay", this.relay.bind(this));
        this._client_handle._modulemng.add_method("game_client_use_skill", this.use_skill.bind(this));
        this._client_handle._modulemng.add_method("game_client_reset_position", this.reset_position.bind(this));
        this._client_handle._modulemng.add_method("game_client_effect_move", this.effect_move.bind(this));
        this._client_handle._modulemng.add_method("game_client_use_props", this.use_props.bind(this));
        this._client_handle._modulemng.add_method("game_client_add_props", this.add_props.bind(this));

        this.cb_game_wait_start_info = null;
        this.cb_game_info = null;
        this.cb_ntf_effect_info = null;
        this.cb_ntf_new_effect_info = null;
        this.cb_turn_player_round = null;
        this.cb_throw_dice = null;
        this.cb_choose_dice = null;

        this.cb_rabbit_choose_dice = null;
        this.cb_move = null;
        this.cb_relay = null;
        this.cb_use_skill = null;
        this.cb_reset_position = null;
        this.cb_effect_move = null;
        this.cb_use_props = null;
        this.cb_add_props = null;
    }

    public cb_game_wait_start_info : (countdown:number, _playground:common.playground, info:common.player_game_info[])=>void | null;
    game_wait_start_info(inArray:any[]){
        let _argv_:any[] = [];
        _argv_.push(inArray[0]);
        _argv_.push(inArray[1]);
        let _array_:any[] = [];
        for(let v_ of inArray[2]){
            _array_.push(common.protcol_to_player_game_info(v_));
        }
        _argv_.push(_array_);
        if (this.cb_game_wait_start_info){
            this.cb_game_wait_start_info.apply(null, _argv_);
        }
    }

    public cb_game_info : (_playground:common.playground, info:common.player_game_info[], round_player_guid:number)=>void | null;
    game_info(inArray:any[]){
        let _argv_:any[] = [];
        _argv_.push(inArray[0]);
        let _array_:any[] = [];
        for(let v_ of inArray[1]){
            _array_.push(common.protcol_to_player_game_info(v_));
        }
        _argv_.push(_array_);
        _argv_.push(inArray[2]);
        if (this.cb_game_info){
            this.cb_game_info.apply(null, _argv_);
        }
    }

    public cb_ntf_effect_info : (info:effect_info[])=>void | null;
    ntf_effect_info(inArray:any[]){
        let _argv_:any[] = [];
        let _array_:any[] = [];
        for(let v_ of inArray[0]){
            _array_.push(protcol_to_effect_info(v_));
        }
        _argv_.push(_array_);
        if (this.cb_ntf_effect_info){
            this.cb_ntf_effect_info.apply(null, _argv_);
        }
    }

    public cb_ntf_new_effect_info : (info:effect_info)=>void | null;
    ntf_new_effect_info(inArray:any[]){
        let _argv_:any[] = [];
        _argv_.push(protcol_to_effect_info(inArray[0]));
        if (this.cb_ntf_new_effect_info){
            this.cb_ntf_new_effect_info.apply(null, _argv_);
        }
    }

    public cb_turn_player_round : (guid:number)=>void | null;
    turn_player_round(inArray:any[]){
        let _argv_:any[] = [];
        _argv_.push(inArray[0]);
        if (this.cb_turn_player_round){
            this.cb_turn_player_round.apply(null, _argv_);
        }
    }

    public cb_throw_dice : (guid:number, dice:number[])=>void | null;
    throw_dice(inArray:any[]){
        let _argv_:any[] = [];
        _argv_.push(inArray[0]);
        let _array_:any[] = [];
        for(let v_ of inArray[1]){
            _array_.push(v_);
        }
        _argv_.push(_array_);
        if (this.cb_throw_dice){
            this.cb_throw_dice.apply(null, _argv_);
        }
    }

    public cb_choose_dice : ()=>void | null;
    choose_dice(inArray:any[]){
        let _cb_uuid = inArray[0];
        let _argv_:any[] = [];
        this.rsp = new game_client_choose_dice_rsp(this._client_handle, this._client_handle.current_hub, _cb_uuid);
        if (this.cb_choose_dice){
            this.cb_choose_dice.apply(null, _argv_);
        }
        this.rsp = null;
    }

    public cb_rabbit_choose_dice : (dice:number)=>void | null;
    rabbit_choose_dice(inArray:any[]){
        let _argv_:any[] = [];
        _argv_.push(inArray[0]);
        if (this.cb_rabbit_choose_dice){
            this.cb_rabbit_choose_dice.apply(null, _argv_);
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

    public cb_use_skill : (guid:number, target_guid:number, target_animal_index:number)=>void | null;
    use_skill(inArray:any[]){
        let _argv_:any[] = [];
        _argv_.push(inArray[0]);
        _argv_.push(inArray[1]);
        _argv_.push(inArray[2]);
        if (this.cb_use_skill){
            this.cb_use_skill.apply(null, _argv_);
        }
    }

    public cb_reset_position : (info:common.player_game_info[])=>void | null;
    reset_position(inArray:any[]){
        let _argv_:any[] = [];
        let _array_:any[] = [];
        for(let v_ of inArray[0]){
            _array_.push(common.protcol_to_player_game_info(v_));
        }
        _argv_.push(_array_);
        if (this.cb_reset_position){
            this.cb_reset_position.apply(null, _argv_);
        }
    }

    public cb_effect_move : (effect_id:common.effect, guid:number, target_animal_index:number, from:number, to:number)=>void | null;
    effect_move(inArray:any[]){
        let _argv_:any[] = [];
        _argv_.push(inArray[0]);
        _argv_.push(inArray[1]);
        _argv_.push(inArray[2]);
        _argv_.push(inArray[3]);
        _argv_.push(inArray[4]);
        if (this.cb_effect_move){
            this.cb_effect_move.apply(null, _argv_);
        }
    }

    public cb_use_props : (guid:number, props_id:common.props, target_guid:number, target_animal_index:number)=>void | null;
    use_props(inArray:any[]){
        let _argv_:any[] = [];
        _argv_.push(inArray[0]);
        _argv_.push(inArray[1]);
        _argv_.push(inArray[2]);
        _argv_.push(inArray[3]);
        if (this.cb_use_props){
            this.cb_use_props.apply(null, _argv_);
        }
    }

    public cb_add_props : (add_type:enum_add_props_type, guid:number, props_id:common.props)=>void | null;
    add_props(inArray:any[]){
        let _argv_:any[] = [];
        _argv_.push(inArray[0]);
        _argv_.push(inArray[1]);
        _argv_.push(inArray[2]);
        if (this.cb_add_props){
            this.cb_add_props.apply(null, _argv_);
        }
    }

}
