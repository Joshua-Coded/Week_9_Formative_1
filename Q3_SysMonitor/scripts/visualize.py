#!/usr/bin/env python3
"""
System Resource Visualization Tool

This program uses the sysmonitor C extension to collect system resource data
and visualizes it using matplotlib.
"""

import time
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import numpy as np
import sysmonitor

# Maximum number of points to display
MAX_POINTS = 60  # 2 minutes (120 seconds) with 2-second intervals

# Initialize data structures
timestamps = []
cpu_data = []
memory_data = []
network_rx_data = []
network_tx_data = []

# Create the figure and subplots
fig, (ax1, ax2, ax3) = plt.subplots(3, 1, figsize=(10, 8))
plt.subplots_adjust(hspace=0.4)

# Set up the plots
def setup():
    ax1.set_title('CPU Usage (%)')
    ax1.set_ylim(0, 100)
    ax1.set_xlim(0, MAX_POINTS)
    ax1.grid(True)
    
    ax2.set_title('Memory Usage (%)')
    ax2.set_ylim(0, 100)
    ax2.set_xlim(0, MAX_POINTS)
    ax2.grid(True)
    
    ax3.set_title('Network Traffic (KB/s)')
    ax3.set_ylim(0, 100)  # Will be adjusted dynamically
    ax3.set_xlim(0, MAX_POINTS)
    ax3.grid(True)
    
    # Create empty line objects
    cpu_line, = ax1.plot([], [], 'r-', label='CPU')
    mem_line, = ax2.plot([], [], 'b-', label='Memory')
    net_rx_line, = ax3.plot([], [], 'g-', label='Download')
    net_tx_line, = ax3.plot([], [], 'm-', label='Upload')
    
    ax1.legend(loc='upper right')
    ax2.legend(loc='upper right')
    ax3.legend(loc='upper right')
    
    return cpu_line, mem_line, net_rx_line, net_tx_line

# Update function for animation
def update(frame):
    # Get system metrics
    metrics = sysmonitor.monitor_system()
    
    # Append data
    timestamps.append(frame)
    cpu_data.append(metrics['cpu'])
    memory_data.append(metrics['memory'])
    
    # Convert network speeds from bytes to kilobytes
    network_rx_kb = metrics['network_rx'] / 1024.0
    network_tx_kb = metrics['network_tx'] / 1024.0
    network_rx_data.append(network_rx_kb)
    network_tx_data.append(network_tx_kb)
    
    # Limit data points to MAX_POINTS
    if len(timestamps) > MAX_POINTS:
        timestamps.pop(0)
        cpu_data.pop(0)
        memory_data.pop(0)
        network_rx_data.pop(0)
        network_tx_data.pop(0)
    
    # X-axis values (adjusted to show only the time window)
    x = range(len(timestamps))
    
    # Update the plots
    cpu_line.set_data(x, cpu_data)
    mem_line.set_data(x, memory_data)
    net_rx_line.set_data(x, network_rx_data)
    net_tx_line.set_data(x, network_tx_data)
    
    # Adjust y-axis limits for network plot
    max_net = max(max(network_rx_data, default=0), max(network_tx_data, default=0))
    ax3.set_ylim(0, max(100, max_net * 1.2))  # At least 100 KB/s or 120% of max
    
    # Update x-axis limits to create a scrolling effect
    if len(timestamps) >= MAX_POINTS:
        for ax in (ax1, ax2, ax3):
            ax.set_xlim(0, MAX_POINTS - 1)
    else:
        for ax in (ax1, ax2, ax3):
            ax.set_xlim(0, max(20, len(timestamps) - 1))
    
    return cpu_line, mem_line, net_rx_line, net_tx_line

def main():
    print("System Monitor starting...")
    print("Press Ctrl+C to exit")
    
    # Set up the plots
    cpu_line, mem_line, net_rx_line, net_tx_line = setup()
    
    # Create animation
    ani = FuncAnimation(fig, update, frames=range(1000), 
                        interval=2000, blit=True)
    
    # Show the plot
    plt.tight_layout()
    plt.show()

if __name__ == "__main__":
    main()
