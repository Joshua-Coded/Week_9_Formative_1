"""
setup.py: Build script for the sysmonitor C extension
"""

from setuptools import setup, Extension

sysmonitor_module = Extension('sysmonitor',
                            sources=['sysmonitor.c'])

setup(name='sysmonitor',
      version='1.0',
      description='System monitoring module for CPU, memory, and network usage',
      ext_modules=[sysmonitor_module])
