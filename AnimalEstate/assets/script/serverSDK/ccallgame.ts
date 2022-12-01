import * as client_handle from "./client_handle";
import * as common from "./common";
/*this enum code is codegen by abelkhan codegen for ts*/

/*this struct code is codegen by abelkhan codegen for typescript*/
/*this caller code is codegen by abelkhan codegen for typescript*/
/*this cb code is codegen by abelkhan for ts*/
export class game_rsp_cb extends client_handle.imodule {
    constructor(modules:client_handle.modulemng){
        super();
    }
}

let rsp_cb_game_handle : game_rsp_cb | null = null;
export class game_caller {
    private _hubproxy:game_hubproxy;
    constructor(_client:client_handle.client){
        if (rsp_cb_game_handle == null){
            rsp_cb_game_handle = new game_rsp_cb(_client._modulemng);
        }
        this._hubproxy = new game_hubproxy(_client);
    }

    public get_hub(hub_name:string)
    {
        this._hubproxy.hub_name_b8b9723b_52d5_3bc2_8583_8bf5fd51de47 = hub_name;
        return this._hubproxy;
    }

}

export class game_hubproxy
{
    private uuid_b8b9723b_52d5_3bc2_8583_8bf5fd51de47 : number = Math.round(Math.random() * 1000);

    public hub_name_b8b9723b_52d5_3bc2_8583_8bf5fd51de47:string;
    private _client_handle:client_handle.client;

    constructor(client_handle_:client_handle.client)
    {
        this._client_handle = client_handle_;
    }

    public into_game(guid:number){
        let _argv_90a69cb9_3a0a_3a86_9cad_499708905276:any[] = [];
        _argv_90a69cb9_3a0a_3a86_9cad_499708905276.push(guid);
        this._client_handle.call_hub(this.hub_name_b8b9723b_52d5_3bc2_8583_8bf5fd51de47, "game_into_game", _argv_90a69cb9_3a0a_3a86_9cad_499708905276);
    }

    public use_skill(){
        let _argv_f54ecac1_af9c_3003_a2f2_ed93134bfdfe:any[] = [];
        this._client_handle.call_hub(this.hub_name_b8b9723b_52d5_3bc2_8583_8bf5fd51de47, "game_use_skill", _argv_f54ecac1_af9c_3003_a2f2_ed93134bfdfe);
    }

    public throw_dice(){
        let _argv_89caa8aa_910b_3726_9283_63467ea68426:any[] = [];
        this._client_handle.call_hub(this.hub_name_b8b9723b_52d5_3bc2_8583_8bf5fd51de47, "game_throw_dice", _argv_89caa8aa_910b_3726_9283_63467ea68426);
    }

}
