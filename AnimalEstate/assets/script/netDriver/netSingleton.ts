import * as login from "./netLogin"
import * as match from "./netMatch"
import * as room from "./netRoom"
import * as friend from "./netFriend"
import * as game from "./netGame"

export class netSingleton {
    public static login = new login.netLogin(); 
    public static friend = new friend.netFriend(netSingleton.login);
    public static game = new game.netGame(netSingleton.login);
    public static room = new room.netRoom(netSingleton.login, netSingleton.game);
    public static match = new match.netMatch(netSingleton.login, netSingleton.room, netSingleton.game);
}