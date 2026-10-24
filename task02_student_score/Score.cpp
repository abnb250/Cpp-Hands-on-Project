#include "Score.h"

string Score::get_kind() const{
    return kind;
}

double Score::get_grade() const{
    return grade;
}

void Score::set_score(double newgra){
    grade = newgra;
    return;
}

