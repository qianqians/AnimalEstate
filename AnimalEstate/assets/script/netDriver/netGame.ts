import * as cli from "../serverSDK/client_handle"
import * as common from "../serverSDK/common"

import * as client_game_caller from "../serverSDK/ccallgame"
import * as game_client_module from "../serverSDK/gamecallc"

import * as singleton from "./netSingleton"

export class netGame {
    private game_hub_name : string;
    private game_caller : client_game_caller.game_caller;

    private game_call_client_module : game_client_module.game_client_module;

    public constructor() {
        this.game_caller = new client_game_caller.game_caller(cli.cli_handle);

        this.game_call_client_module = new game_client_module.game_client_module(cli.cli_handle);
        this.game_call_client_module.cb_game_wait_start_info = this.on_cb_game_wait_start_info.bind(this);
        this.game_call_client_module.cb_game_info = this.on_cb_game_info.bind(this);
        this.game_call_client_module.cb_ntf_effect_info = this.on_cb_ntf_effect_info.bind(this);
        this.game_call_client_module.cb_ntf_new_effect_info = this.on_cb_ntf_new_effect_info.bind(this);
        this.game_call_client_module.cb_turn_player_round = this.on_cb_turn_player_round.bind(this);
        this.game_call_client_module.cb_throw_dice = this.on_cb_throw_dice.bind(this);
        this.game_call_client_module.cb_move = this.on_cb_move.bind(this);
        this.game_call_client_module.cb_relay = this.on_cb_relay.bind(this);
        this.game_call_client_module.cb_use_skill = this.on_cb_use_skill.bind(this);
        this.game_call_client_module.cb_effect_move = this.on_cb_effect_move.bind(this);
    }

    public into_game(game_hub_name : string) {
        this.game_hub_name = game_hub_name;
        this.game_caller.get_hub(this.game_hub_name).into_game(singleton.netSingleton.login.player_info.guid);
    }

    public use_skill() {
        this.game_caller.get_hub(this.game_hub_name).use_skill();
    }

    public throw_dice() {
        this.game_caller.get_hub(this.game_hub_name).throw_dice();
    }

    public cb_game_wait_start_info : (countdown:number, _playground:common.playground, info:common.player_game_info[]) => void;
    private on_cb_game_wait_start_info(countdown:number, _playground:common.playground, info:common.player_game_info[]) {
        this.cb_game_wait_start_info.call(null, countdown, _playground, info);
    }

    public cb_game_info : (_playground:common.playground, info:common.player_game_info[]) => void;
    private on_cb_game_info(_playground:common.playground, info:common.player_game_info[]) {
        this.cb_game_info.call(null, _playground, info);
    }

    public cb_ntf_effect_info : (info:game_client_module.effect_info[]) => void;
    private on_cb_ntf_effect_info(info:game_client_module.effect_info[]) {
        this.cb_ntf_effect_info.call(null, info);
    }

    public cb_ntf_new_effect_info : (info:game_client_module.effect_info) => void;
    private on_cb_ntf_new_effect_info(info:game_client_module.effect_info) {
        this.cb_ntf_new_effect_info.call(null, info);
    }

    public cb_turn_player_round : (guid:number) => void;
    private on_cb_turn_player_round(guid:number) {
        this.cb_turn_player_round.call(null, guid);
    }

    public cb_throw_dice : (guid:number, dice:number[]) => void;
    private on_cb_throw_dice(guid:number, dice:number[]) {
        this.cb_throw_dice.call(null, guid, dice);
    }

    public cb_move : (guid:number, from:number, to:number) => void;
    private on_cb_move(guid:number, from:number, to:number) {
        this.cb_move.call(null, guid, from, to);
    }

    public cb_relay : (guid:number, new_animal_index:number) => void;
    private on_cb_relay(guid:number, new_animal_index:number) {
        this.cb_relay.call(null, guid, new_animal_index);
    }

    public cb_use_skill : (guid:number) => void
    private on_cb_use_skill(guid:number) {
        this.cb_use_skill.call(null, guid);
    }

    public cb_effect_move : (guid:number, effect_id:common.effect, from:number, to:number) => void;
    private on_cb_effect_move(guid:number, effect_id:common.effect, from:number, to:number) {
        this.cb_effect_move.call(null, guid, effect_id, from, to)
    }
}