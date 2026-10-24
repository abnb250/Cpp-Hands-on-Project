#include "Shape.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Square.h"
#include "Triangle.h"
#include <vector>
#include <memory>
#include <iomanip>
#include <string>
#include <sstream>
using std::cout;
using std::cin;

// 创建图形、列出图形、计算总面积、计算总周长、删除图形和退出

std::vector<std::unique_ptr<Shape>> v;

bool ok(double a, double b, double c){
    if(a + b > c && a + c > b && b + c > a) return true;
    return false;
}

bool readint(int n, std::vector<int>& vs){
    string line;
    if(!getline(cin, line)) return false;

    std::stringstream ss(line);
    for(int i = 0; i < n; i++){
        int x;
        if(!(ss >> x)) return false;
        vs.push_back(x);
    }

    char extra;
    if(ss >> extra) return false;
    
    return true;
    
}

bool readdouble(int n, std::vector<double>& vs){
    string line;
    if(!getline(cin, line)) return false;

    std::stringstream ss(line);
    for(int i = 0; i < n; i++){
        int x;
        if(!(ss >> x)) return false;
        vs.push_back(x);
    }

    char extra;
    if(ss >> extra) return false;

    return true;
}

void create() {
    cout << "====================" << '\n';
    cout << "[1] circle" << '\n';
    cout << "[2] rectangle" << '\n';
    cout << "[3] square" << '\n';
    cout << "[4] triangle" << '\n';
    cout << "[0] quit" << '\n';
    cout << '\n';
    cout << "please cin" << '\n';
    cout << "====================" << '\n';
    int choice;
    std::vector<int> tmp;
    if(!readint(1, tmp) || tmp.size() < 1) return;
    choice = tmp[0];
    switch(choice){
        case 1: {
            double r;
            std::vector<double> tm;
            if(!readdouble(1, tm) || tm.size() < 1) {cout << "please use number" << '\n'; break;}
            r = tm[0];
            if(r <= 0){
                cout << "error" << '\n';
                break;
            }
            std::unique_ptr<Shape> tmp = std::make_unique<Circle>(r);
            v.push_back(std::move(tmp));
        }break;
        case 2:{
            double l, s;
            std::vector<double> tm;
            if(!readdouble(2, tm) || tm.size() < 2) {cout << "please use number" << '\n'; break;}
            l = tm[0];
            s = tm[1];
            if(l <= 0 || s <= 0){
                cout << "error" << '\n';
                break;
            }
            std::unique_ptr<Shape> tmp = std::make_unique<Rectangle>(l, s);
            v.push_back(std::move(tmp));
        }break;
        case 3:{
            double b;
            std::vector<double> tm;
            if(!readdouble(1, tm) || tm.size() < 1) {cout << "please use number" << '\n'; break;}
            b = tm[0];
            if(b <= 0){
                cout << "error" << '\n';
                break;
            }
            std::unique_ptr<Shape> tmp = std::make_unique<Square>(b);
            v.push_back(std::move(tmp));
        }break;
        case 4:{
            double a, b, c;
            std::vector<double> tm;
            if(!readdouble(3, tm) || tm.size() < 3) {cout << "please use number" << '\n'; break;}
            a = tm[0];
            b = tm[1];
            c = tm[2];
            if(a <= 0 || b <= 0 || c <= 0 || !ok(a,b,c)){
                cout << "error" << '\n';
                break;
            }
            std::unique_ptr<Shape> tmp = std::make_unique<Triangle>(a, b, c);
            v.push_back(std::move(tmp));
        }break;
        default: {
            cout << "please use other numbers" << '\n';
        }
        case 0: break;
    }
    return;
}

void list() {
    if(v.size() == 0){
        cout << "empty" << '\n';
        return;
    }
    int index = 0;
    for(auto& x : v){
        cout << index++ << '\n';
        x->print();
    }
    return;
}

void getarrea() {
    if(v.size() == 0){
        cout << "empty" << '\n';
        return;
    }
    double res = 0.0;
    for(auto& x : v){
        res += x->area();
    }
    cout << std::fixed << std::setprecision(2) << res << '\n';
    return;
}

void getperimeter() {
    if(v.size() == 0){
        cout << "empty" << '\n';
        return;
    }
    double res = 0.0;
    for(auto& x : v){
        res += x->perimeter();
    }
    cout << std::fixed << std::setprecision(2) << res << '\n';
    return;
}

void deletes() {
    int index;
    cin >> index;
    
    if(v.size() == 0){
        cout << "empty" << '\n';
        return;
    }
    if(index >= v.size() || index < 0){
        cout << "out range" << '\n';
        return;
    }
    v.erase(v.begin() + index);
    return;
}

void quit() {
    cout << "byebye" << '\n';
    return;
}

void showmain(){
    while(1){
        cout << "====================" << '\n';
        cout << "[1] create a shape" << '\n';
        cout << "[2] list the shapes" << '\n';
        cout << "[3] get all area" << '\n';
        cout << "[4] get all perimeter" << '\n';
        cout << "[5] delete a shape" << '\n';
        cout << "[0] quit" << '\n';
        cout << '\n';
        cout << "please cin" << '\n';
        cout << "====================" << '\n';
    
        int choice;
        cin >> choice;
        switch(choice){
            case 1:create(); break;
            case 2:list();break;
            case 3:getarrea();break;
            case 4:getperimeter();break;
            case 5:deletes();break;
            case 0:quit();break;
            default:
                cout << "quit" << '\n';
                break;
        }
        if(choice == 0) break;
    }
}

int main(){
    using namespace std;
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    showmain();
    return 0;
}