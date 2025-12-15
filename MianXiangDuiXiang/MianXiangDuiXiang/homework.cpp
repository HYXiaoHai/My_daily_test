#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>
#include<map>
using namespace std;

enum State
{
	NORMAL,//正常
	STUNNED,//眩晕
	ENHANCED,//增强
	DEAD//死亡
};

class Skill 
{
private:
	string _name;
	string _Introduct;//技能介绍
	int _damage;
	int _manaCost;//蓝耗
	int _cooldown;// 冷却时间
	int _currentCD;//当前冷却时间[0 ,cooldown]
public:
	Skill(string name, string Intro, int damage, int manaCost, int cooldown)
		:_name(name), _Introduct(Intro), _damage(damage), _manaCost(manaCost), _cooldown(cooldown), _currentCD(cooldown)
	{
	}

	//获取信息
	string getName()const
	{
		return _name;
	}
	string getIntroduct()const
	{
		return _Introduct;
	}
	int getDamage()const
	{
		return _damage;
	}
	int getManaCost()const
	{
		return _manaCost;
	}
	int getCooldown()const
	{
		return _cooldown;
	}
	int getCurrentCD()const
	{
		return _currentCD;
	}

	// 设置冷却时间
	void setCurrentCD(int cd)
	{
		_currentCD = cd;
	}

	// 减少冷却
	void reduceCD()
	{
		if (_currentCD < _cooldown)
			_currentCD++;
	}

	// 重置冷却
	void resetCD()
	{
		_currentCD = 0;
	}

	//显示技能信息
	void showSkill()
	{
		cout << "----技能：" << _name << "----" << endl;
		cout << "伤害：" << _damage;
		cout << "蓝耗：" << _manaCost;
		cout << "冷却时间：" << _cooldown;
		cout << "当前冷却：" << _currentCD;
	}
};

class character
{

	string _name;
	string _job;         // 职业
	int _level;          // 等级
	int _maxHP;          // 最大生命
	int _currentHP;      // 当前生命
	int _maxMP;          // 最大蓝
	int _currentMP;      // 当前蓝
	int _defense;		//防御力
	int _attack;         // 攻击力
	State _state;        // 当前状态
	int _stateTimer;     // 状态计时器

	// 技能列表
	vector<Skill*> _skills;
	map<string, int>_skillsindex;
	character(string name, string job, int level = 1)
		:_name(name), _job(job), _level(level)
		, _maxHP(100), _currentHP(100)
		, _maxMP(100), _currentMP(100)
		,_defense(0), _attack(0)
		, _state(NORMAL), _stateTimer(0)
	{
	}

	// 虚函数 - 不同职业有不同的初始化
	virtual void init() = 0;

	// 虚函数 - 不同职业有不同行动
	virtual void action(character* target) = 0;

	//升级
	virtual void levelUP() = 0;

	//是否活着
	bool isAlive() 
	{
		return _currentHP > 0;
	}
	//是否有蓝
	bool hasMana(int cost)
	{
		return _currentMP >= cost;
	}
	// 受到伤害
	void takeDamage(int dmg)
	{
		if (!isAlive())
		{
			cout << "已经死亡" << endl;
			return;
		}
		int Dmg = dmg - _defense;
		if (_state == ENHANCED)dmg -= 1;
		if (Dmg < 1)Dmg = 1;
		_currentHP -= Dmg;
		if (_currentHP <= 0)
		{
			_state = DEAD;
			_currentHP = 0;
		}
		cout << _name << "收到伤害：" << Dmg << " 当前生命值：" << _currentHP << "/" << _maxHP << endl;;
	}

	// 治疗
	void heal(int amount)
	{
		if (!isAlive())
		{
			cout << "角色已死亡，无法治疗" << endl;
			return;
		}
		_currentHP += amount;
		if (_currentHP > _maxHP)_currentHP = _maxHP;
		cout << _name << " 恢复 " << amount << " 点HP，当前HP: " << _currentHP << "/" << _maxHP << endl;
	}

	// 普通攻击
	void basicAttack(character& target)
	{
		if (!isAlive())
		{
			cout << "您已死亡无法攻击" << endl;
			return;
		}
		if (!target.isAlive())
		{
			cout << "目标已死亡" << endl;
			return;
		}
		int dmg = _attack;

		if (_state == ENHANCED)dmg += 1;

		target.takeDamage(dmg);
	}
	int IndexSkill(string name)
	{
		if (_skillsindex.find(name) == _skillsindex.end())
		{
			cout << "没有该技能" << endl;
			return _skills.size()+1;
		}
		else
		return _skillsindex[name];
	}
	// 使用技能
	bool useSkill(character&target,int index)//index搜索
	{
		if (!target.isAlive())
		{
			cout << "目标已死亡" << endl;
			return false;
		}
		if (!isAlive())
		{
			cout << "您已死亡" << endl;
			return false;
		}
		if (index > _skills.size())
		{
			cout << "无效技能" << endl;
			return false;
		}
		if (_skills[index]->getCurrentCD() < _skills[index]->getCooldown())
		{
			cout << "技能正在冷却中：" << _skills[index]->getCurrentCD() << "s/"<< _skills[index]->getCooldown()<<"s" << endl;
			return false;
		}
		if (_currentMP < _skills[index]->getManaCost())
		{
			cout << "您的能量不够" << endl;
			return false;
		}
		//使用技能
		int dmg = _skills[index]->getDamage();
		_currentMP -= _skills[index]->getManaCost();
		_skills[index]->setCurrentCD(0);
		if (_state == ENHANCED)dmg += 1;
		target.takeDamage(dmg);
		return true;
	}
	bool useSkill(character&target,string name)//名字搜索
	{
		if (!target.isAlive())
		{
			cout << "目标已死亡" << endl;
			return false;
		}
		if (!isAlive())
		{
			cout << "您已死亡" << endl;
			return false;
		}
		useSkill(target,IndexSkill(name));
	}
	// 设置状态
	void setState(State s, int duration = 1)
	{
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
	// 添加技能
	void addSkill(Skill* skill)
	{
		if (_skills.size() < 4) {
			_skills.push_back(skill);
			_skillsindex[skill->getName()] = _skills.size() - 1;
		}
		else {
			cout << "技能栏已满！" << endl;
		}
	}
	// 显示技能
	void showskill()
	{
		cout << _name << "技能表：" << endl;
		for (auto e:_skills)
		{
			cout << e->getName() <<"["<< IndexSkill(e->getName()) <<"]" << endl;
		}
		cout << "-------------" << endl;
	}
	// 显示角色信息
	void showCharater()
	{
		cout << "-----角色信息-----" << endl;
		cout << "名字：" << _name << endl;
		cout << "职业：" << _job << endl;
		cout << "等级：" << _level << endl;
		cout << "血量：" << _currentHP <<"/"<<_maxHP<<endl;
		cout << "能量：" << _currentMP <<"/"<<_maxMP<<endl;
		cout << "攻击力:" << _attack << endl;
		cout << "当前状态:"<< getState(_state)<<"持续 "<< _stateTimer << " 回合" << endl;
		cout << "------------------" << endl;
	}
    // 每回合更新
	void update() {
		if (!isAlive()) return;

		// 更新状态
		if (_stateTimer > 0) {
			_stateTimer--;
			if (_stateTimer == 0 && _state != DEAD) {
				_state = NORMAL;
				cout << _name << " 状态恢复正常" << endl;
			}
		}

		// 自动恢复
		if (_state != DEAD) {
			_currentHP += _maxHP * 0.02;
			if (_currentHP > _maxHP) _currentHP = _maxHP;

			_currentMP += _maxMP * 0.05;
			if (_currentMP > _maxMP) _currentMP = _maxMP;
		}

		// 减少技能冷却
		for (auto skill : _skills) {
			skill->reduceCD();
		}
	}
	// 获取属性
	string getName()const
	{
		return _name;
	}
	string getJob()const
	{
		return _job;
	}
	int getHP()const
	{
		return _currentHP;
	}
	int getMaxHP()const
	{
		return _maxHP;
	}
	int getMP()const
	{
		return _currentMP;
	}
	int getAttack()const
	{
		return _attack;
	}
	State getState()const
	{
		return _state;
	}
	string getState(State st)const
	{
		switch (st)
		{
		case NORMAL: return "正常"; break;
		case STUNNED: return  "眩晕"; break;
		case ENHANCED: return  "强化"; break;
		case DEAD: return "死亡"; break;
		default:"状态出错"; break;
		}
	}
	int getSkillCount()const
	{
		return _skills.size();
	}
};

int test(int& b)
{
	b++;
	return b;
}

int main()
{
	int a = 1;
	int b = 2;
	cout<< test(b) <<b<< endl;
}