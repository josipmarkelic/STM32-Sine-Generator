# STM32-Sine-Generator

A simple and efficient sinusoidal waveform generator built using the STM32F407 microcontroller. This project utilizes the STM32's DAC (Digital-to-Analog Converter), timers, and DMA to generate continuous sine waves with configurable frequency.

## 🔧 Features

- ✅ Real-time sine wave generation using lookup table (LUT)
- ✅ Output via DAC channel (e.g. DAC1_OUT1)
- ✅ Adjustable frequency via timer reconfiguration
- ✅ DMA for efficient data transfer without CPU load
- ✅ Built for STM32F407 (e.g. STM32F4Discovery board)
- ✅ Can be used as signal source for analog filters, ADC sampling, or lab testing

## 📦 Requirements

- STM32F407 microcontroller (tested on STM32F4Discovery)
- STM32CubeIDE
- STM32 HAL library
- UART (for testing)

## 📁 Project Structure

- `Src/` – Main source files (wave generation, peripherals)
- `Inc/` – Header files and LUT
- `Core/` – Startup and HAL config files

## 🚀 Getting Started

1. Flash firmware to STM32F407 board
2. Connect DAC output to oscilloscope or ADC input
3. Observe clean sine wave at desired frequency
4. Modify timer settings in code to change output frequency
