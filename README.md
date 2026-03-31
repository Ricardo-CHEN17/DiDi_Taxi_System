# DiDi Taxi System (Console Version)

## Overview
DiDi Taxi System is a C-language, terminal-based ride-hailing simulation.  
It supports two user roles (Passenger and Driver), basic order lifecycle management, account balance and payment flow, and local file-based data persistence.

This project is designed as a learning-oriented implementation of core ride-hailing business logic in a simple command-line environment.

## Main Features

### Passenger Features
- Register and log in
- Create a taxi order (start location, destination)
- View current and historical order information
- Cancel eligible orders
- Pay for completed rides
- Recharge account balance

### Driver Features
- Register and log in
- Register a vehicle
- Toggle online or offline status
- View available waiting orders
- Accept an order
- Mark an order as completed (waiting for passenger payment)
- View personal profile and current order

### System Features
- Local persistence for users, vehicles, and orders
- Basic input validation (phone format, password length, numeric range)
- Simple fare calculation based on distance and car type
- Text-based multi-menu user interface

## Technology Stack
- Language: C
- Runtime: Native console application
- Target platform: Windows (uses `windows.h` and Windows shell commands)
- Data storage: Plain text files in the `data` directory

## Project Structure
```
DiDi_Taxi_System/
├── main.c        # Program entry point
├── ui.c/.h       # Console menus and interaction flow
├── core.c/.h     # Business logic (order, payment, recharge, etc.)
├── data.c/.h     # In-memory data and file persistence
├── utils.c/.h    # Input handling and validation helpers
├── data/         # Generated at runtime for storage
└── DiDi_Taxi_System.exe (optional prebuilt executable)
```

## Build and Run

### Option 1: Run Prebuilt Executable
If the executable is already provided, run:

```
DiDi_Taxi_System.exe
```

### Option 2: Build from Source (GCC/MinGW)
Compile all source files together:

```
gcc main.c ui.c core.c data.c utils.c -o DiDi_Taxi_System.exe
```

Then run:

```
DiDi_Taxi_System.exe
```

## Data Files
On startup, the program ensures the `data` directory exists and loads:
- `data/users.txt`
- `data/vehicles.txt`
- `data/orders.txt`

On exit, it saves all current data back to those files.

## Typical Usage Flow
1. Start the program.
2. Register a new account as Passenger or Driver.
3. If Driver, register a vehicle and switch to online status.
4. If Passenger, create an order.
5. Driver accepts and completes the order.
6. Passenger pays for the ride.
7. System updates balances and order status.

## Current Limitations
- No map display or route navigation
- No real-time location tracking
- No rating or review system
- No network backend (single local process)
- Data format is plain text and not encrypted

## Notes
- This is an educational project and not production-ready software.
- Keep all files in the same project directory when running.
- If file write issues occur on Windows, try running with sufficient permissions.

## Future Improvements
- Add map and GPS simulation
- Add order rating and feedback
- Improve matching strategy (distance/priority based)
- Add better error handling and logging
- Add unit tests and modular refactoring

## Author
- Yijin CHEN