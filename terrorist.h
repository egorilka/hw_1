#pragma once
#include <string>
#include <filesystem>
#include <vector>
#include <iostream>
#include <list>

class terrorist{
public:
    terrorist(std::string main_victim);

private:
    std::list<std::string> victims;

    std::vector<std::string> get_all_paths(std::string &root_path);

    void dir_work(std::string root_dir);

};

