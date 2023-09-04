#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <ctime>
#include <iomanip>
#include "split.h"

class TaskTracker {
private:
    std::vector<std::string> old_processes;
    std::string user_name;
    std::string date;
    std::string log_path = "";
    int plus_hours = 0;
public:
    TaskTracker(std::string name, std::string path = "") {
        user_name = name;
        log_path = path;
        old_processes = getRunningProcesses();
    }

    void update() {
        std::vector<std::string> temp_v = getRunningProcesses();
        isNew(temp_v);
        isOff(temp_v);
    }

    void saveLog(std::string line) {
        std::ofstream out(log_path + date + ".txt", std::ios::app);
        out << line + "\n";
    }
    void isNew(std::vector<std::string> temp_v) {
        for (auto& i: temp_v) {
            bool is_in = false;
            for (auto& proc: old_processes) {
                if (i == proc) {
                    is_in = true;
                    break;
                }
            }
            if (!is_in) {
                old_processes.push_back(i);
                saveLog("STARTED  AT " + getTime() + " " + i);
            }
        }
    }
    void isOff(std::vector<std::string> temp_v) {
        for (auto& i: old_processes) {
            bool is_in = false;
            for (auto& j: temp_v) {
                if (i == j) {
                    is_in = true;
                    break;
                }
            }
            if (!is_in) {
                auto itr = std::find(old_processes.begin(), old_processes.end(), i);
                if (itr != old_processes.end()) old_processes.erase(itr);
                saveLog("FINISHED AT " + getTime() + " " + i);
                break;
            }
        }
    }
    std::vector<std::string> getRunningProcesses() {
        system("top -b -n1 -w=200 > processes.txt");
        std::string line;
        std::ifstream file;
        std::vector<std::string> processes;
        int index = 0;
        file.open("processes.txt");
        if (file.is_open()) {
            while (file) {
                std::getline(file, line);
                if (index >= 7 && line != "") {
                    std::vector<std::string> v = split(line, ' ');
                    v.erase(std::remove(v.begin(), v.end(), ""), v.end());
                    if (v[1] == user_name) {
                        if (processes.size() != 0) {
                            if (processes[processes.size()-1] != v[11]) {
                                processes.push_back(v[11]);
                            }
                        } else {
                            processes.push_back(v[11]);
                        }
                    }
                }
                index++;
            }
        }
        file.close();
        return processes;
    }
    std::string getTime() {
        std::time_t time = std::time(nullptr);
        std::string datetime(100,0);
        datetime.resize(std::strftime(&datetime[0], datetime.size(), "%d/%m/%Y-%H:%M:%S", std::localtime(&time)));
        std::vector<std::string> dt = split(datetime, '-');
        std::vector<std::string> d = split(dt[0], '/');
        std::vector<std::string> t = split(dt[1], ':');
        t[0] = std::to_string(std::stoi(t[0]) + plus_hours);
        std::string output = t[0] + ":" + t[1] + ":" + t[2];
        date = d[0] + "." + d[1] + "." + d[2];
        return output;
    }
    void setPlusHours(int hours) {
        plus_hours = hours;
    }
};

int main() {
    TaskTracker task_tracker("dangel", "../LOGS/");
    task_tracker.setPlusHours(3);

    while (true) {
        task_tracker.update();
    }

    return 0;
}
