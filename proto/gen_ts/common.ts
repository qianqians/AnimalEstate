import * as client_handle from "./client_handle";
/*this enum code is codegen by abelkhan codegen for ts*/

export enum animal{
    chicken = 1,
    monkey = 2,
    rabbit = 3,
    duck = 4,
    mouse = 5,
    bear = 6,
    tiger = 7,
    lion = 8
}

export enum skin{
    chicken = 101,
    monkey = 201,
    rabbit = 301,
    duck = 401,
    mouse = 501,
    bear = 601,
    tiger = 701,
    lion = 801
}

export enum playground{
    grassland = 1,
    hill = 2,
    snow = 3,
    desert = 4
}

/*this struct code is codegen by abelkhan codegen for typescript*/
export class player_friend_info
{
    public guid : number;
    public name : string;
    public coin : number;
    public score : number;

    constructor(){
    }
}

export function player_friend_info_to_protcol(_struct:player_friend_info){
    return _struct;
}

export function protcol_to_player_friend_info(_protocol:any){
    let _struct = new player_friend_info();
    for (const [key, val] of Object.entries(_protocol))        if (key === "guid"){
            _struct.guid = val as number;
        }
        else if (key === "name"){
            _struct.name = val as string;
        }
        else if (key === "coin"){
            _struct.coin = val as number;
        }
        else if (key === "score"){
            _struct.score = val as number;
        }
    return _struct;
}

export class player_info
{
    public guid : number;
    public sdk_uuid : string;
    public name : string;
    public coin : number;
    public score : number;
    public friend_list : player_friend_info[];
    public invite_list : player_friend_info[];
    public be_invited_list : player_friend_info[];
    public hero_list : animal[];
    public skin_list : skin[];
    public playground_list : playground[];

    constructor(){
    }
}

export function player_info_to_protcol(_struct:player_info){
    return _struct;
}

export function protcol_to_player_info(_protocol:any){
    let _struct = new player_info();
    for (const [key, val] of Object.entries(_protocol))        if (key === "guid"){
            _struct.guid = val as number;
        }
        else if (key === "sdk_uuid"){
            _struct.sdk_uuid = val as string;
        }
        else if (key === "name"){
            _struct.name = val as string;
        }
        else if (key === "coin"){
            _struct.coin = val as number;
        }
        else if (key === "score"){
            _struct.score = val as number;
        }
        else if (key === "friend_list"){
            _struct.friend_list = [];
            for(let v_ of val){
                _struct.friend_list.push(protcol_to_player_friend_info(v_));
    }
        }
        else if (key === "invite_list"){
            _struct.invite_list = [];
            for(let v_ of val){
                _struct.invite_list.push(protcol_to_player_friend_info(v_));
    }
        }
        else if (key === "be_invited_list"){
            _struct.be_invited_list = [];
            for(let v_ of val){
                _struct.be_invited_list.push(protcol_to_player_friend_info(v_));
    }
        }
        else if (key === "hero_list"){
            _struct.hero_list = [];
            for(let v_ of val){
                _struct.hero_list.push(v_);
    }
        }
        else if (key === "skin_list"){
            _struct.skin_list = [];
            for(let v_ of val){
                _struct.skin_list.push(v_);
    }
        }
        else if (key === "playground_list"){
            _struct.playground_list = [];
            for(let v_ of val){
                _struct.playground_list.push(v_);
    }
        }
    return _struct;
}

export class player_inline_info
{
    public uuid : string;
    public guid : number;
    public name : string;
    public coin : number;
    public score : number;

    constructor(){
    }
}

export function player_inline_info_to_protcol(_struct:player_inline_info){
    return _struct;
}

export function protcol_to_player_inline_info(_protocol:any){
    let _struct = new player_inline_info();
    for (const [key, val] of Object.entries(_protocol))        if (key === "uuid"){
            _struct.uuid = val as string;
        }
        else if (key === "guid"){
            _struct.guid = val as number;
        }
        else if (key === "name"){
            _struct.name = val as string;
        }
        else if (key === "coin"){
            _struct.coin = val as number;
        }
        else if (key === "score"){
            _struct.score = val as number;
        }
    return _struct;
}

export class room_info
{
    public room_uuid : string;
    public room_owner_guid : number;
    public room_player_list : player_inline_info[];

    constructor(){
    }
}

export function room_info_to_protcol(_struct:room_info){
    return _struct;
}

export function protcol_to_room_info(_protocol:any){
    let _struct = new room_info();
    for (const [key, val] of Object.entries(_protocol))        if (key === "room_uuid"){
            _struct.room_uuid = val as string;
        }
        else if (key === "room_owner_guid"){
            _struct.room_owner_guid = val as number;
        }
        else if (key === "room_player_list"){
            _struct.room_player_list = [];
            for(let v_ of val){
                _struct.room_player_list.push(protcol_to_player_inline_info(v_));
    }
        }
    return _struct;
}

export class game_player_settle_info
{
    public guid : number;
    public name : string;
    public award_coin : number;
    public award_score : number;

    constructor(){
    }
}

export function game_player_settle_info_to_protcol(_struct:game_player_settle_info){
    return _struct;
}

export function protcol_to_game_player_settle_info(_protocol:any){
    let _struct = new game_player_settle_info();
    for (const [key, val] of Object.entries(_protocol))        if (key === "guid"){
            _struct.guid = val as number;
        }
        else if (key === "name"){
            _struct.name = val as string;
        }
        else if (key === "award_coin"){
            _struct.award_coin = val as number;
        }
        else if (key === "award_score"){
            _struct.award_score = val as number;
        }
    return _struct;
}

export class game_settle_info
{
    public settle_info : game_player_settle_info[];

    constructor(){
    }
}

export function game_settle_info_to_protcol(_struct:game_settle_info){
    return _struct;
}

export function protcol_to_game_settle_info(_protocol:any){
    let _struct = new game_settle_info();
    for (const [key, val] of Object.entries(_protocol))        if (key === "settle_info"){
            _struct.settle_info = [];
            for(let v_ of val){
                _struct.settle_info.push(protcol_to_game_player_settle_info(v_));
    }
        }
    return _struct;
}

export class svr_info
{
    public tick_time : number;
    public player_num : number;

    constructor(){
    }
}

export function svr_info_to_protcol(_struct:svr_info){
    return _struct;
}

export function protcol_to_svr_info(_protocol:any){
    let _struct = new svr_info();
    for (const [key, val] of Object.entries(_protocol))        if (key === "tick_time"){
            _struct.tick_time = val as number;
        }
        else if (key === "player_num"){
            _struct.player_num = val as number;
        }
    return _struct;
}

/*this module code is codegen by abelkhan codegen for typescript*/
