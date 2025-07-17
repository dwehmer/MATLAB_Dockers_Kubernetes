#!/bin/bash

# Build and Deploy Script for Three Body Problem C++ App

echo "Building Docker image..."
docker build -t aste580-app:latest .

echo "Docker image built successfully!"

# Optional: Run locally first to test
echo "Testing locally..."
docker run --rm aste580-app:latest

echo "Local test completed!"

# Deploy to Kubernetes
echo "Deploying to Kubernetes..."
kubectl apply -f kubernetes-deployment.yaml

echo "Checking deployment status..."
kubectl get pods -l app=aste580-app

echo "Deployment completed!"

# Useful commands for monitoring:
echo "Useful commands:"
echo "- View pods: kubectl get pods"
echo "- View logs: kubectl logs -l app=aste580-app"
echo "- Delete deployment: kubectl delete -f kubernetes-deployment.yaml"