#include <map>
#include <vector>
#include <iostream>
#include <string>


using namespace std;

class BigInt {
private:
    vector<char> digit;
public:
    BigInt();
    BigInt(string);
    BigInt(int);
    BigInt(const BigInt&);
    ~BigInt();
    vector<char> getDigit();
    BigInt operator+(BigInt) const;
    BigInt operator+(int);
    BigInt operator++(int);
    BigInt operator-(int);
    BigInt operator-(BigInt) const;
    BigInt operator=(BigInt);
    BigInt operator=(int);
    bool operator==(int);
    bool operator==(const BigInt&) const;
    bool operator<(int);
    bool operator<(const BigInt&) const;
    bool operator<=(int);
    bool operator<=(const BigInt&) const;
    friend std::ostream& operator<<(std::ostream& os, BigInt);
    void print();

};
int goldRabbits(int);
BigInt goldRabbits(BigInt);
void pause() { cout << "Press Enter to continue..."; getchar(); }
static int count = 0;

int main() {
    cout << goldRabbits(BigInt(3000)) << endl;   // <----- add this line

    BigInt B1("123456789123456789123456789123456789");
    BigInt B2(B1);
    BigInt MAX(INT_MAX);
    cout << "B1:" << B1 << "\nB2:" << B2 << "\nMAX:" << MAX << endl;
    pause();
    cout << "\nB1:";
    B1.print();
    cout << endl;
    pause();

    for (BigInt i = 0; i <= 3000; i++) // uncomment this
        // for(int i = 0; i <= 3000; i++) // comment this out
    {
          cout << "\ngoldRabbits(" << i << ") = " << goldRabbits(i);

    }

    pause();

    cout << "\nThis is the value of goldRabbits(3000)\n\n";
    BigInt gR3000 = goldRabbits(BigInt(3000));
    gR3000.print();
    cout << endl;
    pause();

    int n = 500;
    try {

        cout << "The value of goldRabbits(n) is:" << goldRabbits(n) << endl;

    }
    catch (string error) {
        cout << error << endl;
        cout << "Transitioning to BigInt\n";
        cout << goldRabbits(BigInt(n));
    }
    pause();

}

int goldRabbits(int n) {

    if ((BigInt(INT_MAX) < goldRabbits(BigInt(n))) && (goldRabbits(BigInt(n - 1)) < BigInt(INT_MAX))) {

        throw " Overflow Error " "-" " goldRabbits overflowed using " + to_string(n);
    }
    else if (n == 0 || n == 1) {
        return 1;
    }

    return goldRabbits(n - 1) + goldRabbits(n - 2);

}

BigInt goldRabbits(BigInt n) {
    static map<BigInt, BigInt> rabbits;
    if (n == 0 || n == 1) {
        rabbits[n] = 1;
        return BigInt(1);
    }
    else {
        rabbits[n] = (rabbits[n - 1] == 0 ? goldRabbits(n - 1):rabbits[n-1]) + (rabbits[n - 2] == 0 ? goldRabbits(n - 2) : rabbits[n - 2]);

    }
    return rabbits.at(n);
}

BigInt::BigInt()
{
    digit.push_back(0);
}

BigInt::BigInt(string input)
{
    for (int i = input.size() - 1; i >= 0; i--)
    {
        digit.push_back(input[i] - '0');
    }
}

BigInt::BigInt(int num)
{
    string temp = to_string(num);
    for (int i = temp.size() - 1; i >= 0; i--)
    {
        digit.push_back(temp[i] - '0');
    }
}

BigInt::BigInt(const BigInt& other)
{
    this->digit = other.digit;
}

BigInt::~BigInt()
{
    digit.clear();
}

vector<char> BigInt::getDigit()
{
    return digit;
}

BigInt BigInt::operator++(int)
{
    return (*this) = (*this) + 1;
}

BigInt BigInt::operator-(BigInt n) const
{
    BigInt x(*this);

    while (x.digit.size() != n.digit.size())
    {
        (x.digit.size() > n.digit.size() ? n.digit.push_back(0) : x.digit.push_back(0));
    }

    for (size_t i = 0; i < x.digit.size(); i++)
    {
        if (x.digit[i] < n.digit[i]) {
            x.digit[i] += 10;
            x.digit[i + 1] -= 1;
        }
        x.digit[i] -= n.digit[i];
        if (x.digit[i] == 0 && n.digit[i] == 0 && i == x.digit.size() - 1)
        {
            x.digit.erase(x.digit.end() - 1);
        }

    }
    return x;
}

BigInt BigInt::operator-(int n)
{
    return (*this) - BigInt(n);
}

BigInt BigInt::operator+(int n)
{
    return (*this) + BigInt(n);
}

BigInt BigInt::operator+(BigInt o) const
{
    BigInt x(*this);

    while (o.digit.size() != x.digit.size()) {
        if (o.digit.size() > x.digit.size())
        {
            x.digit.push_back(0);
        }
        else {
            o.digit.push_back(0);
        }
    }
    char carry = 0;
    for (int i = 0; i < x.digit.size(); i++)
    {
        if (carry == 1) {
            carry = 0;
            x.digit[i] += 1;
        }
        if (x.digit[i] + o.digit[i] >= 10)
        {
            carry = 1;
        }
        x.digit[i] += o.digit[i] - carry * 10;
    }
    if (carry == 1)
    {
        x.digit.push_back(carry);
    }
    return x;
}

BigInt BigInt::operator=(BigInt o)
{
    digit = o.digit;
    return (*this);
}

BigInt BigInt::operator=(int n)
{
    BigInt temp(n);
    this->digit = temp.digit;
    return (*this);
}

bool BigInt::operator==(int n)
{
    return (*this) == BigInt(n);
}

bool BigInt::operator==(const BigInt& n) const
{
    bool isEqual = true;
    if (digit.size() == n.digit.size())
    {
        int i = 0;
        while (i < digit.size() && isEqual)
        {
            if (digit[i] != n.digit[i])
            {
                isEqual = false;
            }
            i++;
        }
    }
    else
    {
        isEqual = false;
    }
    return isEqual;
}

bool BigInt::operator<(int n)
{
    return (*this) < BigInt(n);
}

bool BigInt::operator<(const BigInt& o) const
{
    if (*this == o) { return false; }
    if (digit.size() < o.digit.size()) {
        return true;
    }
    else if (digit.size() > o.digit.size()) {
        return false;
    }
    else {
        int index = digit.size() - 1;
        while (index > -1) {
            if (digit[index] > o.digit[index]) {
                return false;
            }
            else if (digit[index] < o.digit[index]) {
                return true;
            }
            index--;
        }
        return true;

    }
}

bool BigInt::operator<=(int n)
{
    return (*this) <= (BigInt(n));
}

bool BigInt::operator<=(const BigInt& o) const
{
    return (*this) < (o) || (*this) == (o);
}

void BigInt::print()
{
    for (int i = digit.size() - 1; i >= 0; i--)
    {
        cout << int(digit.at(i));
    }
}

ostream& operator<<(ostream& out, BigInt temp)
{
    if (temp.getDigit().size() > 11)
    {
        for (int i = temp.getDigit().size() - 1; i >= temp.digit.size() - 11; i--)
        {
            out << int(temp.getDigit()[i]);
            if (i == temp.getDigit().size() - 1)
            {
                out << ".";
            }
        }
        out << "e" << temp.getDigit().size() << endl;
    }
    else
    {
        temp.print();
    }
    return out;
}
