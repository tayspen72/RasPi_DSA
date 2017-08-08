# RasPi_DSA
RaspberryPi 2 Model B+ Digital Dignal Analyzer

Digital Signal Analyzer Project

Reason For Project
A simple digital signal analyzer could be constructed using a Raspberry Pi to monitor a digital signal using the GPIO pins. With much more advanced software, the signal could be automatically analyzed and interpretted. The objective of this project was to read and map one or more signals to a grid in such a way as to be able to make conclusions about the data. 


Initial Thoughts
Clearly, to obtain an accurate signal measurement, overwriting the kernel and OS would become critical. If a very time sensitive measurement was necessary, that could be researched and modified. For now, simply booting the pi to the terminal vs booting to the full desktop image will be sufficient. There will be system calls that override the program and delay the timing, but this is a simple project, not a complicated one.


DSA Program
The program is split into 5 pieces:
  DSA.sh
  main.c
  makefile
  run
  .gnuplot.in

DSA.sh
  The program script that puts all the pieces together.
  
main.c
  The overall flow of the .c file uses standard process threading. A thread splits off and counts down for some time length that can be interpretted as the capture window. A second thread generates a .csv file, captures data at intervals separated by another capture delay variable and stores the data to the .csv file.

makefile
  Generates a new executable for any changes to the main.c file. (num pin probes, delay length, capture window, etc)
  
run
  Program executable to generate the output.csv file
  
.gnuplot.in
  GnuPlot is used to map the data to a graph. This file is read by the DSA.sh to determine which data to grab for the graph and generates the new graph. 
  
Program Conclusions
The program worked as expected. Included in the git repository are data files and some simple plots generated using the program.
