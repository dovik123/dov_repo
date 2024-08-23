#include <iostream>
#include <cstdlib>
#include <string>
#include <array>

std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

int main() {
    std::string cmd = "nmcli -t -f ACTIVE,SSID dev wifi";
    std::string output = exec(cmd.c_str());

    if (output.find("yes:") != std::string::npos) {
        std::cout << "You are connected to a Wi-Fi network: " 
                  << output.substr(output.find("yes:") + 4) << std::endl;
    } else {
        std::cout << "You are not connected to any Wi-Fi network." << std::endl;
    }

    return 0;
}
