import * as cli from "../serverSDK/client_handle";
import * as common from "../serverSDK/common";
import * as error from "../serverSDK/error"

import * as client_game_caller from "../serverSDK/ccallgame"
import * as game_client_module from "../serverSDK/gamecallc"

import * as singleton from "./netSingleton"

export class netGame {
    private game_hub_name : string;
    private game_caller : client_game_caller.game_caller;

    

    constructor() {
        this.game_caller = new client_game_caller.game_caller(cli.cli_handle);
    }

    public into_game(game_hub_name : string) {
        this.game_hub_name = game_hub_name;
        this.game_caller.get_hub(this.game_hub_name).into_game(singleton.netSingleton.login.player_info.guid);
    }
}