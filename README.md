# Skyscraper Puzzle Solver (4x4)

This project is a **C implementation of a 4x4 Skyscraper puzzle solver**.
It uses **backtracking** and **visibility constraints** to find a valid solution.

## 🏙️ Puzzle Rules

- The grid size is **4x4**
- Each row and column must contain numbers **1 to 4** exactly once
- Numbers represent building heights
- Visibility clues are given from:
  - Top
  - Bottom
  - Left
  - Right
- A building is visible if it is taller than all previous buildings in that direction

## 🔢 Input Format

The program expects **16 numbers** (values between 1 and 4) as a single argument:

