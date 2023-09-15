#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <typeinfo>
#include <sstream>
#include "split.h"

template<typename T> std::string tostring(const T& x) {
    std::ostringstream os;
    os << x;
    return os.str();
}

class AnyList {
private:
    std::vector<std::vector<std::string>> v;
public:
    AnyList() = default;

    void push_back(auto elem) {
        std::vector<std::string> t;
        t.push_back(tostring(elem));
        t.push_back(typeid(elem).name());
        v.push_back(t);
    }
    auto getElement(int index) {
        try {
            return v[index][0];
        } catch (std::exception& ex) {
            return tostring("NULL");
        }
    }
    auto getElementType(int index) {
        try {
            return v[index][1];
        } catch (std::exception& ex) {
            return tostring("NULL");
        }
    }
    auto convertElement(std::string& to, int index) {
        if (typeid(to).name() == getElementType(index)) {
            to = getElement(index);
        }
    }
    auto convertElement(char& to, int index) {
        if (typeid(to).name() == getElementType(index)) {
            to = getElement(index)[0];
        }
    }
    auto convertElement(int& to, int index) {
        if (typeid(to).name() == getElementType(index)) {
            to = std::stoi(getElement(index));
        }
    }
    auto convertElement(float& to, int index) {
        if (typeid(to).name() == getElementType(index)) {
            to = std::stof(getElement(index));
        }
    }
    auto convertElement(double& to, int index) {
        if (typeid(to).name() == getElementType(index)) {
            to = std::stold(getElement(index));
        }
    }
};

int main() {
    AnyList any_list;

    std::string PKc = "str"; any_list.push_back(PKc);
    char c = 'J'; any_list.push_back(c);
    int i = 2; any_list.push_back(i);
    float f = 2.3; any_list.push_back(f);
    double d = 2.1; any_list.push_back(d);

    std::string strr; any_list.convertElement(strr, 0);
    char cc; any_list.convertElement(cc, 1);
    int ii; any_list.convertElement(ii, 2);
    float ff; any_list.convertElement(ff, 3);
    double dd; any_list.convertElement(dd, 4);

    std::cout << strr + "?" << std::endl;
    std::cout << cc << std::endl;
    std::cout << ii + 1 << std::endl;
    std::cout << ff + 1 << std::endl;
    std::cout << dd + 1 << std::endl;

    return 0;
}
