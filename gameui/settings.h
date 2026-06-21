#ifndef __SETTINGS_H__
#define __SETTINGS_H__
#define __SETTINGS_H_ver__ 7

// 调试模式
bool debug_on=0;// 标志
// 日志窗口句柄
FILE*logStream=NULL;

void createLogWindow(){
    if(!debug_on){return;}
    logStream=fopen("saves/combat.log","w");
    if(logStream){
        fprintf(logStream,"========== Combat Log (Debug Mode) ==========\n");
        fprintf(logStream,"战斗详情将在此文件中记录\n\n");
        fflush(logStream);
    }
}// 创建日志文件

void closeLogWindow(){
    if(!debug_on){return;}
    if(logStream){
        fclose(logStream);
        logStream=NULL;
    }
}// 关闭日志文件

void logPrint(int colorCode,const char*format,...){
    if(!debug_on){return;}
    if(!logStream){return;}
    
    va_list args;
    va_start(args,format);
    vfprintf(logStream,format,args);
    fflush(logStream);
    va_end(args);
}// 日志输出函数

// 保存设置到文件
void saveSettings(){
    FILE*fp=fopen("saves/settings.dat","wb");
    if(fp){
        fwrite(&settings,sizeof(GameSettings),1,fp);
        fclose(fp);
    }
}

// 加载设置
void loadSettings(){
    FILE*fp=fopen("saves/settings.dat","rb");
    if(fp) {
        fread(&settings,sizeof(GameSettings),1,fp);
        fclose(fp);
    }
}

// 显示设置菜单
void settingsMenu(){
    system("cls");
    checkProgress(6);  // 打开设置成就
    int nowy=3;

    color(11);
    printf("+----------------------------------------------------------------+\n");
    printf("|                             Settings                           |\n");
    printf("+----------------------------------------------------------------+\n");
    color(7);
    printf("|    1. Auto Insane Mode                                 |       |\n");
    printf("|    2. Debug Log                                        |       |\n");
    printf("|    3. Chinese Tips                                     |       |\n");
    printf("|    4. Full Tips                                        |       |\n");
    printf("|    5. Hide Tips                                        |       |\n");
    printf("|    6. Choose & Learn Skills [EXPERIMENTAL]             |       |\n");
    printf("|    7. Full Roster Mode                                 |       |\n");
    color(11);
    printf("+----------------------------------------------------------------+\n");
    color(4);
    printf("|     Caution: Please think carefully before modifying settings, |\n");
    printf("| particularly those marked \"Chinese\" or \"Non-ASCII Characters,\" |\n");
    printf("| as they may cause text corruption or display anomalies.        |\n");
    printf("|     If an option is marked as [EXPERIMENTAL], it means it's an |\n");
    printf("| experimental game mode while it might cause errors, crashes or |\n");
    printf("| more grievous trouble if your computer cannot withstand it.    |\n");
    color(11);
    printf("+----------------------------------------------------------------+\n");
    color(14);
    printf("|  W/S to move, Enter to toggle, ESC to return to the Main Page  |\n");
    color(11);
    printf("+----------------------------------------------------------------+\n");
    color(7);

    gotoxy(0,3);
    color(14);
    printf("| ->");

    short onoffx=59;
    gotoxy(onoffx,3);
    if(settings.auto_insane){color(10);printf("[ON] ");}
    else{color(8);printf("[OFF]");}
    gotoxy(onoffx,4);
    if(settings.debug_log){color(10);printf("[ON] ");}
    else{color(8);printf("[OFF]");}
    gotoxy(onoffx,5);
    if(settings.chinese_tips){color(10);printf("[ON] ");}
    else{color(8);printf("[OFF]");}
    gotoxy(onoffx,6);
    if(settings.full_tips){color(10);printf("[ON] ");}
    else{color(8);printf("[OFF]");}
    gotoxy(onoffx,7);
    if(settings.hide_tips){color(10);printf("[ON] ");}
    else{color(8);printf("[OFF]");}
    gotoxy(onoffx,8);
    if(settings.Ct_Need_Chose){color(10);printf("[ON] ");}
    else{color(8);printf("[OFF]");}
    gotoxy(onoffx,9);
    if(settings.full_rosters){color(10);printf("[ON] ");}
    else{color(8);printf("[OFF]");}
    color(7);

    while(1){
        char key=getch();
        if((key=='w'||key=='W')&&nowy>3){
            color(7);
            gotoxy(0,nowy);
            printf("|   ");
            nowy--;
            color(14);
            gotoxy(0,nowy);
            printf("| ->");
        }else if((key=='s'||key=='S')&&nowy<9){
            color(7);
            gotoxy(0,nowy);
            printf("|   ");
            nowy++;
            color(14);
            gotoxy(0,nowy);
            printf("| ->");
        }else if(key==13){
            if(nowy==3){
                settings.auto_insane=!settings.auto_insane;
                saveSettings();
                gotoxy(onoffx,nowy);
                if(settings.auto_insane){
                    color(10);
                    printf("[ON] ");
                }else{
                    color(8);
                    printf("[OFF]");
                }
            }else if(nowy==4){
                settings.debug_log=!settings.debug_log;
                saveSettings();
                // 根据设置开关日志
                if(settings.debug_log&&!debug_on){
                    debug_on=1;
                    createLogWindow();
                }else if(!settings.debug_log&&debug_on) {
                    debug_on=0;
                    closeLogWindow();
                }
                gotoxy(onoffx,nowy);
                if(settings.debug_log){
                    color(10);
                    printf("[ON] ");
                }else{
                    color(8);
                    printf("[OFF]");
                }
            }else if(nowy==5){
                settings.chinese_tips=!settings.chinese_tips;
                saveSettings();
                gotoxy(onoffx,nowy);
                if(settings.chinese_tips){
                    color(10);
                    printf("[ON] ");
                }else{
                    color(8);
                    printf("[OFF]");
                }
            }else if(nowy==6){
                settings.full_tips=!settings.full_tips;
                saveSettings();
                gotoxy(onoffx,nowy);
                if(settings.full_tips){
                    color(10);
                    printf("[ON] ");
                }else{
                    color(8);
                    printf("[OFF]");
                }
            }else if(nowy==7){
                settings.hide_tips=!settings.hide_tips;
                saveSettings();
                gotoxy(onoffx,nowy);
                if(settings.hide_tips){
                    color(10);
                    printf("[ON] ");
                }else{
                    color(8);
                    printf("[OFF]");
                }
            }else if(nowy==8){
                settings.Ct_Need_Chose=!settings.Ct_Need_Chose;
                saveSettings();
                gotoxy(onoffx,nowy);
                if(settings.Ct_Need_Chose){
                    color(10);
                    printf("[ON] ");
                }else{
                    color(8);
                    printf("[OFF]");
                }
            }else if(nowy==9){
                settings.full_rosters=!settings.full_rosters;
                saveSettings();
                gotoxy(onoffx,nowy);
                if(settings.full_rosters){
                    color(10);
                    printf("[ON] ");
                }else{
                    color(8);
                    printf("[OFF]");
                }
            }
        }else if(key==27){break;}
    }
}

#endif// __SETTINGS_H__