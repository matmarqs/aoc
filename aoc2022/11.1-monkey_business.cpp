#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <functional>

/* DEFINITIONS */


void print_vector(std::vector <int> const &a) {
   for (int i = 0; i < (int) a.size(); i++)
       std::cout << a.at(i) << ' ';
   std::cout << std::endl;
}


class monkey {
    std::vector <int> items;
    char op;
    std::string snd;
    int test, m_true, m_false;
public:
    int num;
    int inspected;
    monkey (int n, std::vector <int> the_items,
            char opr, std::string snd_p, int t, int tru, int fal) {
        num = n;
        items = the_items;
        op = opr;
        snd = snd_p;
        test = t;
        m_true = tru;
        m_false = fal;
        inspected = 0;
    }
    int operation(int old);
    void info();
    std::string items_str();
    void inspect(std::vector <monkey *> &monkeys);
    void turn(std::vector <monkey *> &monkeys);
};


std::string monkey::items_str() {
    std::stringstream ss;
    int n = (int) items.size();
    for (int i = 0; i < n; i++) {
        if (i == n-1)
           ss << this->items.at(i);
        else
           ss << this->items.at(i) << ", ";
    }
    return ss.str();
}


void monkey::inspect(std::vector <monkey *> &monkeys) {
    int worry = items[0];
    worry = operation(worry) / 3;
    if (worry % test == 0)
        monkeys[m_true]->items.push_back(worry);
    else
        monkeys[m_false]->items.push_back(worry);
    items.erase(items.begin());
    inspected++;
}


void monkey::turn(std::vector <monkey *> &monkeys) {
    while (!items.empty())
        inspect(monkeys);
}


void monkey::info() {
    std::cout << "Monkey " << this->num << ":" << std::endl;
    std::cout << "  Starting items: " << this->items_str() << std::endl;
    std::cout << "  Operation: new = old "
              << this->op << " " << this->snd << std::endl;
    std::cout << "  Test: divisible by " << this->test << std::endl;
    std::cout << "    If true: throw to monkey " << this->m_true << std::endl;
    std::cout << "    If false: throw to monkey " << this->m_false << std::endl;
}


int monkey::operation(int old) {
    if (this->op == '*') {
        if (this->snd == "old")
            return old * old;
        else
            return old * std::stoi(this->snd);
    }
    else {  // op == '+'
        if (this->snd == "old")
            return old + old;
        else
            return old + std::stoi(this->snd);
    }
}


std::vector <int> tokenize(std::string s, std::string delim) {
    std::vector <int> tokens; std::string token;
    size_t pos;
    do {
        pos = s.find(delim);
        token = s.substr(0, pos);
        tokens.push_back(std::stoi(token));
        s.erase(0, pos + delim.length());
    } while (pos != std::string::npos);
    return tokens;
}


void print_inspect(std::vector <monkey *> monkeys) {
    for (monkey *m : monkeys)
        std::cout << "Monkey " << m->num << " inspected items "
                  << m->inspected << " times." << std::endl;
}


// find max element and delete it
int max_elem(std::vector <int> &v) {
    int i_max = 0, sz = (int) v.size();
    for (int i = 1; i < sz; i++)
        if (v[i] > v[i_max])
            i_max = i;
    int max = v[i_max];
    v.erase(v.begin() + i_max);
    return max;
}


int main(int argc, char *argv[]) {

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <file>" << std::endl;
        return EXIT_FAILURE;   // failure
    }

    std::ifstream InputFile(argv[1]);

    /* read until end of file */
    std::vector <monkey *> monkeys; monkey *M;
    int num = 0;
    std::vector <int> items;
    char op = '*'; std::string snd;
    int t = 0, tru = 0, fal = 0;

    std::string line; int i = 0;
    while (std::getline(InputFile, line)) {
        switch (i) {
            case 0:
                num = line[7] - '0';
                //std::cout << num << std::endl;
                break;
            case 1:
                //std::cout << line.substr(18, line.npos) << std::endl;
                items = tokenize(line.substr(18), ", ");
                break;
            case 2:
                op = line[23];
                //std::cout << op << std::endl;
                snd = line.substr(25, line.npos);
                break;
            case 3:
                t = std::stoi(line.substr(21));
                break;
            case 4:
                tru = line[line.length() - 1] - '0';
                break;
            case 5:
                fal = line[line.length() - 1] - '0';
                break;
            default:
                i = -1;
                M = new monkey (num, items, op, snd, t, tru, fal);
                monkeys.push_back(M);
                break;
        }
        i++;
    }
    // last monkey
    M = new monkey (num, items, op, snd, t, tru, fal);
    monkeys.push_back(M);

    // debugging
    //for (i = 0; i < (int) monkeys.size(); i++) {
    //    monkeys[i]->info();
    //    if (i != (int) monkeys.size() - 1)
    //        std::cout << std::endl;
    //}

    int sz = (int) monkeys.size();
    for (int round = 0; round < 20; round++)
        for (i = 0; i < sz; i++) {
            monkeys[i]->turn(monkeys);
        }

    print_inspect(monkeys);

    std::vector <int> inspections;
    for (i = 0; i < sz; i++)
        inspections.push_back(monkeys[i]->inspected);

    int max1 = max_elem(inspections);
    int max2 = max_elem(inspections);

    std::cout << "monkey business = " << max1 * max2 << std::endl;

    // free space
    for (monkey *m : monkeys)
        delete m;
}
