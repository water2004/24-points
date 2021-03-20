#include<iostream>
#include<string>
#include<stack>
#include<map>
#include<sstream>
#include<set>
#include<cstdlib>
#include<ctime>
#include<random>
#pragma GCC optimize(3,"Ofast","inline")
#define eps 0.001
using namespace std;
double a, b, c, d;
set <string> ans;
inline double compute(char c, double num1, double num2)
{
	switch (c)
	{
	case '+': return num1 + num2;
	case '-': return num1 - num2;
	case '*': return num1 * num2;
	case '/': if (num2 != 0) return num1 / num2;
			  else return 100000000;
	}
}
inline double exp(string s)
{
	stack<char> cha;
	stack<double> nums;
	double num;
	map<char, double> a;
	a['+'] = 0;
	a['-'] = 0;
	a['*'] = 1;
	a['/'] = 1;
	int size = s.length();
	bool is_num = false;
	for (int i = 0; i < size; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			if (is_num)
			{
				num *= 10;
				num += s[i] - '0';
				continue;
			}
			else
			{
				num = s[i] - '0';
				is_num = true;
				continue;
			}
		}
		else
		{
			if (is_num)
			{
				nums.push(num);
				num = 0;
			}
			is_num = false;
			if (s[i] == '(' || cha.empty() || cha.top() == '(')
			{
				cha.push(s[i]);
				continue;
			}
			else
			{
				if ((a[cha.top()] < a[s[i]]) && s[i] != ')')
				{
					cha.push(s[i]);
					continue;
				}
				if (s[i] == ')')
				{
					while (cha.top() != '(')
					{
						char c = cha.top();
						cha.pop();
						double num1 = nums.top();
						nums.pop();
						double num2 = nums.top();
						nums.pop();
						nums.push(compute(c, num2, num1));
					}
					cha.pop();
				}
				else
				{
					char c = cha.top();
					cha.pop();
					double num1 = nums.top();
					nums.pop();
					double num2 = nums.top();
					nums.pop();
					nums.push(compute(c, num2, num1));
					cha.push(s[i]);
				}
			}
		}
	}
	if (is_num) nums.push(num);
	stack <char>ch;
	stack <double> nu;
	while (!cha.empty()&&(cha.top() == '*' || cha.top() == '/'))
	{
		char c = cha.top();
		cha.pop();
		double num1 = nums.top();
		nums.pop();
		double num2 = nums.top();
		nums.pop();
		nums.push(compute(c, num2, num1));
	}
	while (!cha.empty())
	{
		char tmp = cha.top();
		cha.pop();
		ch.push(tmp);
	}
	while (!nums.empty())
	{
		double tmp = nums.top();
		nums.pop();
		nu.push(tmp);
	}
	while (!ch.empty())
	{
		char c = ch.top();
		ch.pop();
		double num1 = nu.top();
		nu.pop();
		double num2 = nu.top();
		nu.pop();
		nu.push(compute(c, num1, num2));
	}
	return nu.top();
}
inline bool check(string s)
{
	map<char, double> a;
	a['+'] = 0;
	a['-'] = 0;
	a['*'] = 1;
	a['/'] = 1;
	int len = s.length();
	string cha;
	bool c = false;
	int f = -1;
	bool t = true;
	for (int i = 0; i < len; i++)
	{
		if (s[i] == '(') c = true;
		if (s[i]<'0' || s[i]>'9')
		{
			cha += s[i];
			if (f == -1 && s[i] != '(' && s[i] != ')') f = a[s[i]];
			else
			{
				if (f != a[s[i]]&&s[i]!='('&&s[i]!=')')
					t = false;
			}
		}
	}
	if (t && c) return false;
	if (cha == "/+(+)") return false;
	if (cha == "/-(+)") return false;
	if (cha == "/-(-)") return false;
	if (cha == "/+(-)") return false;
	if (cha == "*+(+)") return false;
	if (cha == "*-(+)") return false;
	if (cha == "*-(-)") return false;
	if (cha == "*+(-)") return false;
	if (cha == "++(*)") return false;
	if (cha == "--(*)") return false;
	if (cha == "+-(*)") return false;
	if (cha == "-+(*)") return false;
	if (cha == "+*(*)") return false;
	if (cha == "-*(*)") return false;
	if (cha == "++(/)") return false;

	if (cha == "(*)++") return false;
	if (cha == "(*)--") return false;
	if (cha == "(*)+-") return false;
	if (cha == "(*)-+") return false;
	if (cha == "(*)+*") return false;
	if (cha == "(*)-*") return false;
	
	if (cha == "(/)++") return false;
	if (cha == "(/)--") return false;
	if (cha == "(/)+-") return false;
	if (cha == "(/)-+") return false;
	if (cha == "(/)+*") return false;
	if (cha == "(/)-*") return false;

	if (cha == "(*)-(*)") return false;
	if (cha == "(/)-(*)") return false;
	if (cha == "(*)-(/)") return false;
	if (cha == "(/)-(/)") return false;
	if (cha == "(*)+(*)") return false;
	if (cha == "(*)+(/)") return false;
	if (cha == "(/)+(*)") return false;
	if (cha == "(/)+(/)") return false;
	if (cha == "(+)*(/)") return false;
	if (cha == "(-)*(/)") return false;
	if (cha == "(*)*(/)") return false;
	if (cha == "(/)*(/)") return false;

	if (cha == "(/)*(+)") return false;
	if (cha == "(/)*(-)") return false;
	if (cha == "(/)*(*)") return false;
	
	if (cha == "+*(/)") return false;
	if (cha == "-*(/)") return false;
	if (cha == "**(/)") return false;
	if (cha == "/*(/)") return false;

	if (cha == "(*)*(*)") return false;
	return true;
}
int count()
{
	ans.clear();
	bool again1 = true, again2 = true, again3 = true, again4 = true, again5 = true, again6 = true;
	bool again7 = true, again8 = true, again9 = true, again10 = true, again11 = true, again12 = true;
	bool again13 = true, again14 = true, again15 = true, again16 = true, again17 = true, again18 = true;
	bool again19 = true, again20 = true, again21 = true, again22 = true, again23 = true, again24 = true;
	map <int, char> cha;
	cha[1] = '+';
	cha[2] = '-';
	cha[3] = '*';
	cha[4] = '/';
	double res;
start:for (int i = 1; i <= 4; i++)
	{
		for (int j = 1; j <= 4; j++)
		{
			for (int k = 1; k <= 4; k++)
			{
				string s,a1,b1,c1,d1;
				stringstream  t;
				t << a;
				t >> a1;
				t.clear();
				t << b;
				t >> b1;
				t.clear();
				t << c;
				t >> c1;
				t.clear();
				t << d;
				t >> d1;
				s = a1;
				s += cha[i];
				s += b1;
				s += cha[j];
				s += c1;
				s += cha[k];
				s += d1;
				res = exp(s);
				if (check(s) && res > 24 - eps && res < 24 + eps) ans.insert(s);

				s.clear();
				s = '(';
				s += a1; 
				s += cha[i];
				s += b1;
				s += ')';
				s += cha[j];
				s += c1;
				s += cha[k];
				s += d1;
				res = exp(s);
				if (check(s) && res > 24 - eps && res < 24 + eps) ans.insert(s);
				
				s.clear();
				s = '(';
				s += a1;
				s += cha[i];
				s += b1;
				s += cha[j];
				s += c1;
				s += ')';
				s += cha[k];
				s += d1;
				res = exp(s);
				if (check(s) && res > 24 - eps && res < 24 + eps) ans.insert(s);

				s.clear();
				s = a1;
				s += cha[i];
				s += '(';
				s += b1;
				s += cha[j];
				s += c1;
				s += cha[k];
				s += d1;
				s += ')';
				res = exp(s);
				if (check(s) && res > 24 - eps && res < 24 + eps) ans.insert(s);

				s.clear();
				s = '(';
				s += a1;
				s += cha[i];
				s += b1;
				s += ')';
				s += cha[j];
				s += '(';
				s += c1;
				s += cha[k];
				s += d1;
				s += ')';
				res = exp(s);
				if (check(s) && res > 24 - eps && res < 24 + eps) ans.insert(s);
			}

	}
}
	  if (again1)//abdc
	  {
		  again1 = false;
		  swap(c, d);
		  goto start;

	  }
	  if (again2)//acbd
	  {
		  again2 = false;
		  swap(b, d);
		  goto start;

	  }
	  if (again3)//acdb
	  {
		  again3 = false;
		  swap(c, d);
		  goto start;

	  }
	  if (again4)//adcb
	  {
		  again4 = false;
		  swap(b, c);
		  goto start;

	  }
	  if (again5)//adbc
	  {
		  again5 = false;
		  swap(d, c);
		  goto start;

	  }
	  if (again6)//dabc
	  {
		  again6 = false;
		  swap(a, b);
		  goto start;

	  }
	  if (again7)//dacb
	  {
		  again7 = false;
		  swap(c, d);
		  goto start;
	  }
	  if (again8)//dbca
	  {
		  again8 = false;
		  swap(b, d);
		  goto start;
	  }
	  if (again9)//dbac
	  {
		  again9 = false;
		  swap(c, d);
		  goto start;
	  }
	  if (again10)//dcab
	  {
		  again10 = false;
		  swap(b, d);
		  goto start;
	  }
	  if (again11)//dcba
	  {
		  again11 = false;
		  swap(c, d);
		  goto start;
	  }
	  if (again12)//bcda
	  {
		  again12 = false;
		  swap(a, c);
		  goto start;
	  }
	  if (again13)//bcad
	  {
		  again13 = false;
		  swap(c, d);
		  goto start;
	  }
	  if (again14)//bcda
	  {
		  again14 = false;
		  swap(c, d);
		  goto start;
	  }
	  if (again15)//badc
	  {
		  again15 = false;
		  swap(b, d);
		  goto start;
	  }
	  if (again16)//bacd
	  {
		  again16 = false;
		  swap(c, d);
		  goto start;
	  }
	  if (again17)//bdca
	  {
		  again17 = false;
		  swap(b, d);
		  goto start;
	  }
	  if (again18)//bdac
	  {
		  again18 = false;
		  swap(c, d);
		  goto start;
	  }
	  if (again19)//cdab
	  {
		  again19 = false;
		  swap(a, d);
		  goto start;
	  }
	  if (again20)//cdba
	  {
		  again20 = false;
		  swap(c, d);
		  goto start;
	  }
	  if (again21)//cbda
	  {
		  again21 = false;
		  swap(c, b);
		  goto start;
	  }
	  if (again22)//cbad
	  {
		  again22 = false;
		  swap(c, d);
		  goto start;
	  }
	  if (again23)//cabd
	  {
		  again23 = false;
		  swap(c, b);
		  goto start;
	  }
	  if (again24)//cadb
	  {
		  again24 = false;
		  swap(c, d);
		  goto start;
	  }
	  return ans.size();
}
void cre()
{
	a = 0, b = 0, c = 0, d = 0;
	while (a == 0) a = rand() % 13;
	while (b == 0) b = rand() % 13;
	while (c == 0) c = rand() % 13;
	while (d == 0) d = rand() % 13;
}
int main()
{
	srand((unsigned)time(NULL));
	int dificulty;
	int cnt;
    system("clear");
	cout << "1:very easy \n2:easy \n3:diffcult \n4:very diffcult \n5:random" << endl;
	//cout << "The harder you choose, the more time it takes to generate the problem " << endl;
	cout << "input diffculty: ";
	cin >> dificulty;
	getchar();
	st:cout << "The problem is being generated,please wait...\n";
	cre();
	cnt = count();
	switch (dificulty)
	{
	case 1:
	{
		while (cnt <= 12)
		{			
			cre();
			cnt = count();
		}
		system("clear");
		cout << a << " " << b << " " << c << " " << d;
		break;
	}
	case 2:
	{
		while (cnt > 12 || cnt < 6)
		{
			cre();
			cnt = count();
		}
		system("clear");
		cout << a << " " << b << " " << c << " " << d;
		break;
	}
	case 3:
	{
		while (cnt >= 6 || cnt < 3)
		{
			cre();
			cnt = count();
		}
		system("clear");
		cout << a << " " << b << " " << c << " " << d;
		break;
	}
	case 4:
	{
		while (cnt > 3||cnt==0)
		{
			cre();
			cnt = count();
		}
		system("clear");
		cout << a <<" "<< b<<" "<< c<<" "<< d;
		break;
	}
	case 5:
	{
		while (cnt == 0)
		{
			cre();
			cnt = count();
		}
		system("clear");
		cout << a << " " << b << " " << c << " " << d;
		cout << "\n";
		if (cnt > 12) cout << "very easy" << endl;
		if (cnt <= 12 && cnt > 6) cout << "easy" << endl;
		if (cnt <= 6 && cnt > 3) cout << "diffcult" << endl;
		if (cnt <= 3) cout << "very diffcult" << endl;
		break;
	}
	default:
	{
		cout << "Selection is invalid!" << endl;
		goto st;
	}
	}
	cout << endl << "Press enter to see the answer" << endl;
	getchar();
	cout << ans.size() << " answers in total:" << endl;
	while (!ans.empty())
	{
		string anss = *ans.begin();
		cout << anss << endl;
		ans.erase(anss);
	}
	cout << endl << "Press enter to do the next problem" << endl;
	//system("pause");
	getchar();
	system("clear");
	goto st;
	return 0;
}