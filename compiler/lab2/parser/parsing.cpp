/*
L<-m(布尔常数) or i(标识符)
L->K->J->C->A(布尔量->布因子->布尔项->布尔表达式)
G(算术量)->F(因子)->E(项)->B(算术表达式)->A(表达式)
G<-h(整数) or i(标识符)

两种表达式可以类比并行aha
*/
/*
属性文法的true只是为了描述跳转(和真实的表达式的真伪无关!!!!!)
*/
#include <iostream>
#include <windows.h>
#include <string.h>
#include <queue>
#include <fstream>
#include <math.h>
#include "stdio.h"
#define ll long long
#define inf 100000
#define clr1(a) memset(a, -1, sizeof(a))
#define clr(a) memset(a, 0, sizeof(a))
#include <set>
#include <ctime>
#include <map>

#include <stack>
#include <string>
using namespace std;
//推导程序的序号
string program_index;

//$空集 #结束符号
// S A B C D
// a b c #
// SAB SbC Ab A# BaD B# CAD Cb DaS Dc

// E T G H F
// + # * ( ) i
// ETG G+TG G# TFH H*FH H# F(E) Fi
//VN and VT
// set<string> VN={"A","B","C","D","E","F","G","J",
// "K","L","N","P","Q","R","S","T","U","V",
// "W","X","Y","Z"
// };
// set<string>VT={"h","i","m","o","type","op"};
set<string> VN; //= {"S", "A", "B", "C", "D"};
set<string> VT; // = {"a", "b", "c", "#"};
set<string> Xs;
//推导式集合
vector<string> inductions_0;
vector<vector<string>> inductions_1;
map<string, vector<int>> inductions_mapper; //first symbol of induction->induction index;
//判断是否是null symbol
map<string, int> isnull;
//fset
map<string, set<string>> fset;
map<string, int> numfset;
//项
class Item
{
public:
	int index;
	int dot;
	string nxts;
	Item(int a, int b, string nxts)
	{
		index = a;
		dot = b;
		this->nxts = nxts;
	}
	void ctString()
	{

		cout << index << " " << dot << " " << nxts << endl;
	}
	bool operator<(const Item &a) const
	{
		if (this->index != a.index)
		{
			return this->index < a.index;
		}
		else if (this->dot != a.dot)
		{
			return this->dot < a.dot;
		}
		else
		{
			return this->nxts < a.nxts;
		}
	}
};
//项集
class Items
{
public:
	vector<Item> items;
	//int t;
	Items()
	{
	}
	size_t myHash(std::vector<Item> const &vec) const
	{
		std::size_t seed = vec.size();
		for (auto &i : vec)
		{
			seed ^= i.index + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		}
		for (auto &i : vec)
		{
			seed ^= i.dot + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		}
		return seed;
	}

	bool operator<(const Items &a) const
	{
		if (myHash(this->items) != myHash(a.items))
			return myHash(this->items) < myHash(a.items);
		else
		{
			for (int i = 0; i < this->items.size(); ++i)
			{
				if (this->items[i].nxts != a.items[i].nxts)
				{
					return this->items[i].nxts < a.items[i].nxts;
				}
			}
			return false;
		}
	}
};
map<Items, int> Items_mapper; //Items->index of items
//项集族
vector<Items> items_a;
//LR table
class Action
{
public:
	bool acc;
	int type; //0-r;1-s;2-goto;-1-acc;
	int nxt;
	int rindex;
	Action(bool a = 0, int b = -2, int c = 0, int d = 0)
	{
		acc = a;
		type = b;
		nxt = c;
		rindex = d;
	}
};
vector<map<string, Action>> LR_table;
int clash;

//spilt
vector<string> mySpilt(string s)
{
	vector<string> ans;
	string tmp_unit = "";
	vector<string> tmp_trans;
	for (int j = 0; j < s.length(); ++j)
	{
		tmp_unit += s[j];
		if (VN.count(tmp_unit) || VT.count(tmp_unit))
		{
			tmp_trans.push_back(tmp_unit);
			tmp_unit = "";
		}
	}
	return tmp_trans;
}
//推导式转换
void transform()
{
	for (int i = 0; i < inductions_0.size(); ++i)
	{
		string tmp_ind = inductions_0[i];
		string tmp_unit = "";

		vector<string> tmp_trans;
		for (int j = 0; j < tmp_ind.length(); ++j)
		{
			tmp_unit += tmp_ind[j];
			if (VN.count(tmp_unit) || VT.count(tmp_unit))
			{
				tmp_trans.push_back(tmp_unit);
				tmp_unit = "";
			}
		}
		inductions_1.push_back(tmp_trans);
		inductions_mapper[tmp_trans[0]].push_back(i);
	}
}
//初始化
void init()
{
	inductions_mapper.clear();
	isnull.clear();
	fset.clear();
	Items_mapper.clear();
	clash = 0;

	fstream fin("test2.txt");
	//cout<<"program"+s+".txt"<<endl;
	if (!fin)
	{
		cout << "The program not exists!" << endl;
	}
	string a;
	char next;
	while (fin >> a)
	{
		//cout<<a;
		VN.insert(a);
		next = fin.get();
		if (next == '\n')
		{
			//cout<<"YES";
			break;
		}
	}
	while (fin >> a)
	{
		VT.insert(a);
		next = fin.get();
		if (next == '\n')
		{
			break;
		}
	}
	while (fin >> a)
	{
		inductions_0.push_back(a);
		next = fin.get();
		if (next == EOF)
		{
			break;
		}
	}
	// //推导式初始化
	// inductions.push_back("SAB");
	// inductions.push_back("SbC");
	// inductions.push_back("Ab");
	// inductions.push_back("A#");
	// inductions.push_back("BaD");
	// inductions.push_back("B#");
	// inductions.push_back("CAD");
	// inductions.push_back("Cb");
	// inductions.push_back("DaS");
	// inductions.push_back("Dc");
	transform();
	Xs.insert(VT.begin(), VT.end());
	Xs.insert(VN.begin(), VN.end());
	for (set<string>::iterator i = VT.begin(); i != VT.end(); ++i)
	{
		isnull[*i] = 0;
	}
	isnull["$"] = 1;
	for (set<string>::iterator i = VT.begin(); i != VT.end(); ++i)
	{
		fset[*i].insert(*i);
	}
}
//空推导式
int findnull(string tmp)
{
	//string tmp=*i;

	if (isnull.count(tmp) != 0)
		return isnull[tmp];
	else
	{
		bool flag = true;
		//cout << tmp << endl;
		for (int i = 0; i < inductions_1.size(); ++i)
		{
			if (inductions_1[i][0] == tmp)
			{
				//cout << tmp << i <<" "<<inductions_1[i][1] << endl;
				if (inductions_1[i][1] == "$")
				{
					isnull[tmp] = 1;
					return 1;
				}

				for (int j = 1; j < inductions_1[i].size(); ++j)
				{
					string test = inductions_1[i][j];
					//cout<<tmp<<" "<<test<<" "<<i<<" "<<j<<" "<<isnull.count(test)<<endl;
					//cout<<test<<endl;
					if (isnull.count(test) != 0)
					{
						if (isnull[test] == 0)
						{
							flag = false;
							break;
						}
						else
						{
							flag = true;
							continue;
						}
					}
					else
					{

						if (findnull(test) == 0)
						{
							flag = false;
							break;
						}
						else
						{
							flag = true;
							continue;
						}
					}
					//cout << 111 << endl;
				}
			}
			if (flag == true)
				break;
		}
		if (flag == false)
		{
			isnull[tmp] = 0;
			return 0;
		}
		else
		{
			isnull[tmp] = 1;
			return 1;
		}
	}
}
//求first集合
set<string> calfs(string a)
{
	if (fset.count(a) != 0)
		return fset[a];
	else
	{
		if (isnull[a] == 1)
			fset[a].insert("$");
		for (int i = 0; i < inductions_1.size(); ++i)
		{

			if (inductions_1[i][0] == a)
			{
				for (int j = 1; j < inductions_1[i].size(); ++j)
				{
					// cout << a << "(" << i << ")"
					//      << ":" << j;
					string tmp = inductions_1[i][j];
					//cout<<tmp<<endl;
					// cout << isnull[tmp] << endl;
					if (VT.count(tmp))
					{
						fset[a].insert(tmp);
						break;
					}
					else
					{ //此处的递归(动态规划)不具有无后效(依赖)性--tmp的calfs(前)依赖于a(后);
						//循环递归操作 直到整个解的空间稳定;
						//cout<<tmp<<endl;
						//cout<<fset.count(tmp)<<endl;
						set<string> tmpset = calfs(tmp);
						tmpset.erase("$");
						fset[a].insert(tmpset.begin(), tmpset.end());
						if (isnull[tmp] == 0)
						{
							break;
						}
					}
				}
			}
		}
		return fset[a];
	}
}
//求序列的fs
set<string> calfs_s(vector<string> a)
{
	set<string> ans;
	for (int i = 0; i < a.size(); ++i)
	{
		set<string> s = fset[a[i]];
		s.erase("$");
		ans.insert(s.begin(), s.end());
		if (isnull[a[i]] == 0)
		{
			return ans;
		}
	}
	ans.insert("$");
	return ans;
}

/*一----
*构造LR(1)项集族以及转移表
*/

//求项集的闭包(去重)
Items myClosure(Items &I)
{
	set<Item> cnt;
	for (auto &i : I.items)
	{
		cnt.insert(i);
	}
	for (int i = 0; i < I.items.size(); ++i)
	{
		Item tmp = I.items[i];
		int tmp_dot = tmp.dot;
		vector<string> ind_tmp = inductions_1[tmp.index];

		if (tmp_dot < ind_tmp.size())
		{
			string tmp_sym = ind_tmp[tmp_dot];
			if (VN.count(tmp_sym))
			{
				string new_nxt = "";
				//确定产生式
				vector<int> ind_index = inductions_mapper[tmp_sym];
				for (int j = tmp_dot + 1; j < ind_tmp.size(); ++j)
				{
					new_nxt += ind_tmp[j];
				}
				new_nxt += tmp.nxts;
				vector<string> new_nxt0 = mySpilt(new_nxt);
				//确定后缀
				set<string> new_nxt1 = calfs_s(new_nxt0);
				//每个B->a的产生式(B是内核项中的VN)
				for (int j = 0; j < ind_index.size(); ++j)
				{
					for (auto &nxt : new_nxt1)
					{

						Item item_tmp(ind_index[j], 1, nxt);
						if (inductions_1[ind_index[j]][1] == "$")
							item_tmp.dot = 2;
						if (cnt.count(item_tmp) == 0)
						{
							I.items.push_back(item_tmp);
							//cout<<"111"<<endl;

							cnt.insert(item_tmp);
						}
					}
				}
			}
		}
	}
	return I;
}
//GOTO函数
//**去重
Items goTO(Items I, string X)
{
	set<Item> cnt;
	cnt.clear();
	Items J;
	vector<Item> items_tmp = I.items;
	for (int i = 0; i < items_tmp.size(); ++i)
	{
		vector<string> ind_tmp = inductions_1[items_tmp[i].index];
		int index_tmp = items_tmp[i].index;
		int dot_tmp = items_tmp[i].dot;
		string nxt_tmp = items_tmp[i].nxts;
		if (ind_tmp[dot_tmp] == X)
		{
			Item item_tmp = Item(index_tmp, dot_tmp + 1, nxt_tmp);
			if (cnt.count(item_tmp) == 0)
			{
				J.items.push_back(Item(index_tmp, dot_tmp + 1, nxt_tmp));
				cnt.insert(item_tmp);
			}
		}
	}
	//cout<<cnt.size();
	return myClosure(J);
}
//求解项集族,建立LR(1)
void cal_items_all()
{
	Item start_item(0, 1, "#");
	Items start_items;
	start_items.items.push_back(start_item);
	Items fitems;
	fitems = myClosure(start_items);
	items_a.push_back(fitems);
	Items_mapper[fitems] = 0;
	for (int i = 0; i < items_a.size(); ++i)
	{
		cout << i << endl;
		//cout << i << " " << items_a.size() << " " << items_a[i].items.size() << endl;
		Items tmp = items_a[i];
		// while (i == 21)
		// {
		//     tmp.items[10].ctString();
		//     tmp.items[12].ctString();
		//     //cout<<(tmp.items[10]==tmp.items[12])<<endl;
		//     cout << endl;
		// }
		//cout<<LR_table[i].size()<<endl;
		//map<string, Action> tmp_map;
		LR_table.push_back(map<string, Action>());
		for (auto &j : Xs)
		{

			Items after_goto = goTO(tmp, j);
			if (after_goto.items.size() > 0)
			{
				if (Items_mapper.count(after_goto) == 0)
				{
					Items_mapper[after_goto] = items_a.size();
					items_a.push_back(after_goto);
					//cout << items_a.size() << " " << after_goto.items.size() << endl;
				}
				int tmp_index = Items_mapper[after_goto];
				//冲突counter
				if (LR_table[i].count(j) != 0)
				{
					clash++;
					//continue;
					if (i == 197)
						system("pause");
				}
				//shift and goto
				if (VN.count(j) != 0)
				{
					Action tmp_ac(false, 2, tmp_index, -1);
					LR_table[i][j] = tmp_ac;
				}
				else
				{
					Action tmp_ac(false, 1, tmp_index, -1);
					LR_table[i][j] = tmp_ac;
				}
			}
		}
		for (auto &j : tmp.items)
		{
			if (j.dot == inductions_1[j.index].size())
			{
				if (j.index == 0 && j.nxts == "#")
				{
					Action tmp_ac(true, -1, -1, -1);
					LR_table[i]["#"] = tmp_ac;
				}
				else
				{
					string tmp = j.nxts;
					if (LR_table[i].count(tmp))
					{
						clash++;
						//continue;
						//if(i==197)system("pause");
					}
					//cout<<j.index<<endl;
					Action tmp_ac(false, 0, -1, j.index);
					LR_table[i][tmp] = tmp_ac;
				}
			}
		}
	}
}

/*二----
*语法分析子程序LR
*/

class FourStatement
{
public:
	string fst, snd, trd, fth;
	bool isback = true;
	FourStatement(string a, string b, string c, string d)
	{
		this->fst = a;
		this->snd = b;
		this->trd = c;
		this->fth = d;
		//nxt=d;
	}
	int getfourth()
	{
		if (isback == false)
		{
			//已经回填过
			return -3;
		}
		if (fth == "-1")
			return atoi(fth.c_str());
		if (isdigit(fth[0]))
		{
			//cout << fth << endl;
			return atoi(fth.c_str());
		}
		else
		{
			//cout << fth << endl;
			//非数字(字母等表示之后无向前拉链的过程了)
			return -2;
		}
	}
	void setfourth(int a)
	{

		this->fth = to_string(a);
		//fth=tmp;
	}
	void setback()
	{
		this->isback = false;
	}
	string getString()
	{
		return '(' + fst + " , " + snd + " , " + trd + " , " + fth + ")";
	}
};
vector<FourStatement> allfs;
//计数四元式
int tmp_cnt = 0;
//插入四元式
void push_fs(string a, string b, string c, string d, bool isback)
{
	FourStatement tmp(a, b, c, d);
	if (!isback)
		tmp.isback = false;
	allfs.push_back(tmp);
	tmp_cnt++;
}
//打印四元式
void print_fs()
{
	for (int i = 0; i < allfs.size(); ++i)
	{
		cout << i << ": " << allfs[i].getString() << endl;
	}
	allfs.clear();
}
// void programBegin(string name)
// {
//     FourStatement tmp("program", name, "-", "-");
//     allfs.push_back(tmp);
//     cout << tmp.getString() << endl;
// }
// void givevalue(string a, string v)
// {
//     FourStatement tmp(":=", v, "-", a);
//     allfs.push_back(tmp);
//     cout << tmp.getString() << endl;
// }
////!!!!!!!!!!!!!!!!!!多态!!!!!!
class base_symbol
{
public:
	string sym;
	int chain = -1;
	int true_1 = -1;
	int false_1 = -1;
	int begin_1 = -1;
	string ini_sym;
	base_symbol(string a = "")
	{
		sym = a;
	}
};
class E_symbol : public base_symbol
{
public:
	//int true_1, false_1, begin_1;

	E_symbol(string d, int a = -1, int b = -1, int c = -1) : base_symbol(d)
	{
		//super(d);
		true_1 = a;
		false_1 = b;
		begin_1 = c;
	}
};
class E_2 : public base_symbol
{
public:
	//string ini_sym;
	E_2(string a, string b) : base_symbol(a)
	{
		ini_sym = b;
	}
};
//假复制,真传值
base_symbol *copyofE_symbol(int index, base_symbol *tmp)
{
	return new E_symbol(inductions_1[index][0], tmp->true_1, tmp->false_1, tmp->begin_1);
}
class C_S : public base_symbol
{
public:
	//int chain;
	C_S(string a, int b) : base_symbol(a)
	{
		chain = b;
	}
};
vector<base_symbol *> sym;
vector<int> sta;
queue<string> sym_i;
queue<string> ready_str;
vector<string> op;

string reduction_0(int index)
{
	vector<string> in_tmp = inductions_1[index];
	int size_tmp = in_tmp.size();
	size_tmp--;
	if (in_tmp[1] != "$")
	{
		while (size_tmp--)
		{
			sta.pop_back();
			base_symbol *tmp = sym[sym.size() - 1];
			delete tmp;
			sym.pop_back();
		}
	}
	//sym.push_back(in_tmp[0]);
	return in_tmp[0];
}

// class mean_symbol
// {
//     public:
//     mean_symbol(){}
// };
// class E : public mean_symbol
// {
//     //bool j;
// public:
//     int begin, te, fe;
//     E(int a = 0, int b = 0, int c = 0)
//     {
//         begin = a;
//         te = b;
//         fe = c;
//     }
// };
// class C_S :public mean_symbol
// {
// public:
//     int chain;
//     C_S(int a)
//     {
//         chain = a;
//     }
// };
// class SS :public mean_symbol
// {
// public:
//     string tmp;
//     SS(string a)
//     {
//         tmp = a;
//     }
// };

/*三----
*语义分析附加(以及中间代码生成)
*/
//符号表(eg:类型)
map<string, string> tbof_sym;
//符号表辅助栈
vector<string> unsolved_one;
//语义动作辅助函数
int myMerge(int a, int b)
{
	////???b指向的链非空;
	//int ans=b;
	//cout << allfs[b].getfourth() << endl;
	if (b == -1 || allfs[b].getfourth() == -3)
	{
		return a;
	}
	else
	{

		int tmp = b;
		while (allfs[b].getfourth() >= 0)
		{

			if (allfs[allfs[b].getfourth()].getfourth() == -2 || allfs[allfs[b].getfourth()].getfourth() == -3)
			{
				break;
			}
			b = allfs[b].getfourth();
		}
		allfs[b].setfourth(a);
		return tmp;
	}
}
bool backpatch(int chain_begin, int b)
{
	if (chain_begin == 15)
	{
		//cout << endl;
	}
	if (chain_begin == -1)
	{
		return false;
	}
	else
	{
		//tmp_1决定set tmp决定get
		int tmp = allfs[chain_begin].getfourth();
		if (tmp != -2 && tmp != -3)
		{
			//cout << chain_begin << endl;
			allfs[chain_begin].setfourth(b);
			allfs[chain_begin].setback();
			//tmp = allfs[chain_begin].getfourth();
			int tmp_1;
			while (tmp != -1 && tmp < allfs.size())
			{
				tmp_1 = allfs[tmp].getfourth();
				if (tmp_1 == -2 || tmp_1 == -3)
					break;
				//cout << tmp << endl;
				//-------------------------
				//if (tmp == 14)
				//cout << endl;
				allfs[tmp].setfourth(b);
				allfs[tmp].setback();
				tmp = tmp_1;
			};
		}
		return true;
	}
}
//辅助四元式函数
void programBegin(string name)
{
	FourStatement tmp("program", name, "-", "-");
	allfs.push_back(tmp);
	tmp_cnt++;
	//cout << tmp.getString() << endl;
}
void givevalue(string a, string v)
{
	FourStatement tmp(":=", v, "-", a);
	allfs.push_back(tmp);
	tmp_cnt++;
	//cout << tmp.getString() << endl;
}
string myOP(string a, string b, string c)
{
	// //四则运算的oprand的运算符号的类型检查
	// if (tbof_sym[a] != tbof_sym[b])
	// {
	//     cout << "type wrong with " << tbof_sym[a] << " " << tbof_sym[b] << endl;
	//     system("pause");
	// }
	string ans = ready_str.front();
	ready_str.pop();
	FourStatement tmp(c, a, b, ans);
	allfs.push_back(tmp);
	tmp_cnt++;
	//cout << tmp.getString() << endl;
	return ans;
}
base_symbol *myOP2(int index, base_symbol *E1, base_symbol *E2, string rop)
{
	int cb = E1->begin_1;
	int te, fe;
	if (rop == "or")
	{
		if (!backpatch(E1->false_1, E2->begin_1))
		{
			E1->false_1 = E2->begin_1;
		}
		te = myMerge(E1->true_1, E2->true_1);
		fe = E2->false_1;
	}
	else
	{

		if (!backpatch(E1->true_1, E2->begin_1))
		{
			E1->true_1 = E2->begin_1;
		};
		te = E2->true_1;
		fe = myMerge(E1->false_1, E2->false_1);
	}
	return new E_symbol(inductions_1[index][0], te, fe, cb);
}
//stack<base_symbol> tmp_s;
//+ - * /
// void op(string a, string b, string c)
// {
//     string tmp_ans = ready_str.front();
//     ready_str.pop();
//     FourStatement tmp(a, b, c, tmp_ans);
//     allfs.push_back(tmp);
//     SS tmp_SS(tmp_ans);
//     tmp_s.push(tmp_SS);
// }

//语义动作以及reduction;

//记录栈
stack<int> s_1;
stack<int> s_2;
base_symbol *semantic_action(int index)
{
	//既要维护符号栈 又要维护四元式结构(符号栈和四元式相互关联----c.chain指向四元式);
	//print_fs();
	//cout << endl; //111
	base_symbol *ans;
	if (index == 60)
	{
		//end()返回下一个地址(域以外的地方)!!!!!
		//cout << 111 << endl;
		auto pter = sym.end();
		pter -= 2;
		base_symbol nxt = *(*(pter));
		//cout << nxt.sym << endl;
		//E_2 nxt=(E_2) nxt;
		programBegin(nxt.ini_sym);
		ans = new base_symbol(inductions_1[index][0]);
	}
	else if (index == 45)
	{
		//cout << 111 << endl;
		auto pter = sym.end() - 1;
		base_symbol *nxt = *pter;
		//cout << ":="<<nxt->ini_sym << endl;
		pter -= 2;
		base_symbol nxt1 = *(*pter); //pter+=1;
		//cout << nxt1.sym << endl;
		//base_symbol nxt3=
		givevalue(nxt1.ini_sym, nxt->ini_sym);
		ans = new base_symbol(inductions_1[index][0]);
	}
	else if (index == 16 || index == 17 || index == 15)
	{
		//end()返回下一个地址(域以外的地方)
		//Gh_1 FG Gi_1
		//cout << 111 << endl;
		auto a = sym[sym.size() - 1];
		ans = new E_2(inductions_1[index][0], (*a).ini_sym);
	}
	else if (index == 18)
	{
		//G(Bini) 复制值
		auto a = sym[sym.size() - 2];
		ans = new E_2(inductions_1[index][0], (*a).ini_sym);
	}
	else if (index == 29)
	{
		//L(Cini) 复制值
		auto a = sym[sym.size() - 2];
		ans = new E_symbol(inductions_1[index][0], a->true_1, a->false_1, a->begin_1);
	}
	else if (index == 9 || index == 4)
	{
		//EiniFE_1 BiniEiniB_1
		//四则运算的最后一步 or F直接推导到E;
		//cout << index << endl;
		auto a = sym[sym.size() - 2];
		auto b = sym[sym.size() - 1];
		//a -= 1;
		if (b->ini_sym == "nothing")
			ans = new E_2(inductions_1[index][0], (*a).ini_sym);
		else
		{
			string op_tmp = op.back();
			op.pop_back();
			string tmp_1 = myOP(a->ini_sym, b->ini_sym, op_tmp);
			ans = new E_2(inductions_1[index][0], tmp_1);
		}
	}
	else if (index == 5 || index == 6 || index == 10 || index == 11)
	{
		//B_1+EiniB_1 B_1-EiniB_1 E_1*iniFE_1 E_1/iniFE_1
		//cout << 111 << endl;
		auto a = sym.end();
		//a--;
		base_symbol *s1 = *(a - 1);
		base_symbol *s2 = *(a - 2);
		base_symbol *s3 = *(a - 3);
		if (s1->ini_sym == "nothing")
		{
			op.push_back(s3->sym.substr(0, 1));
			ans = new E_2(inductions_1[index][0], (*s2).ini_sym);
		}
		else
		{
			string opp = s3->sym.substr(0, 1);
			string a = s1->ini_sym;
			string b = s2->ini_sym;
			string tmp_1 = myOP(a, b, opp);
			ans = new E_2(inductions_1[index][0], tmp_1);
		}
	}
	else if (index == 20 || index == 23)
	{
		//J_1andKJ_1 C_1orJiniC_1
		auto a = sym.end();
		//a--;
		base_symbol *s1 = *(a - 1);
		base_symbol *s2 = *(a - 2);
		base_symbol *s3 = *(a - 3);
		if (s1->ini_sym == "nothing")
		{
			op.push_back(s3->sym);
			ans = copyofE_symbol(index, s2);
			//cout << "nothing" << endl;
		}
		else
		{
			int cb = s2->begin_1;
			if (s3->sym == "and")
			{

				if (!backpatch(s2->false_1, s1->begin_1))
				{
					s2->false_1 = s1->begin_1;
				}
				int te = myMerge(s2->true_1, s1->true_1);
				int fe = s1->false_1;
				ans = new E_symbol(inductions_1[index][0], te, fe, cb);
			}
			else
			{
				if (!backpatch(s2->true_1, s1->begin_1))
				{
					s2->true_1 = s1->begin_1;
				}
				int te = s1->true_1;
				int fe = myMerge(s2->false_1, s1->false_1);
				ans = new E_symbol(inductions_1[index][0], te, fe, cb);
			}
		}
	}
	else if (index == 22 || index == 19)
	{
		//JiniKJ_1 CiniJiniC_1------------------------------------------------------
		//bool运算的最后一步 or 直接推导到;
		auto a = sym[sym.size() - 2];
		auto b = sym[sym.size() - 1];
		if (b->ini_sym == "nothing")
			ans = copyofE_symbol(index, a);

		else
		{
			string op_tmp = op.back();
			op.pop_back();
			ans = myOP2(index, a, b, op_tmp);
			//ans = new E_2(inductions_1[index][0], tmp_1);
		}
	}
	else if (index == 26)
	{
		//KnotK
		auto a = sym[sym.size() - 1];
		int cb = a->begin_1;
		int te = a->true_1;
		int fe = a->false_1;
		ans = new E_symbol(inductions_1[index][0], te, fe, cb);
	}
	else if (index == 12 || index == 7 || index == 24 || index == 21)
	{
		//cout << 111 << endl;
		//加减乘除 and or的导空推导式
		ans = new E_2(inductions_1[index][0], "nothing");
	}
	else if (index == 46)
	{
		//RleftifCinithen
		auto s1 = sym[sym.size() - 2];
		//auto s2=sym[sym.size()-2];
		backpatch(s1->true_1, tmp_cnt);
		ans = new C_S(inductions_1[index][0], s1->false_1);
	}
	else if (index == 48)
	{
		//RiniRleftP(两种if if1)
		auto s1 = sym[sym.size() - 1];
		auto s2 = sym[sym.size() - 2];
		int chain_tmp = myMerge(s1->chain, s2->chain);
		//---
		//if语句的出口在推导式结束的时候出现,进行回填;
		if (sym[sym.size() - 3]->sym != "Rright" && sym[sym.size() - 3]->sym != "Sright" && sym[sym.size() - 3]->sym != "Rleft" && sym[sym.size() - 3]->sym != "Tright")
		{
			backpatch(chain_tmp, tmp_cnt);
			while (!s_1.empty())
			{
				int tmp = s_1.top();
				int tmp_1 = s_2.top();
				backpatch(tmp_1, tmp);
				s_1.pop();
				s_2.pop();
			}
		}
		else
		{
			s_1.push(tmp_cnt);
			s_2.push(chain_tmp);
		}
		ans = new C_S(inductions_1[index][0], chain_tmp);
	}
	//if   and  bool condition-----------------------------------------------------------------------
	else if (index == 47)
	{
		//RrightRleftPelse
		int tmp_stat = tmp_cnt;
		auto s1 = sym[sym.size() - 2];
		auto s2 = sym[sym.size() - 3];
		push_fs("j", "-", "-", "-1", true);

		backpatch(s2->chain, tmp_cnt);
		int tmp = myMerge(tmp_stat, s1->chain);
		ans = new C_S(inductions_1[index][0], tmp);
	}
	else if (index == 49)
	{
		//RiniRrightP(两种if if2)
		auto s1 = sym[sym.size() - 1];
		auto s2 = sym[sym.size() - 2];
		int tmp = myMerge(s1->chain, s2->chain);
		//---
		//if语句的出口在推导式结束的时候出现,进行回填;
		if (sym[sym.size() - 3]->sym != "Rright" && sym[sym.size() - 3]->sym != "Sright" && sym[sym.size() - 3]->sym != "Rleft" && sym[sym.size() - 3]->sym != "Tright")
		{
			backpatch(tmp, tmp_cnt);
			while (!s_1.empty())
			{
				int tmp = s_1.top();
				int tmp_1 = s_2.top();
				backpatch(tmp_1, tmp);
				s_1.pop();
				s_2.pop();
			}
		}
		else
		{
			s_1.push(tmp_cnt);
			s_2.push(tmp);
		}
		ans = new C_S(inductions_1[index][0], tmp);
	}
	else if (32 <= index && index <= 37)
	{
		//N~
		if (index == 32 || index == 36)
		{
			ans = new E_2(inductions_1[index][0], inductions_1[index][1].substr(0, 1));
		}
		else
		{
			ans = new E_2(inductions_1[index][0], inductions_1[index][1]);
		}
	}
	else if (index == 30 || index == 31)
	{
		//Li_1Ni_1 LBiniNBini
		auto s1 = sym[sym.size() - 1];
		auto s2 = sym[sym.size() - 3];
		auto s3 = sym[sym.size() - 2];
		string rop = "j" + s3->ini_sym;
		int cb = tmp_cnt;
		int te = tmp_cnt;
		int fe = tmp_cnt + 1;
		push_fs(rop, s2->ini_sym, s1->ini_sym, "-1", true);
		push_fs("j", "-", "-", "-1", true);
		ans = new E_symbol(inductions_1[index][0], te, fe, cb);
	}
	else if (index == 25)
	{
		//KL 布尔因子的初始化
		auto s1 = sym[sym.size() - 1];
		ans = new E_symbol(inductions_1[index][0], s1->true_1, s1->false_1, s1->begin_1);
	}
	else if (index == 50)
	{
		//WLwhile
		ans = new E_symbol(inductions_1[index][0], -1, -1, tmp_cnt);
	}
	else if (index == 51)
	{
		//SrightWLCinido
		auto s1 = sym[sym.size() - 2];
		auto s2 = sym[sym.size() - 3];
		int cb = s2->begin_1;
		backpatch(s1->true_1, tmp_cnt);
		int chain = s1->false_1;
		base_symbol *tmp = new base_symbol(inductions_1[index][0]);
		tmp->begin_1 = cb;
		tmp->chain = chain;
		ans = tmp;
	}
	else if (index == 52)
	{
		//SiniSrightP
		auto s1 = sym[sym.size() - 1];
		auto s2 = sym[sym.size() - 2];
		backpatch(s1->chain, s2->begin_1);
		push_fs("j", "-", "-", to_string(s2->begin_1), false);
		int chain = s2->chain;
		//外层的控制语句先回填,优先级最高-----每条四元式最多回填一次
		if (sym[sym.size() - 3]->sym != "Rright" && sym[sym.size() - 3]->sym != "Sright" && sym[sym.size() - 3]->sym != "Rleft" && sym[sym.size() - 3]->sym != "Tright")
		{
			backpatch(s2->chain, tmp_cnt);
			while (!s_1.empty())
			{
				int tmp = s_1.top();
				int tmp_1 = s_2.top();
				s_1.pop();
				s_2.pop();
				backpatch(tmp_1, tmp);
				//print_fs();
			}
		}
		else
		{
			s_1.push(tmp_cnt);
			s_2.push(s2->chain);
		}
		base_symbol *tmp = new base_symbol(inductions_1[index][0]);
		tmp->chain = chain;
		ans = tmp;
	}
	else if (index == 57)
	{
		//VrightP;
		auto s1 = sym[sym.size() - 2];
		backpatch(s1->chain, tmp_cnt);
		base_symbol *tmp = new base_symbol(inductions_1[index][0]);
		ans = tmp;
	}
	else if (index == 58)
	{
		//ViniVrightVini
		auto s1 = sym[sym.size() - 2];
		auto s2 = sym[sym.size() - 1];
		base_symbol *tmp = new base_symbol(inductions_1[index][0]);
		tmp->chain = s2->chain;
		ans = tmp;
	}
	else if (index >= 40 && index < 45)
	{
		//PQ ..
		auto s1 = sym[sym.size() - 1];
		base_symbol *tmp = new base_symbol(inductions_1[index][0]);
		tmp->chain = s1->chain;
		ans = tmp;
	}
	else if (index == 53)
	{
		//Trightrepeat
		ans = new base_symbol(inductions_1[index][0]);
		ans->begin_1 = tmp_cnt;
	}
	else if (index == 54)
	{
		//TleftTrightPuntil
		auto s1 = sym[sym.size() - 3];
		auto s2 = sym[sym.size() - 2];
		auto s3 = sym[sym.size() - 1];
		ans = new base_symbol(inductions_1[index][0]);
		ans->begin_1 = s1->begin_1;
		backpatch(s2->chain, tmp_cnt);
	}
	else if (index == 55)
	{
		//TiniTleftCini
		auto s1 = sym[sym.size() - 2];
		auto s2 = sym[sym.size() - 1];
		backpatch(s2->false_1, s1->begin_1);
		ans = new base_symbol(inductions_1[index][0]);
		ans->chain = s2->true_1;
		if (sym[sym.size() - 3]->sym != "Rright" && sym[sym.size() - 3]->sym != "Sright" && sym[sym.size() - 3]->sym != "Rleft" && sym[sym.size() - 3]->sym != "Tright")
		{
			backpatch(ans->chain, tmp_cnt);
			while (!s_1.empty())
			{
				int tmp = s_1.top();
				int tmp_1 = s_2.top();
				s_1.pop();
				s_2.pop();
				backpatch(tmp_1, tmp);
				print_fs();
			}
		}
		else
		{
			s_1.push(tmp_cnt);
			s_2.push(s2->chain);
		}
	}
	else if (index == 61)
	{
		//程序的结束
		push_fs("sys", "-", "-", "-", true);
		ans = new base_symbol(inductions_1[index][0]);
	}
	// else if (index == 64 || index == 65)
	// {
	//     //YZ:initype;Y YZ:initype;
	//     auto s1 = sym[sym.size() - 2 - (65 - index)];
	//     while (!unsolved_one.empty())
	//     {
	//         string tmp = unsolved_one.back();
	//         unsolved_one.pop_back();
	//         tbof_sym.insert(tmp, s1->ini_sym);
	//     }
	//     ans = new base_symbol(inductions_1[index][0]);
	// }
	// else if (index == 66)
	// {
	//     //Zi_1,Z
	//     auto s1 = sym[sym.size() - 3];
	//     unsolved_one.push_back(s1->ini_sym);
	//     ans = new base_symbol(inductions_1[index][0]);
	// }
	// else if (index == 67)
	// {
	//     //Zi_1
	//     auto s1 = sym[sym.size() - 1];
	//     unsolved_one.push_back(s1->ini_sym);
	//     ans = new base_symbol(inductions_1[index][0]);
	// }
	else
	{
		//cout << index << endl;
		ans = new base_symbol(inductions_1[index][0]);
	}
	reduction_0(index);
	return ans;
}
////重构推导栈!!!!

/*四-----
*语法分析+语义分析---
*/
void LRprocess()
{
	//待用符号表(标识符的表) ready_str
	for (int i = 1; i <= 10; ++i)
	{
		string tmp = "T" + to_string(i);
		ready_str.push(tmp);
	}

	//读取数据
	fstream fin, fin2;
	//reading input
	//程序一
	if (program_index == "1")
	{
		fin.open("program1.txt");
		fin2.open("sym_i_1.txt");
	}
	//程序二
	else
	{
		fin.open("program2.txt");
		fin2.open("sym_i_2.txt");
	}
	//控制语句的bool表达式保证了四元式的数量
	//控制语句+语义动作+属性文法证拉链和回填

	sta.push_back(0);
	while (fin2.peek() != EOF)
	{
		string tmp;
		fin2 >> tmp;
		//cout<<tmp<<endl;
		sym_i.push(tmp);
	}
	bool flag = true;
	string sym_tmp;
	while (true)
	{
		if (flag && fin.peek() != EOF)
			fin >> sym_tmp;
		else if (fin.peek() == EOF && flag)
		{
			cout << "wrong!" << endl;
			system("pause");
		}
		else
		{
			flag = true;
		}
		//cout<<sym_tmp;
		int i = sta.size();
		Action tmp_action = LR_table[sta[i - 1]][sym_tmp];
		if (tmp_action.type == -2)
		{
			//推导出错误(语法分析)
			cout << "FALSE TXT" << endl;
			system("pause");
		}
		if (tmp_action.type == -1)
		{
			//cout << sym_tmp << endl;
			cout << "true" << endl;
			return;
		}
		else if (tmp_action.type == 1)
		{
			//shift
			//cout << sym_tmp << endl;
			sta.push_back(tmp_action.nxt);

			if (sym_tmp == "h_1" || sym_tmp == "i_1")
			{
				E_2 *tmp = new E_2(sym_tmp, sym_i.front());
				sym.push_back(tmp);
				sym_i.pop();
			}
			else
			{
				base_symbol *tmp = new base_symbol(sym_tmp);
				sym.push_back(tmp);
			}
			//sym.push_back(sym_tmp);
		}
		else if (tmp_action.type == 0)
		{
			//base_symbol tmp_sym;
			//cout << sta[i - 1] << " " << sym_tmp << " ";
			int index = tmp_action.rindex;
			base_symbol *tmp_sym = semantic_action(index);
			//cout<<index<<endl;
			//cout << index << endl;

			// if (index == 60)
			// {
			//     string tmp_str = sym_i.front();
			//     sym_i.pop();
			//     //programBegin(tmp_str);
			// }
			// if (index == 45)
			// {
			//     string tmp_str = sym_i.front();
			//     sym_i.pop();
			//     string tmp_str2 = sym_i.front();
			//     sym_i.pop();
			//     //givevalue(tmp_str, tmp_str2);
			// }
			// if (index == 11 || 12 || 6 || 7)
			// {
			//     switch (index)
			//     {
			//     case 11:
			//         /* code */
			//         break;

			//     default:
			//         break;
			//     }
			// }
			//关系表达式
			//if()
			// if(index==65||66){
			//     //类型声明
			//     string tmp_str = sym_i.front();
			//     sym_i.pop();
			// }
			//reduction_0(index);
			int tmp_index, tmp_sta;
			tmp_index = sta.size();
			tmp_sta = sta[tmp_index - 1];

			// while (LR_table[tmp_sta][tmp_sym.sym].type == 0)
			// {
			//     index = LR_table[tmp_sta][tmp_sym.sym].rindex;

			//     //语义动作
			//     tmp_sym=semantic_action(index);
			//     //reduction_0(index);
			//     tmp_index = sta.size();
			//     tmp_sta = sta[tmp_index - 1];
			// }

			if (LR_table[tmp_sta][tmp_sym->sym].type != 2)
			{
				//推导出错误(语法分析)
				cout << "FALSE TXT" << endl;
				system("pause");
			}

			sta.push_back(LR_table[tmp_sta][tmp_sym->sym].nxt);
			sym.push_back(tmp_sym);
			//cout << sta[1] << endl;
			flag = false;
		}
	}
}

/*五----
*程序入口
*/
int main()
{
	/*
	*求first set
	*/
	init();
	// bool a=(inductions[3][1]=='#');
	// cout<<a<<endl;
	//cout << findnull("A");
	// for (int i = 0; i < inductions_1.size(); ++i)
	// {
	//     for (int j = 0; j < inductions_1[i].size(); ++j)
	//     {
	//         cout << inductions_1[i][j] << " ";
	//     }
	//     cout << endl;
	// }

	// set<Item> cnt;
	// Item tmp(17,1,"then");
	// cnt.insert(tmp);
	// Item tmp1(17,1,"then");
	// cout<<cnt.count(tmp1)<<endl;

	//---求Null集合
	for (set<string>::iterator i = VN.begin(); i != VN.end(); ++i)
	{
		string tmp = *i;
		//cout<<fset.count(tmp)<<endl;
		//cout << tmp;
		findnull(tmp);
		//cout << tmp << ":";
		// for (int i = 0; i < inductions_mapper[tmp].size(); ++i)
		// {
		//     cout << inductions_mapper[tmp][i] << " ";
		// }
		// cout << endl;
	}
	// for (map<string, int>::iterator i = isnull.begin(); i != isnull.end(); ++i)
	// {
	//     cout << i->first << " " << i->second << endl;
	// }
	//!!!循环递归操作 直到整个解的空间稳定;
	//cout << isnull["B"] << endl;
	//cout<<111<<endl;
	//---求解first set
	while (true)
	{
		bool flag = true;
		for (set<string>::iterator i = VN.begin(); i != VN.end(); ++i)
		{
			fset.erase(*i);
			//cout << fset.count(*i) << endl;
			set<string> tmpset = calfs(*i);
			if (numfset.count(*i))
			{
				if (flag)
				{
					if (numfset[*i] != tmpset.size())
					{
						//cout << "aaa" << endl;
						flag = false;
					}
				}
				numfset[*i] = tmpset.size();
			}
			else
			{
				numfset[*i] = tmpset.size();
				flag = false;
			}
		}
		//cout << flag << endl;
		if (flag)
			break;
	}
	//cout << fset["N"].size() << endl;

	//---test(字符串的first set)
	// vector<string> tmp = mySpilt("aS");
	// set<string> s = calfs_s(tmp);
	// for (set<string>::iterator i = s.begin(); i != s.end(); ++i)
	// {
	//     cout << *i << endl;
	// }
	// cout << endl;
	// Items ans;
	// ans.items.push_back(Item(52, 2, "#"));
	//ans.items.push_back(Item(2, 2, "d"));
	// ans = myClosure(ans);
	//cout<<"111"<<endl;
	//Items J = goTO(ans, "c");
	//ans = J;
	// for (int i = 0; i < ans.items.size(); ++i)
	// {
	//     Item tmp = ans.items[i];
	//     cout << i << ":" << tmp.dot << " " << tmp.index << " " << tmp.nxts << endl;
	// }
	//cout<<111<<endl;
	//cout<<"aaa"<<endl;
	//求项集族
	//cout<<11<<endl;
	try
	{
		cal_items_all();
		//cal_items_all();
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}

	//cal_items_all();
	// for (int i = 0; i < items_a.size(); ++i)
	// {
	//     Items tmp = items_a[i];
	//     cout << "item set index: " << Items_mapper[tmp] << " : " << endl;
	//     for (int j = 0; j < tmp.items.size(); ++j)
	//     {
	//         cout << tmp.items[j].nxts << " ";
	//         cout << tmp.items[j].index << " ";
	//         cout << tmp.items[j].dot << " ";
	//         //cout<<endl;
	//         //cout << inductions_1[tmp.items[j].index].size() << endl;
	//     }
	//     cout << endl;
	//     auto tmp_action = LR_table[i];
	//     for (auto j = tmp_action.begin(); j != tmp_action.end(); ++j)
	//     {
	//         cout << "(" << j->first << " type:" << j->second.type << " next:" << j->second.nxt << " induction:" << j->second.rindex << ") ";
	//     }
	//     cout << endl;
	// }
	cout << endl;
	cout << "The number of collision: " << clash << endl;

	//cout << LR_table[11][":ini"].rindex;

	//LR(1)语法推导

	cout << "王建伟"
		 << " "
		 << "19计联"
		 << " "
		 << " 201930420160" << endl;
	cout << "choose the program index ready to be analysed:(1/2/exit ?): ";
	cin >> program_index;
	while (program_index != "exit")
	///初始化
	{
		tmp_cnt = 0;
		while (!s_1.empty())
		{
			s_1.pop();
		}
		while (!s_2.empty())
		{
			s_2.pop();
		}
		tbof_sym.clear();
		unsolved_one.clear();
		allfs.clear();
		sym.clear();
		sta.clear();
		op.clear();
		while (!sym_i.empty())
		{
			sym_i.pop();
		}
		while (!ready_str.empty())
		{
			ready_str.pop();
		}
		//语法推导(语义+语法)
		LRprocess();
		cout << "sucess!" << endl;

		//打印四元式
		print_fs();

		cout << endl
			 << "choose the program index ready to be analysed:(1/2/exit ?): ";
		cin >> program_index;
	}
}

//plus:: 推导式的第一项必定为 AS->S;
//左递归的消除 提取左公因子
//# VT(结束)
