#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string removeLeadingZeros(string num) {
    while (num.size() > 1 && num[0] == '0') {
        num.erase(0, 1);
    }
    return num;
}

int compare(string num1, string num2) {
    if (num1.size() > num2.size()) return 1;
    if (num1.size() < num2.size()) return -1;
    return num1.compare(num2);    
}

string add(string num1, string num2) {
    string result = "";
    int carry = 0;
    reverse(num1.begin(), num1.end());
    reverse(num2.begin(), num2.end());

    int n = max(num1.size(), num2.size());
    for (int i = 0; i < n; i++) {
        int digit1 = i < num1.size() ? num1[i] - '0' : 0;
        int digit2 = i < num2.size() ? num2[i] - '0' : 0;
        int sum = digit1 + digit2 + carry;
        carry = sum / 10;
        result += (sum % 10) + '0';
    }
    if (carry) {
        result += carry + '0';
    }
    reverse(result.begin(), result.end());
    return result;
}

string subtract(string num1, string num2) {
    string result = "";
    int borrow = 0;
    reverse(num1.begin(), num1.end());
    reverse(num2.begin(), num2.end());

    for (int i = 0; i < num1.size(); i++) {
        int digit1 = num1[i] - '0';
        int digit2 = i < num2.size() ? num2[i] - '0' : 0;
        int diff = digit1 - digit2 - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result += diff + '0';
    }
    reverse(result.begin(), result.end());
    return removeLeadingZeros(result);
}

string multiply(string num1, string num2) {
    string result(num1.size() + num2.size(), '0');

    for (int i = num1.size() - 1; i >= 0; i--) {
        int carry = 0;
        for (int j = num2.size() - 1; j >= 0; j--) {
            int temp = (result[i + j + 1] - '0') + (num1[i] - '0') * (num2[j] - '0') + carry;
            result[i + j + 1] = (temp % 10) + '0';
            carry = temp / 10;
        }
        result[i] += carry;
    }
    return removeLeadingZeros(result);
}

string divide(string num1, string num2) {
    if (num2 == "0") {
        return "Ошибка: деление на ноль";
    }

    string result = "";
    string remainder = "";

    for (char digit : num1) {
        remainder += digit;
        remainder = removeLeadingZeros(remainder);
        int count = 0;
        while (compare(remainder, num2) >= 0) {
            remainder = subtract(remainder, num2);
            count++;
        }
        result += count + '0';
    }
    return removeLeadingZeros(result);
}

int main() {
    string num1, num2;
    char op;

    cout << "Введите первое число: ";
    cin >> num1;
    cout << "Введите оператор (+, -, *, /, <, >, =): ";
    cin >> op;
    cout << "Введите второе число: ";
    cin >> num2;

switch (op) {
    case '+':
        cout << "Результат: " << add(num1, num2) << endl;
        break;

    case '-':
        if (compare(num1, num2) >= 0)
            cout << "Результат: " << subtract(num1, num2) << endl;
        else
            cout << "Результат: -" << subtract(num2, num1) << endl;
        break;

    case '*':
        cout << "Результат: " << multiply(num1, num2) << endl;
        break;

    case '/':
        cout << "Результат: " << divide(num1, num2) << endl;
        break;

    case '>':
        cout << (compare(num1, num2) > 0 ? "true" : "false") << endl;
        break;

    case '<':
        cout << (compare(num1, num2) < 0 ? "true" : "false") << endl;
        break;

    case '=':
        cout << (compare(num1, num2) == 0 ? "true" : "false") << endl;
        break;

    default:
        cout << "Неверный оператор!" << endl;
        break;
}

}