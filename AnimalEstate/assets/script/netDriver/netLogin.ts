import * as cli from "../serverSDK/client_handle"
import * as common from "../serverSDK/common"
import * as error from "../serverSDK/error"

import * as login from "../serverSDK/ccalllogin"
import * as player_login from "../serverSDK/ccallplayer"

import * as player_client from "../serverSDK/playercallc"

export class netLogin {
    private c_login_caller : login.login_caller;
    
    public player_name = "";
    private c_player_login_caller : player_login.player_login_caller;

    private player_client_module : player_client.player_client_module;

    public cb_player_be_displacement : () => void;
    public constructor() {
        this.c_login_caller = new login.login_caller(cli.cli_handle); 
        this.c_player_login_caller = new player_login.player_login_caller(cli.cli_handle);

        this.player_client_module = new player_client.player_client_module(cli.cli_handle);

        this.player_client_module.cb_be_displacement = () =>{
            this.cb_player_be_displacement.call(null);
        }
    }

    public player_info : common.player_info;
    public cb_player_login_sucess : () => void;
    public cb_player_login_non_account : () => void;
    public login_player_no_author(account) {
        cli.cli_handle.get_hub_info("login", (info_list)=>{
            if (info_list.length > 0) {
                var login_hub = info_list[Math.round(Math.random() * info_list.length)]

                this.c_login_caller.get_hub(login_hub.hub_name).player_login_no_author(account).callBack((player_hub_name, token)=>{
                    this.player_name = player_hub_name;
                    
                    this.c_player_login_caller.get_hub(player_hub_name).player_login(token).callBack((player_info)=>{
                        this.player_info = player_info;
                        this.cb_player_login_sucess.call(null);
                    }, (err)=>{
                        if (err == error.error.unregistered_palyer) {
                            this.cb_player_login_non_account.call(null);
                        }
                    }).timeout(3000, ()=>{
                        console.log("login player timeout");
                    });
                }, (err)=>{
                    console.log("login error:" + err);
                }).timeout(3000, ()=>{
                    console.log("login timeout");
                });
            }
            else {
                console.log("login svr list is empty!");
            }
        });
    }


    public create_role(name){
        this.c_player_login_caller.get_hub(this.player_name).create_role(name).callBack((player_info)=>{
            this.player_info = player_info;
            this.cb_player_login_sucess.call(null);
        }, (err)=>{
            console.log("create role error:" + err);
        }).timeout(3000, ()=>{
            console.log("create role timeout");
        });;
    }
} 