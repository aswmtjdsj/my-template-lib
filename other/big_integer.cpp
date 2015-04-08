#include <cstdio>
#include <cassert>
#include <cstring>

#include <iomanip>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>

using namespace std;

#define T short

/***** 10000 grouped *****/
class BigInteger {
    public:
        enum {NEG = -1, ZERO = 0, POS = 1}; // type of T <== weird, but no choice...
        enum {UNIT = 10000};

        BigInteger();

        BigInteger(const string &);
        BigInteger(const char *); 

        /*BigInteger(const vector <T> &);
        BigInteger(vector <T> &&);*/

        BigInteger(const BigInteger &);
        BigInteger(BigInteger &&);

        BigInteger & operator = (const BigInteger &);

        ~BigInteger();

        vector <T> get_nums() const;
        size_t len() const;
        BigInteger & parse(const string &);
        BigInteger & parse(const char *);
        BigInteger & self_handle();
        string rep() const;

        /* + - * / */
        BigInteger operator + (const BigInteger &) const;
        BigInteger & operator += (const BigInteger &);
        BigInteger operator - () const; // Unary
        BigInteger operator - (const BigInteger &) const;
        BigInteger & operator -= (const BigInteger &);
        BigInteger operator * (const T &) const; // small number
        friend BigInteger operator * (const T &, const BigInteger &);
        BigInteger operator * (const BigInteger &) const;
        BigInteger & operator *= (const T &);
        BigInteger & operator *= (const BigInteger &);
        BigInteger operator / (const BigInteger &) const;
        BigInteger & operator /= (const BigInteger &);
        /* + - * / */

        /* bool */
        bool operator == (const BigInteger &) const;
        bool operator > (const BigInteger &) const;
        bool operator < (const BigInteger &) const;

    private:
        T sign;
        vector <T> nums;
};

/***** constructor *****/
BigInteger::BigInteger(): sign(ZERO) {
    nums.clear();
}

BigInteger::BigInteger(const string & input): sign(ZERO) {
    parse(input);
}

BigInteger::BigInteger(const char * input): sign(ZERO) {
    parse(input);
}

/*BigInteger::BigInteger(const vector <T> & another): sign(), nums(another) {
}*/ // with only a vector, a big integer cannot be constructed, as there's no sign information
/***** constructor *****/

/***** move constructor *****/
/*BigInteger::BigInteger(vector <T> && another): sign(POS) {
    if(&nums != &another) {
        nums.clear();
        nums = std::move(another);
        another.clear();
    }
}*/
/***** move constructor *****/

/***** copy constructor *****/
BigInteger::BigInteger(const BigInteger & another): sign(another.sign), nums(another.nums) {
}
/***** copy constructor *****/

/***** move constructor *****/
BigInteger::BigInteger(BigInteger && another) {
    if(this != &another) {
        nums.clear();
        nums = std::move(another.nums);
        sign = std::move(another.sign);
        another.nums.clear();
    }
}
/***** move constructor *****/

/***** assign operator *****/
BigInteger & BigInteger::operator = (const BigInteger & another) {
    // *this = BigInteger(another);
    // sucks!
    sign = another.sign;
    nums = another.nums;
    return *this;
}
/***** assign operator *****/

/***** destructor *****/
BigInteger::~BigInteger() {
    if(nums.size() != 0) {
        nums.clear();
    }
}
/***** destructor *****/

vector <T> BigInteger::get_nums() const {
    return nums;
}

size_t BigInteger::len() const {
    return nums.size();
}

/***** parse input *****/
BigInteger & BigInteger::parse(const string & origin) {
    return parse(origin.c_str());
}
/***** parse input *****/

/***** parse input *****/
BigInteger & BigInteger::parse(const char * origin) {
    if(len() != 0) nums.clear();
    size_t len = strlen(origin);
    assert(len > 0);

    // pre calc nums size
    nums.resize(len/4 + 1, 0); // dependent to 10000
    size_t idx = 0;

    T i = len - 1;
    assert(i < (1ll << ((sizeof(T) * 8) - 1)));
    do { // stored in reverse order
        T temp = 0;
        T s = max(i - 3, 0); // dependent to 10000
        for(T j = s; j <= i; j++) {
            if(!isdigit(origin[j])) {
                if(origin[j] == '+' || origin[j] == '-') {
                    assert(j == 0 && j != (T)len - 1);
                } else {
                    assert(isdigit(origin[j]));
                }
            }
            if(origin[j] == '-') {
                sign = NEG;
            } else if(origin[j] == '+') {
                sign = POS;
            } else {
                temp = temp * 10 + (origin[j] - '0');
            }
        }
        nums[idx++] = temp;
        i = s - 1;
    } while(i >= 0);
    return self_handle();
}
/***** parse input *****/

/***** handle duplicate 0s and sign *****/
BigInteger & BigInteger::self_handle() {
    while(len() > 0 && nums.back() == 0) {
        // cout << "biubiu: " << nums.back() << endl;
        nums.pop_back();
    }
    if(len() == 0) {
        nums.push_back(0); // for 0 as BigInteger
        sign = ZERO;
    } else if(sign != NEG) {
        sign = POS;
    }
    return *this;
}
/***** handle duplicate 0s *****/

/***** compose output *****/
string BigInteger::rep() const {
    string ret = "";
    for(auto idx = nums.rbegin(); idx != nums.rend(); idx++) {
        if(idx == nums.rbegin()) {
            ret = to_string(*idx);
        } else {
            ostringstream ss;
            ss << setw(4) << setfill('0') << *idx; // dependent to 10000
            ret += ss.str();
        }
    }

    if(sign == NEG) {
        ret = "-" + ret;
    }

    return ret;
}
/***** compose output *****/

// operator 

/***** + operator *****/
BigInteger BigInteger::operator + (const BigInteger & another) const {
    if(sign == NEG && another.sign == NEG) { // -x + (-y)
        return -(-*this + -another);
    } else if(sign == NEG && another.sign != NEG) { // -x + y
        return another - -*this;
    } else if(sign != NEG && another.sign == NEG) { // x + (-y)
        return *this - -another;
    }
    assert(sign != NEG && another.sign != NEG);

    BigInteger ret;
    size_t pot_len = max(len(), another.len()); // pre alloc
    ret.nums.resize(pot_len + 1);
    size_t idx = 0;
    T up = 0;
    for(size_t i = 0; i < pot_len; i++) {
        T cur = 0;
        cur += (i < len())?(sign==POS?nums[i]:(sign==NEG?-nums[i]:0)):0;
        cur += (i < another.len())?(another.sign==POS?another.nums[i]:(another.sign==NEG?-another.nums[i]:0)):0;
        cur += up;
        up = cur / UNIT;
        cur = cur % UNIT;
        ret.nums[idx++] = cur;
    }
    if(up > 0) {
        ret.nums[idx++] = up;
        up = 0;
    }

    return ret.self_handle();
}
/***** + operator *****/

/***** unary - operator *****/
BigInteger BigInteger::operator - () const {
    BigInteger temp(*this);
    /*switch(sign) {
        case NEG:
            temp.sign = POS;
            break;
        case POS:
            temp.sign = NEG;
            break;
        default:
            temp.sign = ZERO;
    }*/
    temp.sign = -sign;// dependent to enumeration value set
    return temp;
}
/***** unary - operator *****/

/***** - operator *****/
BigInteger BigInteger::operator - (const BigInteger & another) const {
    if(sign == NEG && another.sign == NEG) {
        return -another - -*this;
    } else if(sign == NEG && another.sign != NEG) {
        return -(-*this + another);
    } else if(sign != NEG && another.sign == NEG) {
        return *this + -another;
    }
    assert(sign != NEG && another.sign != NEG);

    BigInteger ret;
    size_t pot_len = max(len(), another.len()); // pre alloc
    ret.nums.resize(pot_len + 1);
    size_t idx = 0;
    T down = 0;
    for(size_t i = 0; i < pot_len; i++) {
        T cur = 0;
        cur += (i < len())?(sign==POS?nums[i]:(sign==NEG?-nums[i]:0)):0;
        cur -= (i < another.len())?(another.sign==POS?another.nums[i]:(another.sign==NEG?-another.nums[i]:0)):0;
        cur -= down;
        // up = cur / UNIT;
        if(cur < 0) {
            down++;
            cur += UNIT;
        }
        cur = cur % UNIT;
        ret.nums[idx++] = cur;
    } // TODO
    /*if(down > 0) {
        ret.nums[idx++] = up;
        up = 0;
    }*/

    return ret.self_handle();
}
/***** - operator *****/

/***** * operator for big int and small int multiply *****/
BigInteger BigInteger::operator * (const T & small) const {
    if(sign == NEG && small < 0) {
        return (-*this) * (-small);
    } else if(sign == NEG && small > 0) {
        return -((-*this) * small);
    } else if(sign != NEG && small < 0) {
        return -(*this * (-small));
    } else if(small == 0) {
        return BigInteger("0");
    }
    BigInteger ret;
    // TODO
    return ret.self_handle();
}
/***** * operator for big int and small int multiply *****/

/***** * friend operator for small int and big int multiply *****/
BigInteger operator * (const T & small, const BigInteger & big) {
    return big * small;
}
/***** * friend operator for small int and big int multiply *****/

/***** * operator *****/
BigInteger BigInteger::operator * (const BigInteger & another) const {
    BigInteger ret;
    // TODO
    return ret.self_handle();
}
/***** * operator *****/

/***** bool == operator *****/
bool BigInteger::operator == (const BigInteger & another) const {
    if(len() != another.len()) {
        return false;
    }
    if(sign != another.sign) {
        return false;
    }
    size_t length = len();
    for(size_t i = 0; i < length; i++) {
        if(nums[i] != another.nums[i]) {
            return false;
        }
    }
    return true;
}
/***** bool == operator *****/

/***** bool < operator *****/
bool BigInteger::operator < (const BigInteger & another) const {
    if(sign == NEG && another.sign != NEG) return true;
    if(sign == POS && another.sign != POS) return false;
    if(another.sign == NEG) return (-*this) > (-another); // NEG to POS

    // not NEG now
    if(len() != another.len()) return len() < another.len();

    // real compare
    T legacy = 0;
    for(size_t i = len(); i > 0; i--) {
        T a = nums[i-1] + legacy * UNIT, b = another.nums[i-1];
        if(a < b) return true;
        else if(a > b) return false;
        else {
            legacy = a - b;
        }
    }
    return false;
}
/***** bool < operator *****/

/***** bool > operator *****/
bool BigInteger::operator > (const BigInteger & another) const {
    if(sign == NEG && another.sign != NEG) return false;
    if(sign == POS && another.sign != POS) return true;
    // same symbol 
    if(another.sign == NEG) return (-*this) < (-another);

    // not NEG now
    if(len() != another.len()) return len() > another.len();

    // real compare
    T legacy = 0;
    for(size_t i = len(); i > 0; i--) {
        T a = nums[i-1] + legacy * UNIT, b = another.nums[i-1];
        if(a > b) return true;
        else if(a < b) return false;
        else {
            legacy = a - b;
        }
    }
    return false;
}
/***** bool > operator *****/

/***** other operator *****/

/***** operator + for two string/string and big int ****
BigInteger operator + (const string & a, const BigInteger & b) {
    return BigInteger(a) + b;
}

BigInteger operator + (const BigInteger & a, const string & b) {
    return a + BigInteger(b);
}

BigInteger operator + (const string & a, const string & b) {
    return BigInteger(a) + BigInteger(b);
}
**** operator + for two string/string and big int ****

**** operator - for two string/string and big int ****
BigInteger operator - (const string & a, const BigInteger & b) {
    return BigInteger(a) - b;
}

BigInteger operator - (const BigInteger & a, const string & b) {
    return a - BigInteger(b);
}

BigInteger operator - (const string & a, const string & b) {
    return BigInteger(a) - BigInteger(b);
}
**** operator - for two string/string and big int *****/

/***** other operator *****/

void test_parse() {
    string input;
    cin >> input;
    BigInteger big(input);
    BigInteger output = big;
    cout << "output: " << output.rep() << endl;
    cout << "-big: " << (-big).rep() << endl;
}

void test_assign() {
    BigInteger a("0"), b = a;
    b = b;
}

void test_add() {
    string a, b;
    while(cin >> a >> b) {
        BigInteger sum = BigInteger(a) + BigInteger(b);
        cout << sum.rep() << endl;
    }
}

void test_sub() {
    string a, b;
    while(cin >> a >> b) {
        BigInteger sum = BigInteger(a) - BigInteger(b);
        cout << sum.rep() << endl;
    }
}

void test_mult() {
    string a;
    short b;
    while(cin >> a >> b) {
        BigInteger prod = BigInteger(a) * b;
        cout << prod.rep() << endl;
    }
}

void test_equal() {
    string a, b;
    while(cin >> a >> b) {
        cout << (BigInteger(a) == BigInteger(b)) << endl;
    }
}

void test_comp() {
    string a, b;
    while(cin >> a >> b) {
        cout << (BigInteger(a) < BigInteger(b)) << endl;
        // (BigInteger(a) < BigInteger(b));
    }
}

void unit_test() {
    // test_assign();
    // test_parse();
    // test_add();
    // test_sub();
    // test_mult();
    // test_equal();
    test_comp();
}

int main(int argc, char ** argv) {
    unit_test();
}
