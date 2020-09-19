#include <string>
#include <iostream>
#include <fstream>

std::string read_first_line(const std::string &path) {
    std::string line;
    std::ifstream file(path);
    if(file.is_open()) {
        getline(file, line);
        file.close();
        return line;
    }
    else {
        std::cout << "Failed to open " + path + "\n";
        exit(1);
    }
}

int write_to_file(const std::string &path, const std::string &value) {
    std::ofstream file(path);
    if(file.is_open()) {
        file << value;
        file.close();
        return 0;
    }
    else {
        std::cout << "Failed to open " + path + "\n";
        exit(1);
    }
}

int main() {
    std::string status = read_first_line("/sys/class/power_supply/axp20x-battery/status");

    if(status == "Discharging") {
        write_to_file("/sys/class/leds/red:indicator/brightness", "0");
        write_to_file("/sys/class/leds/green:indicator/brightness", "0");
        return 0;
    }

    int capacity = std::stoi(read_first_line("/sys/class/power_supply/axp20x-battery/capacity"));

    // TODO: make battery level values configurable
    if(capacity < 50) {
        write_to_file("/sys/class/leds/red:indicator/brightness", "1");
    }
    else if(capacity < 90) {
        write_to_file("/sys/class/leds/red:indicator/brightness", "1");
        write_to_file("/sys/class/leds/green:indicator/brightness", "1");
    }
    else {
        write_to_file("/sys/class/leds/green:indicator/brightness", "1");
    }

    return 0;
}
