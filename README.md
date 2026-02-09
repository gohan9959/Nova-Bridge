# Nova-Bridge: Real-Time Game State Extraction & AI Engine

**Nova-Bridge** is a high-performance data pipeline and decision engine designed for Pokémon Generation 5. It bridges the gap between emulated memory and external logic by using Lua-based memory mapping and a C++ backend.

## Features
* **Real-Time Memory Scraping:** Automated extraction of battle state data (Species, HP, Moves, Stats) via Lua hooks.
* **Dynamic Anchor Discovery:** Robust search algorithms to locate volatile memory pointers (btl_pokeparam.c) in real-time.
* **Modular Architecture:** Decoupled data collection (Lua) and logic processing (C++) for maximum extensibility.
* **Fair-Play Logic:** Designed to operate only on "observable" game data, simulating a human player's information constraints.

## Technical Stack
* **Languages:** Lua (Scraping), C++ (Logic Engine)
* **Environment:** DeSmuME / MelonDS Emulator Hooks
* **Concepts:** Memory Forensics, Pointer Arithmetic, Asynchronous Data Pipelines

## Structure
* `/Data_Scrapper`: Lua scripts for real-time memory monitoring.
* `/Reverse_Engineering_Tools`: Custom utilities for memory dump analysis and offset discovery.
* `/Logic_Engine`: (In Progress) C++ implementation of battle strategy and move selection.
