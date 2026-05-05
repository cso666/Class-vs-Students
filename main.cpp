#include"core.h"
#include"gameui.h"
#include"experi.h"
#include"fight.h"

/*
 * LINKS
 *
 * __stud__ (A0.h):
 *   stud_A1  (A1.h)  stud_A2  (A2.h)  stud_A3  (A3.h)  stud_A4  (A4.h)
 *   stud_A5  (A5.h)  stud_A6  (A6.h)  stud_A7  (A7.h)  stud_A8  (A8.h)
 *   stud_A9  (A9.h)  stud_A10 (A10.h) stud_A12 (A12.h) stud_A13 (A13.h)
 *   stud_B1  (B1.h)  stud_B2  (B2.h)  stud_B3  (B3.h)  stud_B4  (B4.h)
 *   stud_B5  (B5.h)  stud_B6  (B6.h)  stud_B7  (B7.h)  stud_B8  (B8.h)
 *   stud_B9  (B9.h)  stud_B10 (B10.h) stud_B11 (B11.h) stud_B12 (B12.h)
 *   stud_B13 (B13.h) stud_B14 (B14.h) stud_B15 (B15.h)
 *
 * __CORE_H__ (core.h):
 *   choose                - 根据ID获取学生实例
 *   reset                 - 重置所有学生数据
 *   checkListenStart      - 不听讲惩罚检查
 *   applySubjectStart     - 学科开始效果
 *   applySubjectEnd       - 学科结束效果
 *   init                  - 初始化随机队伍
 *   team_chs              - 选人阶段
 *   sett                  - 显示战斗界面
 *
 * __FIGHT_H__ (fight.h):
 *   hitt                  - 普通攻击
 *   sk_hitt               - 技能攻击
 *   checkIN               - 疯人状态检查
 *   checkCL               - 疯人状态解除
 *   startTurn             - 回合开始
 *   endTurn               - 回合结束
 *   endBattle             - 战斗结束检查
 *   selAtt                - 选择攻击方
 *   selTar                - 选择受击方
 *   selAct                - 选择行动类型
 *   attExe                - 执行攻击
 *   canAct                - 检查是否有可行动人员
 *   turn                  - 主战斗循环
 *   fight                 - 单节课战斗
 *   CVS_game              - 主游戏循环
 *   CVS_main              - 主菜单
 *
 * __EXPERI_H__ (experi.h):
 * 本来想合并的，结果一测！我了个去，遂不合并
 * 取名意为 Experimental Gameplay（实验性玩法），之后再改
 *
 * __GAMEUI_H__ (gameui.h):
 *   achievementMenu       - 成就页面
 *   settingsMenu          - 设置页面
 *   guide                 - 图鉴页面
 *   showTip               - 显示提示
 *   startASCIIart         - 启动字符画
 * 
 * Use compile.bat in the project folder to compile with the icon. 
 * But you can surely use Dev-C++ if you're only debugging.
 * 
 * You can use CTRL+CLICK and jump to the func fastly. (Even at here! main.cpp!! You can try!!)
 * If you can't, try first click the header's, and click in the header.
 * For example, first CTRL+CLICK `__GAMEUI_H__` and then CTRL_CLICK `guide` in gameui.h.
 */

int main(){
	CVS_main();
	return 0;
}
