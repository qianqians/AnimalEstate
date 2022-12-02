import * as cli from "../serverSDK/client_handle";
import * as common from "../serverSDK/common";
import * as error from "../serverSDK/error"

import * as client_call_room_caller from "../serverSDK/ccallroom"
import * as room_client from "../serverSDK/roomcallc"

import * as singleton from "./netSingleton"

export class netRoom {
    private room_hub_name : string;
    private ccallroom : client_call_room_caller.client_room_match_caller;

    private room_call_client : room_client.room_client_module;
    private room_match_call_client : room_client.room_match_client_module;

    constructor() {
        this.ccallroom = new client_call_room_caller.client_room_match_caller(cli.cli_handle);

        this.room_call_client = new room_client.room_client_module(cli.cli_handle);
        this.room_call_client.cb_refresh_room_info = this.on_cb_refresh_room_info.bind(this);
        this.room_call_client.cb_chat = this.on_cb_chat.bind(this);
        this.room_call_client.cb_room_is_free = this.on_cb_room_is_free.bind(this);
        this.room_call_client.cb_player_leave_room_success = this.on_cb_player_leave_room_success.bind(this);
        this.room_call_client.cb_be_kicked = this.on_cb_be_kicked.bind(this);
        this.room_call_client.cb_team_into_match = this.on_cb_team_into_match.bind(this);

        this.room_match_call_client = new room_client.room_match_client_module(cli.cli_handle);
        this.room_match_call_client.cb_role_into_game = this.on_cb_role_into_game.bind(this);
    }

    public into_room(room_hub_name : string) {
        this.room_hub_name = room_hub_name;
        this.ccallroom.get_hub(this.room_hub_name).into_room();
    }

    public chat(chat_str : string) {
        this.ccallroom.get_hub(this.room_hub_name).chat(chat_str);
    }

    public leave_room() {
        this.ccallroom.get_hub(this.room_hub_name).leave_room();
    }

    public kick_out(guid : number) {
        this.ccallroom.get_hub(this.room_hub_name).kick_out(guid);
    }

    public disband() {
        this.ccallroom.get_hub(this.room_hub_name).disband();
    }

    public start_match() {
        this.ccallroom.get_hub(this.room_hub_name).start_match();
    }

    public cb_refresh_room_info : (info:common.room_info) => void;
    private on_cb_refresh_room_info(info:common.room_info) {
        this.cb_refresh_room_info.call(null, info);
    }

    public cb_chat : (chat_player_guid:number, chat_str:string) => void;
    private on_cb_chat(chat_player_guid:number, chat_str:string) {
        this.cb_chat.call(null, chat_player_guid, chat_str)
    }

    public cb_room_is_free : () => void;
    private on_cb_room_is_free() {
        this.cb_room_is_free.call(null);
        this.room_hub_name = "";
    }

    private on_cb_player_leave_room_success() {
        this.room_hub_name = "";
    }

    public cb_be_kicked : () => void;
    private on_cb_be_kicked() {
        this.cb_be_kicked.call(null);
        this.room_hub_name = "";
    }

    public cb_team_into_match : () => void;
    private on_cb_team_into_match() {
        this.cb_team_into_match.call(null);
    }

    private on_cb_role_into_game(game_hub_name:string) {
        singleton.netSingleton.game.into_game(game_hub_name);
    }
}