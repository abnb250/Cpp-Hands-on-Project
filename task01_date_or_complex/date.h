#include <iostream>
#include <algorithm>
#include <cmath>
#include <stdexcept>

#ifndef DATE_H
#define DATE_H

bool okdate(int y, int m, int d);


class Date{
private:
    int year;
    int month;
    int day;
    void update();
public:
    static bool isleap(int y);
    Date() : year(2026), month(10), day(21) {}
    Date(int y, int m, int d) : year(y), month(m), day(d) {
        if(!okdate(y, m, d)) throw std::runtime_error("date isn't right");
    }
    int get_y() const;
    int get_m() const;
    int get_d() const;
    Date& operator +=(int addday);
    Date& operator -=(int subday);
};



#endif