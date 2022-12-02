import * as login from "./netLogin"
import * as match from "./netMatch"
import * as room from "./netRoom"
import * as friend from "./netFriend"
import * as game from "./netGame"

export class netSingleton {
    public static login = new login.netLogin(); 
    public static match = new match.netMatch();
    public static room = new room.netRoom();
    public static friend = new friend.netFriend();
    public static game = new game.netGame();
}