#include<bits/stdc++.h>
#pragma GCC optimize(2)
using namespace std;
int t , n , a[5005];
inline bool zero(int l , int r)
{
	for(int i = l ; i <= r ; i++)
	{
		if(a[i] == 0)
		{
			return 1;
		}
	}
	return 0;
}
int main()
{
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while(t--)
	{
		cin >> n;
		for(int i = 1 ; i <= n ; i++)
		{
			cin >> a[i];
		}
		if(zero(n - 1 , n) && zero(1 , n - 2))
		{
			cout << "3\n" << n - 1 << ' ' << n << "\n1 " << n - 2 << "\n1 2\n";
		}
		else if(zero(n - 1 , n) && !zero(1 , n - 2))
		{
			cout << "2\n" << n - 1 << ' ' << n << "\n1 " << n - 1 << '\n';
		}
		else if(!zero(n - 1 , n) && zero(1 , n - 2))
		{
			cout << "2\n1 " << n - 2 << "\n1 3\n";
		}
		else
		{
			cout << "1\n1 " << n << '\n';
		}
	}
	return 0;
}
