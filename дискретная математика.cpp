#include <iostream>
#include <string>
#include <set>
#include <map>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <vector> 
using namespace std;
class operations {
private:
    map<char, set<char >> sets;
    bool setname(char name) {return name >= 'A' && name <= 'Z';}
    bool set_el(char element) {return element >= 32 && element <= 126;}
    bool setexists(char name) {return sets.find(name) != sets.end();}
    void powersets(const vector<char>& elements, vector<set<char>>& res,
        set<char>& sset_t, int index) {
        if (index == elements.size()) {res.push_back(sset_t);return;}
        powersets(elements, res, sset_t, index + 1);
        sset_t.insert(elements[index]);
        powersets(elements, res, sset_t, index + 1);
        sset_t.erase(elements[index]);}
public:
    void newset(char name) {
        if (!setname(name)) {cout << "Set name must be letter A-Z" << endl; return;}
        if (setexists(name)) {cout << "Set " << name << " already exists" << endl; return;}
        sets[name] = set<char>();
        cout << "Set " << name << " created" << endl;}
    void delset(char name) {
        if (!setexists(name)) {cout << "Set " << name << " not exists" << endl;return;}
        sets.erase(name);
        cout << "Set " << name << " deleted" << endl;}
    void add_el(char set_name, char elem) {
        if (!setexists(set_name)) { cout << "Set " << set_name << " not exists" << endl;return;}
        if (!set_el(elem)) {cout << "Element cannot be entered" << endl;return;}
        auto& ssets = sets[set_name];
        if (ssets.find(elem) != ssets.end()) {cout << "Element " << elem << " already in set " << set_name << endl;return;}
        ssets.insert(elem);
        cout << "Element " << elem << " added to set " << set_name << endl;}
    void rem_el(char set_name, char elem) {
        if (!setexists(set_name)) {cout << "Set " << set_name << " not exists" << endl;return;}
        auto& sset = sets[set_name];
        if (sset.find(elem) == sset.end()) {cout << "Element " << elem << " not found in set " << set_name << endl;return;}
        sset.erase(elem);
        cout << "Element " << elem << " removed from set " << set_name << endl;}
    void pow_set(char name) {
        if (!setexists(name)) {cout << "Set " << name << " not exists" << endl;return;}
        const auto& sset = sets[name];
        vector<char> elements(sset.begin(), sset.end());
        vector<set<char>> allsets;
        set<char> sset_allt;
        powersets(elements, allsets, sset_allt, 0);
        cout << "Pow set of " << name << ":" << endl;
        for (const auto& one_set : allsets) {cout << "{";
            for (auto el = one_set.begin(); el != one_set.end(); ++el) {
                cout << *el;
                if (next(el) != one_set.end()) {cout << ", ";}}
            cout << "}" << endl;}}
    void see_sets(const string& set_name = "") {
        if (set_name.empty()) {
            if (sets.empty()) {cout << "No sets" << endl;return;}
            for (const auto& pair : sets) {
                cout << pair.first << ": {";
                for (auto el = pair.second.begin(); el != pair.second.end(); ++el) {cout << *el;
                    if (next(el) != pair.second.end()) {cout << ", ";}}
                cout << "}" << endl;}}
        else {
            char name = set_name[0];
            if (!setexists(name)) {cout << "Set " << name << " not exists" << endl;return;}
            const auto& sset = sets[name];
            cout << name << ": {";
            for (auto el = sset.begin(); el != sset.end(); ++el) {cout << *el;
                if (next(el) != sset.end()) {cout << ", ";}}
            cout << "}" << endl;}}
    void union_sets(char a, char b) {
        if (!setexists(a) || !setexists(b)) {cout << "One of sets not exists" << endl;return;}
        set<char> res;
        set_union(sets[a].begin(), sets[a].end(),sets[b].begin(), sets[b].end(),inserter(res, res.begin()));
        cout << "Union " << a << " + " << b << ": {";
        for (auto el = res.begin(); el != res.end(); ++el) {cout << *el;
            if (next(el) != res.end()) {cout << ", ";}}
        cout << "}" << endl;}
    void intersection_sets(char a, char b) {
        if (!setexists(a) || !setexists(b)) {cout << "One of sets not exists" << endl;return;}
        set<char> res;
        set_intersection(sets[a].begin(), sets[a].end(),sets[b].begin(), sets[b].end(),inserter(res, res.begin()));
        cout << "Intersection " << a << " & " << b << ": {";
        for (auto el = res.begin(); el != res.end(); ++el) {cout << *el;
            if (next(el) != res.end()) {cout << ", ";}}
        cout << "}" << endl;}
    void difference_sets(char a, char b) {
        if (!setexists(a) || !setexists(b)) {cout << "One of sets not exists" << endl;return;}
        set<char> res;
        set_difference(sets[a].begin(), sets[a].end(),sets[b].begin(), sets[b].end(),inserter(res, res.begin()));
        cout << "Difference " << a << " - " << b << ": {";
        for (auto el = res.begin(); el != res.end(); ++el) {cout << *el;
            if (next(el) != res.end()) {cout << ", ";}}
        cout << "}" << endl;}
    void in_set(char a, char b) {
        if (!setexists(a) || !setexists(b)) {cout << "One of sets not exists" << endl;return;}
        bool res = includes(sets[b].begin(), sets[b].end(),sets[a].begin(), sets[a].end());
        cout << (res ? "true" : "false") << endl;}
    void equal_set(char a, char b) {
        if (!setexists(a) || !setexists(b)) {cout << "One of sets not exists" << endl;return;}
        bool result = (sets[a] == sets[b]);
        cout << (result ? "true" : "false") << endl;}
};
int main() {
    operations operation;
    string oper;
    cout << "Set operations" << endl;
    cout << "Operations: new, del, add, rem, pow, see, +, &, -, <, =" << endl;
    while (true) {
        cout << "-- ";
        getline(cin, oper);
        oper.erase(0, oper.find_first_not_of(' '));
        oper.erase(oper.find_last_not_of(' ') + 1);
        if (oper.empty()) continue;
        istringstream iss(oper);
        string opper;
        iss >> opper;
        if (opper == "new") {
            char name;
            if (iss >> name) operation.newset(name);
            else cout << "Enter: new A" << endl;
        }
        else if (opper == "del") {
            char name;
            if (iss >> name) operation.delset(name);
            else cout << "Enter: del A" << endl;
        }
        else if (opper == "add") {
            char name, elem;
            if (iss >> name >> elem) operation.add_el(name, elem);
            else cout << "Enter: add A x" << endl;
        }
        else if (opper == "rem") {
            char name, elem;
            if (iss >> name >> elem) operation.rem_el(name, elem);
            else cout << "Enter: rem A x" << endl;
        }
        else if (opper == "pow") {
            char name;
            if (iss >> name) operation.pow_set(name);
            else cout << "Enter: pow A" << endl;
        }
        else if (opper == "see") {
            string arg;
            if (iss >> arg) operation.see_sets(arg);
            else operation.see_sets();
        }
        else if (oper.find('+') != string::npos) {
            istringstream iss(oper);
            char a, op, b;
            if (iss >> a >> op >> b && op == '+') {operation.union_sets(a, b);}
            else {cout << "Enter: A + B" << endl;}}
        else if (oper.find('&') != string::npos) {
            istringstream iss(oper);
            char a, op, b;
            if (iss >> a >> op >> b && op == '&') {operation.intersection_sets(a, b);}
            else {cout << "Enter: A & B" << endl;}}
        else if (oper.find('-') != string::npos && oper.find("rem") == string::npos) {
            istringstream iss(oper);
            char a, op, b;
            if (iss >> a >> op >> b && op == '-') {operation.difference_sets(a, b);}
            else {cout << "Enter: A - B" << endl;}}
        else if (oper.find('<') != string::npos) {
            istringstream iss(oper);
            char a, op, b;
            if (iss >> a >> op >> b && op == '<') {operation.in_set(a, b);}
            else {cout << "Enter: A < B" << endl;}}
        else if (oper.find('=') != string::npos) {
            istringstream iss(oper);
            char a, op, b;
            if (iss >> a >> op >> b && op == '=') {operation.equal_set(a, b);}
            else {cout << "Enter: A = B" << endl;}}
        else {
            cout << "Unknown operation: " << oper<< endl;
            cout << "Operations: new, del, add, rem, pow, see, +, &, -, <, =" << endl;}}
    cout << "Program finished" << endl;return 0;
}