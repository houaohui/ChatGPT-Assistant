#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    FILE* file = fopen("/proc/stat", "r");
    if (file == NULL) {
        perror("Error opening /proc/stat");
        return 1;
    }

    char line[128];
    unsigned long long user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;
    unsigned long long total1, total2, total_diff;
    unsigned long long idle1, idle2, idle_diff;

    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "cpu %llu %llu %llu %llu %llu %llu %llu %llu %llu %llu",
            &user, &nice, &system, &idle, &iowait, &irq, &softirq, &steal, &guest, &guest_nice) == 10) {
            total1 = user + nice + system + idle + iowait + irq + softirq + steal + guest + guest_nice;
            idle1 = idle;
            break;
        }
    }
    fclose(file);

    // Sleep for a moment to get the CPU usage difference
    sleep(1);

    file = fopen("/proc/stat", "r");
    if (file == NULL) {
        perror("Error opening /proc/stat");
        return 1;
    }

    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "cpu %llu %llu %llu %llu %llu %llu %llu %llu %llu %llu",
            &user, &nice, &system, &idle, &iowait, &irq, &softirq, &steal, &guest, &guest_nice) == 10) {
            total2 = user + nice + system + idle + iowait + irq + softirq + steal + guest + guest_nice;
            idle2 = idle;
            break;
        }
    }
    fclose(file);

    total_diff = total2 - total1;
    idle_diff = idle2 - idle1;
    double cpu_usage = (1.0 - (double)idle_diff / total_diff) * 100.0;
    printf("CPU Usage: %.2f%%\n", cpu_usage);

    return 0;
}
