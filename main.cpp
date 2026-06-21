/**
 * @file main.cpp
 * @brief The entrance of CVS.
 * 
 * @author Floiyd Forging Team
 * @date 2026-06-20
 * @version 1.2
 * @copyright Floiyd Forging Team
 * @since 2025-12-20
 * 
 * ============================================================
 *  FUNCTION LINKS
 *
 * [game/core.h]
 *   gotoxy                 - 移动控制台光标
 *   color                  - 设置控制台文字颜色
 *   ppput                  - 逐字打印带延迟
 *   setConsoleSize         - 设置控制台窗口大小
 *
 * [game/subject.h]
 *   checkListenStart       - 不听讲惩罚检查
 *   applySubjectStart      - 学科开始效果
 *   applySubjectEnd        - 学科结束效果
 *
 * [game/pregame.h]
 *   hasLinkSkill           - 检查队伍是否存在连携组合
 *   getCtSymbols           - 获取学生词条符号字符串
 *   choose                 - 根据ID获取学生实例
 *   reset                  - 重置所有学生数据
 *   init                   - 初始化随机队伍
 *   team_chs               - 选人阶段
 *   sett                   - 显示战斗界面
 *
 * [gameui/achieve.h]
 *   printAch               - 成就解锁输出
 *   saveAch                - 保存成就到文件
 *   loadAch                - 从文件加载成就
 *   checkProgress          - 解锁进度成就
 *   unlockChallenge        - 解锁挑战成就
 *   achievementMenu        - 显示成就页面
 *
 * [gameui/settings.h]
 *   createLogWindow        - 创建日志文件
 *   closeLogWindow         - 关闭日志文件
 *   logPrint               - 日志输出函数
 *   saveSettings           - 保存设置到文件
 *   loadSettings           - 从文件加载设置
 *   settingsMenu           - 显示设置菜单
 *
 * [gameui/tips.h]
 *   showTip                - 显示Tip
 *
 * [gameui/guide.h]
 *   guide                  - 显示图鉴页面
 *
 * [experi/learnsk.h]
 *   getCtTypeName          - 获取词条类型名称
 *   getCtBorder            - 获取边框样式
 *   Choose_Ct              - 抽词条界面
 *   Choose_Ct_Main         - 抽词条主函数
 *   Fix_Ct                 - 应用词条效果
 *   Lets_Choose_Ct         - 抽词条主入口
 *
 * [basic_gui/pic.h]
 *   display_pic            - 显示BMP图片
 *
 * [game/fight.h]
 *   hitt                   - 普通攻击
 *   sk_hitt                - 技能攻击
 *   toge_fight             - 连携攻击
 *   checkIN                - 疯人状态检查
 *   checkCL                - 疯人状态解除
 *   startTurn              - 回合开始
 *   endTurn                - 回合结束
 *   endBattle              - 战斗结束检查
 *   selAtt                 - 选择攻击方
 *   selTar                 - 选择受击方
 *   selAct                 - 选择行动类型
 *   attDis                 - 攻击显示
 *   attExe                 - 执行攻击
 *   canAct                 - 检查队伍是否有可行动人员
 *   turn                   - 主战斗循环
 *   fight                  - 单节课战斗
 *
 * [game/cvsmain.h]
 *   CVS_game               - 主游戏循环
 *   clear_action_area      - 清空战斗操作区域
 *   startASCIIart          - 启动字符画
 *   CVS_main               - 主菜单
 * ============================================================
 *  STUDENTS
 *
 *   A0.h   - __stud__ 基类
 *   A1.h   - stud_A1 (A01)
 *   A2.h   - stud_A2 (A02)
 *   A3.h   - stud_A3 (A03) + stud_A24
 *   A4.h   - stud_A4 (A04) + stud_A4_L
 *   A5.h   - stud_A5 (A05)
 *   A6.h   - stud_A6 (A06)
 *   A7.h   - stud_A7 (A07)
 *   A8.h   - stud_A8 (A08)
 *   A9.h   - stud_A9 (A09)
 *   A10.h  - stud_A10 (A10)
 *   A12.h  - stud_A12 (A12)
 *   A13.h  - stud_A13 (A13)
 *   B1.h   - stud_B1 (B01)
 *   B2.h   - stud_B2 (B02)
 *   B3.h   - stud_B3 (B03)
 *   B4.h   - stud_B4 (B04)
 *   B5.h   - stud_B5 (B05)
 *   B6.h   - stud_B6 (B06)
 *   B7.h   - stud_B7 (B07)
 *   B8.h   - stud_B8 (B08)
 *   B9.h   - stud_B9 (B09)
 *   B10.h  - stud_B10 (B10)
 *   B11.h  - stud_B11 (B11)
 *   B12.h  - stud_B12 (B12)
 *   B13.h  - stud_B13 (B13)
 *   B14.h  - stud_B14 (B14)
 *   B15.h  - stud_B15 (B15)
 * ============================================================
 *  TREE
 *
 * Project_CVS
 * |   app.rc
 * |   compile.bat
 * |   icon.bmp
 * |   icon.ico
 * |   main.cpp
 * |   README.md
 * |   start.bat
 * |
 * +---experi
 * |       learnsk.h
 * |
 * +---basic_gui
 * |       pic.h
 * |
 * +---game
 * |       core.h
 * |       cvsmain.h
 * |       fight.h
 * |       pregame.h
 * |       subject.h
 * |
 * +---gameui
 * |       achieve.h
 * |       guide.h
 * |       settings.h
 * |       tips.h
 * |
 * \---students
 *         A0.h
 *         A1.h
 *         A2.h
 *         A3.h
 *         A4.h
 *         A5.h
 *         A6.h
 *         A7.h
 *         A8.h
 *         A9.h
 *         A10.h
 *         A12.h
 *         A13.h
 *         B1.h
 *         B2.h
 *         B3.h
 *         B4.h
 *         B5.h
 *         B6.h
 *         B7.h
 *         B8.h
 *         B9.h
 *         B10.h
 *         B11.h
 *         B12.h
 *         B13.h
 *         B14.h
 *         B15.h
 * ============================================================
 *  NOTICE 
 *
 * Use compile.bat in the project folder to compile with the icon. 
 * But you can surely use Dev-C++ if you're only debugging.
 * 
 * You can use CTRL+CLICK and jump to the func fastly.
 * If you can't, try first click the header's, and click in the header.
 * For example, first CTRL+CLICK `__GAMEUI_H__` and then CTRL_CLICK `guide` in gameui.h.
 */

#include"game/core.h"
#include"game/subject.h"
#include"game/pregame.h"
#include"gameui/achieve.h"
#include"gameui/settings.h"
#include"gameui/tips.h"
#include"gameui/guide.h"
#include"experi/learnsk.h"
#ifdef PICUSE
#include"basic_gui/pic.h"
#endif
#include"game/fight.h"
#include"game/cvsmain.h"
using namespace std;

int main(int argc,char**argv){
    if(argc>1){
        string arg=argv[1];
        if(arg=="--help"||arg=="/help"||arg=="\\help"){
            printf(R"---(\
=======Class vs. Students=======
          by Floiyd Forging Team

--[argv] or /[argv] or \[argv]
You can only input 1 argument,
CVS will ignore the redundancies.

(nothing): Run game.
--help: Show this page.
--version: Show CVS's version.
--start: Run game.
)---");
            return 0;
        }else if(arg=="--version"||arg=="/version"||arg=="\\version"){
            printf("Class vs. Students - Version 1.2\n");
            return 0;
        }else if(arg=="--start"||arg=="/start"||arg=="\\start"){}else{
			printf("Invalid argument.\nTry --help to get help.");
			return 0;
		}
    }
	//display_pic("icon.bmp",50,50);
	//Sleep(10000);
	CVS_main();
	return 0;
}