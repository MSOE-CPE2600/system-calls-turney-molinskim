// Name, etc

// info.c

#define _GNU_SOURCE
#include <stdio.h>
#include <time.h>
#include <sys/sysinfo.h>
#include <sys/utsname.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    struct timespec ts;
    struct utsname uname_data;
    struct sysinfo sys_info;
    long num_procs;
    long page_size;
    long total_memory;
    long free_memory;

    // Get current time in nanoseconds
    if (clock_gettime(CLOCK_REALTIME, &ts) == 0) {
        printf("Current time (nanoseconds): %ld\n", ts.tv_sec * 1000000000L + ts.tv_nsec);
    } else {
        perror("clock_gettime");
    }

    // Get system information with uname
    if (uname(&uname_data) == 0) {
        printf("System network name: %s\n", uname_data.nodename);
        printf("Operating system: %s\n", uname_data.sysname);
        printf("OS release: %s\n", uname_data.release);
        printf("OS version: %s\n", uname_data.version);
        printf("Hardware type: %s\n", uname_data.machine);
    } else {
        perror("uname");
    }

    // Get the number of processors
    num_procs = sysconf(_SC_NPROCESSORS_ONLN);
    if (num_procs != -1) {
        printf("Number of CPUs: %ld\n", num_procs);
    } else {
        perror("sysconf - CPUs");
    }

    // Get page size and physical memory details
    page_size = sysconf(_SC_PAGESIZE);
    if (page_size == -1) {
        perror("sysconf - page size");
    }

    if (sysinfo(&sys_info) == 0) {
        total_memory = sys_info.totalram * page_size;
        free_memory = sys_info.freeram * page_size;
        printf("Total physical memory (bytes): %ld\n", total_memory);
        printf("Free memory (bytes): %ld\n", free_memory);
    } else {
        perror("sysinfo");
    }

    return 0;
}
