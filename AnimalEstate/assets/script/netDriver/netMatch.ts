import * as cli from "../serverSDK/client_handle"
import * as common from "../serverSDK/common"

import * as player_room_match from "../serverSDK/ccallplayer"
import * as player_client from "../serverSDK/playercallc"

import * as login from "./netLogin"
import * as room from "./netRoom"
import * as game from "./netGame"

export class netMatch {
    private login_handle : login.netLogin;
    private room_handle : room.netRoom;
    private game_handle : game.netGame;

    private c_player_match_caller : player_room_match.client_match_caller;
    private player_match_module : player_client.player_game_client_module;

    public constructor(_login:login.netLogin, _room:room.netRoom, _game:game.netGame) {
        this.login_handle = _login;
        this.room_handle = _room;
        this.game_handle = _game;

        this.c_player_match_caller = new player_room_match.client_match_caller(cli.cli_handle);

        this.player_match_module = new player_client.player_game_client_module(cli.cli_handle);
        this.player_match_module.cb_room_svr = this.on_cb_room_svr.bind(this);
        this.player_match_module.cb_game_svr = this.on_cb_game_svr.bind(this);
        this.player_match_module.cb_settle = this.on_cb_settle.bind(this);
    }

    public start_match(_playground:common.playground) {
        this.c_player_match_caller.get_hub(this.login_handle.player_name).start_match(_playground);
    }

    private on_cb_room_svr(room_hub_name : string) {
        this.room_handle.into_room(room_hub_name);
    }

    private on_cb_game_svr(game_hub_name : string) {
        this.game_handle.into_game(game_hub_name);
    }

    public cb_settle : (settle_info:common.game_settle_info) => void;
    private on_cb_settle(settle_info:common.game_settle_info) {
        this.cb_settle.call(null, settle_info);
    }
}