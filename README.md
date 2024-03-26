# Embedded_challenge

This project implements a real-time embedded system to calculate the distance travelled and steps taken using an angular velocity sensor (gyroscope). It continuously measures gyroscope values using SPI communication and periodically updates the distance travelled and steps taken on an LCD display.

## Overview

Objective: Calculate the distance travelled and steps taken using gyroscope data.
Components:
Angular velocity sensor (gyroscope)
STM32F429ZI microcontroller board
LCD display (LCD_DISCO_F429ZI)
Key Features:
Continuous measurement of gyroscope values.
Distance calculation based on gyroscope data.
Step counting based on gyroscope peaks.
Demo Video: Watch Demo on YouTube

## Hardware Setup

Connect the angular velocity sensor (gyroscope) to the SPI pins of the microcontroller.
Connect the LCD display to the microcontroller for visual feedback.
Usage

Setup: Upload the provided code to your STM32F429ZI microcontroller board using a compatible IDE (e.g., Mbed Studio).
Connections: Ensure proper connections of the gyroscope and LCD display to the microcontroller.
Execution: Upon running the code, the system will continuously measure gyroscope values and update the LCD display with distance travelled and steps taken.
Monitor: Monitor the LCD display for real-time updates on distance and steps.
Code Structure

The code initializes SPI communication and sets up a ticker for periodic gyroscope readings.
Gyroscope readings are processed to calculate distance travelled and steps taken.
LCD display is updated with distance and step count information.
