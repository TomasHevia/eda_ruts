#include "trees/abb.hpp"
#include <iostream>
#include <bits/stdc++.h>
#include <map>
using namespace std;

map<string, int> variables;

int prec(char c) {
    if (c == '^')
        return 3;
    else if (c == '/' || c == '*')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}

int calculatePostfix(string postfix) {
    stack<int> st;
    for (int i = 0; i < postfix.length(); i++) {
        char c = postfix[i];
        if (isdigit(c)) {
            st.push(c - '0');
        }
        else if (isalpha(c)) {
            st.push(variables[string(1, c)]);
        }
        else {
            int val1 = st.top();
            st.pop();
            int val2 = st.top();
            st.pop();
            switch (c) {
                case '+':
                    st.push(val2 + val1);
                    break;
                case '-':
                    st.push(val2 - val1);
                    break;
                case '*':
                    st.push(val2 * val1);
                    break;
                case '/':
                    st.push(val2 / val1);
                    break;
                case '^':
                    st.push(pow(val2, val1));
                    break;
            }
        }
    }
    return st.top();
}

std::string infixToPostfix(string s) {
    stack<char> st;
    string result;
    for (int i = 0; i < s.length(); i++) {
        char c = s[i];
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            string var_name(1, c);
            while (i + 1 < s.length() && isalnum(s[i + 1])) {
                var_name += s[i + 1];
                i++;
            }
            if (variables.find(var_name) != variables.end()) {
                result += to_string(variables[var_name]);
            }
            else {
                cout << "Variable " << var_name << " no definida." << endl;
                return "";
            }
        }
        else if (isdigit(c)) {
            result += c;
        }
        else if (c == '(') {
            st.push('(');
        }
        else if (c == ')') {
            while (!st.empty() && st.top() != '(') {
                result += st.top();
                st.pop();
            }
            st.pop();
        }
        else {
            while (!st.empty() && prec(s[i]) <= prec(st.top())) {
                result += st.top();
                st.pop();
            }
            st.push(c);
        }
    }
    while (!st.empty()) {
        result += st.top();
        st.pop();
    }
    return result;
}

int main() {
    cout << "Calculadora" << endl;
    while (true) {
		string last_postfix;
        cout << "$ ";
        string input;
        getline(cin, input);

        if (input.empty()) {
            continue;
        }
		if (input != "tree" && input != "fin"){
			if (input.find('=') != string::npos) {
				size_t pos = input.find('=');
				string var_name = input.substr(0, pos);
				string expr = input.substr(pos + 1);
				variables[var_name] = calculatePostfix(infixToPostfix(expr));
			}
			else {
				string postfix = infixToPostfix(input);
				if (!postfix.empty()) {
					last_postfix = postfix;
					int result = calculatePostfix(postfix);
					variables["ans"] = result;
					cout << "ans =  " << result << endl;
				}
			}
		}else{
			if (input == "tree") {
				cout << "Postfix: " << last_postfix << endl;
				trees::ABB tree;
				tree.createPostfixTree(last_postfix);
				tree.traverse();
			}
			if (input == "fin") {
				break;
			}
		}
		
    }

    return 0;
}
