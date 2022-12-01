import * as client_handle from "./client_handle";
/*this enum code is codegen by abelkhan codegen for ts*/

/*this struct code is codegen by abelkhan codegen for typescript*/
/*this caller code is codegen by abelkhan codegen for typescript*/
export class login_player_login_no_author_cb{
    private cb_uuid : number;
    private module_rsp_cb : login_rsp_cb;

    public event_player_login_no_author_handle_cb : (player_hub_name:string, token:string)=>void | null;
    public event_player_login_no_author_handle_err : (err:number)=>void | null;
    public event_player_login_no_author_handle_timeout : ()=>void | null;
    constructor(_cb_uuid : number, _module_rsp_cb : login_rsp_cb){
        this.cb_uuid = _cb_uuid;
        this.module_rsp_cb = _module_rsp_cb;
        this.event_player_login_no_author_handle_cb = null;
        this.event_player_login_no_author_handle_err = null;
        this.event_player_login_no_author_handle_timeout = null;
    }

    callBack(_cb:(player_hub_name:string, token:string)=>void, _err:(err:number)=>void)
    {
        this.event_player_login_no_author_handle_cb = _cb;
        this.event_player_login_no_author_handle_err = _err;
        return this;
    }

    timeout(tick:number, timeout_cb:()=>void)
    {
        setTimeout(()=>{ this.module_rsp_cb.player_login_no_author_timeout(this.cb_uuid); }, tick);
        this.event_player_login_no_author_handle_timeout = timeout_cb;
    }

}

/*this cb code is codegen by abelkhan for ts*/
export class login_rsp_cb extends client_handle.imodule {
    public map_player_login_no_author:Map<number, login_player_login_no_author_cb>;
    constructor(modules:client_handle.modulemng){
        super();
        this.map_player_login_no_author = new Map<number, login_player_login_no_author_cb>();
        modules.add_method("login_rsp_cb_player_login_no_author_rsp", this.player_login_no_author_rsp.bind(this));
        modules.add_method("login_rsp_cb_player_login_no_author_err", this.player_login_no_author_err.bind(this));
    }
    public player_login_no_author_rsp(inArray:any[]){
        let uuid = inArray[0];
        let _argv_2c74a728_390c_3834_83d5_c8331456ea49:any[] = [];
        _argv_2c74a728_390c_3834_83d5_c8331456ea49.push(inArray[1]);
        _argv_2c74a728_390c_3834_83d5_c8331456ea49.push(inArray[2]);
        var rsp = this.try_get_and_del_player_login_no_author_cb(uuid);
        if (rsp && rsp.event_player_login_no_author_handle_cb) {
            rsp.event_player_login_no_author_handle_cb.apply(null, _argv_2c74a728_390c_3834_83d5_c8331456ea49);
        }
    }

    public player_login_no_author_err(inArray:any[]){
        let uuid = inArray[0];
        let _argv_2c74a728_390c_3834_83d5_c8331456ea49:any[] = [];
        _argv_2c74a728_390c_3834_83d5_c8331456ea49.push(inArray[1]);
        var rsp = this.try_get_and_del_player_login_no_author_cb(uuid);
        if (rsp && rsp.event_player_login_no_author_handle_err) {
            rsp.event_player_login_no_author_handle_err.apply(null, _argv_2c74a728_390c_3834_83d5_c8331456ea49);
        }
    }

    public player_login_no_author_timeout(cb_uuid : number){
        let rsp = this.try_get_and_del_player_login_no_author_cb(cb_uuid);
        if (rsp){
            if (rsp.event_player_login_no_author_handle_timeout) {
                rsp.event_player_login_no_author_handle_timeout.apply(null);
            }
        }
    }

    private try_get_and_del_player_login_no_author_cb(uuid : number){
        var rsp = this.map_player_login_no_author.get(uuid);
        this.map_player_login_no_author.delete(uuid);
        return rsp;
    }

}

let rsp_cb_login_handle : login_rsp_cb | null = null;
export class login_caller {
    private _hubproxy:login_hubproxy;
    constructor(_client:client_handle.client){
        if (rsp_cb_login_handle == null){
            rsp_cb_login_handle = new login_rsp_cb(_client._modulemng);
        }
        this._hubproxy = new login_hubproxy(_client);
    }

    public get_hub(hub_name:string)
    {
        this._hubproxy.hub_name_d3bb20a7_d0fc_3440_bb9e_b3cc0630e2d1 = hub_name;
        return this._hubproxy;
    }

}

export class login_hubproxy
{
    private uuid_d3bb20a7_d0fc_3440_bb9e_b3cc0630e2d1 : number = Math.round(Math.random() * 1000);

    public hub_name_d3bb20a7_d0fc_3440_bb9e_b3cc0630e2d1:string;
    private _client_handle:client_handle.client;

    constructor(client_handle_:client_handle.client)
    {
        this._client_handle = client_handle_;
    }

    public player_login_no_author(account:string){
        let uuid_bb47480f_4208_5766_8691_969c21d11b5d = Math.round(this.uuid_d3bb20a7_d0fc_3440_bb9e_b3cc0630e2d1++);

        let _argv_2c74a728_390c_3834_83d5_c8331456ea49:any[] = [uuid_bb47480f_4208_5766_8691_969c21d11b5d];
        _argv_2c74a728_390c_3834_83d5_c8331456ea49.push(account);
        this._client_handle.call_hub(this.hub_name_d3bb20a7_d0fc_3440_bb9e_b3cc0630e2d1, "login_player_login_no_author", _argv_2c74a728_390c_3834_83d5_c8331456ea49);
        let cb_player_login_no_author_obj = new login_player_login_no_author_cb(uuid_bb47480f_4208_5766_8691_969c21d11b5d, rsp_cb_login_handle);
        if (rsp_cb_login_handle){
            rsp_cb_login_handle.map_player_login_no_author.set(uuid_bb47480f_4208_5766_8691_969c21d11b5d, cb_player_login_no_author_obj);
        }
        return cb_player_login_no_author_obj;
    }

}
