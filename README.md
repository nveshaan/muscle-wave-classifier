# Muscle Wave Classifier

## Overview

Electromyography (EMG) measures electrical activity in muscles, enabling gesture recognition for human-computer interaction. This project uses EMG data to classify a user’s fist state (open or closed) with a neural network. The predictions control a remote-controlled car in real-time, showcasing the potential of assistive technology. Check out the project [website](https://nveshaan.github.io/projects/muscle-wave-classifier/)

## Data Acquisition

EMG signals were recorded using the Muscle BioAmp Candy sensor with Arduino UNO from 13 participants, collecting 13,000 samples (256 data points per sample). Data was preprocessed to extract the signal envelope and labeled as:  
- **0**: Open fist  
- **1**: Closed fist  

## Model Design

A fully connected neural network with 3 hidden layers (512, 128, 64 neurons) and a sigmoid-activated output was trained using TensorFlow. The model achieved good convergence with binary crossentropy loss, the Adam optimizer, and a learning rate of 0.001.  

## Real-time Interface

Using an ESP32, the server collects 256 EMG data points, runs inference with the trained model, and transmits control signals to move the car forward (closed fist) or stop (open fist). Communication is handled via Python’s socket library.

## Conclusion

This project demonstrates EMG-based gesture recognition for real-time applications, with potential for future enhancements like expanding gesture types, advanced models, and transfer learning.  
