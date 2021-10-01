#include "../agent.h"
#include <iostream>
#include <memory>

using namespace std;

// https://stackoverflow.com/questions/478898/how-do-i-execute-a-command-and-get-the-output-of-the-command-within-c-using-po
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

int initPlugin(Plugin &args, const string& config) {
    string cmd = args.getConfig(config + ".command", "");
    string out = exec(cmd.c_str());
    cout << out;
    return 0;
}
