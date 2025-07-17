# MATLAB_Dockers_Kubernetes
Example project using MATLAB, MATLAB Coder, Dockers, and Kubernetes


MATLAB

File Name: ASTE_580_WEHMER_HW7_P1.m
- The MATLAB file is a multi-solution solver for the 3-Body Problem in Orbital Mechanics. This script was originally created to solve a homework problem at the University of Southern California; ASTE 580, Orbital Mechanics


MATLAB Coder

File Name: ASTE_580_WEHMER_HW7_P1.cpp
- MATLAB Coder is not a feature I have native to my personal MATLAB software. For purposes of demonstrating how to use the MATLAB Coder, here is the command I would run to generate C code from the MATLAB file:

codegen -config:lib -lang:c++ ASTE580_WEHMER_HW7_P1

This command would generate a standalone C++ library to store the C++ compiled code for the MATLAB script ASTE_580_WEHMER_HW7_P1. For the purposed of this demonstration, I have done the conversion from the .m file to the .cpp file using an online MATLAB to C++ Converter tool (https://www.codeconvert.ai/matlab-to-c++-converter?id=efad009d-c05b-4dc3-b8b7-125fa99b8a82)


DockerFile

File Name: DockerFile.txt

- This file buids the ASTE580_WEHMER_HW7_P1 C++ file in a container.

Kubernetes

kubernetes-deployment.yaml

- This file is used to deploy the application to Kubernetes.

Shell Script

build-deploy.sh

- This is a helper script to build and deploy the pipeline.


CI/CD Pipeline

.gitlab-ci.yml

- This file is used to create an automated CI/CD pipeline.





How to test:


Download the files, navigate to the correct folder in bash.


Send the following bash command:

docker build -t aste580-app:latest .


Once successfully built, next run the app in a container.


Send the following bash command:

docker run --rm aste580-app:latest


Output should result in the completion of the program. Output of the MATLAB script looks like this:

<img width="552" height="490" alt="Screen Shot 2025-07-16 at 9 41 48 PM" src="https://github.com/user-attachments/assets/fee260b6-4d63-4078-8fe4-77c05f2d5e13" />


For testing Kubernetes:


Check if kubectl is working


Send the following bash command:

bashkubectl cluster-info



Deploy your app


Send the following bash command:

bashkubectl apply -f kubernetes-deployment.yaml


Check if it's running:


Send the following bash command:

bashkubectl get pods



