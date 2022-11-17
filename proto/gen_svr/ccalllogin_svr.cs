using System;
using System.Collections;
using System.Collections.Generic;
using System.Threading;
using MsgPack.Serialization;

namespace abelkhan
{
/*this enum code is codegen by abelkhan codegen for c#*/

/*this struct code is codegen by abelkhan codegen for c#*/
/*this module code is codegen by abelkhan codegen for c#*/
    public class login_player_login_no_author_rsp : common.Response {
        private string _client_uuid_2c74a728_390c_3834_83d5_c8331456ea49;
        private UInt64 uuid_a1ff763c_08d3_3f84_8f78_1360ca04e765;
        public login_player_login_no_author_rsp(string client_uuid, UInt64 _uuid)
        {
            _client_uuid_2c74a728_390c_3834_83d5_c8331456ea49 = client_uuid;
            uuid_a1ff763c_08d3_3f84_8f78_1360ca04e765 = _uuid;
        }

        public void rsp(string player_hub_name_e16830b9_52e1_36d5_aff7_3ebaf4d86eb0, string token_6333efe6_4f25_3c9a_a58e_52c6c889a79e){
            var _argv_2c74a728_390c_3834_83d5_c8331456ea49 = new ArrayList();
            _argv_2c74a728_390c_3834_83d5_c8331456ea49.Add(uuid_a1ff763c_08d3_3f84_8f78_1360ca04e765);
            _argv_2c74a728_390c_3834_83d5_c8331456ea49.Add(player_hub_name_e16830b9_52e1_36d5_aff7_3ebaf4d86eb0);
            _argv_2c74a728_390c_3834_83d5_c8331456ea49.Add(token_6333efe6_4f25_3c9a_a58e_52c6c889a79e);
            hub.hub._gates.call_client(_client_uuid_2c74a728_390c_3834_83d5_c8331456ea49, "login_rsp_cb_player_login_no_author_rsp", _argv_2c74a728_390c_3834_83d5_c8331456ea49);
        }

        public void err(Int32 err_ad2710a2_3dd2_3a8f_a4c8_a7ebbe1df696){
            var _argv_2c74a728_390c_3834_83d5_c8331456ea49 = new ArrayList();
            _argv_2c74a728_390c_3834_83d5_c8331456ea49.Add(uuid_a1ff763c_08d3_3f84_8f78_1360ca04e765);
            _argv_2c74a728_390c_3834_83d5_c8331456ea49.Add(err_ad2710a2_3dd2_3a8f_a4c8_a7ebbe1df696);
            hub.hub._gates.call_client(_client_uuid_2c74a728_390c_3834_83d5_c8331456ea49, "login_rsp_cb_player_login_no_author_err", _argv_2c74a728_390c_3834_83d5_c8331456ea49);
        }

    }

    public class login_module : common.imodule {
        public login_module()
        {
            hub.hub._modules.add_mothed("login_player_login_no_author", player_login_no_author);
        }

        public event Action<string> on_player_login_no_author;
        public void player_login_no_author(IList<MsgPack.MessagePackObject> inArray){
            var _cb_uuid = ((MsgPack.MessagePackObject)inArray[0]).AsUInt64();
            var _account = ((MsgPack.MessagePackObject)inArray[1]).AsString();
            rsp = new login_player_login_no_author_rsp(hub.hub._gates.current_client_uuid, _cb_uuid);
            if (on_player_login_no_author != null){
                on_player_login_no_author(_account);
            }
            rsp = null;
        }

    }

}
