#include <iostream>
#include <cmath>
#include <string>
#define ll long long 
using namespace std;
//A
//int main()
//{
//	ll a;
//	cin >> a;
//	if (a == 1) {
//		cout << "Yes";exit(0);
//}	for (ll i = 2;i <= sqrt(a);i++)
//		if (a % i == 0) { cout << "No";exit(0); }
//	cout << "Yes";
//}
//B
//
//int main()
//{
//	int gg = 0;
//	string s;
//	cin >> s;
//	for (int i = 1;i <= s.length();i++)
//	{
//		if (s[i] != s[i - 1]) { gg++; break; }
//	}
//	if (gg == 0 || s.length() == 1) { cout << "-1 -1"; exit(0); }
//
//
//}
//C
//ll seed;
//ll rnd() {
//	ll tv = 2;
//	tv = pow(tv, 32);
//	seed = (seed * 1103515245 + 12345) % tv;return seed;
//}
//void shuffle(ll* a, ll s,ll size)
//{
//	seed = s;
//	for (ll i = 0;i < size - 1;i++)
//		swap(a[i],a[rnd()%(i+1)]);
//}
//int main()
//{
//	ll size;
//	ll* a;
//	cin >> size;
//	a = (ll*)malloc(size * sizeof(ll));
//	for (ll i = 0;i < size;i++)
//		cin >> a[i];
//	shuffle(a, rnd(), size);
//	shuffle(a, rnd(), size);
//	for (ll i = 0;i < size;i++)
//		cout << a[i] << " ";
//}
////D
//int main()
//{
//	ll t;
//	cin >> t;
//	while (t > 0)
//	{
//		ll a, b,a1,b1,a2,b2;
//		cin >> a >> b;	
//		{ a1 = a / 10;a2 = a % 10; };
//		{ b1 = b / 10;b2 = b % 10; };
//		if (a1 * 10 + a2!=a+b && a1 * 10 + a2<=50) cout << a1 * 10 + a2;else
//			if (a1 * 10 + b1!=a+b && a1 * 10 + b1<=50) cout << a1 * 10 + b1;else
//				if (a1 * 10 + b2!=a+b && a1 * 10 + b2<=50) cout << a1 * 10 + b2;else
//					if (a2 * 10 + a1 != a + b && a2 * 10 + a1 <= 50) cout << a2 * 10 + a1;else
//						if (a2 * 10 + b1 != a + b && a2 * 10 + b1 <= 50) cout << a2 * 10 + b1;else
//							if (a2 * 10 + b2 != a + b && a2 * 10 + b2 <= 50) cout << a2 * 10 + b2;else
//								if (b1 * 10 + a2 != a + b && b1 * 10 + a2 <= 50) cout << b1 * 10 + a2;else
//									if (b1 * 10 + a1 != a + b && b1 * 10 + a1 <= 50) cout << b1 * 10 + a1;else
//										if (b1 * 10 + b2 != a + b && b1 * 10 + b2 <= 50) cout << b1 * 10 + b2;else
//											if (b2 * 10 + a1 != a + b && b2 * 10 + a1 <= 50) cout << b2 * 10 + a1;else
//												if (b2 * 10 + b1 != a + b && b2 * 10 + b1 <= 50) cout << b2 * 10 + b1;else
//													if (b2 * 10 + a2 != a + b && b2 * 10 + a2 <= 50) cout << b2 * 10 + a2;
//		t--;
//	}	
//}
//E
int main()
{
	char s[500],c[500];
	gets_s(s);
	ll size = 0;
	while (s[size] != '\0')
	{
		size++;
	}
	ll size2=0;
	for(ll s2=0;s2<size;s2++)
	{
		if (s[s2] != '?' && s[s2] != '*') {
			c[size2] = s[s2];size2++;
		}
	}




}