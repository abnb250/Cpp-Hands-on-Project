#ifndef SCORE_H
#define SCORE_H

#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>
using std::string, std::vector;

class Score{
private:
    string kind;
    double grade;
public:
    Score(): kind("unknown"), grade(0.0){}
    Score(string k, double g) : kind(k), grade(g) {}
    string get_kind() const;
    double get_grade() const;
    void set_score(double newgra);
};

#endif