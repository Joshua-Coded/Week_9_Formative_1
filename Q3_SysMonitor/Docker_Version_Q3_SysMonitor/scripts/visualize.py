#!/usr/bin/env python3
"""
System Resource Visualization Tool

This program uses the sysmonitor C extension to collect system resource data
and visualizes it using matplotlib.
"""
import os
import time
import sys
import matplotlib.pyplot as plt
import numpy as np

# Add current directory to Python path to find the module
sys.path.append(os.path.dirname(os.path.abspath(__file__)))
import sysmonitor

def main():
    print("System Monitor starting...")
    print("Will save plots to output directory...")
    
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
    
    # Set up plot titles and styles
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
    
    # Create output directory
    os.makedirs("output", exist_ok=True)
    
    # Collect data and save plots
    for i in range(30):  # Capture 30 data points (1 minute)
        # Get system metrics
        try:
            metrics = sysmonitor.monitor_system()
            print(f"Metrics: CPU: {metrics['cpu']:.1f}%, Memory: {metrics['memory']:.1f}%, "
                  f"Network RX: {metrics['network_rx']/1024:.1f} KB/s, TX: {metrics['network_tx']/1024:.1f} KB/s")
        except Exception as e:
            print(f"Error getting metrics: {e}")
            # Use dummy values if there's an error
            metrics = {'cpu': 50.0, 'memory': 60.0, 'network_rx': 1024.0, 'network_tx': 512.0}
        
        # Append data
        timestamps.append(i)
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
        
        # Save the current plot
        output_file = f"output/system_metrics_{i:03d}.png"
        plt.savefig(output_file)
        print(f"Saved plot #{i} to {output_file}")
        
        # Wait before next update
        plt.pause(2)  # Wait 2 seconds between updates
    
    print("Monitoring complete. Check the output directory for saved plots.")

if __name__ == "__main__":
    main()
