#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>
#include "Score.h"
using std::string;
using std::vector;

class Student{
private:
    string num;
    string name;
    char sex;
    int age;
    string cla;
    vector<Score> v;
    double sum;
    double ave;
public:
    Student() : num("unknown"), name("unknown"), sex('b'), age(18), cla("7012") {}
    Student(string nu, string na, char se, int ag, string cl) : num(nu), name(na), sex(se), age(ag), cla(cl) {}
    void show_score();
    double get_score(string kindname) const;
    string get_name();
    void showall();
    Student& set_num(string newnum);
    Student& set_name(string newname);
    Student& set_sex(char newsex);
    Student& set_age(int newage);
    Student& set_cla(string newcla);
    bool set_score(string newkind, double newgrade);
    Student& add_sco(Score sc);
    double get_sum() const;
    double get_ave() const;
    void fileall(std::fstream& file);
    
};

bool cmpsum(const Student& a, const Student& b);

bool cmpave(const Student& a, const Student& b);


#endif

