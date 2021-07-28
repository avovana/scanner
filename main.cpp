#include <iostream>
#include <atomic>
#include <thread>
#include <chrono>
#include <filesystem>
#include <csignal>
#include <fstream>

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

#include "ConsoleSampleEventListener.h"

using namespace std;
using namespace std::chrono_literals;
namespace fs = std::filesystem;

atomic_bool done = false;


void signalHandler( int signum ) {
   std::cout << "Interrupt signal (" << signum << ") received.\n";

   // cleanup and close up stuff here
   // terminate program

   exit(signum);
}

int main() {
    signal(SIGINT, signalHandler);

    ScannerEventListener scanner_event_listener;

    if (STATUS_OK != scanner_event_listener.Open()) {
        std::cout << "Corescanner service is not Active." << std::endl;
        return STATUS_ERROR;
    }

    scanner_event_listener.GetScanners();

    // Wait scanner for connect. active waiting
    while (not scanner_event_listener.scanner_attached) {
        std::cout << "not scanner_attached" << std::endl;
        std::this_thread::sleep_for(1000ms);
    }

    const char *homedir;

    if ((homedir = getenv("HOME")) == NULL) {
        std::cout << "get homedir" << std::endl;
        homedir = getpwuid(getuid())->pw_dir;
    }

    std::cout << "homedir: " << homedir << std::endl;
    std::string homedir_str = homedir;
    homedir_str += "/slave_controller_pid.txt";
    cout<<"333" << std::endl;

    std::cout << "__homedir_str_4_: " << homedir_str << std::endl;
    bool pid_file_exists = false;
    cout<<"3335" << std::endl;
    std::cout<<"0" <<std::endl;

    int pid = 0;

    while (not pid_file_exists) {
        cout<<"1"<<std::endl;
        ifstream ifile;
        cout<<"2"<<std::endl;
        ifile.open(homedir_str);
        cout<<"3"<<std::endl;

        if(ifile) {
            cout<<"file exists"<<std::endl;
            string pid_str;
            std::getline(ifile, pid_str);

            pid = stoi(pid_str);

            pid_file_exists = true;
        } else {
            cout<<"file doesn't exist"<<std::endl;
        }
        cout<<"5"<<std::endl;
        std::this_thread::sleep_for(1000ms);
        cout<<"6"<<std::endl;
    }

    auto res = kill(pid, 5);
    std::cout << "res: " << res << std::endl;
    std::cout << "errno: " << errno << std::endl;

    while (not done) {
        std::cout << "in while" << std::endl;

        std::this_thread::sleep_for(1000ms);
    }

    scanner_event_listener.Close();

    return 0;
}
