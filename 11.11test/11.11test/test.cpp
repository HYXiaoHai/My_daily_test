#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;
#define MaxSize 100 //串中最多字符个数
typedef struct
{
	char data[MaxSize]; //存放串字符
	int length; //存放串的实际长度
} SqString; //顺序串类型
//串赋值
void Assign(SqString& s, const char str[])
{
	int i = 0;
	while (str[i] != '\0') //遍历str的所有字符
	{
		s.data[i] = str[i];
		i++;
	}
	s.length = i;
}
void DestroyStr(SqString s)
{
}
//串复制运算算法
void StrCopy(SqString& s, SqString t)
{
	int i;
	for (i = 0; i < t.length; i++)
		s.data[i] = t.data[i];
	s.length = t.length;
}
//求串长
int StrLength(SqString s)
{
	return(s.length);
}
//判断串相等
int StrEqual(SqString s, SqString t)
{
	int i = 0;
	if (s.length != t.length) //串长不同时返回0
		return(0);
	else
	{
		for (i = 0; i < s.length; i++)
			if (s.data[i] != t.data[i]) //有对应字符不同时返回0
				return 0;
		return 1;
	}
}
//串连接运算算法
SqString Concat(SqString s, SqString t)
{
	SqString r;
	int i, j;
	for (i = 0; i < s.length; i++) //将s复制到r
		r.data[i] = s.data[i];
	for (j = 0; j < t.length; j++) //将t复制到r
		r.data[s.length + j] = t.data[j];
	r.length = i + j;
	return r; //返回r
}
//求子串运算算法
SqString SubStr(SqString s, int i, int j)
{
	SqString t; //返回值
	int k;
	if (i<1 || i>s.length || j<1 || i + j>s.length + 1)
		t.length = 0; //参数错误时返回空串
	else
	{
		for (k = i - 1; k < i + j - 1; k++) //从i-1开始取j个
			t.data[k - i + 1] = s.data[k];
		t.length = j;
	}
	return t;
}
//查找子串位置运算算法
int Index(SqString s, SqString t)
{
	int i = 0, j = 0; //i和j分别扫描主串s和子串t
	while (i < s.length && j < t.length) //i控制主串，j控制子串
	{
		if (s.data[i] == t.data[j])
		{
			i++; //对应字符相同时,继续比较下一对字符
			j++; //继续后续字符比较
		}
		else //否则,主串指针回溯重新开始下一次匹配
		{
			i = i - j + 1; //i回退到原来i的下一个位置
			j = 0; //j从t的第一个字符开始
		}
	}
	if (j >= t.length) //说明t扫描完了
		return i - t.length + 1; //返回第一个字符的l逻辑位置
	else
		return 0; //返回0
}
//子串插入运算算法
int InsStr(SqString& s, int i, SqString t)
{
	int j;
	if (i<1 || i>s.length + 1) //最大值是length+1
		return 0; //位置参数错误返回0
	else
	{
		for (j = s.length - 1; j >= i - 1; j--) //从最后一个元素开始
			//将s.data[i-1..s.length-1]后移t.length个位置
			s.data[j + t.length] = s.data[j];
		for (j = 0; j < t.length; j++) //插入子串t
			s.data[i + j - 1] = t.data[j];
		s.length = s.length + t.length; //修改s串长度
		return 1; //成功插入返回1
	}
}
//子串删除
int DelStr(SqString& s, int i, int j)
{
	int k;
	if (i<1 || i>s.length || j<1 || i + j>s.length + 1)
		return 0; //位置参数值错误
	else
	{
		for (k = i + j - 1; k < s.length; k++)
			//将s的第i+j位置之后的字符前移j位
			s.data[k - j] = s.data[k];
		s.length = s.length - j; //修改s的长度
		return 1; //成功删除返回1
	}
}
//子串替换运算算法
SqString RepStrAll(SqString s, SqString s1, SqString s2)
{
	int i;
	i = Index(s, s1); //找到位置
	while (i > 0) //只要有就替换
	{
		DelStr(s, i, s1.length); //删除子串s1
		InsStr(s, i, s2); //插入子串s2
		i = Index(s, s1); //进入下一轮替换
	}
	return s;
}

//输出串运算算法
void DispStr(SqString s)
{
	int i;
	for (i = 0; i < s.length; i++)
		printf("%c", s.data[i]);
	printf("\n");
}

//字符逆置，并用相关数据进行测试。
SqString Inverse(SqString s)
{
	SqString tmp;
	int j = 0;
	for (int i = s.length-1; i >=0; i--)
	{
		/*cout << "测试：" << s.data[i] << endl;*/
		tmp.data[j] = s.data[i];
		j++;
		tmp.length = j;
	}
	tmp.data[j] = '\0';
	return tmp;
}

//数字字符移动到字母字符前面
SqString forward(SqString s)
{
	SqString tmp;
	int j = 0;
	for (int i =0;i<s.length;i++)
	{
		if (s.data[i] >= '0' && s.data[i] <= '9')
		{
			//cout << "测试：" << s.data[i] << endl;
			tmp.data[j] = s.data[i];
			j++;
			tmp.length = j;
		}
	}
	for (int i =0;i<s.length;i++)
	{
		if (s.data[i] >= 'a' && s.data[i] <= 'z')
		{
			//cout << "测试：" << s.data[i] << endl;
			tmp.data[j] = s.data[i];
			j++;
			tmp.length = j;
		}
	}
	tmp.data[j] = '\0';
	return tmp;
}

void test()
{
	SqString s1;
	Assign(s1, "abcd");
	printf("s1:"); DispStr(s1);
	printf("s1的长度:%d\n", StrLength(s1));
	SqString s2 = Inverse(s1);
	printf("s1翻转:"); DispStr(s2);
	printf("s2的长度:%d\n", StrLength(s2));
	cout << endl;

	SqString s3;
	Assign(s3, "a3b45cd9");
	printf("s3:"); DispStr(s3);
	printf("s3的长度:%d\n", StrLength(s3));
	SqString s4 = forward(s3);
	printf("s2数字前置:"); DispStr(s4);
	printf("s4的长度:%d\n", StrLength(s4));
}

int main()
{
	test();
	return 0;
}