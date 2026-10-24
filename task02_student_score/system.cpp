#include "Student.h"
#include "Score.h"
#include <map>
#include <unordered_map>
#include <vector>
#include <fstream>

std::unordered_map<string, Student> maps;

int Showmain(){
    using namespace std;
    cout << "========================" << '\n';
    cout << "[1]show students" << '\n';
    cout << "[2]add a student" << '\n';
    cout << "[3]delete a student" << '\n';
    cout << "[4]set a student" << '\n';
    cout << "[5]show the class" << '\n';
    cout << "[6]read from file" << '\n';
    cout << "[7]save into a file" << '\n';
    cout << "[0]exit" << '\n';
    cout << "========================" << '\n';
    int choice;
    cin >> choice;
    return choice;
}

void op1(){
    using namespace std;
    while(1){
        cout << "========================" << '\n';
        cout << "[a]just a student" << '\n';
        cout << "[b]show all with summary" << '\n';
        cout << "[c]show all with average" << '\n';
        cout << "[d]show all with subject" << '\n';
        cout << "[q]exit" << '\n';
        char choice;
        cin >> choice;
        if(choice == 'q') break;
        if(choice == 'a'){
            cout << "cin number and name" << '\n';
            string nums, nams;
            cin >> nums >> nams;    
            auto it = maps.find(nums);
            if(it == maps.end()){
                cout << "no find" << '\n';
                continue;
            }
            if(it->second.get_name() != nams){
                cout << "name is error" << '\n';
                continue;
            }
            it->second.showall();
        }
        if(choice == 'b'){
            vector<Student> vs;
            for(auto it : maps){
                vs.push_back(it.second);
            }
            sort(vs.begin(), vs.end(), cmpsum);
            for(auto x : vs){
                x.showall();
            }
        }
        if(choice == 'c'){
            vector<Student> vs;
            for(auto it : maps){
                vs.push_back(it.second);
            }
            sort(vs.begin(), vs.end(), cmpave);
            for(auto x : vs){
                x.showall();
            }
        }
        if(choice == 'd'){
            cout << "cin the subject" << '\n';
            string sub;
            cin >> sub;
            vector<Student> vs;
            for(auto it : maps){
                vs.push_back(it.second);
            }
            sort(vs.begin(), vs.end(),[&sub](const Student& a, const Student& b){
                return a.get_score(sub) > b.get_score(sub);
            });
            for(auto x : vs){
                x.showall();
            }
        }
    }
    
}

void op2(){
    using namespace std;
    cout << "cin the basic message: " << '\n';
    // string num;
    // string name;
    // char sex;
    // int age;
    // string cla;
    cout << "number(string), name(string), sex(char), age(int), class(string)." << '\n';
    string nums, nams, clas;
    char sexs;
    int ages;
    cin >> nums >> nams >> sexs >> ages >> clas;
    cout << "everything is ok" << '\n';
    Student tmp(nums, nams, sexs, ages, clas);
    maps[nums] = tmp;
    return;
}

void op3(){
    using namespace std;
    cout << "cin number" << '\n';
    string tmp;
    cin >> tmp;
    maps.erase(tmp);
}

void op4(){
    using namespace std;
    while(1){
        cout << "========================" << '\n';
        cout << "[a]basic message" << '\n';
        cout << "[b]subject score" << '\n';
        cout << "[q]exit" << '\n';
        cout << "========================" << '\n';
        char ch;
        cin >> ch;
        if(ch == 'q') break;
        if(ch == 'a'){
            cout << "cin the number and the basic message" << '\n';
            cout << "number(string), name(string), sex(char), age(int), class(string)." << '\n';
            string nums, nams, clas;
            char sexs;
            int ages;
            cin >> nums >> nams >> sexs >> ages >> clas;
            cout << "everything is ok" << '\n';
            // Student& set_num(string newnum);
            // Student& set_name(string newname);
            // Student& set_sex(char newsex);
            // Student& set_age(int newage);
            // Student& set_cla(string newcla);
            auto it = maps.find(nums);
            if(it == maps.end()){
                cout << "no find" << '\n';
                continue;
            }
            it->second.set_name(nams).set_sex(sexs).set_age(ages).set_cla(clas);
        }
        if(ch == 'b'){
            cout << "cin the number" << '\n';
            string tname;
            cin >> tname;
            auto it = maps.find(tname);
            if(it == maps.end()){
                cout << "no find" << '\n';
                continue;
            }
            cout << "cin the subject name and score" << '\n';
            string sname;
            double sc;
            cin >> sname >> sc;
            bool ok = it->second.set_score(sname, sc);
            if(!ok){
                Score ns(sname, sc);
                it->second.add_sco(ns);
            }
        }
    }
    
}

void op5(){
    using namespace std;
    cout << "========================" << '\n';
    //支持统计班级总分、平均分、最高分、最低分
    double classsum = 0.0, classave, classmax = -1.0, classmin = -1.0;
    int numss = 0;
    for(auto it : maps){
        classsum += it.second.get_sum();
        classmax = max(classmax, it.second.get_sum());
        classmin = min(classmin, it.second.get_sum());
        numss++;
    }
    classave = classsum / (1.0)*numss;
    cout << "class summary: " << classsum << '\n';
    cout << "class average: " << classave << '\n';
    cout << "class max: " << classmax << '\n';
    cout << "class min: " << classmin << '\n';
    cout << "========================" << '\n';
}

void op6(){
    using namespace std;
    cout << "cin the file name" << '\n';
    string fname;
    cin >> fname;
    fstream file(fname, ios::in | ios:: out);
    if(!file.is_open()){
        cout << "file open filed" << '\n';
        return;
    }
    string tmp;
    while(getline(file, tmp)){
        cout << tmp << '\n';
    }
    file.close();
}

void op7(){
    using namespace std;
    cout << "cin the file name" << '\n';
    string fname;
    cin >> fname;
    fstream file(fname, ios::in|ios::out);
    if(!file.is_open()){
        cout << "file open is error" << '\n';
        return;
    }
    for(auto it : maps){
        it.second.fileall(file);
    }
    file.close();
}

void op0(){
    using namespace std;
    cout << "========================" << '\n';
    cout << "welcome to use next time" << '\n';
    cout << "wish you have a goot day" << '\n';
    cout << "========================" << '\n';
}

int main(){
    using namespace std;
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    while(1){
        int choice = Showmain();
        switch(choice){
            case 1: op1(); break;
            case 2: op2(); break;
            case 3: op3(); break;
            case 4: op4(); break;
            case 5: op5(); break;
            case 6: op6(); break;
            case 7: op7(); break;
            case 0: op0(); break;
        }
        if(choice == 0) break;
    }
    
    return 0;
}
