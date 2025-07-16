# MATLAB_Dockers_Kubernetes
Example project using MATLAB, MATLAB Coder, Dockers, and Kubernetes


MATLAB

File Name: ASTE_580_WEHMER_HW7_P1.m
- The MATLAB file is a multi-solution solver for the 3-Body problem in Orbital Mechanics. This script was originally created to solve a homework problem at the University of Southern California; ASTE 580, Orbital Mechanics


MATLAB Coder
- MATLAB Coder is not a feature I have native to my personal MATLAB software. For purposes of demonstrating how to use the MATLAB Coder, here is the commands I would run to generate C code from the MATLAB file:

codegen -config:lib -lang:c++ ASTE580_WEHMER_HW7_P1

This command would generate a standalone C++ library to store the C++ compiled code for the MATLAB script ASTE_580_WEHMER_HW7_P1

