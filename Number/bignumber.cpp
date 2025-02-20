#include <bits/stdc++.h>
using namespace std;

class Number {

    private:
    vector<int> digits; 
    int sign;   // 1 for positive, -1 for negatives

    vector<int> addVectors(const vector<int>& a, const vector<int>& b) {
        vector<int> res;
        int carry = 0;
        int n = max(a.size(), b.size());
        for (int i = 0; i < n or carry; i++) {
            int d1 = (i < a.size() ? a[i] : 0);
            int d2 = (i < b.size() ? b[i] : 0);
            int sum = d1 + d2 + carry;
            res.push_back(sum % 10);
            carry = sum / 10;
        }
        return res;
    }
    
    // Assumes that a >= b
     vector<int> subtractVectors(const vector<int>& a, const vector<int>& b) {
        vector<int> res = a;
        int carry = 0;
        for (int i = 0; i < b.size() or carry; i++) {
            int d1 = res[i];
            int d2 = (i < b.size() ? b[i] : 0);
            int sub = d1 - d2 - carry;
            if (sub < 0)
            {
                sub += 10;
                carry = 1;
            } 
            else carry = 0;
            res[i] = sub;
        }
        while (res.size() > 1 && res.back() == 0)
            res.pop_back();
        return res;
    }
    
    // Compare the absolute values of two Numbers
    // Returns 1 if |this| > |other|, -1 if |this| < |other|, or 0 if equal
    int compareAbs(const Number &other) const {
        if (digits.size() != other.digits.size())
            return digits.size() > other.digits.size() ? 1 : -1;
        for (int i = digits.size() - 1; i >= 0; i--) {
            if (digits[i] != other.digits[i])
                return digits[i] > other.digits[i] ? 1 : -1;
        }
        return 0;
    }

    string toString() const {
        string str;
        if (sign == -1 && !(digits.size() == 1 && digits[0] == 0))
            str.push_back('-');
        for (int i = digits.size() - 1; i >= 0; i--)
            str.push_back(digits[i] + '0');
        return str;
    }
    
    void removeLeadingZeros() {
        while (digits.size() > 1 && digits.back() == 0)
            digits.pop_back();
        if (digits.size() == 1 && digits[0] == 0)
            sign = 1;
    }
public:
    // Constructor that converts a string to a Number
    Number(const string &str) : sign(1), digits() {

        int index = 0;
        if (str[0] == '-') {
            sign = -1;
            index++;
        } 
        else if (str[0] == '+') {
            sign = 1;
            index++;
        }
        
        // Skip leading zeros
        while (index < str.size() && str[index] == '0') {
            index++;
        }
        
        // If all characters are zeros, the number is 0
        if (index == str.size()) {
            digits.push_back(0);
            sign = 1;
            return;
        }

        // Store in reverse 
        for (int i = index; i < str.size(); i++) {
            digits.push_back(str[i] - '0');
        }
        reverse(digits.begin(), digits.end());
    }
    
    // Default constructor
    Number() : sign(1), digits(1, 0) {}

    Number operator+(const Number &other) const {
        Number result;
        //Both numbers have the same sign -> add absolute values
        if (this->sign == other.sign) {
            result.digits = addVectors(this->digits, other.digits);
            result.sign = this->sign;
        }
        // Different signs -> subtract the smaller absolute value from the larger one
        else {
            int cmp = compareAbs(other);
            if (cmp == 0) {
                return Number("0");
            } else if (cmp > 0) {
                result.digits = subtractVectors(this->digits, other.digits);
                result.sign = this->sign;
            } else {
                result.digits = subtractVectors(other.digits, this->digits);
                result.sign = other.sign;
            }
        }
        result.removeLeadingZeros();
        return result;
    }
    
    // Overload the operator
    Number operator-(const Number &other) const {
        return *this + (-other);
    }
    
    // Unary minus operator
    Number operator-() const {
        Number result(*this);
        if (!(result.digits.size() == 1 && result.digits[0] == 0))
            result.sign = -result.sign;
        return result;
    }

    Number operator*(const Number &other) const
    {
        Number result;
        if ((digits.size() == 1 && digits[0] == 0) ||
            (other.digits.size() == 1 && other.digits[0] == 0))
            return Number("0");

        vector<int> res(digits.size() + other.digits.size(), 0);

        for (int i = 0; i < digits.size(); i++) {
            for (int j = 0; j < other.digits.size(); j++) {
                res[i + j] += digits[i] * other.digits[j];
            }
        }

        int carry = 0;
        for (int i = 0; i < res.size(); i++) {
            int temp = res[i] + carry;
            res[i] = temp % 10;
            carry = temp / 10;
        }

        while (res.size() > 1 && res.back() == 0)
            res.pop_back();

        result.digits = res;
        result.sign = this->sign * other.sign;
        if(result.digits.size() == 1 and result.digits[0] == 0)
            result.sign = 1;
        return result;
    }

    Number operator/(const Number &other) const {
        // If |dividend| < |divisor| quotient is 0.
        if (this->compareAbs(other) < 0)
            return Number("0");
        
        Number dividendAbs = *this; dividendAbs.sign = 1;
        Number divisorAbs = other; divisorAbs.sign = 1;
        
        string dividendStr = dividendAbs.toString();
        string quotientStr = "";
        Number remainder("0");
        
        for (char ch : dividendStr) {
            // Multiply remainder by 10 and add the current digit.
            remainder = remainder * Number("10");
            remainder = remainder + Number(string(1, ch));
            
            int count = 0;
            while (remainder.compareAbs(divisorAbs) >= 0) {
                remainder = remainder - divisorAbs;
                count++;
            }
            quotientStr.push_back('0' + count);
        }
        // Remove any leading zeros
        int pos = quotientStr.find_first_not_of('0');
        if (pos != string::npos)
            quotientStr = quotientStr.substr(pos);
        else
            quotientStr = "0";
        
        Number result(quotientStr);
        result.sign = this->sign * other.sign;
        if (result.digits.size() == 1 && result.digits[0] == 0)
            result.sign = 1;
        return result;
    }

    Number operator%(const Number &other) const{
        return *this - ((*this) / other) * other;
    }

    bool operator==(const Number & other) const{
        return this->toString() == other.toString();
    }
    
    bool operator<(const Number & other) const{
        if(this->sign != other.sign)
            return this->sign < other.sign;
        if(digits.size() != other.digits.size())
            return (this->sign == 1) ? (digits.size() < other.digits.size()) : (digits.size() > other.digits.size());
        for(int i = digits.size() - 1; i >= 0; i--)
        {
            if(digits[i] != other.digits[i])
                return (this->sign == 1) ? (digits[i] < other.digits[i]) : (digits[i] > other.digits[i]);
        }
        return false;
    }
    
    bool operator<=(const Number & other) const{
        return (*this < other) or (*this == other);
    }

    bool operator>(const Number & other) const{
        return !(*this <= other);
    }

    bool operator>=(const Number & other) const{
        return !(*this < other);
    }
    
    friend ostream &operator<<(ostream &out, const Number &num) {
        out << num.toString();
        return out;
    }
};

int main() {
    string a, b;
    
    cout<<"Enter the first number: ";
    cin>>a;
    cout<<"Enter the second number: ";
    cin>>b;
    
    Number num1(a), num2(b);
    Number sum = num1 + num2;
    Number difference = num1 - num2;
    Number product = num1 * num2; 
    Number division = num1 / num2;
    cout<<"Sum: "<<sum<<endl;
    cout<<"Difference: "<<difference<<endl;
    cout<<"Product: "<<product<<endl;
    cout<<"Division: "<<division<<endl;
    
    return 0;
}
