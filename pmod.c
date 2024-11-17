/************************************************
* Name: Marshall Molinski
* Assignment Name: Lab 9 - System Calls
* Section: CPE2600 111
************************************************/
// pmod.c
#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <sys/resource.h>

int main() {
    int current_priority;
    int new_priority;
    struct timespec sleep_time;

    // Get the current priority
    current_priority = getpriority(PRIO_PROCESS, 0);
    if (current_priority == -1 && errno != 0) {
        perror("Error getting current priority");
        return 1;
    }

    // Reduce the priority by 10
    new_priority = current_priority + 10; // A higher number indicates lower priority
    if (setpriority(PRIO_PROCESS, 0, new_priority) == -1) {
        perror("Error setting new priority");
        return 1;
    }
    printf("Priority reduced by 10. New priority: %d\n", new_priority);

    // Define sleep time (1,837,272,638 nanoseconds)
    sleep_time.tv_sec = 1;  // 1 second
    sleep_time.tv_nsec = 837272638;  // Remaining nanoseconds to reach the full time

    // Sleep for the specified time
    if (nanosleep(&sleep_time, NULL) == -1) {
        perror("Error during nanosleep");
        return 1;
    }

    printf("Goodbye!\n");

    return 0;
}
