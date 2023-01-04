import * as cli from "../serverSDK/client_handle"
import * as common from "../serverSDK/common"

import * as client_game_caller from "../serverSDK/ccallgame"
import * as game_client_module from "../serverSDK/gamecallc"

import * as login from "./netLogin"

export class netGame {
    private login_handle : login.netLogin;

    public game_hub_name : string;
    private game_caller : client_game_caller.game_caller;

    private game_call_client_module : game_client_module.game_client_module;

    public PlayerAnimalMap : Map<number, Map<number, any> > = new Map<number, Map<number, any> >();

    public constructor(_login : login.netLogin) {
        this.login_handle = _login;

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
        this.game_caller.get_hub(this.game_hub_name).into_game(this.login_handle.player_info.guid);
    }

    public use_skill(target_guid:number, target_animal_index:number) {
        this.game_caller.get_hub(this.game_hub_name).use_skill(target_guid, target_animal_index);
    }

    public throw_dice() {
        this.game_caller.get_hub(this.game_hub_name).throw_dice();
    }

    public get_playground_len(){
        if (this.Playground == common.playground.lakeside) {
            return 64;
        }

        return 0;
    }

    public Countdown:number;
    public Playground:common.playground;
    public CurrentPlayerInfo:common.player_game_info = null;
    public PlayerGameInfo:common.player_game_info[];
    public cb_game_wait_start_info : () => void;
    private on_cb_game_wait_start_info(countdown:number, _playground:common.playground, info:common.player_game_info[]) {
        this.Countdown = countdown;
        this.Playground = _playground;
        this.PlayerGameInfo = info;
        if (this.cb_game_wait_start_info) {
            this.cb_game_wait_start_info.call(null);
        }
    }

    public cb_game_info : () => void;
    private on_cb_game_info(_playground:common.playground, info:common.player_game_info[], round_player_guid:number) {
        this.Playground = _playground;
        console.log("this.Playground:", this.Playground);
        this.PlayerGameInfo = info;
        for(let info of this.PlayerGameInfo) {
            if (info.guid == round_player_guid) {
                this.CurrentPlayerInfo = info;
            }
        }
        if (this.cb_game_info) {
            this.cb_game_info.call(null);
        }
    }

    public cb_ntf_effect_info : (info:game_client_module.effect_info[]) => void;
    private on_cb_ntf_effect_info(info:game_client_module.effect_info[]) {
        if (this.cb_ntf_effect_info) {
            this.cb_ntf_effect_info.call(null, info);
        }
    }

    public cb_ntf_new_effect_info : (info:game_client_module.effect_info) => void;
    private on_cb_ntf_new_effect_info(info:game_client_module.effect_info) {
        if (this.cb_ntf_new_effect_info) {
            this.cb_ntf_new_effect_info.call(null, info);
        }
    }

    public cb_turn_player_round : (guid:number) => void;
    private on_cb_turn_player_round(guid:number) {
        if (this.cb_turn_player_round) {
            this.cb_turn_player_round.call(null, guid);
        }
    }

    public cb_throw_dice : (guid:number, dice:number[]) => void;
    private on_cb_throw_dice(guid:number, dice:number[]) {
        if (this.cb_throw_dice) {
            this.cb_throw_dice.call(null, guid, dice);
        }
    }

    public cb_move : (guid:number, animal_index:number, from:number, to:number) => void;
    private on_cb_move(guid:number, animal_index:number, from:number, to:number) {
        if (this.cb_move) {
            this.cb_move.call(null, guid, animal_index, from, to);
        }
    }

    public cb_relay : (guid:number, new_animal_index:number) => void;
    private on_cb_relay(guid:number, new_animal_index:number) {
        if (this.cb_relay) {
            this.cb_relay.call(null, guid, new_animal_index);
        }
    }

    public cb_use_skill : (guid:number) => void
    private on_cb_use_skill(guid:number) {
        if (this.cb_use_skill) {
            this.cb_use_skill.call(null, guid);
        }
    }

    public cb_effect_move : (guid:number, effect_id:common.effect, from:number, to:number) => void;
    private on_cb_effect_move(guid:number, effect_id:common.effect, from:number, to:number) {
        if (this.cb_effect_move) {
            this.cb_effect_move.call(null, guid, effect_id, from, to);
        }
    }
}