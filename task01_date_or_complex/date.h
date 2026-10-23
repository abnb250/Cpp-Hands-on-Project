#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>

class Date{
private:
    int year;
    int month;
    int day;
    bool isok() const;
public:
    Date(int y = 2000, int m = 1, int d = 1): year(y), month(m), day(d) {
        if(!isok()){year = 2000; month = 1; day = 1;}
    }
    static bool isleap(int y);
    Date addday(int num) const;
    Date subday(int num) const;
    int getday() const;
    int getyear() const;
    int getmonth() const;
    std::string getdate() const;
    friend std::ostream& operator<<(std::ostream& os, const Date& a);
    bool operator==(const Date& b) const;
    bool operator!=(const Date& b) const;
    bool operator<(const Date& b) const;
};

#endif