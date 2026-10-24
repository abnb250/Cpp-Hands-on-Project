#include "Student.h"

void Student::show_score(){
    using namespace std;
    if(v.size() == 0){
        cout << "no score" << '\n';
        return;
    }
    for(Score x : v){
        cout << x.get_kind() << ": " << x.get_grade() << '\n';
    }
    cout << "===========" << '\n';
    return;
}

double Student::get_score(string kindname) const{
    for(Score x : v){
        if(x.get_kind() == kindname){
            return x.get_grade();
        }
    }
    return -1;
}

string Student::get_name(){
    return name;
}

void Student::showall(){
    using namespace std;
    // string num;
    // string name;
    // char sex;
    // int age;
    // string cla;
    // vector<Score> v;
    // double sum;
    // double ave;
    cout << "========================" << '\n';
    cout << "number: " << num << '\n';
    cout << "name: " << name << '\n';
    cout << "sex: " << sex << '\n';
    cout << "age: " << age << '\n';
    cout << "class:" << cla << '\n';
    show_score();
    cout << "summary: " << get_sum() << '\n';
    cout << "average" << get_ave() << '\n';
    cout << "========================" << '\n';
}

Student& Student::set_num(string newnum) {
    num = newnum;
    return *this;
}

Student& Student::set_name(string newname){
    name = newname;
    return *this;
}

Student& Student::set_sex(char newsex){
    sex = newsex;
    return *this;
}

Student& Student::set_age(int newage){
    age = newage;
    return *this;
}

Student& Student::set_cla(string newcla){
    cla = newcla;
    return *this;
}

bool Student::set_score(string newkind, double newgrade){
    using namespace std;
    if(v.size() == 0){
        cout << "nofind" << '\n';
        return false;
    }
    for(Score &x : v){
        if(x.get_kind() == newkind){
            x.set_score(newgrade);
            return true;
        }
    }
    cout << "nofind" << '\n';
    return false;
}

Student& Student::add_sco(Score sc) {
    v.push_back(sc);
    return *this;
}

double Student::get_sum() const{
    double sum = 0;
    for(Score x : v){
        sum += x.get_grade();
    }
    return sum;
}

double Student::get_ave() const{
    double sum = get_sum();
    double nums = static_cast<double>(v.size());
    if(nums == 0){
        std::cout << "/ 0" << '\n';
        return 0.0;
    }
    return sum/nums;
}

bool cmpsum(const Student& a, const Student& b){
    return a.get_sum() > b.get_sum();
}

bool cmpave(const Student& a, const Student& b){
    return a.get_ave() > b.get_ave();
}

void Student::fileall(std::fstream& file){
    using namespace std;
    file << "========================" << '\n';
    file << "number: " << num << '\n';
    file << "name: " << name << '\n';
    file << "sex: " << sex << '\n';
    file << "age: " << age << '\n';
    file << "class:" << cla << '\n';
    if(v.size() == 0){
        file << "no score" << '\n';
    }
    else{
        for(Score x : v){
            file << x.get_kind() << ": " << x.get_grade() << '\n';
        }
    }
    file << "summary: " << get_sum() << '\n';
    file << "average" << get_ave() << '\n';
    file << "========================" << '\n';
}