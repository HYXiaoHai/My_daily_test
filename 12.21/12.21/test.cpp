#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <vector>      
#include <stack>       
#include <map>        
#include <string>
#include <algorithm>   
using namespace std;

#define MAXLEVEL 100//最高级

//角色类别
enum Job
{
	战士,
	法师,
	刺客,
	辅助,
	射手
};

string JobToString(Job job) {
	switch (job) {
	case 战士: return "战士";
	case 法师: return "法师";
	case 刺客: return "刺客";
	case 辅助: return "辅助";
	case 射手: return "射手";
	default: return "战士";
	}
}

Job StringToJob(const string& jobStr) {
	if (jobStr == "战士") return 战士;
	if (jobStr == "法师") return 法师;
	if (jobStr == "刺客") return 刺客;
	if (jobStr == "辅助") return 辅助;
	if (jobStr == "射手") return 射手;
	return 战士; //默认
}

//角色类
class Role
{
private:
	string _name;
	string _id; //角色ID
	Job _job;   //职业
	int _level; //等级
	int _hp;    //当前生命值
	int _maxHp; //最大生命值
	int _attack;//攻击力
	int _defense;//防御力

	//初始化角色
	void Initrole(Job job)
	{
		_level = 1;
		switch (job)
		{
		case 战士:  //战士：高血量，平衡攻击防御
			_hp = 100; _maxHp = 100; _attack = 15; _defense = 10;
			break;
		case 法师:  //法师：低血量，高攻击，低防御
			_hp = 70; _maxHp = 70; _attack = 25; _defense = 5;
			break;
		case 射手:  //射手：中等属性
			_hp = 80; _maxHp = 80; _attack = 20; _defense = 6;
			break;
		case 刺客:  //刺客：中等属性，略有不同
			_hp = 80; _maxHp = 80; _attack = 20; _defense = 7;
			break;
		case 辅助:  //辅助：高血量，低攻击，高防御
			_hp = 90; _maxHp = 90; _attack = 10; _defense = 20;
			break;
		default:    //默认值
			_hp = 70; _maxHp = 70; _attack = 18; _defense = 7;
			break;
		}
	}

public:
	Role(string name, Job job, string id)
		: _name(name), _job(job), _id(id)
	{
		Initrole(job);
	}

	//用于恢复角色
	Role(string name, Job job, string id, int level, int hp, int attack, int defense)
		: _name(name), _job(job), _id(id), _level(level), _hp(hp),
		_attack(attack), _defense(defense)
	{
		_maxHp = _hp;
	}

	//显示角色信息
	void PrintRole() const
	{
		cout << "********* 角色信息 *********" << endl;
		cout << "角色ID: " << _id << endl;
		cout << "角色名: " << _name << endl;
		cout << "职业: " << JobToString(_job) << endl;
		cout << "等级: " << _level << endl;
		cout << "生命值: " << _hp << "/" << _maxHp << endl;
		cout << "攻击力: " << _attack << endl;
		cout << "防御力: " << _defense << endl;
		cout << "战斗力: " << calculatePower() << endl;
		cout << "****************************" << endl;
	}

	// 角色升级
	void levelUp()
	{
		if (_level >= MAXLEVEL)
		{
			cout << _name << " 已经是最高级!" << endl;
			return;
		}
		_level++;
		_maxHp += 20;
		_hp = _maxHp;//升级时恢复满血
		_attack += 5;
		_defense += 3;
		cout << _name << " 升级了！现在是 " << _level << " 级" << endl;
	}

	//计算战斗力
	int calculatePower() const
	{
		//攻击力*2+防御力+当前血量/10；
		return _attack * 2 + _defense + _hp / 10;
	}

	//设置角色状态
	void setState(int level, int hp, int attack, int defense)
	{
		_level = level;
		_hp = hp;
		_maxHp = hp;
		_attack = attack;
		_defense = defense;
	}

	//获得数据
	string getName() const { return _name; }
	string getId() const { return _id; }
	Job getJob() const { return _job; }
	int getLevel() const { return _level; }
	int getHp() const { return _hp; }
	int getMaxHp() const { return _maxHp; }
	int getAttack() const { return _attack; }
	int getDefense() const { return _defense; }
};

//角色存档类
class RoleArchive {
private:
	string _roleId; //角色ID
	string _roleName;//角色名
	Job _job;   //职业
	int _level; //等级
	int _hp;    //当前生命值
	int _attack;//攻击力
	int _defense;//防御力

public:
	RoleArchive(const Role& role)
		: _roleId(role.getId())
		, _roleName(role.getName())
		, _job(role.getJob())
		, _level(role.getLevel())
		, _hp(role.getHp())
		, _attack(role.getAttack())
		, _defense(role.getDefense())
	{
	}

	//显示存档信息
	void show() const {
		cout << "存档：" << _roleName << " [ID:" << _roleId
			<< " 职业:" << JobToString(_job) << " 等级:" << _level
			<< " 生命值:" << _hp << " 攻击:" << _attack << "]" << endl;
	}

	//获得存档数据
	string getId() const { return _roleId; }
	string getName() const { return _roleName; }
	Job getJob() const { return _job; }
	int getLevel() const { return _level; }
	int getHp() const { return _hp; }
	int getAttack() const { return _attack; }
	int getDefense() const { return _defense; }
};

// 角色管理系统类
class RoleManager
{
private:
	vector<Role> roleList;//保存角色

	map<string, int> nameToIndex;  //通过名字查找角色索引
	map<string, int> idToIndex;    //通过ID查找角色索引
	stack<RoleArchive> archiveStack;//保存角色存档
	//战斗力排序（降序）
	static bool CompareRolePower(const Role& r1, const Role& r2)
	{
		return r1.calculatePower() > r2.calculatePower();
	}

	//等级排序（降序）
	static bool CompareRoleLevel(const Role& r1, const Role& r2)
	{
		return r1.getLevel() > r2.getLevel();
	}

	//攻击力排序（降序）
	static bool CompareRoleAttack(const Role& r1, const Role& r2)
	{
		return r1.getAttack() > r2.getAttack();
	}
private:

public:
	//添加角色
	void Addrole(string name, Job job, string id)
	{
		//查找是否存在ID冲突
		if (idToIndex.find(id) != idToIndex.end())
		{
			cout << "错误：ID " << id << " 已存在，添加失败！" << endl;
			return;
		}

		//查找名字重复
		if (nameToIndex.find(name) != nameToIndex.end())
		{
			int tag = 0;
			cout << "警告：角色名 " << name << "重复 是否继续添加：" << endl;
			cout << "1.否     2.是" << endl;
			cin >> tag;
			switch (tag)
			{
			case 1:cout << "添加失败" << endl; return;
			case 2:cout << "继续添加：" << name << endl; break;
			default:cout << "添加失败" << endl; return;//默认不重名
			}
		}

		//添加角色到vector
		Role newrole(name, job, id);
		roleList.push_back(newrole);

		//更新两个map映射表
		int index = roleList.size() - 1;
		nameToIndex[name] = index;//建立名字到索引的映射
		idToIndex[id] = index;//建立ID到索引的映射

		cout << "添加角色成功：" << name << " (" << JobToString(job) << ") ID:" << id << endl;
	}

	//通过名字查找角色
	Role* FindroleByName(string name)
	{
		auto it = nameToIndex.find(name);
		if (it != nameToIndex.end()) {
			int index = it->second;//获取索引
			return &roleList[index];//返回vector中的角色指针
		}
		cout << "未找到角色：" << name << endl;
		return nullptr;
	}

	//通过ID查找角色
	Role* FindroleById(string id)
	{
		auto it = idToIndex.find(id);
		if (it != idToIndex.end()) {
			int index = it->second;//获取索引
			return &roleList[index];//返回vector中的角色指针
		}
		cout << "未找到ID为 " << id << " 的角色" << endl;
		return nullptr;
	}

	//删除角色
	void removeRole(string Str) {
		//查找角色是否存在
		auto itname = nameToIndex.find(Str);
		auto itID = idToIndex.find(Str);
		if (itname == nameToIndex.end() && itID == idToIndex.end()) {
			cout << "错误：找不到角色 " << Str << endl;
			return;
		}
		//找到了
		int index = -1;
		if (itname != nameToIndex.end())
		{
			index = itname->second;
		}
		if (itID != idToIndex.end())
		{
			index = itID->second;
		}
		Role& role = roleList[index];
		string id = role.getId();
		string name = role.getName();

		roleList.erase(roleList.begin() + index);

		//从map中删除对应的键值对
		nameToIndex.erase(name);
		idToIndex.erase(id);

		//更新map中其他角色的索引
		updateIndexMaps();
		cout << name << " 删除成功" << endl;
	}

	//角色升级
	void levelUpRole(string name)
	{
		Role* role = FindroleByName(name);
		if (role == nullptr) {
			return;
		}

		saveArchive(*role);//保存当前状态到栈
		role->levelUp();//执行升级操作
	}

	//保存角色存档到栈
	void saveArchive(const Role& role)
	{
		RoleArchive archive(role);
		archiveStack.push(archive);
		cout << "已保存存档：" << role.getName() << endl;
	}

	//从栈恢复角色状态
	void restoreRole(string name)
	{
		if (archiveStack.empty()) {
			cout << "错误：没有可恢复的存档" << endl;
			return;
		}

		Role* role = FindroleByName(name);
		if (role == nullptr) {
			return;
		}

		//从栈顶获取存档
		RoleArchive archive = archiveStack.top();
		archiveStack.pop();

		//检查存档是否匹配当前角色
		if (archive.getId() != role->getId()) {
			cout << "警告：存档不匹配当前角色，放回栈中" << endl;
			archiveStack.push(archive);
			return;
		}

		//恢复角色状态
		role->setState(archive.getLevel(), archive.getHp(),
			archive.getAttack(), archive.getDefense());

		cout << "恢复角色状态：" << name << endl;
		archive.show();
	}

	//按战斗力排序
	void SortByPower()
	{
		cout << "按战斗力排序角色..." << endl;
		sort(roleList.begin(), roleList.end(), CompareRolePower);
		updateIndexMaps();//更新索引映射
	}

	//按等级排序
	void SortByLevel()
	{
		cout << "按等级排序角色..." << endl;
		sort(roleList.begin(), roleList.end(), CompareRoleLevel);
		updateIndexMaps();//更新索引映射
	}

	//按攻击力排序
	void SortByAttack()
	{
		cout << "按攻击力排序角色..." << endl;
		sort(roleList.begin(), roleList.end(), CompareRoleAttack);
		updateIndexMaps();//更新索引映射
	}

	//更新索引映射
	void updateIndexMaps()
	{
		nameToIndex.clear();//清空旧数据
		idToIndex.clear();//清空旧数据

		//重新建立映射关系
		for (int i = 0; i < roleList.size(); i++) {
			nameToIndex[roleList[i].getName()] = i;//建立名字到索引的映射
			idToIndex[roleList[i].getId()] = i;//建立ID到索引的映射
		}
	}

	//获取角色数量
	int Rolecount() const
	{
		return roleList.size();
	}

	//显示所有角色
	void ShowAllRole() const
	{
		if (roleList.empty())
		{
			cout << "您没有角色！" << endl;
			return;
		}
		cout << "\n======== 角色列表（共" << roleList.size() << "个角色）========" << endl;
		for (const auto& role : roleList)
		{
			role.PrintRole();
		}
		cout << "==========================================" << endl;
	}
	//显示系统状态
	void showSystemStatus() const
	{
		cout << "\n========== 系统状态 ==========" << endl;
		cout << "角色数量：" << roleList.size() <<endl;
		cout << "存档数量：" << archiveStack.size() << endl;
		cout << "索引映射：" << nameToIndex.size() << "个名字索引" << endl;
		cout << "===============================" << endl;
	}
};
//测试辅助函数
namespace test_help
{
	void testadd()//角色添加
	{
		RoleManager manager;

		cout << "【测试1：添加角色】" << endl;
		cout << "添加5个不同职业的角色到vector中" << endl;
		manager.Addrole("张三", 战士, "1001");
		manager.Addrole("李四", 法师, "1002");
		manager.Addrole("王五", 射手, "1003");
		manager.Addrole("赵六", 刺客, "1004");
		manager.Addrole("小七", 辅助, "1005");

		cout << "\n测试重复ID" << endl;
		manager.Addrole("重复ID测试", 战士, "1001");
		cout << "\n测试重复名字" << endl;
		manager.Addrole("张三", 战士, "1006");

		manager.ShowAllRole();
		manager.showSystemStatus();
	}
	void testFind()//角色查找
	{
		RoleManager manager;
		manager.Addrole("张三", 战士, "1001");
		manager.Addrole("李四", 法师, "1002");
		manager.Addrole("王五", 射手, "1003");
		manager.Addrole("赵六", 刺客, "1004");
		manager.Addrole("小七", 辅助, "1005");

		cout << "\n【测试2：查找角色（map数据结构应用）】" << endl;
		cout << "1. 通过名字查找（使用nameToIndex map）:" << endl;
		Role* r1 = manager.FindroleByName("王五");
		if (r1 != nullptr) {
			cout << "找到角色王五：" << endl;
			r1->PrintRole();
		}

		cout << "\n2. 通过ID查找:" << endl;
		Role* r2 = manager.FindroleById("1002");
		if (r2 != nullptr) {
			cout << "通过ID找到角色：" << endl;
			r2->PrintRole();
		}

		cout << "\n3. 查找不存在的角色（错误处理）:" << endl;
		manager.FindroleByName("不存在的角色");
		manager.FindroleById("9999");
	}
	void testlevelup()//角色升级
	{
		RoleManager manager;
		manager.Addrole("张三", 战士, "1001");
		manager.Addrole("李四", 法师, "1002");
		manager.Addrole("王五", 射手, "1003");
		manager.Addrole("赵六", 刺客, "1004");
		manager.Addrole("小七", 辅助, "1005");

		cout << "\n【测试3：角色升级与存档（stack数据结构应用）】" << endl;
		cout << "角色升级前自动保存状态到stack中..." << endl;
		manager.levelUpRole("张三");
		manager.levelUpRole("李四");
		manager.levelUpRole("张三"); // 再次升级
		cout << "\n测试升级不存在角色：" << endl;
		manager.levelUpRole("不存在的角色"); // 测试错误情况

		cout << "\n升级后的角色列表：" << endl;
		manager.ShowAllRole();
		manager.showSystemStatus();
	}

	void testarchive()//角色备份
	{
		RoleManager manager;
		manager.Addrole("张三", 战士, "1001");
		manager.Addrole("李四", 法师, "1002");
		manager.Addrole("王五", 射手, "1003");
		manager.Addrole("赵六", 刺客, "1004");
		manager.Addrole("小七", 辅助, "1005");
		cout << "\n【测试4：状态保存与恢复】" << endl;
		Role* currentRole = manager.FindroleByName("张三");
		currentRole->levelUp();
		if (currentRole) {
			cout << "1. 当前张三的状态：" << endl;
			currentRole->PrintRole();

			cout << "\n2. 手动保存当前状态到stack：" << endl;
			manager.saveArchive(*currentRole);

			cout << "\n3. 再次升级张三：" << endl;
			currentRole->levelUp();
			cout << "升级后张三的状态：" << endl;
			currentRole->PrintRole();

			cout << "\n4. 从stack恢复张三之前的状态（撤销升级）：" << endl;
			manager.restoreRole("张三");
			cout << "恢复后张三的状态：" << endl;
			currentRole->PrintRole();
		}
	}

	void testsort()//角色排序
	{
		RoleManager manager;
		manager.Addrole("张三", 战士, "1001");
		manager.Addrole("李四", 法师, "1002");
		manager.Addrole("王五", 射手, "1003");
		manager.Addrole("赵六", 刺客, "1004");
		manager.Addrole("小七", 辅助, "1005");
		manager.levelUpRole("张三");
		manager.levelUpRole("张三");
		manager.levelUpRole("李四");

		cout << "\n【测试5：排序功能（算法与数据结构结合）】" << endl;
		cout << "排序前角色顺序：" << endl;
		manager.ShowAllRole();

		cout << "1. 按战斗力排序（降序）：" << endl;
		manager.SortByPower();
		manager.ShowAllRole();

		cout << "2. 按等级排序（降序）：" << endl;
		manager.SortByLevel();
		manager.ShowAllRole();

		cout << "3. 按攻击力排序（降序）：" << endl;
		manager.SortByAttack();
		manager.ShowAllRole();
	}

	void testrremove()//角色移除
	{
		RoleManager manager;
		manager.Addrole("张三", 战士, "1001");
		manager.Addrole("李四", 法师, "1002");
		manager.Addrole("王五", 射手, "1003");
		manager.Addrole("赵六", 刺客, "1004");
		manager.Addrole("小七", 辅助, "1005");

		cout << "\n【测试6：删除角色（vector和map的协同操作）】" << endl;
		cout << "删除前角色数量：" << manager.Rolecount() << endl;
		cout << "删除角色'张三'和'李四（ID）'：" << endl;
		manager.removeRole("张三");
		manager.removeRole("1002");
		cout << "查找张三" << endl;
		manager.FindroleByName("张三");
		cout << "删除后角色数量：" << manager.Rolecount() << endl;

		cout << "\n剩余角色列表：" << endl;
		manager.ShowAllRole();

		cout << "\n测试删除不存在的角色：" << endl;
		manager.removeRole("不存在的角色");
		manager.removeRole("1001");

		cout << endl << "最终系统状态" << endl;
		manager.showSystemStatus();
	}
	//自定义测试
	void selftest() {
		RoleManager manager;
		int choice;

		do {
			cout << "\n========== 自定义测试菜单 ==========" << endl;
			cout << "0. 返回主菜单" << endl;
			cout << "1. 显示所有角色" << endl;
			cout << "2. 添加新角色" << endl;
			cout << "3. 查找角色" << endl;
			cout << "4. 升级角色" << endl;
			cout << "5. 删除角色" << endl;
			cout << "6. 排序角色" << endl;
			cout << "7. 保存/恢复存档" << endl;
			cout << "===================================" << endl;
			cout << "请选择 (0-7): ";
			cin >> choice;

			// 处理输入缓冲区
			if (choice != 0) {
				cin.ignore(); // 忽略换行符
			}


			switch (choice) {
			case 1:
				cout << "\n【显示所有角色】" << endl;
				manager.ShowAllRole();
				break;

			case 2:
			{
				cout << "\n【添加新角色】" << endl;
				string name;
				string id;
				cout << "请输入 “角色名 ID”: ";
				cin >> name >> id;
				cout << "请选择职业 (1战士 2法师 3射手 4刺客 5辅助): ";
				int jobChoice;
				cin >> jobChoice;
				Job job;
				switch (jobChoice) {
				case 1: job = 战士; break;
				case 2: job = 法师; break;
				case 3: job = 射手; break;
				case 4: job = 刺客; break;
				case 5: job = 辅助; break;
				default: job = 战士; cout << "输入错误，默认为战士" << endl;
				}
				manager.Addrole(name, job, id);
			}
			break;
			case 3:
			{
				cout << "\n【查找角色】" << endl;
				cout << "请输入要查找的角色名: ";
				string findName;
				cin >> findName;
				Role* foundRole = manager.FindroleByName(findName);
				if (foundRole != nullptr) {
					cout << "\n找到角色:" << endl;
					foundRole->PrintRole();
				}
			}
			break;
			case 4:
			{
				cout << "\n【升级角色】" << endl;
				cout << "请输入要升级的角色名: ";
				string levelUpName;
				cin >> levelUpName;
				manager.levelUpRole(levelUpName);
			}
			break;

			case 5:
			{
				cout << "\n【删除角色】" << endl;
				cout << "请输入要删除的角色名或ID: ";
				string deleteTarget;
				cin >> deleteTarget;
				manager.removeRole(deleteTarget);
			}
			break;

			case 6:
			{
				cout << "\n【排序角色】" << endl;
				cout << "1. 按战斗力排序" << endl;
				cout << "2. 按等级排序" << endl;
				cout << "3. 按攻击力排序" << endl;
				cout << "请选择排序方式 (1-3): ";
				int sortChoice;
				cin >> sortChoice;

				switch (sortChoice) {
				case 1:
					manager.SortByPower();
					cout << "已按战斗力排序" << endl;
					break;
				case 2:
					manager.SortByLevel();
					cout << "已按等级排序" << endl;
					break;
				case 3:
					manager.SortByAttack();
					cout << "已按攻击力排序" << endl;
					break;
				default:
					cout << "输入错误，按战斗力排序" << endl;
					manager.SortByPower();
				}
			}
			break;

			case 7:
			{
				cout << "\n【存档功能演示】" << endl;
				cout << "1. 保存当前角色状态" << endl;
				cout << "2. 恢复角色状态" << endl;
				cout << "请选择 (1-2): ";
				int archiveChoice;
				cin >> archiveChoice;
				if (archiveChoice == 1) {
					cout << "请输入要保存的角色名: ";
					string saveName;
					cin >> saveName;
					Role* roleSave = manager.FindroleByName(saveName);
					if (roleSave) {
						manager.saveArchive(*roleSave);
					}
				}
				else if (archiveChoice == 2) {
					cout << "请输入要恢复的角色名: ";
					string restoreName;
					cin >> restoreName;
					manager.restoreRole(restoreName);
				}
			}
			break;
			case 8:
				cout << "\n【显示系统信息】" << endl;
				manager.showSystemStatus();
				break;
			case 0:
				cout << "返回主菜单..." << endl;
				break;

			default:
				cout << "无效选择，请重新输入!" << endl;
			}

		} while (choice != 0);
	}
}

// 测试函数
void test() {
	int tag;//保存玩家选项
	while (1)
	{
		cout << "    游戏角色属性管理系统 - 数据结构演示     " << endl;
		cout << "==========================================" << endl;
		cout << "|0-------------------------------退出演示|" << endl;
		cout << "|1-------------------------------角色添加|" << endl;
		cout << "|2-------------------------------角色查找|" << endl;
		cout << "|3-------------------------------角色升级|" << endl;
		cout << "|4-------------------------------角色备份|" << endl;
		cout << "|5-------------------------------角色排序|" << endl;
		cout << "|6-------------------------------角色移除|" << endl;
		cout << "|7-------------------------------自主测试|" << endl;
		cout << "==========================================" << endl;
		cout << "请输入：";
		cin >> tag;
		switch (tag)
		{
		case 0:
			cout << "\n==========================================" << endl;
			cout << "              测试结束                   " << endl;
			cout << "==========================================" << endl;
			return;
			break;
		case 1:test_help::testadd(); cout << endl; break;
		case 2:test_help::testFind();  cout << endl; break;
		case 3:test_help::testlevelup();  cout << endl; break;
		case 4:test_help::testarchive();  cout << endl; break;
		case 5:test_help::testsort(); cout << endl; break;
		case 6:test_help::testrremove();  cout << endl; break;
		case 7:test_help::selftest();  cout << endl; break;
		default:
			cout << "无效选择" << endl;
			break;
		}
	}
}

int main()
{
	//运行测试函数
	test();

	cout << "\n\n按Enter键退出程序...";
	cin.get();
	return 0;
}