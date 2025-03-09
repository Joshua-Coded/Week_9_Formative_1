/**
 * File: sysmonitor.c
 * Description: C extension for Python to monitor system resources (CPU, memory, network)
 */

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// Structure to hold system metrics
typedef struct {
    double cpu_usage;
    double memory_usage;
    double network_rx_speed;
    double network_tx_speed;
} SystemMetrics;

// Function to parse /proc/stat for CPU usage
static int get_cpu_usage(unsigned long long *idle_time, unsigned long long *total_time) {
    FILE *fp;
    unsigned long long user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;
    char buffer[1024];
    
    fp = fopen("/proc/stat", "r");
    if (fp == NULL) {
        return 0;
    }
    
    if (fgets(buffer, sizeof(buffer), fp) == NULL) {
        fclose(fp);
        return 0;
    }
    
    fclose(fp);
    
    sscanf(buffer, "cpu %llu %llu %llu %llu %llu %llu %llu %llu %llu %llu",
           &user, &nice, &system, &idle, &iowait, &irq, &softirq, &steal, &guest, &guest_nice);
    
    // Calculate total and idle times
    *idle_time = idle + iowait;
    *total_time = user + nice + system + idle + iowait + irq + softirq + steal;
    
    return 1;
}

// Function to get memory usage from /proc/meminfo
static double get_memory_usage() {
    FILE *fp;
    char buffer[1024];
    unsigned long total_mem = 0, free_mem = 0, buffers = 0, cached = 0;
    double used_percentage = 0.0;
    
    fp = fopen("/proc/meminfo", "r");
    if (fp == NULL) {
        return 0.0;
    }
    
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        if (strncmp(buffer, "MemTotal:", 9) == 0) {
            sscanf(buffer, "MemTotal: %lu kB", &total_mem);
        } else if (strncmp(buffer, "MemFree:", 8) == 0) {
            sscanf(buffer, "MemFree: %lu kB", &free_mem);
        } else if (strncmp(buffer, "Buffers:", 8) == 0) {
            sscanf(buffer, "Buffers: %lu kB", &buffers);
        } else if (strncmp(buffer, "Cached:", 7) == 0) {
            sscanf(buffer, "Cached: %lu kB", &cached);
        }
    }
    
    fclose(fp);
    
    if (total_mem > 0) {
        // Calculate used memory percentage (excluding buffers/cache)
        unsigned long used_mem = total_mem - free_mem - buffers - cached;
        used_percentage = (double)used_mem / total_mem * 100.0;
    }
    
    return used_percentage;
}

// Function to get network usage from /proc/net/dev
static int get_network_usage(unsigned long *rx_bytes, unsigned long *tx_bytes) {
    FILE *fp;
    char buffer[1024];
    char interface[32];
    unsigned long rx, tx;
    
    fp = fopen("/proc/net/dev", "r");
    if (fp == NULL) {
        return 0;
    }
    
    // Skip the first two lines (headers)
    fgets(buffer, sizeof(buffer), fp);
    fgets(buffer, sizeof(buffer), fp);
    
    *rx_bytes = 0;
    *tx_bytes = 0;
    
    // Sum up all interfaces except loopback (lo)
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        sscanf(buffer, "%s %lu %*u %*u %*u %*u %*u %*u %*u %lu", interface, &rx, &tx);
        
        // Remove the colon from interface name
        char *colon = strchr(interface, ':');
        if (colon) *colon = '\0';
        
        // Skip loopback interface
        if (strcmp(interface, "lo") != 0) {
            *rx_bytes += rx;
            *tx_bytes += tx;
        }
    }
    
    fclose(fp);
    return 1;
}

// Python function: monitor_system()
static PyObject* monitor_system(PyObject *self, PyObject *args) {
    unsigned long long idle_time1, total_time1, idle_time2, total_time2;
    unsigned long rx_bytes1, tx_bytes1, rx_bytes2, tx_bytes2;
    double cpu_usage, memory_usage;
    double rx_speed, tx_speed;
    
    // Get initial readings
    if (!get_cpu_usage(&idle_time1, &total_time1) || 
        !get_network_usage(&rx_bytes1, &tx_bytes1)) {
        return PyErr_SetFromErrno(PyExc_OSError);
    }
    
    // Wait for 2 seconds
    sleep(2);
    
    // Get new readings
    if (!get_cpu_usage(&idle_time2, &total_time2) || 
        !get_network_usage(&rx_bytes2, &tx_bytes2)) {
        return PyErr_SetFromErrno(PyExc_OSError);
    }
    
    // Calculate CPU usage
    unsigned long long idle_diff = idle_time2 - idle_time1;
    unsigned long long total_diff = total_time2 - total_time1;
    
    if (total_diff > 0) {
        cpu_usage = 100.0 * (1.0 - ((double)idle_diff / total_diff));
    } else {
        cpu_usage = 0.0;
    }
    
    // Get memory usage
    memory_usage = get_memory_usage();
    
    // Calculate network speed (bytes per second)
    rx_speed = (double)(rx_bytes2 - rx_bytes1) / 2.0; // 2 seconds interval
    tx_speed = (double)(tx_bytes2 - tx_bytes1) / 2.0;
    
    // Return the metrics as a Python dictionary
    return Py_BuildValue("{s:d,s:d,s:d,s:d}",
                         "cpu", cpu_usage,
                         "memory", memory_usage,
                         "network_rx", rx_speed,
                         "network_tx", tx_speed);
}

// Module method definitions
static PyMethodDef SysMonitorMethods[] = {
    {"monitor_system", monitor_system, METH_NOARGS, 
     "Monitor system resources (CPU, memory, network) with a 2-second interval."},
    {NULL, NULL, 0, NULL}  // Sentinel
};

// Module definition
static struct PyModuleDef sysmonitormodule = {
    PyModuleDef_HEAD_INIT,
    "sysmonitor",       // Module name
    "System monitoring module that captures CPU, memory, and network usage.",
    -1,                 // Module state is global
    SysMonitorMethods
};

// Initialize the module
PyMODINIT_FUNC PyInit_sysmonitor(void) {
    return PyModule_Create(&sysmonitormodule);
}
