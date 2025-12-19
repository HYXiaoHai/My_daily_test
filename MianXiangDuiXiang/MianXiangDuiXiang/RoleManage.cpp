#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>
#include<map>
#include<string>
using namespace std;

//状态
enum State
{
	NORMAL,//正常
	STUNNED,//眩晕
	ENHANCED,//增强
	DEAD//死亡
};

//技能类
class Skill
{
private:
	string _name;
	string _Introduct;//技能介绍
	int _damage;//伤害
	int _manaCost;//能量消耗
	int _cooldown;// 冷却时间
	int _currentCD;//当前冷却时间[0 ,cooldown]
	State _effectState;//技能附加的状态效果
	int _effectDuration;//状态持续时间

public:
	Skill(string name, string Intro, int damage, int manaCost, int cooldown,
		State effectState = NORMAL, int effectDuration = 0)
		:_name(name), _Introduct(Intro), _damage(damage), _manaCost(manaCost),
		_cooldown(cooldown), _currentCD(0), _effectState(effectState),
		_effectDuration(effectDuration)
	{ }

	//获取信息
	string getName()const{
		return _name;
	}
	string getIntroduct()const{
		return _Introduct;
	}
	int getDamage()const{
		return _damage;
	}
	int getManaCost()const{
		return _manaCost;
	}
	int getCooldown()const{
		return _cooldown;
	}
	int getCurrentCD()const{
		return _currentCD;
	}
	State getEffectState()const{
		return _effectState;
	}
	int getEffectDuration()const{
		return _effectDuration;
	}

	//设置冷却时间
	void setCurrentCD(int cd){
		_currentCD = cd;
	}
	//减少冷却
	void reduceCD(){
		if (_currentCD > 0)
			_currentCD--;
	}
	//重置冷却
	void resetCD(){
		_currentCD = _cooldown;
	}
	//显示技能信息
	void showSkill()
	{
		cout << "[" << _name << "] " << _Introduct << endl;
		cout << "  伤害:" << _damage << " 能量消耗:" << _manaCost<< " 冷却:" << _cooldown << " 当前冷却:" << _currentCD;

		if (_effectState != NORMAL)
		{
			cout << endl << "  附加效果:";
			switch (_effectState)
			{
			case STUNNED: cout << "眩晕"; break;
			case ENHANCED: cout << "强化"; break;
			default: break;
			}
			cout << "持续时间:" << _effectDuration << "回合" << endl;
		}
		cout << endl;
	}
};

//角色基础类
class character
{
public:
	string _name;
	string _job;//职业
	int _level;//等级
	int _maxHP;//最大生命
	int _currentHP;//当前生命
	int _maxMP;//最大能量
	int _currentMP;//当前能量
	int _defense;//防御力
	int _attack;//攻击力
	State _state;//当前状态
	int _stateTimer;//状态需要的回合

	//技能列表
	vector<Skill*> _skills;
	map<string, int>_skillsindex;

	character(string name, string job, int level = 1)
		:_name(name), _job(job), _level(level)
		, _maxHP(80), _currentHP(80)
		, _maxMP(100), _currentMP(100)
		, _defense(0), _attack(0)
		, _state(NORMAL), _stateTimer(0)
	{
	}

	virtual ~character()
	{
		//清理技能
		for (auto skill : _skills)
		{
			delete skill;
		}
		_skills.clear();
		_skillsindex.clear();
	}

	//初始化
	virtual void init() = 0;

	//升级
	virtual void levelUP() = 0;

	//是否活着
	bool isAlive(){
		return _currentHP > 0;
	}

	//是否有能量
	bool hasMana(int cost){
		return _currentMP >= cost;
	}

	//受到伤害
	void takeDamage(int dmg){
		if (!isAlive())
		{
			cout << _name << " 已经死亡" << endl;
			return;
		}
		int Dmg = dmg - _defense;
		if (_state == ENHANCED) Dmg -= 1;//增强状态减少1点伤害
		if (Dmg < 1) Dmg = 1;
		_currentHP -= Dmg;
		if (_currentHP <= 0)
		{
			_state = DEAD;
			_currentHP = 0;
			cout << _name << " 已死亡！" << endl;
		}
		else
		{
			cout << _name << " 受到 " << Dmg << " 点伤害，当前生命值：" << _currentHP << "/" << _maxHP << endl;
		}
	}

	//是否可以行动 死亡+眩晕
	bool canActive(){
		if (!isAlive())
		{
			cout << _name << " 已死亡" << endl;
			return false;
		}

		//眩晕状态无法行动
		if (_state == STUNNED)
		{
			cout << _name << " 处于眩晕状态，无法行动！" << endl;
			return false;
		}
		return true;
	}

	//治疗
	void heal(int amount){
		if (!canActive())
			return;
		_currentHP += amount;
		if (_currentHP > _maxHP) _currentHP = _maxHP;
		cout << _name << " 恢复 " << amount << " 点HP，当前HP: " << _currentHP << "/" << _maxHP << endl;
	}

	//普通攻击
	bool basicAttack(character& target){
		if (!canActive())
			return false;
		if (!target.isAlive())
		{
			cout << target._name << " 目标已死亡" << endl;
			return false;
		}

		int dmg = _attack;
		if (_state == ENHANCED) dmg += 1;

		cout << _name << " 对 " << target._name << " 进行普通攻击！" << endl;
		target.takeDamage(dmg);
		return true;
	}

	int IndexSkill(string name){
		if (_skillsindex.find(name) == _skillsindex.end())
		{
			return -1;//没找到
		}
		else
			return _skillsindex[name];
	}
	//使用技能
	bool useSkill(character& target, int index) //index搜索
	{
		if (!target.isAlive()){
			cout << target._name << " 目标已死亡" << endl;
			return false;
		}
		if (!canActive())
			return false;

		if (index < 0 || index >= (int)_skills.size()){
			cout << "无效技能索引" << endl;
			return false;
		}

		Skill* skill = _skills[index];

		if (skill->getCurrentCD() > 0){
			cout << skill->getName() << " 技能正在冷却中：" << skill->getCurrentCD() << "/" << skill->getCooldown() << "回合" << endl;
			return false;
		}

		if (_currentMP < skill->getManaCost()){
			cout << _name << " 能量不够，需要 " << skill->getManaCost() << " 当前 " << _currentMP << endl;
			return false;
		}

		//使用技能
		int dmg = skill->getDamage();
		_currentMP -= skill->getManaCost();
		skill->resetCD();//使用后重置冷却

		if (_state == ENHANCED) dmg += 1;

		cout << _name << " 使用 " << skill->getName() << " 攻击 " << target._name << endl;
		target.takeDamage(dmg);

		return true;
	}

	bool useSkill(character& target, string name)//名字搜索
	{
		int index = IndexSkill(name);
		if (index == -1){
			cout << _name << " 没有技能：" << name << endl;
			return false;
		}
		return useSkill(target, index);
	}


	//使用防御技能
	bool useDefenseSkill(int index){
		if (!canActive())
			return false;

		if (index < 0 || index >= (int)_skills.size()){
			cout << "无效技能索引" << endl;
			return false;
		}

		Skill* skill = _skills[index];

		if (skill->getCurrentCD() > 0){
			cout << skill->getName() << " 技能正在冷却中：" << skill->getCurrentCD() << "/" << skill->getCooldown() << "回合" << endl;
			return false;
		}

		if (_currentMP < skill->getManaCost()){
			cout << _name << " 能量不够，需要 " << skill->getManaCost() << " 当前 " << _currentMP << endl;
			return false;
		}

		//使用技能
		_currentMP -= skill->getManaCost();
		skill->resetCD();//重置冷却

		//增加防御力并恢复生命
		_defense += 5;
		heal(10);
		cout << _name << " 使用 " << skill->getName() << "，防御力提升至 " << _defense << endl;
		return true;
	}

	//使用眩晕技能
	bool useStunSkill(character& target, int index)
	{
		if (!target.isAlive()){
			cout << target._name << " 目标已死亡" << endl;
			return false;
		}

		if (!canActive())
			return false;

		if (index < 0 || index >= (int)_skills.size()){
			cout << "无效技能索引" << endl;
			return false;
		}

		Skill* skill = _skills[index];

		if (skill->getCurrentCD() > 0){
			cout << skill->getName() << " 技能正在冷却中：" << skill->getCurrentCD() << "/" << skill->getCooldown() << "回合" << endl;
			return false;
		}

		if (_currentMP < skill->getManaCost()){
			cout << _name << " 能量不够，需要 " << skill->getManaCost() << " 当前 " << _currentMP << endl;
			return false;
		}

		//使用技能
		int dmg = skill->getDamage();
		_currentMP -= skill->getManaCost();
		skill->resetCD();

		if (_state == ENHANCED) dmg += 1;

		cout << _name << " 使用 " << skill->getName() << " 攻击 " << target._name << endl;
		target.takeDamage(dmg);

		if (skill->getEffectState() == STUNNED){
			target.setState(STUNNED, skill->getEffectDuration());
		}

		return true;
	}

	//设置状态
	void setState(State s, int duration = 1)
	{
		if (!isAlive() && s != DEAD){
			cout << _name << " 已死亡，无法改变状态" << endl;
			return;
		}

		_state = s;
		_stateTimer = duration;
		cout << _name << " 进入";
		switch (s) {
		case NORMAL: cout << "正常"; break;
		case STUNNED: cout << "眩晕"; break;
		case ENHANCED: cout << "强化"; break;
		case DEAD: cout << "死亡"; break;
		}
		cout << "状态，持续" << duration << "回合" << endl;
	}

	//设置防御力
	void setDefense(int defense){
		_defense = defense;
	}

	//设置攻击力
	void setAttack(int attack){
		_attack = attack;
	}

	//添加技能
	void addSkill(Skill* skill){
		if (_skills.size() < 4) {
			_skills.push_back(skill);
			_skillsindex[skill->getName()] = _skills.size() - 1;
		}
		else {
			cout << "技能栏已满！" << endl;
			delete skill;
		}
	}

	//显示技能
	void showskill(){
		cout << _name << " 技能表：" << endl;
		for (size_t i = 0; i < _skills.size(); ++i){
			cout << i << ". ";
			_skills[i]->showSkill();
		}
		cout << _skills.size() << ". 普通攻击" << endl;
		cout << _skills.size() + 1 << ". 跳过本回合" << endl;
		cout << "-------------" << endl;
	}

	//角色信息
	void showCharater()
	{
		cout << "======== " << _name << " [" << _job << "] ========" << endl;
		cout << "等级: " << _level << endl;
		cout << "血量: " << _currentHP << "/" << _maxHP << endl;
		cout << "能量: " << _currentMP << "/" << _maxMP << endl;
		cout << "攻击: " << _attack << " 防御: " << _defense << endl;
		cout << "状态: " << getStateString() << " 持续 " << _stateTimer << " 回合" << endl;
		cout << "==========================" << endl;
	}

	//每回合更新
	void update() {
		if (!isAlive()) return;

		//更新状态
		if (_stateTimer > 0) {
			_stateTimer--;
			if (_stateTimer == 0 && _state != DEAD) {
				_state = NORMAL;
				cout << _name << " 状态恢复正常" << endl;
			}
		}

		//自动恢复
		if (_state != DEAD) {
			_currentHP += (int)(_maxHP * 0.02);
			if (_currentHP > _maxHP) _currentHP = _maxHP;

			_currentMP += (int)(_maxMP * 0.05);
			if (_currentMP > _maxMP) _currentMP = _maxMP;
		}

		//减少技能冷却
		for (auto skill : _skills) {
			skill->reduceCD();
		}
	}
	//获取属性
	string getName()const{
		return _name;
	}
	string getJob()const{
		return _job;
	}
	int getHP()const{
		return _currentHP;
	}
	int getMaxHP()const{
		return _maxHP;
	}
	int getMP()const{
		return _currentMP;
	}
	int getMaxMP()const{
		return _maxMP;
	}
	int getAttack()const{
		return _attack;
	}
	int getDefense()const{
		return _defense;
	}
	State getState()const{
		return _state;
	}
	string getStateString()const{
		switch (_state){
		case NORMAL: return "正常";
		case STUNNED: return "眩晕";
		case ENHANCED: return "强化";
		case DEAD: return "死亡";
		default: return "状态出错";
		}
	}
	int getSkillCount()const{
		return _skills.size();
	}
};
//战士
class Warrior :public character
{
public:
	Warrior(string name, int level = 1)
		:character(name, "战士", level)
	{
		init();
	}
	void init() override{
		_maxHP = 80 + _level * 15;
		_currentHP = _maxHP;
		_maxMP = 80 + _level * 3;
		_currentMP = _maxMP;
		_attack = 15 + _level * 2;
		_defense = 10 + _level * 1;

		//战士技能
		addSkill(new Skill("重击", "强力物理攻击", 30, 15, 2));
		addSkill(new Skill("防御姿态", "提升防御力并恢复生命", 0, 10, 3));
		addSkill(new Skill("斩杀", "对低血量敌人造成大量伤害", 50, 25, 5));
		addSkill(new Skill("震荡", "造成伤害并有概率使目标眩晕", 20, 20, 4, STUNNED, 1)); 
	}
	//升级
	void levelUP() override{
		_level++;
		_maxHP += 15;
		_currentHP = _maxHP; 
		_maxMP += 3;
		_currentMP = _maxMP;
		_attack += 2;
		_defense += 1;
		cout << _name << " 升级到 " << _level << " 级！" << endl;
		showCharater();
	}
};

void test()
{
	cout << "===== 游戏角色能力系统测试 =====" << endl << endl;

	Warrior warrior1("亚瑟", 1);
	Warrior warrior2("莱恩", 1);

	cout << "=== 初始角色信息 ===" << endl;
	warrior1.showCharater();
	cout << endl;
	warrior2.showCharater();
	cout << endl;

	cout << "=== 角色技能 ===" << endl;
	cout << warrior1.getName() << "的技能：" << endl;
	warrior1.showskill();
	cout << endl;
	cout << warrior2.getName() << "的技能：" << endl;
	warrior2.showskill();
	cout << endl;

	cout << "===== 战斗开始 =====" << endl << endl;

	int round = 1;
	bool warrior1Turn = true; // true: warrior1, false: warrior2回合
	while (warrior1.isAlive() && warrior2.isAlive()){
		cout << "==================== 第 " << round << " 回合 ====================" << endl;

		cout << "当前状态:" << endl;
		warrior1.showCharater();
		warrior2.showCharater();
		cout << endl;

		//确定当前行动的角色
		character* current = warrior1Turn ? &warrior1 : &warrior2;
		character* next = warrior1Turn ? &warrior2 : &warrior1;
		bool warrior1Stuflag = true;//记录是否需要处理第一个角色逃避眩晕的bug
		if (current->isAlive()){
			cout << ">>> " << current->getName() << " 的回合 <<<" << endl;
			cout << "请选择行动：" << endl;
			current->showskill();

			int choice;
			bool Action = false;
			while (!Action){
				cout << "请输入选择 (0-" << current->getSkillCount() + 1 << "): ";
				cin >> choice;

				if (choice >= 0 && choice < current->getSkillCount()){
					//使用技能
					if (choice == 1) //防御技能
					{
						Action = current->useDefenseSkill(choice);
					}
					else if (choice == 3) //眩晕技能
					{
						Action = current->useStunSkill(*next, choice);
						if (warrior1Turn == false)//记录是否需要处理第一个角色逃避眩晕的bug
							warrior1Stuflag = false;
					}
					//攻击技能
					else{
						Action = current->useSkill(*next, choice);
					}
				}
				else if (choice == current->getSkillCount())
				{
					//普通攻击
					Action = current->basicAttack(*next);
				}
				else if (choice == current->getSkillCount() + 1)
				{
					//跳过本回合
					cout << current->getName() << " 跳过本回合" << endl;
					Action = true;
				}
				else
				{
					cout << "无效选择，请重新输入！" << endl;
				}
			}
			cout << endl;
		}
		//切换角色
		warrior1Turn = !warrior1Turn;
		//检查是否有一方死亡
		if (!warrior1.isAlive() || !warrior2.isAlive())
		{
			break;
		}
		//debug:处理第一个角色逃避眩晕的bug
		if (warrior1Turn&&warrior1.getState()== STUNNED&&(!warrior1Stuflag))
		{
			warrior1Stuflag = true;
			warrior1._stateTimer++;
		}
		//如果双方都存活，更新状态
		if (warrior1Turn)
		{
			warrior1.update();
			warrior2.update();
			round++;
		}

		//每2回合暂停一下，让用户看清楚
		if (round % 2 == 0)
		{
			cout << "按回车继续...";
			cin.ignore();
			cin.get();
			cout << endl;
		}
	}

	cout << "=============== 战斗结束 ===============" << endl;
	if (warrior1.isAlive())
	{
		cout << warrior1.getName() << " 胜利！" << endl;
		warrior1.levelUP(); //胜利者升级
	}
	else if (warrior2.isAlive())
	{
		cout << warrior2.getName() << " 胜利！" << endl;
		warrior2.levelUP();
	}

	cout << "===== 最终状态 =====" << endl;
	warrior1.showCharater();
	warrior2.showCharater();

	cout << "===== 测试完成 =====" << endl;
}

// 主函数
int main()
{
	test();
	cin.ignore();
	cin.get();
	return 0;
}

