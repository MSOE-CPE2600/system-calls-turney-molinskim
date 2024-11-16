// Name, etc

// pinfo.c
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <sys/resource.h>
#include <unistd.h>
#include <errno.h>

void print_scheduler(int policy) {
    switch (policy) {
        case SCHED_OTHER:
            printf("Scheduling policy: SCHED_OTHER\n");
            break;
        case SCHED_FIFO:
            printf("Scheduling policy: SCHED_FIFO\n");
            break;
        case SCHED_RR:
            printf("Scheduling policy: SCHED_RR\n");
            break;
#ifdef SCHED_BATCH
        case SCHED_BATCH:
            printf("Scheduling policy: SCHED_BATCH\n");
            break;
#endif
#ifdef SCHED_IDLE
        case SCHED_IDLE:
            printf("Scheduling policy: SCHED_IDLE\n");
            break;
#endif
        default:
            printf("Scheduling policy: Unknown\n");
            break;
    }
}

int main(int argc, char *argv[]) {
    pid_t pid;
    int priority;
    int policy;
    struct sched_param param;

    // Determine if a process ID is provided
    if (argc > 1) {
        pid = atoi(argv[1]);
    } else {
        pid = getpid(); // Default to current process ID
    }

    // Get the priority of the specified process
    errno = 0;
    priority = getpriority(PRIO_PROCESS, pid);
    if (errno != 0) {
        perror("Error getting priority");
        return 1;
    }
    printf("Process priority: %d\n", priority);

    // Get the scheduling policy of the specified process
    policy = sched_getscheduler(pid);
    if (policy == -1) {
        perror("Error getting scheduling policy");
        return 1;
    }
    print_scheduler(policy);

    return 0;
}
