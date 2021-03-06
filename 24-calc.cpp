#include<iostream>
#include<string>
#include<stack>
#include<map>
#include<sstream>
#include<set>
#pragma GCC optimize(3,"Ofast","inline")
#define eps 0.001
using namespace std;
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
inline double exp(string s)//�������ʽs��ֵ
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
	/*len = cha.length();
	for (int i = 0; i < cha.length()-1; i++)
	{
		if (cha[i] == ')' && (cha[i + 1] == '+' || cha[i + 1] == '-') && ((i > 0 ? cha[i - 1] == '*' || cha[i - 1] == '/' : 1) && (i < len - 4 ? cha[i + 3] != '*' && cha[i + 3] != '/' : 1)))
			return false;
		if (cha[i] == '(' && (cha[i + 1] == '*' || cha[i + 1] == '/') && (i > 0 ? cha[i - 1] != '/' : 1))
			return false;
		if (cha[i] == ')' && (a[cha[i - 1]] == a[cha[i + 1]]))
			return false;
	}*/
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
	// if (cha == "*(+(+))") return false;
	// if (cha == "*(+(-))") return false;
	// if (cha == "(+(+))*") return false;
	// if (cha == "(+(-))*") return false;
	// if (cha == "(+(+))/") return false;
	// if (cha == "(+(-))/") return false;
	// if (cha == "((+)+)*") return false;
	// if (cha == "((-)+)*") return false;
	// if (cha == "((+)+)/") return false;
	// if (cha == "((-)+)/") return false;
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
int main()
{
	set <string> ans;
	double a, b, c, d;
	bool again1 = true, again2 = true, again3 = true, again4 = true, again5 = true, again6 = true;
	bool again7 = true, again8 = true, again9 = true, again10 = true, again11 = true, again12 = true;
	bool again13 = true, again14 = true, again15 = true, again16 = true, again17 = true, again18 = true;
	bool again19 = true, again20 = true, again21 = true, again22 = true, again23 = true, again24 = true;
	cin >> a >> b >> c >> d;
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
				// if (check(s)&&exp(s) == 24) ans.insert(s);
				// s.clear();
				// s = a1;
				// s += cha[i];
				// s += '(';
				// s += b1;
				// s += cha[j];
				// s += c1;
				// s += ')';
				// s += cha[k];
				// s += d1;
				// if (check(s)&&exp(s) == 24) ans.insert(s);
				// s.clear();
				// s = a1;
				// s += cha[i];
				// s += b1;
				// s += cha[j];
				// s += '(';
				// s += c1;
				// s += cha[k];
				// s += d1;
				// s+=')';
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
				// s.clear();
				// s = a1;
				// s += cha[i];
				// s += '(';
				// s += b1;
				// s += cha[j];
				// s += c1;
				// s += cha[k];
				// s += d1;
				// s += ')';
				// if (check(s)&&exp(s) == 24) ans.insert(s);
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
				// s.clear();
				// s = a1;
				// s += cha[i];
				// s += '(';
				// s += b1;
				// s += cha[j];
				// s += '(';
				// s += c1;
				// s += cha[k];
				// s += d1;
				// s += "))";
				// if (check(s)&&exp(s) == 24) ans.insert(s);
				// s.clear();
				// s = "((";
				// s += a1;
				// s += cha[i];
				// s += b1;
				// s += ')';
				// s += cha[j];
				// s += c1;
				// s += ')';
				// s += cha[k];
				// s += d1;
				// if (check(s) && exp(s) == 24) ans.insert(s);
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
	  if (ans.empty())
	  {
		  cout << "Answers no found!" << "\n";
		  return 0;
	  }
	  cout << ans.size() << " answers have been found:" << endl;
	  while (!ans.empty())
	  {
		  string s = *ans.begin();
		  cout << s << endl;
		  ans.erase(s);
	  }
	return 0;
}