<div align="center">

<img src="https://capsule-render.vercel.app/api?type=waving&color=0:11998e,100:38ef7d&height=180&section=header&text=DAA%20Lab-06&fontSize=55&fontColor=ffffff&animation=fadeIn&fontAlignY=38&desc=Complexity%20Anatomy%20%7C%20Design%20%26%20Analysis%20of%20Algorithms&descAlignY=58&descSize=18" width="100%"/>

<img src="https://readme-typing-svg.demolab.com?font=Fira+Code&size=22&duration=2500&pause=800&color=11998E&center=true&vCenter=true&multiline=true&repeat=true&width=850&height=60&lines=Every+operation+has+a+price+tag...;Arrays+%7C+Matrices+%7C+Divide-and-Conquer+%7C+Reversal+Sort+%7C+Dynamic+Programming" alt="Typing SVG" />

![Language](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Course](https://img.shields.io/badge/Course-DAA-FF6F00?style=for-the-badge&logo=leetcode&logoColor=white)
![Semester](https://img.shields.io/badge/Semester-3rd-6A5ACD?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Completed-2ECC71?style=for-the-badge&logo=checkmarx&logoColor=white)
![Institute](https://img.shields.io/badge/IIIT-Bhubaneswar-9146FF?style=for-the-badge)

</div>

---

## 📌 Lab Metadata

| Field | Detail |
|---|---|
| 🧪 **Lab No.** | 06 |
| 📘 **Course** | Design and Analysis of Algorithm (DAA) |
| 🎓 **Program** | BTech (CS-B and CE), 3rd Semester |
| 📅 **Date** | August 31, 2026 |
| 👨‍🏫 **Instructor** | Dr. Ajaya Kumar Dash |
| 🎯 **Theme** | Complexity anatomy of everyday operations — arrays, matrices, divide-and-conquer, a clever sorting constraint, **and Dynamic Programming** |

---

## 🧠 Core Idea Behind This Lab

> Not every problem needs a fancy algorithm — but *every* operation has a cost, and this lab is about **naming that cost precisely**: from a single linear scan of an array, to `O(n³)` matrix work, to squeezing a convolution down to `O(n log n)` with divide-and-conquer, to sorting under a bizarre "reversal-only" constraint.

```mermaid
flowchart LR
    A["Raw Operation"] --> B{"How much of the input<br/>must be touched?"}
    B -->|"Once, no comparisons"| C["O(n) - Linear"]
    B -->|"Repeated halving"| D["O(n log n) - Divide and Conquer"]
    B -->|"Nested over all pairs"| E["O(n^2) / O(n^3) - Polynomial"]
    style A fill:#4D96FF,color:#fff,stroke:#2c5fb8,stroke-width:2px
    style B fill:#9D4EDD,color:#fff,stroke:#6a2ca0,stroke-width:2px
    style C fill:#06D6A0,color:#000,stroke:#049270,stroke-width:2px
    style D fill:#FFD93D,color:#000,stroke:#d9ad00,stroke-width:2px
    style E fill:#FF6B6B,color:#fff,stroke:#c94242,stroke-width:2px
```

---

## 📂 Problem Index

| # | Problem | Core Idea | Complexity Range |
|---|---------|-----------|--------------------|
| 1 | [1D Array Operations](#1--1d-array-operations-and-their-complexities) | 9 classic array queries, worst-case each | `O(n)` → `O(n log n)` |
| 2 | [2D Matrix Operations](#2--2d-square-matrix-operations-and-their-complexities) | 7 classic `n×n` matrix operations | `O(n²)` → `O(n³)` |
| 3 | [Convolution via Divide & Conquer](#3--convolution-operation-on-vectors-of-size-n) | FFT-style D&C convolution | `O(n log n)` |
| 4 | [Sorting via Reversal](#4--sorting-via-reversal-procedure) | Bound reversal count, then bound reversal *cost* | `O(n)` reversals · `O(n log² n)` cost |
| 5 | [Nth Fibonacci via DP](#5--nth-fibonacci-number-using-dynamic-programming) | Bottom-up tabulation / memoization | `O(n)` |
| 6 | [0/1 Knapsack via DP](#6--01-knapsack-problem-using-dynamic-programming) | 2D DP table over items × capacity | `O(n·W)` |
| 7 | [Longest Common Subsequence](#7--longest-common-subsequence-lcs-using-dynamic-programming) | 2D DP table over both strings | `O(m·n)` |
| 8 | [Matrix Chain Multiplication](#8--matrix-chain-multiplication-using-dynamic-programming) | Interval DP over chain splits | `O(n³)` |

---

<div align="center">
<img src="https://capsule-render.vercel.app/api?type=rect&color=0:11998e,100:38ef7d&height=4&width=100%25" width="100%"/>
</div>

## 1. 📏 1D Array Operations and Their Complexities

**Setup:** An unsorted array of `n` integers. For each operation below, we derive the **worst-case** complexity.

| # | Operation | Worst-Case Complexity | Why |
|---|---|---|---|
| i | Maximum element | `O(n)` | One linear scan, track running max |
| ii | First & second largest | `O(n)` | Single pass, track top-2 running values |
| iii | Mean | `O(n)` | Sum in one pass, divide by `n` |
| iv | Median | `O(n log n)`* | Sort then pick middle — *drops to `O(n)` with a selection algorithm (Lab-05!)* |
| v | Standard deviation | `O(n)` | One pass for mean, one pass for squared deviations — still linear |
| vi | Mode | `O(n log n)`* | Sort + linear scan for longest run — *`O(n)` possible via hashing if value range allows* |
| vii | Remove all duplicates | `O(n log n)`* | Sort then skip repeats — *`O(n)` possible via hashing (extra space)* |
| viii | Reverse the array | `O(n)` | Swap from both ends inward, `n/2` swaps |
| ix | Partition around random pivot | `O(n)` | One Lomuto/Hoare-style pass, in-place |

<sub>* Two valid strategies exist for iv, vi, vii — a sort-based `O(n log n)` approach (works for any comparable type) or a hash/selection-based `O(n)` approach (needs extra space or a boundable value range). Both are worth showing in your program's complexity discussion.</sub>

```mermaid
%%{init: {"themeVariables": {"xyChart": {"plotColorPalette": "#FF6B6B, #FFD93D, #06D6A0, #4D96FF, #9D4EDD, #FF9F1C, #00C2CB, #F72585, #7BE0AD"}}}}%%
xychart-beta
    title "Q1: Worst-Case Growth Across the 9 Array Operations"
    x-axis ["Max", "Top-2", "Mean", "Median", "Std-Dev", "Mode", "Dedup", "Reverse", "Partition"]
    y-axis "Relative Growth Order" 0 --> 3
    bar [1, 1, 1, 2, 1, 2, 2, 1, 1]
```

> Seven of the nine operations are pure `O(n)` — the only two that climb to `O(n log n)` (median, mode) do so *only* when you lean on sorting rather than a smarter selection/hashing trick.

---

## 2. 🧮 2D Square Matrix Operations and Their Complexities

**Setup:** Square matrices with `n` rows and `n` columns.

| # | Operation | Worst-Case Complexity | Why |
|---|---|---|---|
| i | Matrix addition | `O(n²)` | Touch every one of the `n²` cells exactly once |
| ii | Matrix multiplication | `O(n³)` naive | Triple nested loop — `n²` output cells, each an `O(n)` dot product <br>*(Strassen's algorithm improves this to ≈`O(n^2.807)`)* |
| iii | Check zero matrix | `O(n²)` | Must inspect every cell in the worst case |
| iv | Check symmetric matrix | `O(n²)` | Compare `A[i][j]` with `A[j][i]` for all pairs |
| v | Determinant | `O(n³)` | Via Gaussian elimination / LU decomposition — naive cofactor expansion is `O(n!)`, avoid it |
| vi | Transpose in-place | `O(n²)` | Swap `A[i][j] ↔ A[j][i]` for the upper triangle only |
| vii | Eigenvalue / eigenvector | `O(n³)` per iteration | No closed form beyond `n = 4`; iterative methods (e.g. QR algorithm) repeat `O(n³)` steps until convergence |

```mermaid
%%{init: {"themeVariables": {"xyChart": {"plotColorPalette": "#4D96FF, #F72585, #06D6A0, #FFD93D, #9D4EDD, #00C2CB, #FF6B6B"}}}}%%
xychart-beta
    title "Q2: Worst-Case Growth Across the 7 Matrix Operations"
    x-axis ["Addition", "Multiply", "Zero-Check", "Symmetric", "Determinant", "Transpose", "Eigen"]
    y-axis "Relative Growth Order" 0 --> 4
    bar [2, 3, 2, 2, 3, 2, 3]
```

> Anything that must **combine** two full matrices (multiplication) or **reduce** one to a scalar via elimination (determinant, eigenvalues) jumps a full order to `O(n³)` — everything that just **reads or rearranges** cells stays at `O(n²)`.

---

<div align="center">
<img src="https://capsule-render.vercel.app/api?type=rect&color=0:38ef7d,100:11998e&height=4&width=100%25" width="100%"/>
</div>

## 3. 🔊 Convolution Operation on Vectors of Size n

**Problem:** Compute `C[k] = Σ A[j]·B[k−j]` for vectors `A` (length `m`) and `B` (length `n`, `n ≥ m`), in `O(n log n)` using divide-and-conquer.

**Approach — Frequency-Domain Divide & Conquer (FFT-style):** Direct convolution is `O(n·m)` — for every output index you sum over all valid `j`. The `O(n log n)` trick treats each vector as a polynomial's coefficients and recursively **splits by even/odd index** (just like the Fast Fourier Transform), multiplies in the transformed domain, then combines back.

```mermaid
flowchart TD
    A["Vectors A, B as polynomials"] --> B["Split each into even-indexed / odd-indexed halves"]
    B --> C["Recursively transform each half - T(n/2)"]
    C --> D["Combine transformed halves in O(n) - butterfly step"]
    D --> E["Pointwise multiply transformed A and B - O(n)"]
    E --> F["Inverse transform back to coefficient form - O(n log n)"]
    F --> G["Convolution result C"]
    style A fill:#4D96FF,color:#fff,stroke:#2c5fb8,stroke-width:2px
    style B fill:#9D4EDD,color:#fff,stroke:#6a2ca0,stroke-width:2px
    style C fill:#00C2CB,color:#000,stroke:#008c93,stroke-width:2px
    style D fill:#FFD93D,color:#000,stroke:#d9ad00,stroke-width:2px
    style E fill:#FF9F1C,color:#000,stroke:#c97900,stroke-width:2px
    style F fill:#F72585,color:#fff,stroke:#b81b64,stroke-width:2px
    style G fill:#06D6A0,color:#000,stroke:#049270,stroke-width:2px
```

**Recurrence:** `T(n) = 2·T(n/2) + O(n)` → by the Master Theorem, `T(n) = O(n log n)`.

```mermaid
%%{init: {"themeVariables": {"xyChart": {"plotColorPalette": "#FF6B6B, #06D6A0"}}}}%%
xychart-beta
    title "Q3: Direct Convolution vs Divide-and-Conquer"
    x-axis ["n=100", "n=1000", "n=10000", "n=100000"]
    y-axis "Relative Operation Count" 0 --> 100
    line [1, 10, 30, 60]
    line [1, 3, 5, 7]
```

> Top line: naive `O(n·m)` direct convolution. Bottom line: `O(n log n)` divide-and-conquer — the gap widens dramatically as `n` grows.

| Approach | Time Complexity | Notes |
|---|---|---|
| Direct summation | `O(n·m)` | Simple but slow for large vectors |
| Divide & Conquer (FFT-style) | `O(n log n)` | Requires `n ≥ m`; pad `B` with zeros to match a power-of-two length |

---

## 4. 🔄 Sorting via Reversal Procedure

**Problem:** Given a permutation of `1..n`, sort it using only `reverse(p, i, j)` — reversing a contiguous subrange.

### Part A — Sorting in `O(n)` reversals

**Claim:** Any permutation can be sorted using at most `2(n−1)` reversals.

**Proof sketch (Selection-by-Reversal):** For each position `i` from `1` to `n−1`:
1. Find the position `k` of value `i` in the unsorted suffix.
2. `reverse(p, i, k)` — this brings value `i` to the front of the unsorted suffix, but possibly *reversed relative to its neighbours* — one reversal is actually enough to place it exactly at position `i` since reversing `[i, k]` puts the element that was at `k` directly into position `i`.

```mermaid
flowchart TD
    A["i = 1"] --> B["Find position k of value i in p[i..n]"]
    B --> C["reverse(p, i, k)"]
    C --> D["value i now correctly placed at position i"]
    D --> E{"i < n-1 ?"}
    E -->|Yes| F["i = i + 1"]
    F --> B
    E -->|No| G["Array fully sorted"]
    style A fill:#4D96FF,color:#fff,stroke:#2c5fb8,stroke-width:2px
    style B fill:#9D4EDD,color:#fff,stroke:#6a2ca0,stroke-width:2px
    style C fill:#FF9F1C,color:#000,stroke:#c97900,stroke-width:2px
    style D fill:#00C2CB,color:#000,stroke:#008c93,stroke-width:2px
    style E fill:#F72585,color:#fff,stroke:#b81b64,stroke-width:2px
    style F fill:#FFD93D,color:#000,stroke:#d9ad00,stroke-width:2px
    style G fill:#06D6A0,color:#000,stroke:#049270,stroke-width:2px
```

| Metric | Bound |
|---|---|
| Reversals used | `O(n)` — at most one per position, `n−1` total |
| Time to *find* each reversal (naive) | `O(n)` per step → `O(n²)` overall for this simple version |

### Part B — Bounding the total *cost* to `O(n log² n)`

Here the cost of `reverse(p, i, j)` is its length `|j − i| + 1`, so the *naive* Part-A approach (each reversal can cost up to `O(n)`) totals `O(n²)` cost in the worst case — too expensive.

**Approach — Divide & Conquer Merge via Reversal:** Recursively sort the left and right halves of the permutation, then **merge them using rotations built from reversals** (the classic "reverse three blocks" trick: `reverse(A); reverse(B); reverse(A+B)` rotates `A` and `B` past each other in a cost proportional to their combined length, similar to array-rotation-by-reversal).

```mermaid
flowchart TD
    A["Permutation of size n"] --> B["Recursively sort LEFT half - T(n/2)"]
    A --> C["Recursively sort RIGHT half - T(n/2)"]
    B --> D["Merge via block reversal - O(n log n) cost"]
    C --> D
    D --> E["Fully sorted permutation"]
    style A fill:#4D96FF,color:#fff,stroke:#2c5fb8,stroke-width:2px
    style B fill:#9D4EDD,color:#fff,stroke:#6a2ca0,stroke-width:2px
    style C fill:#FF9F1C,color:#000,stroke:#c97900,stroke-width:2px
    style D fill:#F72585,color:#fff,stroke:#b81b64,stroke-width:2px
    style E fill:#06D6A0,color:#000,stroke:#049270,stroke-width:2px
```

**Recurrence:** `T(n) = 2·T(n/2) + O(n log n)` — the extra `log n` factor in the merge step (each merge itself needs a logarithmic number of reversal passes to interleave blocks) gives, by the Master Theorem:

```
T(n) = O(n log² n)
```

```mermaid
%%{init: {"themeVariables": {"xyChart": {"plotColorPalette": "#FF6B6B, #06D6A0"}}}}%%
xychart-beta
    title "Q4: Reversal-Sort Cost - Naive vs Divide-and-Conquer Merge"
    x-axis ["n=100", "n=1000", "n=10000", "n=100000"]
    y-axis "Relative Total Cost" 0 --> 100
    line [1, 15, 60, 100]
    line [1, 4, 9, 15]
```

> Top line: naive `O(n²)` reversal cost. Bottom line: `O(n log² n)` divide-and-conquer merge-by-reversal — the same "split, solve, combine" pattern from Q3, applied to a completely different constraint.

| Metric | Bound |
|---|---|
| Number of reversals | `O(n)` |
| Total *cost* (sum of reversal lengths) | `O(n log² n)` |
| Correctness | Each merge step preserves sortedness of the combined range by construction of the block-reversal rotation |

---

<div align="center">
<img src="https://capsule-render.vercel.app/api?type=rect&color=0:F72585,100:9D4EDD&height=4&width=100%25" width="100%"/>
</div>

# 🧩 Dynamic Programming — Bonus Set

> Recursion re-solves the same subproblems over and over. Dynamic Programming just **remembers the answer the first time** — either top-down (memoization) or bottom-up (tabulation) — turning exponential blow-ups into polynomial time.

```mermaid
flowchart LR
    A["Naive Recursion"] --> B{"Overlapping subproblems?"}
    B -->|"Yes - store results"| C["Memoization (Top-Down)"]
    B -->|"Yes - build iteratively"| D["Tabulation (Bottom-Up)"]
    C --> E["Exponential -> Polynomial Time"]
    D --> E
    style A fill:#FF6B6B,color:#fff,stroke:#c94242,stroke-width:2px
    style B fill:#9D4EDD,color:#fff,stroke:#6a2ca0,stroke-width:2px
    style C fill:#4D96FF,color:#fff,stroke:#2c5fb8,stroke-width:2px
    style D fill:#FF9F1C,color:#000,stroke:#c97900,stroke-width:2px
    style E fill:#06D6A0,color:#000,stroke:#049270,stroke-width:2px
```

## 5. 🐇 Nth Fibonacci Number using Dynamic Programming

**Problem:** Compute the `n`-th Fibonacci number efficiently.

**Approach:** Naive recursion recomputes `fib(k)` an exponential number of times because `fib(n-1)` and `fib(n-2)` both independently recurse into overlapping calls. DP fixes this by storing each `fib(k)` the first time it's computed.

```mermaid
flowchart TD
    A["fib(n)"] --> B["Naive: fib(n-1) + fib(n-2)<br/>recomputes shared subcalls -> O(2^n)"]
    A --> C["DP: dp[i] = dp[i-1] + dp[i-2]<br/>each value computed once -> O(n)"]
    style A fill:#9D4EDD,color:#fff,stroke:#6a2ca0,stroke-width:2px
    style B fill:#FF6B6B,color:#fff,stroke:#c94242,stroke-width:2px
    style C fill:#06D6A0,color:#000,stroke:#049270,stroke-width:2px
```

```mermaid
%%{init: {"themeVariables": {"xyChart": {"plotColorPalette": "#FF6B6B, #06D6A0"}}}}%%
xychart-beta
    title "Q5: Naive Recursion vs Dynamic Programming (Fibonacci)"
    x-axis ["n=10", "n=20", "n=30", "n=40"]
    y-axis "Relative Operation Count (log-ish scale)" 0 --> 100
    line [1, 6, 40, 100]
    line [1, 2, 3, 4]
```

| Approach | Time | Space |
|---|---|---|
| Naive recursion | `O(2ⁿ)` | `O(n)` call stack |
| DP — Tabulation (array) | `O(n)` | `O(n)` |
| DP — Space-optimized (2 variables) | `O(n)` | `O(1)` |

---

## 6. 🎒 0/1 Knapsack Problem using Dynamic Programming

**Problem:** Given `n` items with weights and profits, and a knapsack of capacity `W`, find the maximum achievable profit.

**Approach:** Build a 2D table `dp[i][w]` = best profit using the first `i` items within capacity `w`. Each cell either **skips** item `i` or **takes** it (if it fits), taking the better of the two.

```mermaid
flowchart TD
    A["dp[i][w]"] --> B{"weight[i] <= w ?"}
    B -->|No| C["dp[i][w] = dp[i-1][w]<br/>(cannot include item i)"]
    B -->|Yes| D["dp[i][w] = max(<br/>dp[i-1][w],<br/>dp[i-1][w-weight[i]] + profit[i])"]
    C --> E["Fill next cell"]
    D --> E
    style A fill:#4D96FF,color:#fff,stroke:#2c5fb8,stroke-width:2px
    style B fill:#9D4EDD,color:#fff,stroke:#6a2ca0,stroke-width:2px
    style C fill:#FF9F1C,color:#000,stroke:#c97900,stroke-width:2px
    style D fill:#06D6A0,color:#000,stroke:#049270,stroke-width:2px
    style E fill:#F72585,color:#fff,stroke:#b81b64,stroke-width:2px
```

```mermaid
%%{init: {"themeVariables": {"xyChart": {"plotColorPalette": "#FF6B6B, #06D6A0"}}}}%%
xychart-beta
    title "Q6: Brute Force (2^n subsets) vs DP Table (n*W)"
    x-axis ["Small", "Medium", "Large", "Very Large"]
    y-axis "Relative Operation Count" 0 --> 100
    line [2, 20, 60, 100]
    line [1, 4, 10, 18]
```

| Metric | Complexity | Why |
|---|---|---|
| Time | `O(n·W)` | Fill an `n × W` table, `O(1)` work per cell |
| Space | `O(n·W)` | Full 2D table — droppable to `O(W)` by keeping only the previous row |
| Brute force baseline | `O(2ⁿ)` | Every item is either in or out — `2ⁿ` subsets to check |

---

<div align="center">
<img src="https://capsule-render.vercel.app/api?type=rect&color=0:9D4EDD,100:4D96FF&height=4&width=100%25" width="100%"/>
</div>

## 7. 🧬 Longest Common Subsequence (LCS) using Dynamic Programming

**Problem:** Given two strings, find the length of their longest common subsequence, and display the subsequence itself.

**Approach:** Build a 2D table `dp[i][j]` = LCS length of the first `i` characters of string A and first `j` characters of string B. Matching characters extend the diagonal; mismatches take the best of skipping one character from either string.

```mermaid
flowchart TD
    A["dp[i][j]"] --> B{"A[i] == B[j] ?"}
    B -->|Yes| C["dp[i][j] = dp[i-1][j-1] + 1<br/>(extend the match)"]
    B -->|No| D["dp[i][j] = max(dp[i-1][j], dp[i][j-1])<br/>(skip a character)"]
    C --> E["Backtrack diagonal moves to rebuild the subsequence"]
    D --> E
    style A fill:#4D96FF,color:#fff,stroke:#2c5fb8,stroke-width:2px
    style B fill:#9D4EDD,color:#fff,stroke:#6a2ca0,stroke-width:2px
    style C fill:#06D6A0,color:#000,stroke:#049270,stroke-width:2px
    style D fill:#FF9F1C,color:#000,stroke:#c97900,stroke-width:2px
    style E fill:#F72585,color:#fff,stroke:#b81b64,stroke-width:2px
```

```mermaid
%%{init: {"themeVariables": {"xyChart": {"plotColorPalette": "#4D96FF, #FFD93D, #06D6A0, #F72585"}}}}%%
xychart-beta
    title "Q7: LCS DP Table Growth (m x n cells)"
    x-axis ["10x10", "50x50", "100x100", "200x200"]
    y-axis "Table Cells Filled" 0 --> 100
    bar [1, 25, 100, 100]
```

| Metric | Complexity | Why |
|---|---|---|
| Time | `O(m·n)` | Fill every cell of the `(m+1)×(n+1)` table once |
| Space | `O(m·n)` | Full table needed to backtrack and reconstruct the subsequence — droppable to `O(min(m,n))` if only the *length* is needed |

---

## 8. ⛓️ Matrix Chain Multiplication using Dynamic Programming

**Problem:** Given dimensions of `N−1` matrices in array `arr[]`, find the minimum number of scalar multiplications needed to multiply the full chain.

**Worked Example (from the lab sheet):**

| Input | Value |
|---|---|
| `N` | `4` |
| `arr[]` | `{10, 30, 5, 60}` |
| **Output (min. scalar multiplications)** | **`4500`** |
| **Time Complexity** | **`O(N³)`** |

**Approach — Interval DP:** `dp[i][j]` = minimum cost to multiply matrices `i` through `j`. Try every possible split point `k` inside the range and keep the cheapest.

```mermaid
flowchart TD
    A["dp[i][j] for chain i..j"] --> B["Try every split point k, i <= k < j"]
    B --> C["cost = dp[i][k] + dp[k+1][j] + arr[i-1]*arr[k]*arr[j]"]
    C --> D["dp[i][j] = min over all k of cost"]
    D --> E{"All chain lengths done?"}
    E -->|No| F["Grow chain length, repeat"]
    F --> B
    E -->|Yes| G["dp[1][N-1] = minimum total multiplications"]
    style A fill:#4D96FF,color:#fff,stroke:#2c5fb8,stroke-width:2px
    style B fill:#9D4EDD,color:#fff,stroke:#6a2ca0,stroke-width:2px
    style C fill:#FF9F1C,color:#000,stroke:#c97900,stroke-width:2px
    style D fill:#00C2CB,color:#000,stroke:#008c93,stroke-width:2px
    style E fill:#F72585,color:#fff,stroke:#b81b64,stroke-width:2px
    style F fill:#FFD93D,color:#000,stroke:#d9ad00,stroke-width:2px
    style G fill:#06D6A0,color:#000,stroke:#049270,stroke-width:2px
```

**Why `O(N³)`:** There are `O(N²)` sub-ranges `(i, j)`, and each range tries up to `O(N)` split points `k` → `O(N²) × O(N) = O(N³)`.

```mermaid
%%{init: {"themeVariables": {"xyChart": {"plotColorPalette": "#FF6B6B, #06D6A0"}}}}%%
xychart-beta
    title "Q8: Brute Force Parenthesizations vs Interval DP"
    x-axis ["N=4", "N=6", "N=8", "N=10"]
    y-axis "Relative Operation Count" 0 --> 100
    line [2, 14, 55, 100]
    line [1, 3, 7, 12]
```

| Metric | Complexity | Why |
|---|---|---|
| Time | `O(N³)` | `O(N²)` sub-ranges × `O(N)` split points each |
| Space | `O(N²)` | 2D table over all `(i, j)` chain sub-ranges |
| Brute force baseline | `O(4ⁿ / n^1.5)` (Catalan number growth) | Every possible parenthesization of the chain |

---

## 📊 Complexity Landscape — All Eight Problems

```mermaid
%%{init: {"themeVariables": {"xyChart": {"plotColorPalette": "#06D6A0, #FF6B6B, #FFD93D, #4D96FF, #9D4EDD, #FF9F1C, #00C2CB, #F72585"}}}}%%
xychart-beta
    title "Growth Order Snapshot Across the Lab"
    x-axis ["Q1 Array", "Q2 Matrix", "Q3 Convolution", "Q4 Reversal", "Q5 Fibonacci", "Q6 Knapsack", "Q7 LCS", "Q8 MCM"]
    y-axis "Relative Growth Order" 0 --> 4
    bar [1, 3, 2, 2, 1, 2, 2, 3]
```

| Problem | Dominant Complexity | Technique Signature |
|---|---|---|
| 1️⃣ Array Operations | 🟢 mostly `O(n)`, up to `O(n log n)` | Single/linear passes, occasional sort |
| 2️⃣ Matrix Operations | 🔴 `O(n²)` to `O(n³)` | Nested loops over cells / elimination |
| 3️⃣ Convolution | 🟡 `O(n log n)` | Divide-and-conquer (FFT-style) |
| 4️⃣ Reversal Sort | 🟡 `O(n)` moves, `O(n log² n)` cost | Selection + divide-and-conquer merge |
| 5️⃣ Fibonacci (DP) | 🟢 `O(n)` | Memoization / tabulation over one dimension |
| 6️⃣ 0/1 Knapsack (DP) | 🟡 `O(n·W)` | 2D table over items × capacity |
| 7️⃣ LCS (DP) | 🟡 `O(m·n)` | 2D table over both string lengths |
| 8️⃣ Matrix Chain Mult. (DP) | 🔴 `O(n³)` | Interval DP over chain split points |

---

## 🛠️ Tech Stack

<div align="center">
<img src="https://skillicons.dev/icons?i=c,git,github,vscode,linux" />
</div>

<div align="center">

![C](https://img.shields.io/badge/Standard-C99-00599C?style=flat-square&logo=c)
![Compiler](https://img.shields.io/badge/Compiler-GCC-A42E2B?style=flat-square&logo=gnu)
![Focus](https://img.shields.io/badge/Focus-Complexity_Analysis-11998E?style=flat-square)

</div>

---

## ✅ Key Takeaways

- 📏 **Not every array operation is equal.** Seven of nine classic array queries are plain `O(n)` — only median and mode tempt you into `O(n log n)` unless you reach for selection algorithms or hashing.
- 🧮 **Matrix operations jump a full order** the moment they *combine* rather than just *read* — multiplication and determinant both land at `O(n³)`, while addition, transpose, and checks stay at `O(n²)`.
- 🔊 **Divide-and-conquer beats brute force by trading multiplication for addition** — convolution's `O(n·m)` direct sum collapses to `O(n log n)` once you split, transform, and recombine.
- 🔄 **Constraints change the whole analysis.** Sorting via reversal is trivial in *reversal count* (`O(n)`), but bounding the *cost* of those reversals forces a completely different divide-and-conquer merge strategy — a great example of how the cost model shapes the algorithm.
- 🧩 **Dynamic Programming is memoized recursion, nothing more mystical.** Fibonacci's `O(2ⁿ)` naive tree collapses to `O(n)` the moment you stop recomputing the same subproblem twice.
- 🎒 **The DP table's shape mirrors the problem's dimensions.** Knapsack indexes by (items × capacity), LCS by (length of A × length of B), Matrix Chain by (start × end of a sub-chain) — the state you memoize *is* the axis of the table.

---

## 🗂️ Repository Structure

```
Lab-06/
│
├── 📁 Outputs/
│   ├── 🖼️ output-1.png   # Output — 1D Array Operations
│   ├── 🖼️ output-2.png   # Output — 2D Matrix Operations
│   ├── 🖼️ output-3.png   # Output — Convolution via Divide & Conquer
│   ├── 🖼️ output-4.png   # Output — Sorting via Reversal
│   ├── 🖼️ output-5.png   # Output — Nth Fibonacci (DP)
│   ├── 🖼️ output-6.png   # Output — 0/1 Knapsack (DP)
│   ├── 🖼️ output-7.png   # Output — Longest Common Subsequence (DP)
│   └── 🖼️ output-8.png   # Output — Matrix Chain Multiplication (DP)
│
├── 🇨 prog1.c             # Q1 · 1D Array Operations       → O(n) - O(n log n)
├── 🇨 prog2.c             # Q2 · 2D Matrix Operations      → O(n²) - O(n³)
├── 🇨 prog3.c             # Q3 · Convolution (D&C)         → O(n log n)
├── 🇨 prog4.c             # Q4 · Sorting via Reversal       → O(n log² n) cost
├── 🇨 prog5.c             # Q5 · Nth Fibonacci (DP)         → O(n)
├── 🇨 prog6.c             # Q6 · 0/1 Knapsack (DP)          → O(n·W)
├── 🇨 prog7.c             # Q7 · LCS (DP)                   → O(m·n)
├── 🇨 prog8.c             # Q8 · Matrix Chain Mult. (DP)    → O(n³)
└── 📘 README.md           # You are here
```

| Program File | Problem Solved | Output |
|---|---|---|
| `prog1.c` | 1D Array Operations and Their Complexities | `Outputs/output-1.png` |
| `prog2.c` | 2D Square Matrix Operations and Their Complexities | `Outputs/output-2.png` |
| `prog3.c` | Convolution via Divide & Conquer | `Outputs/output-3.png` |
| `prog4.c` | Sorting via Reversal Procedure | `Outputs/output-4.png` |
| `prog5.c` | Nth Fibonacci Number using DP | `Outputs/output-5.png` |
| `prog6.c` | 0/1 Knapsack Problem using DP | `Outputs/output-6.png` |
| `prog7.c` | Longest Common Subsequence using DP | `Outputs/output-7.png` |
| `prog8.c` | Matrix Chain Multiplication using DP | `Outputs/output-8.png` |

### ⚡ Build & Run

```bash
# Compile any program (example: prog1.c)
gcc prog1.c -o prog1

# Run it
./prog1        # Linux / macOS
prog1.exe      # Windows
```

> Repeat for `prog2.c` → `prog8.c`. `prog2.c` expects square-matrix dimensions as input; `prog3.c` and `prog4.c` generate or read their own sample vectors/permutations; `prog6.c`–`prog8.c` take item/string/matrix-dimension inputs as described in each problem section above.

---

<div align="center">

<img src="https://capsule-render.vercel.app/api?type=waving&color=0:38ef7d,100:11998e&height=120&section=footer" width="100%"/>

**Made with 🧠 + ☕ for DAA Lab-06 · IIIT Bhubaneswar**

</div>