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
using namespace chrono_literals;
namespace fs = filesystem;

atomic_bool done = false;

void signalHandler( int signum ) {
   cout << "Interrupt signal (" << signum << ") received.\n";

   // cleanup and close up stuff here
   // terminate program

   exit(signum);
}

int main() {
    signal(SIGINT, signalHandler);

    ScannerEventListener scanner_event_listener;

    if (scanner_event_listener.Open() not_eq STATUS_OK) {
        cout << "scanner_status=not_active." << endl;
        return STATUS_ERROR;
    }

    cout << "scanner_status=active." << endl;

    scanner_event_listener.GetScanners();

    while (not done) {
        cout << "main_thread=works INFO" << endl;

        this_thread::sleep_for(10000ms);
    }

    return 0;
}
