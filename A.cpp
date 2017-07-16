#include <iostream>
#include <queue>
#include <map>
#include <list>
#include <vector>
#include <string>
#include <stack>
#include <limits>
#include <climits>
#include <cassert>
#include <fstream>
#include <cstring>
#include <cmath>
#include <bitset>
#include <iomanip>
#include <algorithm>
#include <functional>
#include <cstdio>
#include <ciso646>
#include <set>
#include <array>
#include <unordered_map>

using namespace std;

#define FOR(i,a,b) for (int i=(a);i<(b);i++)
#define RFOR(i,a,b) for (int i=(b)-1;i>=(a);i--)
#define REP(i,n) for (int i=0;i<(n);i++)
#define RREP(i,n) for (int i=(n)-1;i>=0;i--)

#define inf 0x3f3f3f3f
#define PB push_back
#define MP make_pair
#define ALL(a) (a).begin(),(a).end()
#define SET(a,c) memset(a,c,sizeof a)
#define CLR(a) memset(a,0,sizeof a)
#define VS vector<string>
#define VI vector<ll>
#define DEBUG(x) cout<<#x<<": "<<x<<endl
#define MIN(a,b) (a>b?b:a)
#define MAX(a,b) (a>b?a:b)
#define pi 2*acos(0.0)
#define INFILE() freopen("in0.txt","r",stdin)
#define OUTFILE()freopen("out0.txt","w",stdout)
#define ll long long
#define ull unsigned long long
#define pii pair<ll,ll>
#define pcc pair<char,char>
#define pic pair<ll,char>
#define pci pair<char,ll>
#define eps 1e-14
#define FST first
#define SEC second
#define SETUP cin.tie(0), ios::sync_with_stdio(false), cout << setprecision(15)

namespace {
	struct input_returnner {
		ll N; input_returnner(ll N_ = 0) :N(N_) {}
		template<typename T> operator vector<T>() const { vector<T> res(N); for (auto &a : res) cin >> a; return std::move(res); }
		template<typename T> operator T() const { T res; cin >> res; return res; }
		template<typename T> T operator - (T right) { return T(input_returnner()) - right; }
		template<typename T> T operator + (T right) { return T(input_returnner()) + right; }
		template<typename T> T operator * (T right) { return T(input_returnner()) * right; }
		template<typename T> T operator / (T right) { return T(input_returnner()) / right; }
		template<typename T> T operator << (T right) { return T(input_returnner()) << right; }
		template<typename T> T operator >> (T right) { return T(input_returnner()) >> right; }
	};
	template<typename T> input_returnner in() { return in<T>(); }
	input_returnner in() { return input_returnner(); }
	input_returnner in(ll N) { return std::move(input_returnner(N)); }
}

const ll MOD = 1e9 + 7;

struct ModInt {
	ll v = 0;
	ModInt() {}
	template<class T> ModInt(const T& right) {
		v = right;
		if (v >= 0) v %= MOD;
		else v += ((-v) / MOD + 1)*MOD;
		v %= MOD;
	}
	void operator = (const ModInt& right) { v = right.v; }
	template<class T> void operator = (const T& right) {
		v = right;
		if (v >= 0) v %= MOD;
		else v = v += ((-v) / MOD + 1)*MOD;
		v %= MOD;
	}

	ModInt operator + (const ModInt& right) { return (v + right.v) % MOD; }
	ModInt operator - (const ModInt& right) { return (MOD - (v - right.v)); }
	ModInt operator * (const ModInt& right) { return (v * right.v) % MOD; }
	ModInt operator / (const ModInt& right) { return v / right.v; }

	void operator += (const ModInt& right) { v = (v + right.v) % MOD; }
	void operator -= (const ModInt& right) { v = (MOD - (v - right.v)); }
	void operator *= (const ModInt& right) { v = (v* right.v) % MOD; }
	void operator /= (const ModInt& right) { v = v / right.v; }

	bool operator == (const ModInt& right) { return v == right.v; }
};

ostream& operator << (ostream& os, const ModInt& value) {
	os << value.v;
	return os;
}

string YN[] = { "NO", "YES" };

void solve();
/// ---template---


// x^n % mod
// O(log n)
template<typename T>
T mod_pow(T x, T n, T mod) {
	T res = 1;
	while (n > 0) {
		if (n & 1) res = (res * x) % mod;
		x = (x*x) %mod;
		n >>= 1;
	}
	return res;
}

template<class T>
struct fkmat {
	vector<vector<T> > mat;

	size_t getRowCount() const { return mat.size(); }
	size_t getColomnCount() const { return mat[0].size(); }
	size_t size() const { return mat.size(); }

	fkmat(size_t size_row,size_t size_colomn):mat(size_row, vector<T>(size_colomn)) {}

	vector<T>& operator [] (const int index) { return mat[index]; }

	//Identity matrix
	fkmat<T> Identity() {
		for (int i = 0; i < mat.size(); ++i) {
			mat[i][i] = 1;
		}
		return *this;
	}

	void operator = (const fkmat<T>& right) {
		mat.clear();
		mat.resize(right.size());
		for (int i = 0; i < right.size(); ++i) {
			mat[i] = right.mat[i];
		}
	}

	fkmat<T> operator + (const fkmat<T>& right) {
		fkmat<T> res(getRowCount(), getColomnCount());

		for (int i = 0; i < mat.size(); ++i) {
			for (int j = 0; j < mat[i].size(); ++j) {
				res[i][j] = mat[i][j] + right.mat[i][j];
			}
		}
		
		return res;
	}

	fkmat<T> operator - (const fkmat<T>& right) {
		fkmat<T> res(getRowCount(), getColomnCount());

		for (int i = 0; i < mat.size(); ++i) {
			for (int j = 0; j < mat[i].size(); ++j) {
				res[i][j] = mat[i][j] - right.mat[i][j];
			}
		}
		
		return res;
	}

	fkmat<T> operator * (const fkmat<T>& right) {
		fkmat<T> res(getRowCount(), getColomnCount());
		assert(getRowCount() == right.getColomnCount());

		for (int r = 0; r < getRowCount(); ++r) {
			for (int c = 0; c < right.getColomnCount(); ++c) {
				for (int k = 0; k < getColomnCount(); ++k) {
					res[r][c] += mat[r][k] * right.mat[k][c];
				}
			}
		}

		return res;
	}

	void operator += (const fkmat<T>& right) {
		for (int i = 0; i < mat.size(); ++i) {
			for (int j = 0; j < mat[i].size(); ++j) {
				mat[i][j] += right.mat[i][j];
			}
		}
	}
	
	void operator -= (const fkmat<T>& right) {
		for (int i = 0; i < mat.size(); ++i) {
			for (int j = 0; j < mat[i].size(); ++j) {
				mat[i][j] -= right.mat[i][j];
			}
		}
	}

	void operator *= (const fkmat<T>& right) {
		*this = *this * right;
	}

	//power n
	void pow(long long n, fkmat<T>* dst) {
		dst->Identity();
		fkmat<T> x(getRowCount(), getColomnCount());
		x.mat = mat;
		while (n > 0) {
			if (n & 1) *dst = *dst * x;
			x *= x;
			n >>= 1;
		}
	}

	//power n
	void pow(long long n) {
		fkmat<T> res(getRowCount(), getColomnCount());
		res.Identity();
		fkmat<T> x(getRowCount(), getColomnCount());
		x.mat = mat;
		while (n > 0) {
			if (n & 1) res = res * x;
			x *= x;
			n >>= 1;
		}
		mat = res.mat;
	}

	void print() {
		for (size_t i = 0; i < mat.size(); ++i) {
			for (size_t j = 0; j < mat[i].size(); ++j) {
				cout << mat[i][j] << " ";
			}
			cout << endl;
		}
	}
};

signed main(void) {
	SETUP;
	solve();
#ifdef _DEBUG
	system("pause");
#endif
	return 0;
}

void solve() {
	fkmat<ModInt> m(2, 2);
	m[0][0] = 1;
	m[0][1] = 1;
	m[1][0] = 1;

	long long a = mod_pow<long long>(1241230, 1230124, 1e9 + 7);
	m.pow(a);
	cout << a << endl;
	cout << m[0][1] << endl;
}