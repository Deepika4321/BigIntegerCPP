#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class BigInt {
private:
    string digits;

public:
    BigInt() {
        digits = "0";
    }

    BigInt(const string& num) {
        int i = 0;
        while (i < num.size() - 1 && num[i] == '0')
            i++;
        digits = num.substr(i);
    }

    // OUTPUT
    friend ostream& operator<<(ostream& out, const BigInt& b) {
        out << b.digits;
        return out;
    }

    // COMPARISON
    bool operator<(const BigInt& b) const {
        if (digits.length() != b.digits.length())
            return digits.length() < b.digits.length();
        return digits < b.digits;
    }

    bool operator==(const BigInt& b) const {
        return digits == b.digits;
    }

    // ADDITION
    BigInt operator+(const BigInt& b) const {
        string s1 = digits;
        string s2 = b.digits;

        if (s1.length() < s2.length())
            swap(s1, s2);

        int carry = 0;
        string result = "";

        int i = s1.length() - 1;
        int j = s2.length() - 1;

        while (i >= 0 || j >= 0 || carry) {
            int sum = carry;
            if (i >= 0) sum += s1[i--] - '0';
            if (j >= 0) sum += s2[j--] - '0';

            result.push_back((sum % 10) + '0');
            carry = sum / 10;
        }

        reverse(result.begin(), result.end());
        return BigInt(result);
    }

    // SUBTRACTION (this >= b)
    BigInt operator-(const BigInt& b) const {
        string s1 = digits;
        string s2 = b.digits;

        int i = s1.length() - 1;
        int j = s2.length() - 1;
        int borrow = 0;
        string result = "";

        while (i >= 0) {
            int diff = (s1[i] - '0') - borrow;
            if (j >= 0)
                diff -= (s2[j] - '0');

            if (diff < 0) {
                diff += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }

            result.push_back(diff + '0');
            i--;
            j--;
        }

        while (result.size() > 1 && result.back() == '0')
            result.pop_back();

        reverse(result.begin(), result.end());
        return BigInt(result);
    }

    // MULTIPLICATION
    BigInt operator*(const BigInt& b) const {
        int n = digits.size();
        int m = b.digits.size();

        string result(n + m, '0');

        for (int i = n - 1; i >= 0; i--) {
            int carry = 0;
            for (int j = m - 1; j >= 0; j--) {
                int mul = (digits[i] - '0') * (b.digits[j] - '0');
                int sum = mul + (result[i + j + 1] - '0') + carry;

                result[i + j + 1] = (sum % 10) + '0';
                carry = sum / 10;
            }
            result[i] += carry;
        }

        int idx = 0;
        while (idx < result.size() - 1 && result[idx] == '0')
            idx++;

        return BigInt(result.substr(idx));
    }
};

/* ---------- EXTRA FEATURES ---------- */

BigInt factorial(int n) {
    BigInt result("1");
    for (int i = 2; i <= n; i++) {
        result = result * BigInt(to_string(i));
    }
    return result;
}

BigInt fibonacci(int n) {
    if (n == 0) return BigInt("0");
    if (n == 1) return BigInt("1");

    BigInt a("0"), b("1"), c;
    for (int i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

BigInt power(BigInt base, int exp) {
    BigInt result("1");
    while (exp > 0) {
        if (exp % 2 == 1)
            result = result * base;
        base = base * base;
        exp /= 2;
    }
    return result;
}

int main() {
    BigInt a("123456789123456789");
    BigInt b("987654321987654321");

    cout << "Addition = " << a + b << endl;
    cout << "Multiplication = " << a * b << endl;

    cout << "Factorial(50) = " << factorial(50) << endl;
    cout << "Fibonacci(200) = " << fibonacci(200) << endl;
    cout << "2^100 = " << power(BigInt("2"), 100) << endl;

    return 0;
}
