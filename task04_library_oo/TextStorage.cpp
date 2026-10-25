#include "TextStorage.h"
#include <fstream>
#include <sstream>

void TextStorage::save(std::vector<std::unique_ptr<LibaryItem>>& items) {
    std::string na = "data.txt";
    std::ofstream os(na);
    if(!os.is_open()){
        throw std::runtime_error("file open failed");
    }

    for(auto &x : items){
        os << "=======================" << '\n';
        os << "kind  : " << x->kind() << '\n';
        os << "name  : " << x->getname() << '\n';
        os << "id    : " << x->getid() << '\n';
        os << "status: " << x->Check() << '\n';
        os << "=======================" << '\n';
    }
    
    if(!os){
        throw std::runtime_error("file save failed");
    }

}

std::vector<std::unique_ptr<LibaryItem>> TextStorage::load() {
    using std::string;
    using std::stringstream;
    string na = "data.txt";
    std::ifstream is(na);
    if(!is.is_open()){
        throw std::runtime_error("file open failed");
    }

    std::vector<std::unique_ptr<LibaryItem>> items;
    string line;
    std::size_t linenum;
    int part = 1;
    string nkind, nname, nid, nstatus;

    while(getline(is, line)){
        if(line.empty()) continue;
        if(line == "=======================") continue;
        string res;
        int pos = 0;
        int l = line.size();
        for(int i = 0; i < l; i++){
            if(line[i] == ':'){
                pos = i;
                break;
            }
        }
        pos += 2;
        for(int i = pos; i < l; i++){
            res += line[i];
        }
        if(part == 1){
            nkind = res;
        }
        else if(part == 2){
            nname = res;
        }
        else if(part == 3){
            nid = res;
        }
        else if(part == 4){
            nstatus = res;
            int x = stoi(nstatus);
            bool y = (x == 1 ? true : false);
            part = 0;
            std::unique_ptr<LibaryItem> item;
            if(nkind == "Book"){
                Book tmp(nid, nname, y, nkind);
                item = std::make_unique<Book>(tmp);
            }
            else if(nkind == "Magazine"){
                Magazine tmp(nid, nname, y, nkind);
                item = std::make_unique<Magazine>(tmp);
            }
            else{
                throw std::runtime_error("unknown kind: " + nkind);
            }
            items.push_back(std::move(item));
        }
        part++;
    }
    

    if(!is.bad()){
        throw std::runtime_error("file load failed");
    }

    return items;
}