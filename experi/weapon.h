#ifndef __WEAPON_H__
#define __WEAPON_H__
#define __WEAPON_H_ver__ 4
#define NOW_NUM_OF_WEAPON 6
// #include<weapon_enchant.h>
/*
1	#define NOW_NUM_OF_WEAPON	数字 +1
2	新增 class wp_xxx	定义新武器类
3	声明全局变量 wp_xxx xxx;	在全局变量区域
4	every_weapon[] 数组	添加 &xxx
5   A0.h加extern和声明
*/

// 父类
class weapon
{
public:
    stud* student;
    int id;
    string name;
    int rarity; // 稀有度
    bool had;
    bool equipped;
    //  bool enchanted;//附魔
    //  vector<enchant*>info;
    /*
    0:灰
    1:绿
    2:蓝
    3:紫
    4:金
    */
    weapon()
    {
        student=nullptr;
        id = -1;
        rarity = 0;
        had = false;
        equipped = false;
    }
    virtual void equip(stud *target)
    {
        ;
    }
    virtual void on_using(stud *our_target, stud *beside_target, vector<stud *> team, vector<stud *> beside_team)
    {
        ;
    }
    virtual void unequip(stud *target)
    {
        ;
    }
    ~weapon() = default;
};
// 武器0：空
class wp_empty : public weapon
{
public:
    wp_empty()
    {
        id = 0;
        name = "empty";
        rarity = 0;
    }
};
// 武器1:中性笔
/*
效果：
1.伤害+3
2.攻击时有10%概率让对方连续3回合扣3滴血，且1回合不能移动。
*/
class wp_pen : public weapon
{
public:
    wp_pen()
    {
        id = 1;
        name = "pen";
        rarity = 1;
    }
    void equip(stud *target) override
    {
        target->tmp_att_plus[0].first+=3;
    }
    void on_using(stud *our_target, stud *beside_target, vector<stud *> team, vector<stud *> beside_team) override
    {
        if (rand() % 10 == 9)
        {
            beside_target->on_turn_end_cred.push_back({-3, 3});
            beside_target->can_act = false;
            beside_target->cant_act = 1;
        }
    }
    void unequip(stud *target) override
    {
        target->tmp_att_plus[0].first-=3;
    }
};
// 武器2:尺子
/*
效果：
1.攻击时各有33%概率{
 1.对方扣5滴血
 2.连续3回合扣2滴血
 3.对方三回合受到攻击乘1.2
}
 */
class wp_ruler : public weapon
{
public:
    wp_ruler()
    {
        id = 2;
        name = "ruler";
        rarity = 1;
    }
    void equip(stud *target) override
    {
        ;
    }
    void on_using(stud *our_target, stud *beside_target, vector<stud *> team, vector<stud *> beside_team) override
    {
        int action = rand() % 3;
        switch (action)
        {
        case 0:
        {
            beside_target->cred(-5);
            break;
        }
        case 1:
        {
            beside_target->on_turn_end_cred.push_back({-2, 3});
            break;
        }
        case 2:
        {
            beside_target->be_att_mul.push_back({1.2, 3});
            break;
        }
        }
    }
    void unequip(stud *target) override
    {
        ;
    }
};
// 武器3:橡皮
/*
效果：
1.装备上攻击力*0.5
2.在使用时对方全队受到5的溅射伤害
*/
class wp_eraser : public weapon
{
public:
    wp_eraser()
    {
        id = 3;
        name = "eraser";
        rarity = 1;
    }
    void equip(stud *target) override
    {
        target->att_mul[0].first*=0.5;
    }
    void on_using(stud *our_target, stud *beside_target, vector<stud *> team, vector<stud *> beside_team) override
    {
        for (auto x : beside_team)
        {
            x->cred(-5);
        }
    }
    void unequip(stud *target) override
    {
        target->att_mul[0].first*=2.0;
    }
};
//武器4：铅笔
/*
效果：
1.攻击力+5
2.当攻击时对方沉默1~4回合不等
*/
class wp_pencil : public weapon {
    public:
    wp_pencil(){
        id=4;
        name="pencil";
        rarity=2;
    }
    void equip(stud*target) override {
        target -> tmp_att_plus[0].first+=5;
    }
    void on_using(stud *our_target, stud *beside_target, vector<stud *> team, vector<stud *> beside_team) override {
        int r=rand()%4+1;
        beside_target -> can_act=false;
        beside_target -> cant_act=r;
    }
    void unequip(stud* target) override {
        target -> tmp_att_plus[0].first-=5;
    }
};
//武器5：杯子(雾)
/*
效果：
1.攻击力+8
2.当B10使用杯子攻击A2时，攻击力+15，扣20蓝，否则有1/30的概率加10攻击，对方6回合不能行动，我方2回合不能行动，且我方扣5蓝，10白
3.否则攻击后加15蓝
*/
class wp_cup : public weapon {
    public:
    wp_cup(){
        id=5;
        name="cup";
        rarity=3;
    }
    void equip(stud* target) override {
        target -> tmp_att_plus[0].first+=8;
    }
    void on_using(stud* our_target,stud* beside_target,vector<stud*> team,vector<stud*>beside_team) override {
        int r=rand()%30;
        if(beside_target -> id ==2 && our_target -> id==23){
            our_target -> tmp_att_plus.push_back({15,1});
            our_target -> cblue(-20);
        }
        else if(r==1){
            our_target -> tmp_att_plus.push_back({10,1});
            beside_target -> can_act=false;
            beside_target -> cant_act=6;
            our_target -> can_act =false;
            our_target -> cant_act=2;
            our_target -> cblue(-5);
            our_target -> cwhite(-10);
        }
        else {
            our_target -> cblue(15);
        }
    }
    void unequip(stud* target) override {
        target -> tmp_att_plus[0].first-=8;
    }
};
//武器6：书
/*
效果：
1.攻击力+5
2.攻击时-5白
3.攻击时有20%概率加3攻击
*/
class wp_book : public weapon{
    public:
    wp_book(){
        id=6;
        name="book";
        rarity=1;
    }
    void equip(stud* target) override {
        target -> tmp_att_plus[0].first+=3;
    }
    void on_using(stud* our_target,stud* beside_target,vector<stud*> team ,vector<stud*> beside_team) override {
        our_target->cwhite(-5);
        int r=rand()%5;
        if(r==0){
            our_target -> tmp_att_plus.push_back({3,1});
        }
    }
    void unequip(stud* target) override {
        target -> tmp_att_plus[0].first-=3;
    }
};
vector<weapon *> TAweapon;
vector<weapon *> TBweapon;
wp_empty EMPTY;
wp_pen pen;
wp_ruler ruler;
wp_eraser eraser;
wp_pencil pencil;
wp_cup cup;
wp_book book;
weapon *every_weapon[NOW_NUM_OF_WEAPON] = {&pen, &ruler, &eraser,&pencil,&cup,&book};
bool all = false;
weapon *get_rand_weapon()
{
    int r = rand() % NOW_NUM_OF_WEAPON;
    if (!all)
    {
        while (every_weapon[r]->had)
            r = rand() % NOW_NUM_OF_WEAPON;
        every_weapon[r]->had = true;
        bool flag = true;
        for (int i = 0; i < NOW_NUM_OF_WEAPON; i++)
        {
            if (!every_weapon[i]->had)
            {
                flag = false;
                break;
            }
        }
        all = flag;
        return every_weapon[r];
    }
    return &EMPTY;
}
void reset_every_weapon()
{
    all = false;
    for (int i = 0; i < NOW_NUM_OF_WEAPON; i++)
    {
        every_weapon[i]->had = false;
        every_weapon[i]->equipped = false;
    }
}
long long get_color_of_weapon(weapon *ptr)
{
    switch (ptr->rarity)
    {
    case 0:
    {
        return 7;
        break;
    }
    case 1:
    {
        return 10;
        break;
    }
    case 2:
    {
        return 11;
        break;
    }
    case 3:
    {
        return 13;
    }
    case 4:
    {
        return 6;
    }
    default:
    {
        return 7;
        break;
    }
    }
}
const char *get_weapon_name(weapon *ptr)
{
    return ptr->name.c_str();
}
vector<weapon *> getAvailableWeaponsWithEmpty(vector<weapon *> &teamWeapons)
{
    vector<weapon *> result;
    result.push_back(&EMPTY); // EMPTY 始终可用
    for (auto w : teamWeapons)
    {
        if (!w->equipped && w->id != 0)
        {
            result.push_back(w);
        }
    }
    return result;
}

// 切换到下一个武器（direction: 1=左, -1=右）
void switchWeapon(stud *student, vector<weapon *> &teamWeapons, int &weaponPointer, int direction)
{
    if (student == nullptr || student->wp == nullptr) return;
    vector<weapon *> available = getAvailableWeaponsWithEmpty(teamWeapons);
    if (available.empty())
        return;

    // 确保 weaponPointer 有效
    if (weaponPointer >= (int)available.size())
    {
        weaponPointer = available.size() - 1;
    }

    // 移动指针
    if (direction == 1)
    { // 左
        if (weaponPointer > 0)
            weaponPointer--;
        else
            weaponPointer = available.size() - 1;
    }
    else
    { // 右
        if (weaponPointer < (int)available.size() - 1)
            weaponPointer++;
        else
            weaponPointer = 0;
    }

    weapon *selected = available[weaponPointer];

    // 如果选中的是 EMPTY，卸下武器
    if (selected->id == 0)
    {
        if (student->wp->id != 0)
        {
            student->wp->equipped = false;
            student -> wp -> unequip(student);
        }
        student->wp = &EMPTY;
    }
    else
    {
        // 旧武器放回仓库
        if (student->wp->id != 0)
        {
            student->wp->equipped = false;
            student -> wp -> unequip(student);
        }
        student->wp = selected;
        selected->equipped = true;
        selected -> equip(student);
    }
}

// 统计可用武器数量（不包括 EMPTY）
int countAvailableWeapons(vector<weapon *> &weapons)
{
    int count = 0;
    for (auto w : weapons)
    {
        if (!w->equipped && w->id != 0)
            count++;
    }
    return count;
}

// 获取第 index 个可用武器
weapon *getAvailableWeapon(vector<weapon *> &weapons, int index)
{
    int count = 0;
    for (auto w : weapons)
    {
        if (!w->equipped && w->id != 0)
        {
            if (count == index)
                return w;
            count++;
        }
    }
    return &EMPTY;
}

// 卸载所有学生的武器（重置 equipped 状态）
void unequip_every_student()
{
    for (auto w : TAweapon)
    {
        if (w->student != nullptr) {
            w->unequip(w->student);
            w->student = nullptr;
        }
        w->equipped = false;
    }
    for (auto w : TBweapon)
    {
        if (w->student != nullptr) {   
            w->unequip(w->student);
            w->student = nullptr;
        }
        w->equipped = false;
    }
}

// ============================================================
//  change_weapon 主函数
// ============================================================

void change_weapon(vector<stud *> tA, vector<stud *> tB)
{
    system("cls");
    color(7);
    unequip_every_student();

    for (auto s : tA) {
        if (s != nullptr) s->wp = &EMPTY;
    }
    for (auto s : tB) {
        if (s != nullptr) s->wp = &EMPTY;
    }

    for (int i = 0; i < TAweapon.size(); i++) {
        if (TAweapon[i] == NULL) {
            TAweapon.erase(TAweapon.begin() + i);
            i--;
        }
    }
    for (int i = 0; i < TBweapon.size(); i++) {
        if (TBweapon[i] == NULL) {
            TBweapon.erase(TBweapon.begin() + i);
            i--;
        }
    }
    vector<stud*> aliveA, aliveB;
    for (auto s : tA) {
        if (s != NULL && isalive[s->id] && s->red >= 0 && s->status != 0) {
            aliveA.push_back(s);
        }
    }
    for (auto s : tB) {
        if (s != NULL && isalive[s->id] && s->red >= 0 && s->status != 0) {
            aliveB.push_back(s);
        }
    }
    
    // 如果所有学生都死了，直接返回
    if (aliveA.empty() && aliveB.empty()) return;
    
    // 如果某队没人了，用空 vector
    if (aliveA.empty() || aliveB.empty()) {
        // 没有学生的队伍无法分配武器，直接返回
        return;
    }

    // ============================================================
    //  Team A
    // ============================================================
    if (!TAweapon.empty())
    {
        int pointer = 1;       // 当前选中的学生 (1-5)
        int weaponPointer = 0; // 当前选中的武器索引

        while (true)
        {
            system("cls");
            printf("Team A's turn, choose weapon for students.\n");
            printf("Your Weapon (use A/D to cycle):\n");

            // 显示可用武器（包括 EMPTY）
            vector<weapon *> available = getAvailableWeaponsWithEmpty(TAweapon);

            if (available.empty())
            {
                printf("(no available weapons)");
            }
            else
            {
                // 确保 weaponPointer 有效
                if (weaponPointer >= (int)available.size())
                {
                    weaponPointer = available.size() - 1;
                }

                for (int i = 0; i < (int)available.size(); i++)
                {
                    if (i == weaponPointer)
                    {
                        
                        printf("-> ");
                    }
                    else
                    {
                        printf("   ");
                    }
                    if (available[i]->id == 0)
                    {
                        
                        printf("[empty]   ");
                        
                    }
                    else
                    {
                        color(get_color_of_weapon(available[i]));
                        printf("[%s]    ", available[i]->name.c_str());
                        
                    }
                }
            }
            printf("\n\n");
            color(7);
            
            printf("Students:\n");
            for (int i = 1; i <= 5; i++)
            {   
                printf("%s     [%s] ", tA[i - 1]->name.c_str(), tA[i - 1]->wp->name.c_str());
                if (pointer == i){
                    color(14);
                    printf("<-");
                    color(7);
                }
                printf("\n");
                
            }
            printf("W/S: change student | A/D: cycle weapon | ENTER: exit\n");

            char op = getch();

            if ((op == 'w' || op == 'W') && pointer > 1)
            {
                pointer--;
                weaponPointer = 0;
            }
            else if ((op == 's' || op == 'S') && pointer < 5)
            {
                pointer++;
                weaponPointer = 0;
            }
            else if (op == 'a' || op == 'A')
            {
                // 向左切换武器（包括 EMPTY）
                switchWeapon(tA[pointer - 1], TAweapon, weaponPointer, 1);
            }
            else if (op == 'd' || op == 'D')
            {
                // 向右切换武器（包括 EMPTY）
                switchWeapon(tA[pointer - 1], TAweapon, weaponPointer, -1);
            }
            else if (op == '\r' || op == '\n')
            {
                break;
            }
        }
    }

    system("cls");

    // ============================================================
    //  Team B
    // ============================================================
    if (!TBweapon.empty())
    {
        color(7);
        int pointer = 1;
        int weaponPointer = 0;

        while (true)
        {
            system("cls");
            printf("Team B's turn, choose weapon for students.\n");
            printf("Your Weapon (use A/D to cycle):\n");

            vector<weapon *> available = getAvailableWeaponsWithEmpty(TBweapon);

            if (available.empty())
            {
                printf("(no available weapons)");
                
            }
            else
            {
                if (weaponPointer >= (int)available.size())
                {
                    weaponPointer = available.size() - 1;
                }

                for (int i = 0; i < (int)available.size(); i++)
                {
                    if (i == weaponPointer)
                    {
                        color(14);
                        printf("-> ");
                    }
                    else
                    {
                        printf("   ");
                    }
                    if (available[i]->id == 0)
                    {
                        printf("[empty]   ");
                    }
                    else
                    {
                        color(get_color_of_weapon(available[i]));
                        printf("[%s]    ", available[i]->name.c_str());
                        color(7);
                    }
                }
            }
            printf("\n\n");

            color(7);
            printf("Students:\n");
            for (int i = 1; i <= 5; i++)
            {
                printf("%s     [%s] ", tB[i - 1]->name.c_str(), tB[i - 1]->wp->name.c_str());
                if (pointer == i)
                    printf("<-");
                printf("\n");
            }
            printf("W/S: change student | A/D: cycle weapon | ENTER: exit\n");

            char op = getch();

            if ((op == 'w' || op == 'W') && pointer > 1)
            {
                pointer--;
                weaponPointer = 0;
            }
            else if ((op == 's' || op == 'S') && pointer < 5)
            {
                pointer++;
                weaponPointer = 0;
            }
            else if (op == 'a' || op == 'A')
            {
                switchWeapon(tB[pointer - 1], TBweapon, weaponPointer, 1);
            }
            else if (op == 'd' || op == 'D')
            {
                switchWeapon(tB[pointer - 1], TBweapon, weaponPointer, -1);
            }
            else if (op == '\r' || op == '\n')
            {
                break;
            }
        }
    }

    color(7);
    system("cls");
}
#endif