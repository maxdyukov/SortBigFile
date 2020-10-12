#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <fstream>
#include <algorithm>
#include <utility>


using namespace std;

ofstream result("out.txt");
map<string, fstream *> file_map;

vector<string> names_files = {"t0.txt", "t1.txt", "t2.txt", "t3.txt"};
vector<int> vec_num(names_files.size());

pair<bool, int> getFromFile(const string &name) {
    auto it = file_map.find(name);
    int k;
    if (!it->second->eof()) {
       *(it->second) >> k;
       return make_pair(true, k);
    }
    it->second->close();
    return make_pair(false, -1);
}

void writeOutFile(int i) {
    if (result.is_open()) {
        result << i << " ";
    }
}

int main() {
    for(auto &i : names_files) {
        fstream *file = new fstream(i);
        file_map.emplace(i, file); 
    }
    bool firstTime = true;
    map<string, int> income;
    for(auto item : file_map) {
        auto tempPair = getFromFile(item.first);
        if (tempPair.first) {
            income[item.first] = tempPair.second;
        }
        else {
            file_map.erase(item.first);
        }
    }
    while(file_map.size() > 0) {
        auto minIt = min_element(income.begin(), income.end(), [](const pair<string, int> &lhs, 
                                    const pair<string, int> &rhs) {return lhs.second < rhs.second;});
        writeOutFile(minIt->second);
        auto tempPair = getFromFile(minIt->first);
        if (tempPair.first) {
            income[minIt->first] = tempPair.second;
        }
        else {
            file_map.erase(minIt->first);
            income.erase(minIt->first);
        }
           // income.find(minIt.first) = getFromFile(minIt.first).second;
            
        
    }
    
	return 0;
}