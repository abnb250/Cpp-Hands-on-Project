#ifndef TEXTSTORAGE_H
#define TEXTSTORAGE_H

#include "Libary.h"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <memory>
#include <stdexcept>
#include <iomanip>

class TextStorage : public Storage{
public:
    ~TextStorage() {}
    void save(std::vector<std::unique_ptr<LibaryItem>>& itmes) override;
    std::vector<std::unique_ptr<LibaryItem>> load() override;
};

#endif