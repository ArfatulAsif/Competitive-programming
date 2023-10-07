UVA - 13028

// Intermediary
// Young kid on the block
// AIAsif try's Continuing the journey
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#define endl "\n"
// #define int long long int  [don't use this]
#define ordered_set tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>

// Just kisu jinish mone rakhte hobe
//  1. BigInteger negetive(-) number support kore na
//  2. BigInteger P = something . erokom initialize kora jabe na
//  3. BigInteger P;  P = .. erokom korte hobe
//  aro kisu halka palta change . like function return Big_binexp(...) erokom na dia nicher moto dite hoy
//  esob sara mutamuti Normal integer er moto sob operation kora jay

class BigInteger
{
public:
        string digits;

        // Constructors:
        BigInteger(unsigned long long n = 0);
        BigInteger(string &);
        BigInteger(const char *);
        BigInteger(BigInteger &);

        // Helper Functions:
        friend void divide_by_2(BigInteger &a);
        friend bool Null(const BigInteger &);
        friend int Length(const BigInteger &);
        int operator[](const int) const;

        /* * * * Operator Overloading * * * */

        // Direct assignment
        BigInteger &operator=(const BigInteger &);

        // Post/Pre - Incrementation
        BigInteger &operator++();
        BigInteger operator++(int temp);
        BigInteger &operator--();
        BigInteger operator--(int temp);

        // Addition and Subtraction
        friend BigInteger &operator+=(BigInteger &, const BigInteger &);
        friend BigInteger operator+(const BigInteger &, const BigInteger &);
        friend BigInteger operator-(const BigInteger &, const BigInteger &);
        friend BigInteger &operator-=(BigInteger &, const BigInteger &);

        // Comparison operators
        friend bool operator==(const BigInteger &, const BigInteger &);
        friend bool operator!=(const BigInteger &, const BigInteger &);
        friend bool operator>(const BigInteger &, const BigInteger &);
        friend bool operator>=(const BigInteger &, const BigInteger &);
        friend bool operator<(const BigInteger &, const BigInteger &);
        friend bool operator<=(const BigInteger &, const BigInteger &);

        // Multiplication and Division
        friend BigInteger &operator*=(BigInteger &, const BigInteger &);
        friend BigInteger operator*(const BigInteger &, const BigInteger &);
        friend BigInteger &operator/=(BigInteger &, const BigInteger &);
        friend BigInteger operator/(const BigInteger &, const BigInteger &);

        // Modulo
        friend BigInteger operator%(const BigInteger &, const BigInteger &);
        friend BigInteger &operator%=(BigInteger &, const BigInteger &);

        // Power Function
        friend BigInteger &operator^=(BigInteger &, const BigInteger &);
        friend BigInteger operator^(BigInteger &, const BigInteger &);

        // Square Root Function
        friend BigInteger sqrt(BigInteger &a);

        // OUTPUT
        friend ostream &operator<<(ostream &, const BigInteger &);

        // Others
        friend BigInteger NthCatalan(int n);
        friend BigInteger NthFibonacci(int n);
        friend BigInteger Factorial(int n);
};

BigInteger::BigInteger(string &s)
{
        digits = "";
        int n = s.size();
        for (int i = n - 1; i >= 0; i--)
        {
                if (!isdigit(s[i]))
                        throw("ERROR");
                digits.push_back(s[i] - '0');
        }
}

BigInteger::BigInteger(unsigned long long nr)
{
        do
        {
                digits.push_back(nr % 10);
                nr /= 10;
        } while (nr);
}
BigInteger::BigInteger(const char *s)
{
        digits = "";
        for (int i = strlen(s) - 1; i >= 0; i--)
        {
                if (!isdigit(s[i]))
                        throw("ERROR");
                digits.push_back(s[i] - '0');
        }
}
BigInteger::BigInteger(BigInteger &a)
{
        digits = a.digits;
}

bool Null(const BigInteger &a)
{
        if (a.digits.size() == 1 && a.digits[0] == 0)
                return true;
        return false;
}
int Length(const BigInteger &a)
{
        return a.digits.size();
}
int BigInteger::operator[](const int index) const
{
        if (digits.size() <= index || index < 0)
                throw("ERROR");
        return digits[index];
}
bool operator==(const BigInteger &a, const BigInteger &b)
{
        return a.digits == b.digits;
}
bool operator!=(const BigInteger &a, const BigInteger &b)
{
        return !(a == b);
}
bool operator<(const BigInteger &a, const BigInteger &b)
{
        int n = Length(a), m = Length(b);
        if (n != m)
                return n < m;
        while (n--)
                if (a.digits[n] != b.digits[n])
                        return a.digits[n] < b.digits[n];
        return false;
}
bool operator>(const BigInteger &a, const BigInteger &b)
{
        return b < a;
}
bool operator>=(const BigInteger &a, const BigInteger &b)
{
        return !(a < b);
}
bool operator<=(const BigInteger &a, const BigInteger &b)
{
        return !(a > b);
}

BigInteger &BigInteger::operator=(const BigInteger &a)
{
        digits = a.digits;
        return *this;
}

BigInteger &BigInteger::operator++()
{
        int i, n = digits.size();
        for (i = 0; i < n && digits[i] == 9; i++)
                digits[i] = 0;
        if (i == n)
                digits.push_back(1);
        else
                digits[i]++;
        return *this;
}
BigInteger BigInteger::operator++(int temp)
{
        BigInteger aux;
        aux = *this;
        ++(*this);
        return aux;
}

BigInteger &BigInteger::operator--()
{
        if (digits[0] == 0 && digits.size() == 1)
                throw("UNDERFLOW");
        int i, n = digits.size();
        for (i = 0; digits[i] == 0 && i < n; i++)
                digits[i] = 9;
        digits[i]--;
        if (n > 1 && digits[n - 1] == 0)
                digits.pop_back();
        return *this;
}
BigInteger BigInteger::operator--(int temp)
{
        BigInteger aux;
        aux = *this;
        --(*this);
        return aux;
}

BigInteger &operator+=(BigInteger &a, const BigInteger &b)
{
        int t = 0, s, i;
        int n = Length(a), m = Length(b);
        if (m > n)
                a.digits.append(m - n, 0);
        n = Length(a);
        for (i = 0; i < n; i++)
        {
                if (i < m)
                        s = (a.digits[i] + b.digits[i]) + t;
                else
                        s = a.digits[i] + t;
                t = s / 10;
                a.digits[i] = (s % 10);
        }
        if (t)
                a.digits.push_back(t);
        return a;
}
BigInteger operator+(const BigInteger &a, const BigInteger &b)
{
        BigInteger temp;
        temp = a;
        temp += b;
        return temp;
}

BigInteger &operator-=(BigInteger &a, const BigInteger &b)
{
        if (a < b)
                throw("UNDERFLOW");
        int n = Length(a), m = Length(b);
        int i, t = 0, s;
        for (i = 0; i < n; i++)
        {
                if (i < m)
                        s = a.digits[i] - b.digits[i] + t;
                else
                        s = a.digits[i] + t;
                if (s < 0)
                        s += 10,
                            t = -1;
                else
                        t = 0;
                a.digits[i] = s;
        }
        while (n > 1 && a.digits[n - 1] == 0)
                a.digits.pop_back(),
                    n--;
        return a;
}
BigInteger operator-(const BigInteger &a, const BigInteger &b)
{
        BigInteger temp;
        temp = a;
        temp -= b;
        return temp;
}

BigInteger &operator*=(BigInteger &a, const BigInteger &b)
{
        if (Null(a) || Null(b))
        {
                a = BigInteger();
                return a;
        }
        int n = a.digits.size(), m = b.digits.size();
        vector<int> v(n + m, 0);
        for (int i = 0; i < n; i++)
                for (int j = 0; j < m; j++)
                {
                        v[i + j] += (a.digits[i]) * (b.digits[j]);
                }
        n += m;
        a.digits.resize(v.size());
        for (int s, i = 0, t = 0; i < n; i++)
        {
                s = t + v[i];
                v[i] = s % 10;
                t = s / 10;
                a.digits[i] = v[i];
        }
        for (int i = n - 1; i >= 1 && !v[i]; i--)
                a.digits.pop_back();
        return a;
}
BigInteger operator*(const BigInteger &a, const BigInteger &b)
{
        BigInteger temp;
        temp = a;
        temp *= b;
        return temp;
}

BigInteger &operator/=(BigInteger &a, const BigInteger &b)
{
        if (Null(b))
                throw("Arithmetic Error: Division By 0");
        if (a < b)
        {
                a = BigInteger();
                return a;
        }
        if (a == b)
        {
                a = BigInteger(1);
                return a;
        }
        int i, lgcat = 0, cc;
        int n = Length(a), m = Length(b);
        vector<int> cat(n, 0);
        BigInteger t;
        for (i = n - 1; t * 10 + a.digits[i] < b; i--)
        {
                t *= 10;
                t += a.digits[i];
        }
        for (; i >= 0; i--)
        {
                t = t * 10 + a.digits[i];
                for (cc = 9; cc * b > t; cc--)
                        ;
                t -= cc * b;
                cat[lgcat++] = cc;
        }
        a.digits.resize(cat.size());
        for (i = 0; i < lgcat; i++)
                a.digits[i] = cat[lgcat - i - 1];
        a.digits.resize(lgcat);
        return a;
}
BigInteger operator/(const BigInteger &a, const BigInteger &b)
{
        BigInteger temp;
        temp = a;
        temp /= b;
        return temp;
}

BigInteger &operator%=(BigInteger &a, const BigInteger &b)
{
        if (Null(b))
                throw("Arithmetic Error: Division By 0");
        if (a < b)
        {
                return a;
        }
        if (a == b)
        {
                a = BigInteger();
                return a;
        }
        int i, lgcat = 0, cc;
        int n = Length(a), m = Length(b);
        vector<int> cat(n, 0);
        BigInteger t;
        for (i = n - 1; t * 10 + a.digits[i] < b; i--)
        {
                t *= 10;
                t += a.digits[i];
        }
        for (; i >= 0; i--)
        {
                t = t * 10 + a.digits[i];
                for (cc = 9; cc * b > t; cc--)
                        ;
                t -= cc * b;
                cat[lgcat++] = cc;
        }
        a = t;
        return a;
}
BigInteger operator%(const BigInteger &a, const BigInteger &b)
{
        BigInteger temp;
        temp = a;
        temp %= b;
        return temp;
}

BigInteger &operator^=(BigInteger &a, const BigInteger &b)
{
        BigInteger Exponent, Base(a);
        Exponent = b;
        a = 1;
        while (!Null(Exponent))
        {
                if (Exponent[0] & 1)
                        a *= Base;
                Base *= Base;
                divide_by_2(Exponent);
        }
        return a;
}
BigInteger operator^(BigInteger &a, BigInteger &b)
{
        BigInteger temp(a);
        temp ^= b;
        return temp;
}

void divide_by_2(BigInteger &a)
{
        int add = 0;
        for (int i = a.digits.size() - 1; i >= 0; i--)
        {
                int digit = (a.digits[i] >> 1) + add;
                add = ((a.digits[i] & 1) * 5);
                a.digits[i] = digit;
        }
        while (a.digits.size() > 1 && !a.digits.back())
                a.digits.pop_back();
}

BigInteger sqrt(BigInteger &a)
{
        BigInteger left(1), right(a), v(1), mid, prod;
        divide_by_2(right);
        while (left <= right)
        {
                mid += left;
                mid += right;
                divide_by_2(mid);
                prod = (mid * mid);
                if (prod <= a)
                {
                        v = mid;
                        ++mid;
                        left = mid;
                }
                else
                {
                        --mid;
                        right = mid;
                }
                mid = BigInteger();
        }
        return v;
}

BigInteger NthCatalan(int n)
{
        BigInteger a(1), b;
        for (int i = 2; i <= n; i++)
                a *= i;
        b = a;
        for (int i = n + 1; i <= 2 * n; i++)
                b *= i;
        a *= a;
        a *= (n + 1);
        b /= a;
        return b;
}

BigInteger NthFibonacci(int n)
{
        BigInteger a(1), b(1), c;
        if (!n)
                return c;
        n--;
        while (n--)
        {
                c = a + b;
                b = a;
                a = c;
        }
        return b;
}

BigInteger Factorial(int n)
{
        BigInteger f(1);
        for (int i = 2; i <= n; i++)
                f *= i;
        return f;
}

ostream &operator<<(ostream &out, const BigInteger &a)
{
        for (int i = a.digits.size() - 1; i >= 0; i--)
                cout << (short)a.digits[i];
        return cout;
}

BigInteger Big_binexp(BigInteger a, BigInteger b, BigInteger M) // For CP : normally use int else use [BigInteger Big_binexp(BigInteger a, BigInteger b , BigInteger M)]
{

        BigInteger ans("1");

        BigInteger zero("0");

        while (b > zero)
        {
                if (b % BigInteger("2") == BigInteger("1"))
                {

                        ans = (ans * a) % M;
                }

                b /= BigInteger("2");

                a = (a * a) % M;
        }
        return ans;
}

BigInteger Smart_binexp(BigInteger a, BigInteger b, BigInteger M) // For this theorem M need to be a prime
{

        // a^b mod m = (a mod m)^b mod m
        // if m is a prime , we can reduce b = b%(m-1)   : Farmatt little theorem

        a = a % M;
        b = b % (M - 1);

        BigInteger ans;

        ans = Big_binexp(a, b, M);

        return ans;
}



int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);

        int t;
        cin >> t;

        for (int tt = 1; tt <= t; tt++)
        {
                string s;
                cin >> s;

                if (s == "0")
                {
                        cout << "Case " << tt << ": " << 1 << endl;
                        continue;
                }

                BigInteger a(s);

                a--;

                BigInteger three("3");

                BigInteger M("1000000007");

                BigInteger P; // BigInteger P = Big_binexp(three , a , M); lekha jabe na

                P = Smart_binexp(three, a, M); // P = Big_binexp(three , a , M); dia TLE khabe

                BigInteger m1, m2;
                m1 = (2 * P) % M;

                m2 = (P + M - 1) % M;

                m2 = (m2 * 500000004) % M;

                BigInteger ans;
                ans = (M + m1 - m2) % M; // neg number is not supported by BigInteger

                cout << "Case " << tt << ": " << ans << endl;
        }

        return 0;
}
