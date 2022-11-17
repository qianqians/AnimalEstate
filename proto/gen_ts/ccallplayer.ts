import * as client_handle from "./client_handle";
import * as common from "./common";
/*this enum code is codegen by abelkhan codegen for ts*/

/*this struct code is codegen by abelkhan codegen for typescript*/
/*this caller code is codegen by abelkhan codegen for typescript*/
export class player_login_player_login_cb{
    private cb_uuid : number;
    private module_rsp_cb : player_login_rsp_cb;

    public event_player_login_handle_cb : (info:common.player_info)=>void | null;
    public event_player_login_handle_err : (err:number)=>void | null;
    public event_player_login_handle_timeout : ()=>void | null;
    constructor(_cb_uuid : number, _module_rsp_cb : player_login_rsp_cb){
        this.cb_uuid = _cb_uuid;
        this.module_rsp_cb = _module_rsp_cb;
        this.event_player_login_handle_cb = null;
        this.event_player_login_handle_err = null;
        this.event_player_login_handle_timeout = null;
    }

    callBack(_cb:(info:common.player_info)=>void, _err:(err:number)=>void)
    {
        this.event_player_login_handle_cb = _cb;
        this.event_player_login_handle_err = _err;
        return this;
    }

    timeout(tick:number, timeout_cb:()=>void)
    {
        setTimeout(()=>{ this.module_rsp_cb.player_login_timeout(this.cb_uuid); }, tick);
        this.event_player_login_handle_timeout = timeout_cb;
    }

}

export class player_login_create_role_cb{
    private cb_uuid : number;
    private module_rsp_cb : player_login_rsp_cb;

    public event_create_role_handle_cb : (info:common.player_info)=>void | null;
    public event_create_role_handle_err : (err:number)=>void | null;
    public event_create_role_handle_timeout : ()=>void | null;
    constructor(_cb_uuid : number, _module_rsp_cb : player_login_rsp_cb){
        this.cb_uuid = _cb_uuid;
        this.module_rsp_cb = _module_rsp_cb;
        this.event_create_role_handle_cb = null;
        this.event_create_role_handle_err = null;
        this.event_create_role_handle_timeout = null;
    }

    callBack(_cb:(info:common.player_info)=>void, _err:(err:number)=>void)
    {
        this.event_create_role_handle_cb = _cb;
        this.event_create_role_handle_err = _err;
        return this;
    }

    timeout(tick:number, timeout_cb:()=>void)
    {
        setTimeout(()=>{ this.module_rsp_cb.create_role_timeout(this.cb_uuid); }, tick);
        this.event_create_role_handle_timeout = timeout_cb;
    }

}

/*this cb code is codegen by abelkhan for ts*/
export class player_login_rsp_cb extends client_handle.imodule {
    public map_player_login:Map<number, player_login_player_login_cb>;
    public map_create_role:Map<number, player_login_create_role_cb>;
    constructor(modules:client_handle.modulemng){
        super();
        this.map_player_login = new Map<number, player_login_player_login_cb>();
        modules.add_method("player_login_rsp_cb_player_login_rsp", this.player_login_rsp.bind(this));
        modules.add_method("player_login_rsp_cb_player_login_err", this.player_login_err.bind(this));
        this.map_create_role = new Map<number, player_login_create_role_cb>();
        modules.add_method("player_login_rsp_cb_create_role_rsp", this.create_role_rsp.bind(this));
        modules.add_method("player_login_rsp_cb_create_role_err", this.create_role_err.bind(this));
    }
    public player_login_rsp(inArray:any[]){
        let uuid = inArray[0];
        let _argv_803b03c3_eef6_3b5c_a790_4cd13c6c4e4b:any[] = [];
        _argv_803b03c3_eef6_3b5c_a790_4cd13c6c4e4b.push(common.protcol_to_player_info(inArray[1]));
        var rsp = this.try_get_and_del_player_login_cb(uuid);
        if (rsp && rsp.event_player_login_handle_cb) {
            rsp.event_player_login_handle_cb.apply(null, _argv_803b03c3_eef6_3b5c_a790_4cd13c6c4e4b);
        }
    }

    public player_login_err(inArray:any[]){
        let uuid = inArray[0];
        let _argv_803b03c3_eef6_3b5c_a790_4cd13c6c4e4b:any[] = [];
        _argv_803b03c3_eef6_3b5c_a790_4cd13c6c4e4b.push(inArray[1]);
        var rsp = this.try_get_and_del_player_login_cb(uuid);
        if (rsp && rsp.event_player_login_handle_err) {
            rsp.event_player_login_handle_err.apply(null, _argv_803b03c3_eef6_3b5c_a790_4cd13c6c4e4b);
        }
    }

    public player_login_timeout(cb_uuid : number){
        let rsp = this.try_get_and_del_player_login_cb(cb_uuid);
        if (rsp){
            if (rsp.event_player_login_handle_timeout) {
                rsp.event_player_login_handle_timeout.apply(null);
            }
        }
    }

    private try_get_and_del_player_login_cb(uuid : number){
        var rsp = this.map_player_login.get(uuid);
        this.map_player_login.delete(uuid);
        return rsp;
    }

    public create_role_rsp(inArray:any[]){
        let uuid = inArray[0];
        let _argv_30293c4a_8f5b_307e_a08a_ff76e003f95d:any[] = [];
        _argv_30293c4a_8f5b_307e_a08a_ff76e003f95d.push(common.protcol_to_player_info(inArray[1]));
        var rsp = this.try_get_and_del_create_role_cb(uuid);
        if (rsp && rsp.event_create_role_handle_cb) {
            rsp.event_create_role_handle_cb.apply(null, _argv_30293c4a_8f5b_307e_a08a_ff76e003f95d);
        }
    }

    public create_role_err(inArray:any[]){
        let uuid = inArray[0];
        let _argv_30293c4a_8f5b_307e_a08a_ff76e003f95d:any[] = [];
        _argv_30293c4a_8f5b_307e_a08a_ff76e003f95d.push(inArray[1]);
        var rsp = this.try_get_and_del_create_role_cb(uuid);
        if (rsp && rsp.event_create_role_handle_err) {
            rsp.event_create_role_handle_err.apply(null, _argv_30293c4a_8f5b_307e_a08a_ff76e003f95d);
        }
    }

    public create_role_timeout(cb_uuid : number){
        let rsp = this.try_get_and_del_create_role_cb(cb_uuid);
        if (rsp){
            if (rsp.event_create_role_handle_timeout) {
                rsp.event_create_role_handle_timeout.apply(null);
            }
        }
    }

    private try_get_and_del_create_role_cb(uuid : number){
        var rsp = this.map_create_role.get(uuid);
        this.map_create_role.delete(uuid);
        return rsp;
    }

}

let rsp_cb_player_login_handle : player_login_rsp_cb | null = null;
export class player_login_caller {
    private _hubproxy:player_login_hubproxy;
    constructor(_client:client_handle.client){
        if (rsp_cb_player_login_handle == null){
            rsp_cb_player_login_handle = new player_login_rsp_cb(_client._modulemng);
        }
        this._hubproxy = new player_login_hubproxy(_client);
    }

    public get_hub(hub_name:string)
    {
        this._hubproxy.hub_name_803b03c3_eef6_3b5c_a790_4cd13c6c4e4b = hub_name;
        return this._hubproxy;
    }

}

export class player_login_hubproxy
{
    private uuid_803b03c3_eef6_3b5c_a790_4cd13c6c4e4b : number = Math.round(Math.random() * 1000);

    public hub_name_803b03c3_eef6_3b5c_a790_4cd13c6c4e4b:string;
    private _client_handle:client_handle.client;

    constructor(client_handle_:client_handle.client)
    {
        this._client_handle = client_handle_;
    }

    public player_login(token:string){
        let uuid_ab86d08e_f3b3_5b3e_a2b9_8a2b5c189a51 = Math.round(this.uuid_803b03c3_eef6_3b5c_a790_4cd13c6c4e4b++);

        let _argv_803b03c3_eef6_3b5c_a790_4cd13c6c4e4b:any[] = [uuid_ab86d08e_f3b3_5b3e_a2b9_8a2b5c189a51];
        _argv_803b03c3_eef6_3b5c_a790_4cd13c6c4e4b.push(token);
        this._client_handle.call_hub(this.hub_name_803b03c3_eef6_3b5c_a790_4cd13c6c4e4b, "player_login_player_login", _argv_803b03c3_eef6_3b5c_a790_4cd13c6c4e4b);
        let cb_player_login_obj = new player_login_player_login_cb(uuid_ab86d08e_f3b3_5b3e_a2b9_8a2b5c189a51, rsp_cb_player_login_handle);
        if (rsp_cb_player_login_handle){
            rsp_cb_player_login_handle.map_player_login.set(uuid_ab86d08e_f3b3_5b3e_a2b9_8a2b5c189a51, cb_player_login_obj);
        }
        return cb_player_login_obj;
    }

    public create_role(name:string){
        let uuid_ef86ed88_4838_5896_8241_9edf3c4b6d21 = Math.round(this.uuid_803b03c3_eef6_3b5c_a790_4cd13c6c4e4b++);

        let _argv_30293c4a_8f5b_307e_a08a_ff76e003f95d:any[] = [uuid_ef86ed88_4838_5896_8241_9edf3c4b6d21];
        _argv_30293c4a_8f5b_307e_a08a_ff76e003f95d.push(name);
        this._client_handle.call_hub(this.hub_name_803b03c3_eef6_3b5c_a790_4cd13c6c4e4b, "player_login_create_role", _argv_30293c4a_8f5b_307e_a08a_ff76e003f95d);
        let cb_create_role_obj = new player_login_create_role_cb(uuid_ef86ed88_4838_5896_8241_9edf3c4b6d21, rsp_cb_player_login_handle);
        if (rsp_cb_player_login_handle){
            rsp_cb_player_login_handle.map_create_role.set(uuid_ef86ed88_4838_5896_8241_9edf3c4b6d21, cb_create_role_obj);
        }
        return cb_create_role_obj;
    }

}
/*this cb code is codegen by abelkhan for ts*/
export class client_match_rsp_cb extends client_handle.imodule {
    constructor(modules:client_handle.modulemng){
        super();
    }
}

let rsp_cb_client_match_handle : client_match_rsp_cb | null = null;
export class client_match_caller {
    private _hubproxy:client_match_hubproxy;
    constructor(_client:client_handle.client){
        if (rsp_cb_client_match_handle == null){
            rsp_cb_client_match_handle = new client_match_rsp_cb(_client._modulemng);
        }
        this._hubproxy = new client_match_hubproxy(_client);
    }

    public get_hub(hub_name:string)
    {
        this._hubproxy.hub_name_a67a32be_6a98_3d05_88d9_696d83c9d775 = hub_name;
        return this._hubproxy;
    }

}

export class client_match_hubproxy
{
    private uuid_a67a32be_6a98_3d05_88d9_696d83c9d775 : number = Math.round(Math.random() * 1000);

    public hub_name_a67a32be_6a98_3d05_88d9_696d83c9d775:string;
    private _client_handle:client_handle.client;

    constructor(client_handle_:client_handle.client)
    {
        this._client_handle = client_handle_;
    }

    public start_match(){
        let _argv_5d1645a8_78f1_3219_bb7e_d14f420c9e1d:any[] = [];
        this._client_handle.call_hub(this.hub_name_a67a32be_6a98_3d05_88d9_696d83c9d775, "client_match_start_match", _argv_5d1645a8_78f1_3219_bb7e_d14f420c9e1d);
    }

}
export class client_room_player_create_room_cb{
    private cb_uuid : number;
    private module_rsp_cb : client_room_player_rsp_cb;

    public event_create_room_handle_cb : (room_hub_name:string, _room_info:common.room_info)=>void | null;
    public event_create_room_handle_err : (err:number)=>void | null;
    public event_create_room_handle_timeout : ()=>void | null;
    constructor(_cb_uuid : number, _module_rsp_cb : client_room_player_rsp_cb){
        this.cb_uuid = _cb_uuid;
        this.module_rsp_cb = _module_rsp_cb;
        this.event_create_room_handle_cb = null;
        this.event_create_room_handle_err = null;
        this.event_create_room_handle_timeout = null;
    }

    callBack(_cb:(room_hub_name:string, _room_info:common.room_info)=>void, _err:(err:number)=>void)
    {
        this.event_create_room_handle_cb = _cb;
        this.event_create_room_handle_err = _err;
        return this;
    }

    timeout(tick:number, timeout_cb:()=>void)
    {
        setTimeout(()=>{ this.module_rsp_cb.create_room_timeout(this.cb_uuid); }, tick);
        this.event_create_room_handle_timeout = timeout_cb;
    }

}

export class client_room_player_agree_join_room_cb{
    private cb_uuid : number;
    private module_rsp_cb : client_room_player_rsp_cb;

    public event_agree_join_room_handle_cb : (room_hub_name:string, _room_info:common.room_info)=>void | null;
    public event_agree_join_room_handle_err : (err:number)=>void | null;
    public event_agree_join_room_handle_timeout : ()=>void | null;
    constructor(_cb_uuid : number, _module_rsp_cb : client_room_player_rsp_cb){
        this.cb_uuid = _cb_uuid;
        this.module_rsp_cb = _module_rsp_cb;
        this.event_agree_join_room_handle_cb = null;
        this.event_agree_join_room_handle_err = null;
        this.event_agree_join_room_handle_timeout = null;
    }

    callBack(_cb:(room_hub_name:string, _room_info:common.room_info)=>void, _err:(err:number)=>void)
    {
        this.event_agree_join_room_handle_cb = _cb;
        this.event_agree_join_room_handle_err = _err;
        return this;
    }

    timeout(tick:number, timeout_cb:()=>void)
    {
        setTimeout(()=>{ this.module_rsp_cb.agree_join_room_timeout(this.cb_uuid); }, tick);
        this.event_agree_join_room_handle_timeout = timeout_cb;
    }

}

/*this cb code is codegen by abelkhan for ts*/
export class client_room_player_rsp_cb extends client_handle.imodule {
    public map_create_room:Map<number, client_room_player_create_room_cb>;
    public map_agree_join_room:Map<number, client_room_player_agree_join_room_cb>;
    constructor(modules:client_handle.modulemng){
        super();
        this.map_create_room = new Map<number, client_room_player_create_room_cb>();
        modules.add_method("client_room_player_rsp_cb_create_room_rsp", this.create_room_rsp.bind(this));
        modules.add_method("client_room_player_rsp_cb_create_room_err", this.create_room_err.bind(this));
        this.map_agree_join_room = new Map<number, client_room_player_agree_join_room_cb>();
        modules.add_method("client_room_player_rsp_cb_agree_join_room_rsp", this.agree_join_room_rsp.bind(this));
        modules.add_method("client_room_player_rsp_cb_agree_join_room_err", this.agree_join_room_err.bind(this));
    }
    public create_room_rsp(inArray:any[]){
        let uuid = inArray[0];
        let _argv_0f87a215_0b4f_3a78_9d92_9bd3f4aa6dee:any[] = [];
        _argv_0f87a215_0b4f_3a78_9d92_9bd3f4aa6dee.push(inArray[1]);
        _argv_0f87a215_0b4f_3a78_9d92_9bd3f4aa6dee.push(common.protcol_to_room_info(inArray[2]));
        var rsp = this.try_get_and_del_create_room_cb(uuid);
        if (rsp && rsp.event_create_room_handle_cb) {
            rsp.event_create_room_handle_cb.apply(null, _argv_0f87a215_0b4f_3a78_9d92_9bd3f4aa6dee);
        }
    }

    public create_room_err(inArray:any[]){
        let uuid = inArray[0];
        let _argv_0f87a215_0b4f_3a78_9d92_9bd3f4aa6dee:any[] = [];
        _argv_0f87a215_0b4f_3a78_9d92_9bd3f4aa6dee.push(inArray[1]);
        var rsp = this.try_get_and_del_create_room_cb(uuid);
        if (rsp && rsp.event_create_room_handle_err) {
            rsp.event_create_room_handle_err.apply(null, _argv_0f87a215_0b4f_3a78_9d92_9bd3f4aa6dee);
        }
    }

    public create_room_timeout(cb_uuid : number){
        let rsp = this.try_get_and_del_create_room_cb(cb_uuid);
        if (rsp){
            if (rsp.event_create_room_handle_timeout) {
                rsp.event_create_room_handle_timeout.apply(null);
            }
        }
    }

    private try_get_and_del_create_room_cb(uuid : number){
        var rsp = this.map_create_room.get(uuid);
        this.map_create_room.delete(uuid);
        return rsp;
    }

    public agree_join_room_rsp(inArray:any[]){
        let uuid = inArray[0];
        let _argv_dd5a04d0_146c_30d4_bf08_5551c02a714b:any[] = [];
        _argv_dd5a04d0_146c_30d4_bf08_5551c02a714b.push(inArray[1]);
        _argv_dd5a04d0_146c_30d4_bf08_5551c02a714b.push(common.protcol_to_room_info(inArray[2]));
        var rsp = this.try_get_and_del_agree_join_room_cb(uuid);
        if (rsp && rsp.event_agree_join_room_handle_cb) {
            rsp.event_agree_join_room_handle_cb.apply(null, _argv_dd5a04d0_146c_30d4_bf08_5551c02a714b);
        }
    }

    public agree_join_room_err(inArray:any[]){
        let uuid = inArray[0];
        let _argv_dd5a04d0_146c_30d4_bf08_5551c02a714b:any[] = [];
        _argv_dd5a04d0_146c_30d4_bf08_5551c02a714b.push(inArray[1]);
        var rsp = this.try_get_and_del_agree_join_room_cb(uuid);
        if (rsp && rsp.event_agree_join_room_handle_err) {
            rsp.event_agree_join_room_handle_err.apply(null, _argv_dd5a04d0_146c_30d4_bf08_5551c02a714b);
        }
    }

    public agree_join_room_timeout(cb_uuid : number){
        let rsp = this.try_get_and_del_agree_join_room_cb(cb_uuid);
        if (rsp){
            if (rsp.event_agree_join_room_handle_timeout) {
                rsp.event_agree_join_room_handle_timeout.apply(null);
            }
        }
    }

    private try_get_and_del_agree_join_room_cb(uuid : number){
        var rsp = this.map_agree_join_room.get(uuid);
        this.map_agree_join_room.delete(uuid);
        return rsp;
    }

}

let rsp_cb_client_room_player_handle : client_room_player_rsp_cb | null = null;
export class client_room_player_caller {
    private _hubproxy:client_room_player_hubproxy;
    constructor(_client:client_handle.client){
        if (rsp_cb_client_room_player_handle == null){
            rsp_cb_client_room_player_handle = new client_room_player_rsp_cb(_client._modulemng);
        }
        this._hubproxy = new client_room_player_hubproxy(_client);
    }

    public get_hub(hub_name:string)
    {
        this._hubproxy.hub_name_8bda7395_33b3_34a3_bd3e_b6d6b2ba9cb2 = hub_name;
        return this._hubproxy;
    }

}

export class client_room_player_hubproxy
{
    private uuid_8bda7395_33b3_34a3_bd3e_b6d6b2ba9cb2 : number = Math.round(Math.random() * 1000);

    public hub_name_8bda7395_33b3_34a3_bd3e_b6d6b2ba9cb2:string;
    private _client_handle:client_handle.client;

    constructor(client_handle_:client_handle.client)
    {
        this._client_handle = client_handle_;
    }

    public create_room(){
        let uuid_596b5288_d0f2_52ea_802a_a61621d93808 = Math.round(this.uuid_8bda7395_33b3_34a3_bd3e_b6d6b2ba9cb2++);

        let _argv_0f87a215_0b4f_3a78_9d92_9bd3f4aa6dee:any[] = [uuid_596b5288_d0f2_52ea_802a_a61621d93808];
        this._client_handle.call_hub(this.hub_name_8bda7395_33b3_34a3_bd3e_b6d6b2ba9cb2, "client_room_player_create_room", _argv_0f87a215_0b4f_3a78_9d92_9bd3f4aa6dee);
        let cb_create_room_obj = new client_room_player_create_room_cb(uuid_596b5288_d0f2_52ea_802a_a61621d93808, rsp_cb_client_room_player_handle);
        if (rsp_cb_client_room_player_handle){
            rsp_cb_client_room_player_handle.map_create_room.set(uuid_596b5288_d0f2_52ea_802a_a61621d93808, cb_create_room_obj);
        }
        return cb_create_room_obj;
    }

    public invite_role_join_room(guid:number){
        let _argv_4afdf6f4_2ff9_314b_9be9_c6d0fa96e4f8:any[] = [];
        _argv_4afdf6f4_2ff9_314b_9be9_c6d0fa96e4f8.push(guid);
        this._client_handle.call_hub(this.hub_name_8bda7395_33b3_34a3_bd3e_b6d6b2ba9cb2, "client_room_player_invite_role_join_room", _argv_4afdf6f4_2ff9_314b_9be9_c6d0fa96e4f8);
    }

    public agree_join_room(team_id:string){
        let uuid_2b5aaead_9c5d_5e1b_b2f5_62a6bfb42fe9 = Math.round(this.uuid_8bda7395_33b3_34a3_bd3e_b6d6b2ba9cb2++);

        let _argv_dd5a04d0_146c_30d4_bf08_5551c02a714b:any[] = [uuid_2b5aaead_9c5d_5e1b_b2f5_62a6bfb42fe9];
        _argv_dd5a04d0_146c_30d4_bf08_5551c02a714b.push(team_id);
        this._client_handle.call_hub(this.hub_name_8bda7395_33b3_34a3_bd3e_b6d6b2ba9cb2, "client_room_player_agree_join_room", _argv_dd5a04d0_146c_30d4_bf08_5551c02a714b);
        let cb_agree_join_room_obj = new client_room_player_agree_join_room_cb(uuid_2b5aaead_9c5d_5e1b_b2f5_62a6bfb42fe9, rsp_cb_client_room_player_handle);
        if (rsp_cb_client_room_player_handle){
            rsp_cb_client_room_player_handle.map_agree_join_room.set(uuid_2b5aaead_9c5d_5e1b_b2f5_62a6bfb42fe9, cb_agree_join_room_obj);
        }
        return cb_agree_join_room_obj;
    }

}
export class client_friend_lobby_find_role_cb{
    private cb_uuid : number;
    private module_rsp_cb : client_friend_lobby_rsp_cb;

    public event_find_role_handle_cb : (find_info:common.player_friend_info)=>void | null;
    public event_find_role_handle_err : (err:number)=>void | null;
    public event_find_role_handle_timeout : ()=>void | null;
    constructor(_cb_uuid : number, _module_rsp_cb : client_friend_lobby_rsp_cb){
        this.cb_uuid = _cb_uuid;
        this.module_rsp_cb = _module_rsp_cb;
        this.event_find_role_handle_cb = null;
        this.event_find_role_handle_err = null;
        this.event_find_role_handle_timeout = null;
    }

    callBack(_cb:(find_info:common.player_friend_info)=>void, _err:(err:number)=>void)
    {
        this.event_find_role_handle_cb = _cb;
        this.event_find_role_handle_err = _err;
        return this;
    }

    timeout(tick:number, timeout_cb:()=>void)
    {
        setTimeout(()=>{ this.module_rsp_cb.find_role_timeout(this.cb_uuid); }, tick);
        this.event_find_role_handle_timeout = timeout_cb;
    }

}

/*this cb code is codegen by abelkhan for ts*/
export class client_friend_lobby_rsp_cb extends client_handle.imodule {
    public map_find_role:Map<number, client_friend_lobby_find_role_cb>;
    constructor(modules:client_handle.modulemng){
        super();
        this.map_find_role = new Map<number, client_friend_lobby_find_role_cb>();
        modules.add_method("client_friend_lobby_rsp_cb_find_role_rsp", this.find_role_rsp.bind(this));
        modules.add_method("client_friend_lobby_rsp_cb_find_role_err", this.find_role_err.bind(this));
    }
    public find_role_rsp(inArray:any[]){
        let uuid = inArray[0];
        let _argv_ba126e3b_fd75_3aa1_a5be_1d096547ca8f:any[] = [];
        _argv_ba126e3b_fd75_3aa1_a5be_1d096547ca8f.push(common.protcol_to_player_friend_info(inArray[1]));
        var rsp = this.try_get_and_del_find_role_cb(uuid);
        if (rsp && rsp.event_find_role_handle_cb) {
            rsp.event_find_role_handle_cb.apply(null, _argv_ba126e3b_fd75_3aa1_a5be_1d096547ca8f);
        }
    }

    public find_role_err(inArray:any[]){
        let uuid = inArray[0];
        let _argv_ba126e3b_fd75_3aa1_a5be_1d096547ca8f:any[] = [];
        _argv_ba126e3b_fd75_3aa1_a5be_1d096547ca8f.push(inArray[1]);
        var rsp = this.try_get_and_del_find_role_cb(uuid);
        if (rsp && rsp.event_find_role_handle_err) {
            rsp.event_find_role_handle_err.apply(null, _argv_ba126e3b_fd75_3aa1_a5be_1d096547ca8f);
        }
    }

    public find_role_timeout(cb_uuid : number){
        let rsp = this.try_get_and_del_find_role_cb(cb_uuid);
        if (rsp){
            if (rsp.event_find_role_handle_timeout) {
                rsp.event_find_role_handle_timeout.apply(null);
            }
        }
    }

    private try_get_and_del_find_role_cb(uuid : number){
        var rsp = this.map_find_role.get(uuid);
        this.map_find_role.delete(uuid);
        return rsp;
    }

}

let rsp_cb_client_friend_lobby_handle : client_friend_lobby_rsp_cb | null = null;
export class client_friend_lobby_caller {
    private _hubproxy:client_friend_lobby_hubproxy;
    constructor(_client:client_handle.client){
        if (rsp_cb_client_friend_lobby_handle == null){
            rsp_cb_client_friend_lobby_handle = new client_friend_lobby_rsp_cb(_client._modulemng);
        }
        this._hubproxy = new client_friend_lobby_hubproxy(_client);
    }

    public get_hub(hub_name:string)
    {
        this._hubproxy.hub_name_f2e2d46a_373f_3b99_b818_f5e5b675f4da = hub_name;
        return this._hubproxy;
    }

}

export class client_friend_lobby_hubproxy
{
    private uuid_f2e2d46a_373f_3b99_b818_f5e5b675f4da : number = Math.round(Math.random() * 1000);

    public hub_name_f2e2d46a_373f_3b99_b818_f5e5b675f4da:string;
    private _client_handle:client_handle.client;

    constructor(client_handle_:client_handle.client)
    {
        this._client_handle = client_handle_;
    }

    public find_role(guid:string){
        let uuid_23e9c7cc_ac81_5213_8bc2_d73a51d7f87b = Math.round(this.uuid_f2e2d46a_373f_3b99_b818_f5e5b675f4da++);

        let _argv_ba126e3b_fd75_3aa1_a5be_1d096547ca8f:any[] = [uuid_23e9c7cc_ac81_5213_8bc2_d73a51d7f87b];
        _argv_ba126e3b_fd75_3aa1_a5be_1d096547ca8f.push(guid);
        this._client_handle.call_hub(this.hub_name_f2e2d46a_373f_3b99_b818_f5e5b675f4da, "client_friend_lobby_find_role", _argv_ba126e3b_fd75_3aa1_a5be_1d096547ca8f);
        let cb_find_role_obj = new client_friend_lobby_find_role_cb(uuid_23e9c7cc_ac81_5213_8bc2_d73a51d7f87b, rsp_cb_client_friend_lobby_handle);
        if (rsp_cb_client_friend_lobby_handle){
            rsp_cb_client_friend_lobby_handle.map_find_role.set(uuid_23e9c7cc_ac81_5213_8bc2_d73a51d7f87b, cb_find_role_obj);
        }
        return cb_find_role_obj;
    }

    public invite_role_friend(self_account:common.player_friend_info, target_account:common.player_friend_info){
        let _argv_7b2d0e53_b589_37f7_a9bc_31fcce44d278:any[] = [];
        _argv_7b2d0e53_b589_37f7_a9bc_31fcce44d278.push(common.player_friend_info_to_protcol(self_account));
        _argv_7b2d0e53_b589_37f7_a9bc_31fcce44d278.push(common.player_friend_info_to_protcol(target_account));
        this._client_handle.call_hub(this.hub_name_f2e2d46a_373f_3b99_b818_f5e5b675f4da, "client_friend_lobby_invite_role_friend", _argv_7b2d0e53_b589_37f7_a9bc_31fcce44d278);
    }

    public agree_role_friend(invite_account:string, be_agree:boolean){
        let _argv_1f120946_a2d8_34bf_a794_941de0d70f98:any[] = [];
        _argv_1f120946_a2d8_34bf_a794_941de0d70f98.push(invite_account);
        _argv_1f120946_a2d8_34bf_a794_941de0d70f98.push(be_agree);
        this._client_handle.call_hub(this.hub_name_f2e2d46a_373f_3b99_b818_f5e5b675f4da, "client_friend_lobby_agree_role_friend", _argv_1f120946_a2d8_34bf_a794_941de0d70f98);
    }

}
