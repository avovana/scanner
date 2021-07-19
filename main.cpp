#include <iostream>
#include <atomic>
#include <thread>
#include <chrono>

#include <signal.h>
#include <string.h>


#include "ConsoleSampleEventListener.h"

using namespace std;
using namespace std::chrono_literals;

atomic_bool done = false;

static void hdl (int sig, siginfo_t *siginfo, void *context)
{
    printf ("Sending PID: %ld, UID: %ld\n", (long)siginfo->si_pid, (long)siginfo->si_uid);
    done = true;
}


int main()
{
    // signal options
    struct sigaction act;
    memset (&act, '\0', sizeof(act));
    act.sa_sigaction = &hdl; /* Use the sa_sigaction field because the handles has two additional parameters */
    act.sa_flags = SA_SIGINFO; /* The SA_SIGINFO flag tells sigaction() to use the sa_sigaction field, not sa_handler. */
    if (sigaction(SIGTERM, &act, NULL) < 0) {
        std::cout << "smth" << std::endl;
        return 1;
    }

    ScannerEventListener sel;

    if(STATUS_OK != sel.Open())
    {
        std::cout << "Corescanner service is not Active." << std::endl;
        return STATUS_ERROR;
    }

    sel.GetScanners();

    while (not done) {
        std::this_thread::sleep_for(100ms);
    }

    sel.Close();

    return 0;
}
