# System Monitoring Tool

## Overview

This project implements a system monitoring tool that captures CPU usage, memory usage, and network traffic in real-time. It consists of a C extension module for Python that collects system metrics with a 2-second sampling interval, and a Python visualization script that displays the metrics in real-time graphs.

## Features

- Real-time monitoring of system resources:
  - CPU usage percentage
  - Memory usage percentage
  - Network traffic (upload/download speeds in KB/s)
- C extension for efficient data collection from `/proc` filesystem
- 2-second sampling interval for accurate measurements
- Real-time visualization using matplotlib
- Multi-threaded operation

## Directory Structure

```
Q3_SysMonitor/
├── Makefile              # Build script
├── README.md             # This documentation
├── include/              # Header files directory
├── src/                  # Source files directory
│   ├── sysmonitor.c      # C extension source code
│   └── setup.py          # Python setup script
└── scripts/              # Python scripts directory
    └── visualize.py      # Python visualization script
```

## Requirements

- Python 3.x with development headers
- GCC compiler
- Python packages:
  - matplotlib
  - numpy
- Linux operating system with `/proc` filesystem

## Building

To build the C extension module:

```bash
make
```

This will compile the C extension using Python's setuptools and make it available for import in Python.

## Usage

After building the extension, run the visualization script:

```bash
python3 scripts/visualize.py
```

This will launch a graphical interface showing three real-time plots:
1. CPU usage over time
2. Memory usage over time
3. Network traffic (download/upload) over time

The window will continuously update with new data every 2 seconds.

## Implementation Details

### C Extension (`sysmonitor.c`)

The C extension collects system metrics by reading from the proc filesystem:

- **CPU Usage**: Reads `/proc/stat` and calculates the percentage of CPU time spent in non-idle states
- **Memory Usage**: Reads `/proc/meminfo` and calculates the percentage of used memory (excluding buffers/cache)
- **Network Traffic**: Reads `/proc/net/dev` and calculates the bytes received/transmitted per second

The extension implements a Python module with a `monitor_system()` function that:
1. Takes initial readings
2. Waits for 2 seconds
3. Takes new readings
4. Calculates the metrics based on the differences
5. Returns the metrics as a Python dictionary

### Python Visualization (`visualize.py`)

The visualization script:
1. Imports the C extension module
2. Creates a matplotlib figure with three subplots
3. Uses matplotlib's animation capabilities to update the plots in real-time
4. Maintains a scrolling window of data points
5. Dynamically adjusts the y-axis scale for the network plot based on traffic volume

## Customization

You can modify the following aspects of the tool:

- **Sampling Interval**: Change the `sleep(2)` call in the C extension to adjust the sampling interval
- **Display Window**: Modify the `MAX_POINTS` constant in the visualization script to change how many data points are displayed
- **Colors and Styling**: Adjust the plot colors and styles in the visualization script

## Troubleshooting

- If you encounter permission issues when reading `/proc` files, make sure you have the necessary permissions
- If the extension fails to build, ensure you have Python development headers installed
- If the visualization doesn't show data, check that the C extension is correctly built and can be imported

## Cleaning Up

To clean build artifacts:

```bash
make clean
```

This will remove the compiled C extension and other build artifacts.
