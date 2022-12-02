import * as cli from "../serverSDK/client_handle"
import * as common from "../serverSDK/common"

import * as player_room_match from "../serverSDK/ccallplayer"
import * as player_client from "../serverSDK/playercallc"

import * as singleton from "./netSingleton"

export class netMatch {
    private c_player_match_caller : player_room_match.client_match_caller;
    private player_match_module : player_client.player_game_client_module;

    public constructor() {
        this.c_player_match_caller = new player_room_match.client_match_caller(cli.cli_handle);

        this.player_match_module = new player_client.player_game_client_module(cli.cli_handle);
        this.player_match_module.cb_room_svr = this.on_cb_room_svr.bind(this);
        this.player_match_module.cb_game_svr = this.on_cb_game_svr.bind(this);
        this.player_match_module.cb_settle = this.on_cb_settle.bind(this);
    }

    public start_match(_playground:common.playground) {
        this.c_player_match_caller.get_hub(singleton.netSingleton.login.player_name).start_match(_playground);
    }

    private on_cb_room_svr(room_hub_name : string) {
        singleton.netSingleton.room.into_room(room_hub_name);
    }

    private on_cb_game_svr(game_hub_name : string) {
        singleton.netSingleton.game.into_game(game_hub_name);
    }

    public cb_settle : (settle_info:common.game_settle_info) => void;
    private on_cb_settle(settle_info:common.game_settle_info) {
        this.cb_settle.call(null, settle_info);
    }
}