#include <bits/stdc++.h>
using namespace std;
 
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"
#define int long long
 
#define db(...) ZZ(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1> void ZZ(const char* name, Arg1&& arg1){std::cerr << name << " = " << arg1 << endl;}
template <typename Arg1, typename... Args>void ZZ(const char* names, Arg1&& arg1, Args&&... args)
{
	const char* comma = strchr(names + 1, ',');
	std::cerr.write(names, comma - names) << " = " << arg1;
	ZZ(comma, args...);
}
 
int32_t main()
{
	IOS;
	for(int i=1;i<=2;i++)
	{
		for(int j=1;j<=2;j++)
		{
			for(char ch='a';ch<='b';ch++)
			{
				db(i);
				db(i, j);
				db(i, j, ch);
			}
		}
	}
	return 0;
}
 
/* Output:
i = 1
i = 1, j = 1
i = 1, j = 1, ch = a
i = 1
i = 1, j = 1
i = 1, j = 1, ch = b
i = 1
i = 1, j = 2
i = 1, j = 2, ch = a
i = 1
i = 1, j = 2
i = 1, j = 2, ch = b
i = 2
i = 2, j = 1
i = 2, j = 1, ch = a
i = 2
i = 2, j = 1
i = 2, j = 1, ch = b
i = 2
i = 2, j = 2
i = 2, j = 2, ch = a
i = 2
i = 2, j = 2
i = 2, j = 2, ch = b
*/