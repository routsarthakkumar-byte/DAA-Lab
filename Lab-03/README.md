<p align="center">
  <img alt="Language" src="https://img.shields.io/badge/LANGUAGE-C-00599C?style=for-the-badge&logo=c&logoColor=white">
  <img alt="Questions" src="https://img.shields.io/badge/QUESTIONS-6-7C3AED?style=for-the-badge">
  <img alt="Theme" src="https://img.shields.io/badge/THEME-DIVIDE%20%26%20CONQUER-0EA5E9?style=for-the-badge">
  <img alt="Status" src="https://img.shields.io/badge/STATUS-READY-06B6D4?style=for-the-badge">
</p>

<h1 align="center">DAA Laboratory · Lab 03</h1>
<p align="center"><strong>Binary vs Ternary Search · Defective Coin · Max/Min · Strassen · Special Matrices · Loop Invariants</strong></p>
<p align="center">Design and Analysis of Algorithms · 3rd Semester · August 11, 2026</p>

---

## Laboratory Dashboard

| Question | What the implementation validates | Final result |
|---|---|---|
| **Q1 · Binary vs Ternary Search** | Implements both searches on the same sorted array and counts comparisons/probes | Both `O(log n)`; binary search has the smaller comparison constant |
| **Q2 · Defective Coin** | Simulates a balance scale and finds the lighter coin (or reports none) | At most `⌈log₂ n⌉ + O(1)` weighings |
| **Q3 · Max and Min using D&C** | Pairwise tournament approach to find both max and min | `≤ 3n/2` comparisons |
| **Q4 · Strassen Multiplication** | Multiplies two `n × n` matrices using Strassen’s method | `Θ(n^{log₂ 7}) ≈ Θ(n^{2.807})` |
| **Q5 · Special-Pattern Matrices** | Exploits the recursive structure `M = [M₁ M₂; M₂ M₁]` to multiply with only two recursive products | `Θ(n²)` |
| **Q6 · Loop Invariant in Sorting** | Selection-sort style algorithm with explicit loop-invariant reasoning | Best case = Worst case = `Θ(n²)` |

---

## What this lab covers

- **Q1** – Binary search vs ternary search: same asymptotic class, but binary wins on the constant factor in the comparison model.
- **Q2** – Classic balance-scale problem solved with divide-and-conquer; handles the “possibly none” case.
- **Q3** – Optimal pairwise tournament for simultaneous max and min (bounded by `3n/2`).
- **Q4** – Full Strassen matrix multiplication with the classic 7-product recurrence.
- **Q5** – Special structured matrices reduced to only **two** half-size multiplications, giving an optimal `Θ(n²)` algorithm.
- **Q6** – Selection-sort variant used to illustrate initialization, maintenance and termination of a loop invariant; complexity is always quadratic.

---

## Repository Map

```text
Lab-03/
├── README.md
├── prog1.c                  ← Q1 · Binary vs Ternary Search
├── prog2.c                  ← Q2 · Defective Coin
├── prog3.c                  ← Q3 · Max and Min (D&C)
├── prog4.c                  ← Q4 · Strassen Matrix Multiplication
├── prog5.c                  ← Q5 · Special-Pattern Matrix Multiplication
├── prog6.c                  ← Q6 · Selection Sort + Loop Invariant
├── a.exe
└── Outputs/
    ├── image.png
    └── Screenshot *.png     ← sample runs / evidence
    