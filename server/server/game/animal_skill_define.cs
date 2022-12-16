using abelkhan;
using System.Collections.Generic;
using System.Security.Cryptography;
using System.Security.Principal;

namespace game
{
    partial class client_proxy
    {
        private bool check_could_use_skill()
        {
            if (rounds < 5)
            {
                return false;
            }

            if (skill_is_used)
            {
                return false;
            }

            return true;
        }

        enum enum_skill_state
        {
            em_phantom_dice = 1,
            em_thief = 2,
            em_step_lotus = 3,
            em_preemptive_strike = 4,
            em_move_halved = 5,
            em_can_not_move = 6,
            em_immunity = 7,
            em_unable_use_props = 8,
            em_action_three = 9,
            em_turtle_shell = 10,
            em_fake_dice = 11,
        }

//1.号角：选择一个角色移动能力减弱(每轮移动色子点数/2)（持续两回合）
//2.炸弹：选择一个角色轰炸，使他停止行动2回合
//3.救命毫毛：使用后三回合内免疫一次道具攻击
//4.天雷：除自己外，所有玩家向后退后三格
//5.小丑礼盒：戏弄人的盒子，效果是使任意一个玩家三回合无法使用道具。
//6.亢奋花瓣：使你下个回合额外获得两次行动回合。
//7.夹子：原地留下一个夹子，使踩上角色无法使用丢骰子移动。
//8.地雷：原地留下一个夹子，使踩上的玩家后退4格。
//9.弹簧：原地留下一个夹子，使踩上的玩家弹会上次移动位置。
//10.无敌龟壳：反射一次负面道具效果，（但不能反射给发射者）
//11.香蕉：使任意一个玩家下次投骰子往反方向移动。
//12.西瓜皮：原地扔下西瓜皮，踩上的玩家随机向前或是向后移动3格
//13.红蘑菇，选择一个你的角色，使他向前固定移动4格。
//14.扭蛋：随机获得一个道具。
//15.假骰子：选择一个玩家，使他下次投骰子只能投出1—3，


//幻影骰子：使用后，之后五个回合，你的骰子只有6（如果遇到假骰子，则假骰子失效）
//移魂大法：选择一个自己的角色和一个其他角色，然后你的角色成为他的棋子，他的棋子成为你的棋子
//神偷再世：偷取一个玩家的所有道具然后可以在这个回合使用三次道具
//步步生莲：选择你的一个角色，之后他走过的地方以30%的概率生成一个(夹子/地雷/弹簧)持续五个回合
//先发制人：该玩家开局第一个行动，并且摇到3以下就拥有额外一个行动回合（无限触发）
//移形换影：调换你场上一个角色和其他玩家场上的某个角色的位置
//奥特光波：选择一个角色，让他沉睡十回合
//乾坤大挪移：使用后，所有角色位置会排队来到你选定的角色身后

        private void phantom_dice_skill(long target_client_guid, short target_animal_index)
        {
            skill_Effects.Add(new()
            {
                skill_state = enum_skill_state.em_phantom_dice,
                continued_rounds = 5,
            });
        }

        private void soul_moving_method(long target_client_guid, short target_animal_index)
        {
            var target_client = _impl.get_client_proxy(target_client_guid);
            var src = target_client.PlayerGameInfo.animal_info[target_animal_index];
            var dest = PlayerGameInfo.animal_info[PlayerGameInfo.current_animal_index];

            target_client.PlayerGameInfo.animal_info[target_animal_index] = dest;
            PlayerGameInfo.animal_info[PlayerGameInfo.current_animal_index] = src;
        }

        private void thief_reborn(long target_client_guid, short target_animal_index)
        {
            var target_client = _impl.get_client_proxy(target_client_guid);
            props_list.AddRange(target_client.props_list);
            target_client.props_list.Clear();

            active_State.could_use_props = true;
            active_State.use_props_count = 3;
        }

        private void step_lotus(long target_client_guid, short target_animal_index)
        {
            skill_Effects.Add(new()
            {
                skill_state = enum_skill_state.em_step_lotus,
                continued_rounds = 5,
            });
        }

        private void preemptive_strike(long target_client_guid, short target_animal_index)
        {
            _impl.ClientProxys.Remove(this);
            _impl.ClientProxys.Insert(0, this);

            skill_Effects.Add(new()
            {
                skill_state = enum_skill_state.em_preemptive_strike,
                continued_rounds = int.MaxValue,
            });
        }

        private void swap_places(long target_client_guid, short target_animal_index)
        {
            var target_client = _impl.get_client_proxy(target_client_guid);
            var src = target_client.PlayerGameInfo.animal_info[target_animal_index];
            var dest = PlayerGameInfo.animal_info[PlayerGameInfo.current_animal_index];

            var tmp_pos = src.current_pos;
            src.current_pos = dest.current_pos;
            dest.current_pos = tmp_pos;
        }


    }
}
