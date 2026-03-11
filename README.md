# C Programming Assignment Portfolio

This repository contains 3 C programs prepared for the assignment:

1. Dynamic Student Record Engine
2. Adaptive Text Intelligence Tool
3. Callback-Based Device Monitoring Simulator

Student ID used in the code: **1164570746**

---

## 1) Project Files

- `project1_dynamic_student_record_engine.c`
- `project2_adaptive_text_intelligence_tool.c`
- `project3_callback_device_monitoring_simulator.c`

---

## 2) Requirements Coverage Summary

### Project 1: Dynamic Student Record Engine

Implemented:

- Structure with fields: `id`, `name`, `grade`
- Dynamic allocation and resizing (`malloc`, `realloc`, `free`)
- Pointer traversal over student array
- Function pointer dispatch for menu operations
- Required operations:
  - add students
  - display students
  - sort students
  - calculate average
  - find top student
  - run custom analysis
  - perform full analysis
- String comparison (`strcmp`) for name sorting
- Custom analysis function: **Grade Stability Score**
- Own dataset with 10–15 students
- Student ID printed in output header

### Project 2: Adaptive Text Intelligence Tool

Implemented:

- Dynamic allocation for input text and word-stat array
- Pointer-based word parsing
- Required structure:
  - `struct wordStat { char name[40]; int count; }`
- Required analysis functions via function pointers:
  - `count_words()`
  - `longest_word()`
  - `most_frequent()`
- Custom analysis function: **vowel_density()**
- Required string functions used:
  - `strlen`
  - `strcmp`
  - `strcpy`
- Memory addresses printed for key structures

### Project 3: Callback-Based Device Monitoring Simulator

Implemented:

- Required `struct Device` design with union-based readings
- Dynamic memory for an array of devices
- At least 3 device types:
  - temperature
  - pressure
  - battery
- Callback processing through function pointers:
  - `process_device(struct Device*, void (*callback)(struct Device*))`
- Standard callbacks:
  - `battery_monitor()`
  - `temperature_monitor()`
  - `pressure_monitor()`
- Custom callback:
  - `anomaly_score_monitor()`
- Pointer traversal + union usage demonstrated
- Simulates **10 random readings**

---

## 3) How to Compile and Run (Windows + GCC)

Open PowerShell in this folder (`PROJECT2`) and run:

```powershell
gcc -Wall -Wextra -std=c11 project1_dynamic_student_record_engine.c -o project1.exe -lm
gcc -Wall -Wextra -std=c11 project2_adaptive_text_intelligence_tool.c -o project2.exe
gcc -Wall -Wextra -std=c11 project3_callback_device_monitoring_simulator.c -o project3.exe
```

Run programs:

```powershell
.\project1.exe
.\project2.exe
.\project3.exe
```

If `gcc` is not recognized, use full path:

```powershell
& "C:\msys64\ucrt64\bin\gcc.exe" -Wall -Wextra -std=c11 project1_dynamic_student_record_engine.c -o project1.exe -lm
& "C:\msys64\ucrt64\bin\gcc.exe" -Wall -Wextra -std=c11 project2_adaptive_text_intelligence_tool.c -o project2.exe
& "C:\msys64\ucrt64\bin\gcc.exe" -Wall -Wextra -std=c11 project3_callback_device_monitoring_simulator.c -o project3.exe
```

---

## 4) Quick Usage Guide

### Project 1 (`project1.exe`)

Menu options:

1. Add students
2. Display students
3. Sort students
4. Calculate average
5. Find top student
6. Run custom analysis
7. Perform full analysis
8. Exit

Suggested demo flow:

- Display students
- Sort by name
- Calculate average
- Run custom analysis
- Exit

### Project 2 (`project2.exe`)

Flow:

1. Enter a paragraph from a book/article
2. View printed memory addresses
3. Use menu options to run analyses

Suggested demo flow:

- Option 1 (count words)
- Option 2 (longest word)
- Option 3 (most frequent)
- Option 4 (custom analysis)
- Option 5 (run all)
- Option 6 (exit)

### Project 3 (`project3.exe`)

Flow:

- Program auto-generates 10 device readings
- For each device, program prints:
  - raw reading
  - standard callback output
  - custom callback output

No menu input required.

---


