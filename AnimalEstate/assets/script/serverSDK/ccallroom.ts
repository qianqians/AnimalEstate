import * as client_handle from "./client_handle";
import * as common from "./common";
/*this enum code is codegen by abelkhan codegen for ts*/

/*this struct code is codegen by abelkhan codegen for typescript*/
/*this caller code is codegen by abelkhan codegen for typescript*/
/*this cb code is codegen by abelkhan for ts*/
export class client_room_match_rsp_cb extends client_handle.imodule {
    constructor(modules:client_handle.modulemng){
        super();
    }
}

let rsp_cb_client_room_match_handle : client_room_match_rsp_cb | null = null;
export class client_room_match_caller {
    private _hubproxy:client_room_match_hubproxy;
    constructor(_client:client_handle.client){
        if (rsp_cb_client_room_match_handle == null){
            rsp_cb_client_room_match_handle = new client_room_match_rsp_cb(_client._modulemng);
        }
        this._hubproxy = new client_room_match_hubproxy(_client);
    }

    public get_hub(hub_name:string)
    {
        this._hubproxy.hub_name_b5f3fac6_a396_3fba_b454_dfa0635d459f = hub_name;
        return this._hubproxy;
    }

}

export class client_room_match_hubproxy
{
    private uuid_b5f3fac6_a396_3fba_b454_dfa0635d459f : number = Math.round(Math.random() * 1000);

    public hub_name_b5f3fac6_a396_3fba_b454_dfa0635d459f:string;
    private _client_handle:client_handle.client;

    constructor(client_handle_:client_handle.client)
    {
        this._client_handle = client_handle_;
    }

    public into_room(){
        let _argv_98a2a5aa_24ec_3da8_9e3a_6f538c18f72e:any[] = [];
        this._client_handle.call_hub(this.hub_name_b5f3fac6_a396_3fba_b454_dfa0635d459f, "client_room_match_into_room", _argv_98a2a5aa_24ec_3da8_9e3a_6f538c18f72e);
    }

    public chat(chat_str:string){
        let _argv_963291b4_683e_3905_b8fb_55e87bd3c071:any[] = [];
        _argv_963291b4_683e_3905_b8fb_55e87bd3c071.push(chat_str);
        this._client_handle.call_hub(this.hub_name_b5f3fac6_a396_3fba_b454_dfa0635d459f, "client_room_match_chat", _argv_963291b4_683e_3905_b8fb_55e87bd3c071);
    }

    public leave_room(){
        let _argv_382a8a22_f4e3_3394_8ae3_d355baaef1ac:any[] = [];
        this._client_handle.call_hub(this.hub_name_b5f3fac6_a396_3fba_b454_dfa0635d459f, "client_room_match_leave_room", _argv_382a8a22_f4e3_3394_8ae3_d355baaef1ac);
    }

    public kick_out(player_guid:number){
        let _argv_316c421a_7e25_3ef2_86d6_1c294eb65792:any[] = [];
        _argv_316c421a_7e25_3ef2_86d6_1c294eb65792.push(player_guid);
        this._client_handle.call_hub(this.hub_name_b5f3fac6_a396_3fba_b454_dfa0635d459f, "client_room_match_kick_out", _argv_316c421a_7e25_3ef2_86d6_1c294eb65792);
    }

    public disband(){
        let _argv_61e085ae_c852_39f0_82bf_61120861bcdd:any[] = [];
        this._client_handle.call_hub(this.hub_name_b5f3fac6_a396_3fba_b454_dfa0635d459f, "client_room_match_disband", _argv_61e085ae_c852_39f0_82bf_61120861bcdd);
    }

    public start_match(){
        let _argv_5d1645a8_78f1_3219_bb7e_d14f420c9e1d:any[] = [];
        this._client_handle.call_hub(this.hub_name_b5f3fac6_a396_3fba_b454_dfa0635d459f, "client_room_match_start_match", _argv_5d1645a8_78f1_3219_bb7e_d14f420c9e1d);
    }

}
