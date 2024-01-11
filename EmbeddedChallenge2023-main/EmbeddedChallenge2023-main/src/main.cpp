/*-----------------------------------------------------------------------
Real Time Embedded Systems:Embedded Challenge

Authors : Vaishnavi Mahanti(vm2521)

Objective : Calculate the Distance travelled and steps taken. 

/*
DataReading: Ability to successfully and continuously measure gyro values from the angular velocity sensor
Use spi, ticker to read the data.
spi, ticker -> set_flag(), set_mode();

Link for the Demo Youtube Video is : https://youtu.be/7nIimy7XJX8
------------------------------------------------------------------------*/
#include "mbed.h"
#include "drivers/LCD_DISCO_F429ZI.h"
#include <chrono>
#include <cmath>

using namespace std::chrono;

LCD_DISCO_F429ZI lcd;

SPI spi(PF_9, PF_8, PF_7);
DigitalOut cs(PC_1);

// Variables for gyroscope readings and distance calculation
volatile int flag = 0;
double Dist = 0;  
int steps = 0;        
int state = 0;        

// Function declarations
void set_flag();
void init_gyroscope();
int16_t read_gyroscope_data(int address);
void Distance_calculation(int16_t tempData);
void distance_in_meters(int16_t Z_axis_data);

int main() {
    cs = 1;

    // Initialize gyroscope and SPI settings
    init_gyroscope();
    spi.format(8, 3);
    spi.frequency(100000);

    // Set the font for the LCD display
    lcd.SetFont(&Font16);

    // Set up a ticker to periodically set the flag for gyroscope readings
    Ticker t;
    t.attach(&set_flag, 0.05);

    
    while (1) {
        // Check if a new gyroscope reading is available
        if (flag) {
            // Read the gyroscope data and perform distance calculation
            int16_t Z_axis_data = read_gyroscope_data(0xAC);
            Distance_calculation(Z_axis_data);
            distance_in_meters(Z_axis_data);
            // Reset the flag after processing the gyroscope reading
            flag = 0;
        }
    }
}

// Ticker callback function to set the flag for gyroscope readings
void set_flag() {
    flag = 1;
}

// Function to initialize the gyroscope
void init_gyroscope() {
    cs = 0;
    spi.write(0x20);
    spi.write(0xCF);
    cs = 1;
}

// Function to read gyroscope data from the specified address
int16_t read_gyroscope_data(int address) {
    cs = 0;
    spi.write(address);
    uint8_t low_byte = spi.write(0x00);
    cs = 1;

    cs = 0;
    spi.write(address + 1);
    int8_t high_byte = spi.write(0x00);
    cs = 1;

    return low_byte + (high_byte << 8);
}

// Function to update the LCD display with distance in meters
void distance_in_meters(int16_t Z_axis_data) {
    if (Z_axis_data < -12000 && state == 0) {
        state = 1;
    }
    if (Z_axis_data < -12000 && state == 1) {
        state = 0;
        steps++;
        double meters = steps * 6 ;
        int meters_int = static_cast<int>(meters);  
        char buf[20];
        sprintf(buf, "meters:%d.%dm\n", meters_int / 10, meters_int % 10);
        lcd.DisplayStringAtLine(10, (uint8_t *)buf);
    }
}


// Function to perform distance calculation based on gyroscope data
void Distance_calculation(int16_t tempData) {
    double Gyro_Data;
    if (abs(tempData) > 3000) {
        Gyro_Data = (0.00875 * abs(tempData + 63));
        Dist += (double)(0.05 * Gyro_Data / 360 * 2 * M_PI * 1.020);
        char buf[20];
        sprintf(buf, "Distance: %d", (int)Dist); // Number of steps taken
        lcd.DisplayStringAtLine(9, (uint8_t *)buf);
    }
}
