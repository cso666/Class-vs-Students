#include"core.h"
#include"gameui.h"
#include"fight.h"

/* CAUTION
 *
 * core.h is including these funcs:
 *   choose reset checkListenStart applySubjectStart
 *   applySubjectEnd init team_chs sett
 *
 * fight.h is including these funcs:
 *   hitt sk_hitt checkIN checkCL startTurn endTurn
 *   endBattle selAtt selTar selAct attExe canAct
 *   turn fight CVS_game CVS_main
 * 
 * Use compile.bat in the project folder to compile with the icon.
 * But you can surely use Dev-C++ if you're only debugging.
 * 
 * You can use CTRL+CLICK and jump to the func fastly.
 * (Even at here! main.cpp!! You can try!!)
 */

int main(){
	CVS_main();
	return 0;
}