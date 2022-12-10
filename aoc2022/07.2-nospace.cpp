#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdio>

/* DEFINITIONS */
#define SPACE 40000000;

typedef long long lint;

class node {
    std::string name;
    char type;  // 'd' for dir and 'f' for file
    lint size;  // dirs have zero size at first, but they will get total after
    node *parent;   // parent node
    std::vector <node *> children;
    int index;
    public:
        node (std::string nm, char tp, lint sz) {
            name = nm;
            type = tp;
            size = sz;
            parent = NULL;
            children = std::vector <node *> ();
            index = -1;
        }
        std::string get_name();
        void print_children();
        node *get_parent();
        node *get_child(std::string name);
        void add_child(node *new_child);
        lint get_size();
        lint find_mindir(lint required_space);
        void destroy_node();
};

std::string node::get_name() {
    return this->name;
}

void node::print_children() {
    for (node *child : this->children)
        std::cout << child->get_name() << ", ";
    std::cout << std::endl;
}

void node::add_child(node *new_child) {
    this->children.push_back(new_child);
    new_child->parent = this;
    new_child->index = (int) this->children.size() - 1;
}

node* node::get_parent() {
    return this->parent;
}

// if found, it returns the child node with that name
// if not found, it returns the same node
node* node::get_child(std::string child_name) {
    for (node *child : this->children)
        if (child->name == child_name)
            return child;
    return this;
}

void node::destroy_node() {
    for (node *child : this->children) {
        child->destroy_node();
    }
    //this->parent->children.erase(this->parent->children.begin() + this->index);
    delete this;
}


lint node::get_size() {
    lint sz = this->size;
    for (node *child : this->children)
        sz += child->get_size();
    return sz;
}

// global variable because I am lazy
std::vector <lint> dirs_sizes;
lint node::find_mindir(lint required_space) {
    lint sz = this->size;
    for (node *child : this->children)
        sz += child->find_mindir(required_space);
    if (sz >= required_space && this->type == 'd')
        dirs_sizes.push_back(sz);
    return sz;
}

lint find_min(std::vector <lint> array) {
    lint min = 1000000000000;
    for (lint n : array)
        if (n < min)
            min = n;
    return min;
}

int main(int argc, char *argv[]) {

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <file>" << std::endl;
        return EXIT_FAILURE;   // failure
    }

    std::ifstream InputFile(argv[1]);

    /* read until end of file */
    std::string line;
    node *root = new node("/", 'd', 0), *pwd = root, *aux;
    while (std::getline(InputFile, line)) {
        //std::cout << "linha " << i++ << ": " << line << std::endl;
        //std::cout << "pwd: " << pwd->get_name() << std::endl;
        //std::cout << "pwd children: ";
        //pwd->print_children();
        if (line[0] == '$') {   // we have a command
            std::string cmd = line.substr(2, 2), arg;
            if (cmd == "cd") {
                std::string arg = line.substr(5, line.npos);
                if (arg == "/")
                    pwd = root;
                else if (arg == "..") {
                    if (pwd != root)
                        pwd = pwd->get_parent();
                }
                else {
                    aux = pwd;
                    pwd = pwd->get_child(arg);
                    if (pwd == aux)
                        std::cerr << "cd: " << arg << ": No such file or directory\n";
                }
            }
        }
        else if (line.substr(0, 3) == "dir") {  // we have a directory
            std::string dir_name = line.substr(4, line.npos);
            //std::cout << "we have a dir" << std::endl;
            //std::cout << "dir_name = " << dir_name << std::endl;
            aux = pwd->get_child(dir_name);
            if (aux == pwd) {   // directory not yet added as a node
                aux = new node(dir_name, 'd', 0);
                pwd->add_child(aux);
            }
        }
        else {  // we have a file
            int sz; std::string file_name;
            std::stringstream ss;
            ss << line;
            ss >> sz >> file_name;
            aux = pwd->get_child(file_name);
            if (aux == pwd) {   // file not yet added as a node
                aux = new node(file_name, 'f', (lint) sz);
                pwd->add_child(aux);
            }
        }
    }
    lint root_size = root->get_size();
    lint required_space = root_size - SPACE;
    std::cout << "root size = " << root_size << std::endl;
    root->find_mindir(required_space);
    std::cout << "min dir size = " << find_min(dirs_sizes) << std::endl;
    root->destroy_node();   // delete everything
}
