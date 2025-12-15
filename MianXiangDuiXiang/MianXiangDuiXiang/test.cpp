#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;

// 角色状态
enum State {
    NORMAL,    // 正常
    INJURED,   // 受伤（攻击力下降）
    STUNNED,   // 眩晕（无法行动）
    ENHANCED,  // 强化（攻击力提升）
    DEAD       // 死亡
};

// 技能类
class Skill {
private:
    string _name;        // 技能名称
    string _desc;        // 技能描述
    int _damage;         // 伤害值
    int _manaCost;       // 魔法消耗
    int _cooldown;       // 冷却时间
    int _currentCD;      // 当前冷却

public:
    Skill(string name, string desc, int damage, int manaCost, int cooldown,int currentCD =0)
        : _name(name), _desc(desc), _damage(damage), _manaCost(manaCost), _cooldown(cooldown), _currentCD(currentCD)
    {}

    // 获取技能信息
    string getName() { return _name; }
    string getDesc() { return _desc; }
    int getDamage() { return _damage; }
    int getManaCost() { return _manaCost; }
    int getCooldown() { return _cooldown; }
    int getCurrentCD() { return _currentCD; }

    // 设置冷却时间
    void setCurrentCD(int cd) { _currentCD = cd; }

    // 减少冷却
    void reduceCD() {
        if (_currentCD > 0) _currentCD--;
    }

    // 重置冷却
    void resetCD() { _currentCD = _cooldown; }

    // 显示技能信息
    void display() {
        cout << "[" << _name << "] " << _desc << " 伤害:" << _damage
            << " 消耗:" << _manaCost << " 冷却:" << _cooldown
            << " 当前冷却:" << _currentCD << endl;
    }
};

// 角色基类
class Character {
protected:
    string name;        // 角色名
    string job;         // 职业
    int level;          // 等级
    int maxHP;          // 最大生命
    int currentHP;      // 当前生命
    int maxMP;          // 最大魔法
    int currentMP;      // 当前魔法
    int attack;         // 攻击力
    int defense;        // 防御力
    int magicAttack;    // 魔法攻击
    int magicDefense;   // 魔法防御
    double critChance;  // 暴击率
    State state;        // 当前状态
    int stateTimer;     // 状态计时器

    // 技能列表
    vector<Skill*> skills;

    // 战斗统计
    int totalDamage;
    int damageTaken;
    int kills;

public:
    Character(string n, string j, int lvl = 1)
        : name(n), job(j), level(lvl), maxHP(100), currentHP(100), maxMP(50), currentMP(50),
        attack(10), defense(5), magicAttack(10), magicDefense(5), critChance(0.05),
        state(NORMAL), stateTimer(0), totalDamage(0), damageTaken(0), kills(0) {
    }

    virtual ~Character() {
        for (auto skill : skills) {
            delete skill;
        }
        skills.clear();
    }

    // 虚函数 - 不同职业有不同的初始化
    virtual void init() = 0;

    // 虚函数 - 不同职业有不同行动
    virtual void action(Character* target) = 0;

    // 虚函数 - 升级
    virtual void levelUp() = 0;

    // 通用方法
    bool isAlive() { return currentHP > 0; }
    bool hasMana(int cost) { return currentMP >= cost; }

    // 受到伤害
    void takeDamage(int dmg) {
        if (!isAlive()) return;

        int actual = dmg - defense;
        if (actual < 1) actual = 1;

        currentHP -= actual;
        damageTaken += actual;

        if (currentHP < 0) currentHP = 0;
        if (currentHP == 0) state = DEAD;

        cout << name << " 受到 " << actual << " 点伤害，剩余HP: " << currentHP << "/" << maxHP << endl;

        // 受到大量伤害可能进入受伤状态
        if (isAlive() && actual > maxHP * 0.25) {
            if (rand() % 100 < 30) {  // 30%概率受伤
                setState(INJURED, 2);
            }
        }
    }

    // 治疗
    void heal(int amount) {
        if (!isAlive()) return;

        currentHP += amount;
        if (currentHP > maxHP) currentHP = maxHP;
        cout << name << " 恢复 " << amount << " 点HP，当前HP: " << currentHP << "/" << maxHP << endl;
    }

    // 恢复魔法
    void restoreMP(int amount) {
        if (!isAlive()) return;

        currentMP += amount;
        if (currentMP > maxMP) currentMP = maxMP;
    }

    // 普通攻击
    void basicAttack(Character* target) {
        if (!isAlive() || !target->isAlive()) return;

        // 眩晕状态无法行动
        if (state == STUNNED) {
            cout << name << " 被眩晕，无法行动！" << endl;
            return;
        }

        int dmg = attack;

        // 状态影响
        if (state == INJURED) dmg = dmg * 0.7;
        if (state == ENHANCED) dmg = dmg * 1.3;

        // 暴击判断
        if ((rand() % 100) < critChance * 100) {
            dmg = dmg * 1.5;
            cout << name << " 发动暴击！" << endl;
        }

        target->takeDamage(dmg);
        totalDamage += dmg;

        // 如果目标死亡
        if (!target->isAlive()) {
            kills++;
        }
    }

    // 使用技能
    bool useSkill(int index, Character* target) {
        if (!isAlive() || !target->isAlive()) return false;

        // 眩晕状态无法行动
        if (state == STUNNED) {
            cout << name << " 被眩晕，无法行动！" << endl;
            return false;
        }

        // 检查技能是否存在
        if (index < 0 || index >= skills.size()) {
            cout << "技能不存在！" << endl;
            return false;
        }

        Skill* skill = skills[index];

        // 检查技能是否可用
        if (skill->getCurrentCD() > 0) {
            cout << skill->getName() << " 冷却中，剩余" << skill->getCurrentCD() << "回合" << endl;
            return false;
        }

        // 检查魔法值
        if (!hasMana(skill->getManaCost())) {
            cout << "魔法值不足，无法使用 " << skill->getName() << endl;
            return false;
        }

        // 使用技能
        currentMP -= skill->getManaCost();

        // 技能效果
        int dmg = skill->getDamage();
        if (state == INJURED) dmg = dmg * 0.7;
        if (state == ENHANCED) dmg = dmg * 1.3;

        target->takeDamage(dmg);
        totalDamage += dmg;

        cout << name << " 使用 " << skill->getName() << " 对 " << target->getName()
            << " 造成 " << dmg << " 点伤害！" << endl;

        // 设置冷却
        skill->resetCD();

        // 如果目标死亡
        if (!target->isAlive()) {
            kills++;
        }

        return true;
    }

    // 每回合更新
    void update() {
        if (!isAlive()) return;

        // 更新状态
        if (stateTimer > 0) {
            stateTimer--;
            if (stateTimer == 0 && state != DEAD) {
                state = NORMAL;
                cout << name << " 状态恢复正常" << endl;
            }
        }

        // 自动恢复
        if (state != DEAD) {
            currentHP += maxHP * 0.02;
            if (currentHP > maxHP) currentHP = maxHP;

            currentMP += maxMP * 0.05;
            if (currentMP > maxMP) currentMP = maxMP;
        }

        // 减少技能冷却
        for (auto skill : skills) {
            skill->reduceCD();
        }
    }

    // 设置状态
    void setState(State s, int duration = 1) {
        state = s;
        stateTimer = duration;

        cout << name << " 进入";
        switch (s) {
        case NORMAL: cout << "正常"; break;
        case INJURED: cout << "受伤"; break;
        case STUNNED: cout << "眩晕"; break;
        case ENHANCED: cout << "强化"; break;
        case DEAD: cout << "死亡"; break;
        }
        cout << "状态，持续" << duration << "回合" << endl;
    }

    // 添加技能
    void addSkill(Skill* skill) {
        if (skills.size() < 4) {
            skills.push_back(skill);
        }
        else {
            cout << "技能栏已满！" << endl;
        }
    }

    // 显示技能
    void showSkills() {
        cout << name << " 的技能：" << endl;
        for (int i = 0; i < skills.size(); i++) {
            cout << i << ". ";
            skills[i]->display();
        }
    }

    // 显示角色信息
    void showInfo() {
        cout << "===== " << name << " [" << job << "] =====" << endl;
        cout << "等级: " << level << " HP: " << currentHP << "/" << maxHP
            << " MP: " << currentMP << "/" << maxMP << endl;
        cout << "攻击: " << attack << " 防御: " << defense
            << " 魔攻: " << magicAttack << " 魔防: " << magicDefense << endl;
        cout << "状态: ";
        switch (state) {
        case NORMAL: cout << "正常"; break;
        case INJURED: cout << "受伤"; break;
        case STUNNED: cout << "眩晕"; break;
        case ENHANCED: cout << "强化"; break;
        case DEAD: cout << "死亡"; break;
        }
        cout << " 暴击率: " << critChance * 100 << "%" << endl;
    }

    // 显示战斗统计
    void showStats() {
        cout << "===== " << name << " 战斗统计 =====" << endl;
        cout << "造成伤害: " << totalDamage << endl;
        cout << "承受伤害: " << damageTaken << endl;
        cout << "击杀数: " << kills << endl;
    }

    // 获取属性
    string getName() { return name; }
    string getJob() { return job; }
    int getHP() { return currentHP; }
    int getMaxHP() { return maxHP; }
    int getMP() { return currentMP; }
    int getAttack() { return attack; }
    int getDefense() { return defense; }
    State getState() { return state; }
    int getSkillCount() { return skills.size(); }

    // 设置属性
    void setAttack(int a) { attack = a; }
    void setDefense(int d) { defense = d; }
    void setMagicAttack(int ma) { magicAttack = ma; }
};

// 战士类
class Warrior : public Character {
private:
    int rage;  // 怒气值

public:
    Warrior(string n, int lvl = 1) : Character(n, "战士", lvl), rage(0) {
        init();
    }

    void init() override {
        // 战士属性
        maxHP = 150 + level * 15;
        currentHP = maxHP;
        maxMP = 30 + level * 3;
        currentMP = maxMP;
        attack = 15 + level * 2;
        defense = 10 + level * 1;
        magicAttack = 5 + level * 1;
        magicDefense = 5 + level * 0.5;
        critChance = 0.08;

        // 战士技能
        addSkill(new Skill("重击", "强力物理攻击", 25, 10, 2));
        addSkill(new Skill("防御姿态", "提升防御力", 0, 15, 3));
        addSkill(new Skill("旋风斩", "攻击所有敌人", 15, 20, 4));
        addSkill(new Skill("斩杀", "对低血量敌人造成大量伤害", 40, 25, 5));
    }

    void action(Character* target) override {
        // 战士行动逻辑
        if (!isAlive()) return;

        // 优先使用斩杀技能
        if (target->getHP() < target->getMaxHP() * 0.3) {
            if (useSkill(3, target)) return;
        }

        // 如果自身血量低，使用防御
        if (getHP() < getMaxHP() * 0.4) {
            if (useSkill(1, this)) {  // 对自己使用防御技能
                setDefense(getDefense() + 5);
                cout << name << " 防御力提升至 " << getDefense() << endl;
                return;
            }
        }

        // 否则使用普通攻击
        basicAttack(target);

        // 攻击后增加怒气
        rage += 10;
        if (rage > 100) rage = 100;
        cout << name << " 怒气值: " << rage << "/100" << endl;

        // 怒气满了可以释放特殊技能
        if (rage >= 50) {
            rage -= 50;
            cout << name << " 消耗50怒气发动狂暴！攻击力提升！" << endl;
            setAttack(getAttack() + 5);
        }
    }

    void levelUp() override {
        level++;
        maxHP += 15;
        currentHP += 15;
        maxMP += 3;
        currentMP += 3;
        attack += 2;
        defense += 1;
        cout << name << " 升级到 " << level << " 级！" << endl;
        showInfo();
    }

    int getRage() { return rage; }
};

// 法师类
class Mage : public Character {
private:
    int arcanePower;  // 奥术能量

public:
    Mage(string n, int lvl = 1) : Character(n, "法师", lvl), arcanePower(0) {
        init();
    }

    void init() override {
        // 法师属性
        maxHP = 80 + level * 8;
        currentHP = maxHP;
        maxMP = 100 + level * 15;
        currentMP = maxMP;
        attack = 5 + level * 1;
        defense = 3 + level * 0.5;
        magicAttack = 20 + level * 3;
        magicDefense = 15 + level * 2;
        critChance = 0.1;

        // 法师技能
        addSkill(new Skill("火球术", "基础魔法攻击", 20, 15, 1));
        addSkill(new Skill("寒冰箭", "造成伤害并降低目标速度", 15, 12, 2));
        addSkill(new Skill("治疗术", "恢复生命值", 25, 20, 3));
        addSkill(new Skill("奥术冲击", "强力魔法攻击", 40, 30, 4));
    }

    void action(Character* target) override {
        // 法师行动逻辑
        if (!isAlive()) return;

        // 如果自身血量低，使用治疗
        if (getHP() < getMaxHP() * 0.5) {
            if (useSkill(2, this)) {
                heal(30);  // 额外治疗效果
                return;
            }
        }

        // 如果魔法值充足，使用奥术冲击
        if (getMP() > 50 && arcanePower >= 30) {
            if (useSkill(3, target)) {
                arcanePower -= 30;
                return;
            }
        }

        // 否则使用火球术
        if (useSkill(0, target)) {
            // 使用魔法增加奥术能量
            arcanePower += 15;
            if (arcanePower > 100) arcanePower = 100;
            cout << name << " 奥术能量: " << arcanePower << "/100" << endl;
            return;
        }

        // 如果所有技能都不可用，普通攻击
        basicAttack(target);
    }

    void levelUp() override {
        level++;
        maxHP += 8;
        currentHP += 8;
        maxMP += 15;
        currentMP += 15;
        magicAttack += 3;
        magicDefense += 2;
        cout << name << " 升级到 " << level << " 级！" << endl;
        showInfo();
    }

    int getArcanePower() { return arcanePower; }
};

//// 主函数
//int main() {
//    srand(time(0));  // 随机种子
//
//    cout << "========== 游戏角色能力系统 ==========" << endl;
//    cout << "基于面向对象思想设计的游戏角色系统" << endl;
//    cout << "包含封装、继承、多态等特性" << endl;
//    cout << "======================================" << endl;
//
//
//
//    cout << "\n========== 系统特性总结 ==========" << endl;
//    cout << "1. 封装：所有角色属性封装在类内部" << endl;
//    cout << "2. 继承：Warrior和Mage继承自Character" << endl;
//    cout << "3. 多态：通过虚函数实现不同职业的行为差异" << endl;
//    cout << "4. 游戏设计：包含状态管理、技能冷却、职业平衡等" << endl;
//    cout << "======================================" << endl;
//
//    return 0;
//}