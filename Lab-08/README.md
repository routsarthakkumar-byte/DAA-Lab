<div align="center">

<img src="https://capsule-render.vercel.app/api?type=waving&color=0:136a8a,100:267871&height=180&section=header&text=DAA%20Lab-08&fontSize=55&fontColor=ffffff&animation=fadeIn&fontAlignY=38&desc=Dynamic%20Programming%20%7C%20Design%20%26%20Analysis%20of%20Algorithms&descAlignY=58&descSize=18" width="100%"/>

<img src="https://readme-typing-svg.demolab.com?font=Fira+Code&size=22&duration=2500&pause=800&color=2E9CCA&center=true&vCenter=true&multiline=true&repeat=true&width=850&height=60&lines=Remember+once%2C+reuse+forever...;Coins+%7C+Subsequences+%7C+Edit+Distance+%7C+Rods+%7C+BSTs+%7C+Collatz" alt="Typing SVG" />

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
| 🧪 **Lab No.** | 08 |
| 📘 **Course** | Design and Analysis of Algorithm (DAA) |
| 🎓 **Program** | BTech (CS-B and CE), 3rd Semester |
| 📅 **Date** | September 29, 2026 |
| 👨‍🏫 **Instructor** | Dr. Ajaya Kumar Dash |
| 🎯 **Theme** | The Dynamic Programming design paradigm — 8 classic DP problems plus one legendary open problem |

---

## 🧠 Core Idea Behind This Lab

> Every problem below (except the last) shares one DNA strand: **optimal substructure** — the best answer to the whole problem is built from the best answers to smaller pieces of it — combined with **overlapping subproblems**, meaning naive recursion would solve the exact same piece again and again. DP's entire trick is a memory: *solve once, store it, reuse it.*

```mermaid
flowchart LR
    A["Problem has optimal substructure?"] -->|No| X["Greedy or Divide & Conquer instead"]
    A -->|Yes| B["Subproblems overlap?"]
    B -->|No| Y["Plain recursion is already efficient"]
    B -->|Yes| C["Dynamic Programming"]
    C --> D["Top-Down: Memoization"]
    C --> E["Bottom-Up: Tabulation"]
    style A fill:#2E9CCA,color:#fff,stroke:#1b6b8f,stroke-width:2px
    style B fill:#9D4EDD,color:#fff,stroke:#6a2ca0,stroke-width:2px
    style C fill:#06D6A0,color:#000,stroke:#049270,stroke-width:2px
    style D fill:#4D96FF,color:#fff,stroke:#2c5fb8,stroke-width:2px
    style E fill:#FF9F1C,color:#000,stroke:#c97900,stroke-width:2px
    style X fill:#FF6B6B,color:#fff,stroke:#c94242,stroke-width:2px
    style Y fill:#FFD93D,color:#000,stroke:#d9ad00,stroke-width:2px
```

---

## 📂 Problem Index

| # | Problem | DP State | Complexity |
|---|---------|----------|------------|
| 1 | [Minimum Coin Change](#1--minimum-coin-change) | `dp[amount]` | `O(n·V)` |
| 2 | [Coin Change — Total Ways](#2--coin-change-total-number-of-ways) | `dp[coin][amount]` | `O(n·V)` |
| 3 | [Longest Common Subsequence](#3--longest-common-subsequence-lcs) | `dp[i][j]` over both strings | `O(m·n)` |
| 4 | [Longest Increasing Subsequence](#4--longest-increasing-subsequence) | `dp[i]` = LIS ending at `i` | `O(n²)` → `O(n log n)` |
| 5 | [Maximum Sum Increasing Subsequence](#5--maximum-sum-increasing-subsequence) | `dp[i]` = best sum ending at `i` | `O(n²)` |
| 6 | [Edit Distance with Traceback](#6--edit-distance-with-traceback-information) | `dp[i][j]` over both strings | `O(m·n)` |
| 7 | [Rod Cutting with Reconstruction](#7--rod-cutting-with-reconstruction) | `dp[length]` | `O(n²)` |
| 8 | [Optimal Binary Search Trees](#8--optimal-binary-search-trees-obst) | `dp[i][j]` over key ranges | `O(n³)` |
| 9 | [Collatz Conjecture](#9--collatz-conjecture-open-unsolved-problem) | *(not DP — open problem)* | Unbounded / unproven |

---

<div align="center">
<img src="https://capsule-render.vercel.app/api?type=rect&color=0:136a8a,100:267871&height=4&width=100%25" width="100%"/>
</div>

## 1. 🪙 Minimum Coin Change

**Problem:** Given coin denominations `C` and target amount `V`, find the **minimum number of coins** to make `V` (infinite supply of each coin), or `-1` if impossible.

**Approach:** `dp[v]` = minimum coins to make amount `v`. For each amount, try every coin and take the best.

```mermaid
flowchart TD
    A["dp[0] = 0"] --> B["For v = 1 to V"]
    B --> C["For each coin c <= v"]
    C --> D["dp[v] = min(dp[v], dp[v-c] + 1)"]
    D --> E{"dp[V] still infinity?"}
    E -->|Yes| F["Return -1"]
    E -->|No| G["Return dp[V]"]
    style A fill:#4D96FF,color:#fff,stroke:#2c5fb8,stroke-width:2px
    style B fill:#9D4EDD,color:#fff,stroke:#6a2ca0,stroke-width:2px
    style C fill:#FF9F1C,color:#000,stroke:#c97900,stroke-width:2px
    style D fill:#06D6A0,color:#000,stroke:#049270,stroke-width:2px
    style E fill:#F72585,color:#fff,stroke:#b81b64,stroke-width:2px
    style F fill:#FF6B6B,color:#fff,stroke:#c94242,stroke-width:2px
    style G fill:#06D6A0,color:#000,stroke:#049270,stroke-width:2px
```

```mermaid
%%{init: {"themeVariables": {"xyChart": {"plotColorPalette": "#FF6B6B, #06D6A0"}}}}%%
xychart-beta
    title "Q1: Brute-Force Combinations vs DP Table Fill"
    x-axis ["V=10", "V=50", "V=100", "V=500"]
    y-axis "Relative Operation Count" 0 --> 100
    line [3, 25, 60, 100]
    line [1, 4, 8, 35]
```

| Metric | Complexity |
|---|---|
| Time | `O(n·V)` — `V` amounts × `n` coins each |
| Space | `O(V)` — one array indexed by amount |

---

## 2. 🔢 Coin Change: Total Number of Ways

**Problem:** Count the **total distinct combinations** of coins summing to `V` (order doesn't matter).

**Approach:** The key difference from Q1 — iterate coins in the **outer** loop so each combination is counted once, not once per ordering.

```mermaid
flowchart TD
    A["dp[0] = 1, dp[1..V] = 0"] --> B["For each coin c in C"]
    B --> C["For v = c to V"]
    C --> D["dp[v] = dp[v] + dp[v-c]"]
    D --> E{"More coins left?"}
    E -->|Yes| B
    E -->|No| F["dp[V] = total ways"]
    style A fill:#4D96FF,color:#fff,stroke:#2c5fb8,stroke-width:2px
    style B fill:#9D4EDD,color:#fff,stroke:#6a2ca0,stroke-width:2px
    style C fill:#FF9F1C,color:#000,stroke:#c97900,stroke-width:2px
    style D fill:#06D6A0,color:#000,stroke:#049270,stroke-width:2px
    style E fill:#F72585,color:#fff,stroke:#b81b64,stroke-width:2px
    style F fill:#06D6A0,color:#000,stroke:#049270,stroke-width:2px
```

| Metric | Complexity |
|---|---|
| Time | `O(n·V)` | 
| Space | `O(V)` |

> ⚠️ **Loop order matters here!** Swapping the two loops (amount outer, coin inner) would count permutations instead of combinations — a classic DP gotcha worth noting in your program comments.

---

<div align="center">
<img src="https://capsule-render.vercel.app/api?type=rect&color=0:267871,100:136a8a&height=4&width=100%25" width="100%"/>
</div>

## 3. 🧬 Longest Common Subsequence (LCS)

**Problem:** Given sequences `X` (length `m`) and `Y` (length `n`), find the length of their LCS and reconstruct it.

**Approach:** `dp[i][j]` = LCS length of `X[1..i]` and `Y[1..j]`. Matching characters extend the diagonal; mismatches take the best of two neighbors.

```mermaid
flowchart TD
    A["dp[i][j]"] --> B{"X[i] == Y[j] ?"}
    B -->|Yes| C["dp[i][j] = dp[i-1][j-1] + 1"]
    B -->|No| D["dp[i][j] = max(dp[i-1][j], dp[i][j-1])"]
    C --> E["Backtrack diagonals to rebuild the subsequence"]
    D --> E
    style A fill:#4D96FF,color:#fff,stroke:#2c5fb8,stroke-width:2px
    style B fill:#9D4EDD,color:#fff,stroke:#6a2ca0,stroke-width:2px
    style C fill:#06D6A0,color:#000,stroke:#049270,stroke-width:2px
    style D fill:#FF9F1C,color:#000,stroke:#c97900,stroke-width:2px
    style E fill:#F72585,color:#fff,stroke:#b81b64,stroke-width:2px
```

| Metric | Complexity |
|---|---|
| Time | `O(m·n)` |
| Space | `O(m·n)` — full table needed for backtracking/reconstruction |

---

## 4. 📈 Longest Increasing Subsequence

**Problem:** Find the length of the longest strictly increasing subsequence in array `A`.

**Approach — Two levels of sophistication:**

```mermaid
flowchart TD
    A["dp[i] = 1 + max(dp[j]) for all j < i where A[j] < A[i]"] --> B["Classic DP: O(n^2)"]
    C["Maintain 'tails' array of smallest tail<br/>per LIS length, binary search to place each element"] --> D["Patience Sorting: O(n log n)"]
    style A fill:#4D96FF,color:#fff,stroke:#2c5fb8,stroke-width:2px
    style B fill:#FF6B6B,color:#fff,stroke:#c94242,stroke-width:2px
    style C fill:#9D4EDD,color:#fff,stroke:#6a2ca0,stroke-width:2px
    style D fill:#06D6A0,color:#000,stroke:#049270,stroke-width:2px
```

```mermaid
%%{init: {"themeVariables": {"xyChart": {"plotColorPalette": "#FF6B6B, #06D6A0"}}}}%%
xychart-beta
    title "Q4: Classic O(n^2) DP vs Patience-Sorting O(n log n)"
    x-axis ["n=100", "n=1000", "n=10000", "n=100000"]
    y-axis "Relative Operation Count" 0 --> 100
    line [1, 10, 60, 100]
    line [1, 3, 5, 7]
```

| Approach | Time | Space |
|---|---|---|
| Classic DP | `O(n²)` | `O(n)` |
| Patience sorting + binary search | `O(n log n)` | `O(n)` |

---

## 5. 💰 Maximum Sum Increasing Subsequence

**Problem:** Find the maximum possible **sum** of a strictly increasing subsequence (not just the longest length).

**Approach:** Nearly identical structure to Q4, but the DP tracks accumulated sum instead of length.

```mermaid
flowchart TD
    A["dp[i] = A[i] - standalone sum"] --> B["For each j < i where A[j] < A[i]"]
    B --> C["dp[i] = max(dp[i], dp[j] + A[i])"]
    C --> D{"More i left?"}
    D -->|Yes| B
    D -->|No| E["Answer = max over all dp[i]"]
    style A fill:#4D96FF,color:#fff,stroke:#2c5fb8,stroke-width:2px
    style B fill:#9D4EDD,color:#fff,stroke:#6a2ca0,stroke-width:2px
    style C fill:#06D6A0,color:#000,stroke:#049270,stroke-width:2px
    style D fill:#F72585,color:#fff,stroke:#b81b64,stroke-width:2px
    style E fill:#FF9F1C,color:#000,stroke:#c97900,stroke-width:2px
```

| Metric | Complexity |
|---|---|
| Time | `O(n²)` |
| Space | `O(n)` |

---

<div align="center">
<img src="https://capsule-render.vercel.app/api?type=rect&color=0:136a8a,100:267871&height=4&width=100%25" width="100%"/>
</div>

## 6. ✏️ Edit Distance with Traceback Information

**Problem:** Minimum insertions/deletions/substitutions to transform string `A` (length `m`) into `B` (length `n`), with the traceback path printed.

**Approach:** `dp[i][j]` = edit distance between `A[1..i]` and `B[1..j]`. Matching characters cost nothing; mismatches take the cheapest of insert, delete, or substitute.

```mermaid
flowchart TD
    A["dp[i][j]"] --> B{"A[i] == B[j] ?"}
    B -->|Yes| C["dp[i][j] = dp[i-1][j-1]"]
    B -->|No| D["dp[i][j] = 1 + min(<br/>dp[i-1][j] delete,<br/>dp[i][j-1] insert,<br/>dp[i-1][j-1] substitute)"]
    C --> E["Store the chosen direction for traceback"]
    D --> E
    E --> F["Backtrack from dp[m][n] to print the operation sequence"]
    style A fill:#4D96FF,color:#fff,stroke:#2c5fb8,stroke-width:2px
    style B fill:#9D4EDD,color:#fff,stroke:#6a2ca0,stroke-width:2px
    style C fill:#06D6A0,color:#000,stroke:#049270,stroke-width:2px
    style D fill:#FF9F1C,color:#000,stroke:#c97900,stroke-width:2px
    style E fill:#00C2CB,color:#000,stroke:#008c93,stroke-width:2px
    style F fill:#F72585,color:#fff,stroke:#b81b64,stroke-width:2px
```

| Metric | Complexity |
|---|---|
| Time | `O(m·n)` |
| Space | `O(m·n)` — needed to reconstruct the traceback path |

---

## 7. 🪵 Rod Cutting with Reconstruction

**Problem:** Given rod length `n` and price array `P`, find the maximum revenue from cutting the rod into pieces, **and** the exact lengths used.

**Approach:** `dp[len]` = best revenue for a rod of length `len`. Try every first-cut length and recurse on the remainder; store the chosen first cut for reconstruction.

```mermaid
flowchart TD
    A["dp[0] = 0"] --> B["For len = 1 to n"]
    B --> C["Try every cut i = 1..len"]
    C --> D["dp[len] = max(dp[len], P[i] + dp[len-i])"]
    D --> E["Store best i in choice[len]"]
    E --> F{"len == n done?"}
    F -->|No| B
    F -->|Yes| G["Walk choice[] from n down to 0<br/>to reconstruct the piece lengths"]
    style A fill:#4D96FF,color:#fff,stroke:#2c5fb8,stroke-width:2px
    style B fill:#9D4EDD,color:#fff,stroke:#6a2ca0,stroke-width:2px
    style C fill:#FF9F1C,color:#000,stroke:#c97900,stroke-width:2px
    style D fill:#06D6A0,color:#000,stroke:#049270,stroke-width:2px
    style E fill:#00C2CB,color:#000,stroke:#008c93,stroke-width:2px
    style F fill:#F72585,color:#fff,stroke:#b81b64,stroke-width:2px
    style G fill:#FFD93D,color:#000,stroke:#d9ad00,stroke-width:2px
```

| Metric | Complexity |
|---|---|
| Time | `O(n²)` — `n` lengths × up to `n` cut choices each |
| Space | `O(n)` for `dp[]`, plus `O(n)` for the choice/reconstruction array |

---

## 8. 🌳 Optimal Binary Search Trees (OBST)

**Problem:** Given `n` sorted keys with search probabilities and `n+1` dummy-key probabilities, build the BST that **minimizes expected search cost**.

**Approach — Interval DP:** `dp[i][j]` = minimum expected cost of a tree containing keys `i` through `j`. Try every key in the range as the root; add the cost of the subtree plus the total probability weight of the range (since every node's depth increases by one when it's not the root).

```mermaid
flowchart TD
    A["dp[i][j] for keys i..j"] --> B["Try every root r in range i..j"]
    B --> C["cost = dp[i][r-1] + dp[r+1][j] + weight(i,j)"]
    C --> D["dp[i][j] = min over all r of cost"]
    D --> E{"All ranges computed?"}
    E -->|No| F["Grow range size, repeat"]
    F --> B
    E -->|Yes| G["dp[1][n] = minimum expected search cost"]
    style A fill:#4D96FF,color:#fff,stroke:#2c5fb8,stroke-width:2px
    style B fill:#9D4EDD,color:#fff,stroke:#6a2ca0,stroke-width:2px
    style C fill:#FF9F1C,color:#000,stroke:#c97900,stroke-width:2px
    style D fill:#00C2CB,color:#000,stroke:#008c93,stroke-width:2px
    style E fill:#F72585,color:#fff,stroke:#b81b64,stroke-width:2px
    style F fill:#FFD93D,color:#000,stroke:#d9ad00,stroke-width:2px
    style G fill:#06D6A0,color:#000,stroke:#049270,stroke-width:2px
```

```mermaid
%%{init: {"themeVariables": {"xyChart": {"plotColorPalette": "#FF6B6B, #FFD93D, #06D6A0"}}}}%%
xychart-beta
    title "Q8: OBST - Naive Enumeration vs Standard DP vs Knuth-Optimized DP"
    x-axis ["Naive Catalan-growth", "Standard DP O(n^3)", "Knuth-Optimized O(n^2)"]
    y-axis "Relative Cost" 0 --> 100
    bar [100, 45, 15]
```

| Metric | Complexity |
|---|---|
| Time (standard interval DP) | `O(n³)` — `O(n²)` ranges × `O(n)` root choices each |
| Time (Knuth's optimization) | `O(n²)` — exploits monotonicity of optimal root choice |
| Space | `O(n²)` |

---

<div align="center">
<img src="https://capsule-render.vercel.app/api?type=rect&color=0:267871,100:136a8a&height=4&width=100%25" width="100%"/>
</div>

## 9. 🌀 Collatz Conjecture (Open, Unsolved Problem)

**The recurrence:**

```
        ⎧ n / 2        if n is even
T(n)  = ⎨
        ⎩ 3n + 1       if n is odd
```

Repeatedly apply `T` starting from any positive integer `n` — conjectured (but **unproven**) to always eventually reach `1`.

> 🔓 This one isn't a DP problem at all — there's no optimal substructure to exploit, because nobody has proven the recursion even *terminates* for every input. It's included here as a C-programming exercise in iteration, pointers/dynamic memory, and integer-overflow handling, and as a reminder that **"simple to state" ≠ "simple to solve."**

```mermaid
flowchart TD
    A["Start with n >= 1"] --> B{"n == 1 ?"}
    B -->|Yes| C["Trajectory complete"]
    B -->|No| D{"n even?"}
    D -->|Yes| E["n = n / 2"]
    D -->|No| F["n = 3n + 1"]
    E --> B
    F --> B
    style A fill:#4D96FF,color:#fff,stroke:#2c5fb8,stroke-width:2px
    style B fill:#9D4EDD,color:#fff,stroke:#6a2ca0,stroke-width:2px
    style C fill:#06D6A0,color:#000,stroke:#049270,stroke-width:2px
    style D fill:#FF9F1C,color:#000,stroke:#c97900,stroke-width:2px
    style E fill:#F72585,color:#fff,stroke:#b81b64,stroke-width:2px
    style F fill:#FF6B6B,color:#fff,stroke:#c94242,stroke-width:2px
```

**Example trajectory — `n = 27`:** one of the most famous small starting values, taking **111 steps** and spiking to a peak value of **9,232** before collapsing to 1 — a striking illustration of how "simple rules" can produce wildly chaotic-looking behavior.

```mermaid
%%{init: {"themeVariables": {"xyChart": {"plotColorPalette": "#F72585"}}}}%%
xychart-beta
    title "Q9: Collatz Trajectory of n=27 (sampled steps)"
    x-axis ["Step 0", "Step 10", "Step 20", "Step 30", "Step 40", "Step 50", "Step 60", "Step 70", "Step 77 (peak)", "Step 90", "Step 100", "Step 111"]
    y-axis "Value" 0 --> 10000
    line [27, 214, 274, 350, 890, 566, 719, 911, 9232, 244, 53, 1]
```

| Metric | Status |
|---|---|
| Termination for all `n ≥ 1` | ❓ **Unproven** — verified computationally for enormous ranges, never proven in general |
| Worst-case trajectory length | **Unbounded / unknown** — no closed-form bound exists |
| Per-step cost | `O(1)` arithmetic, but **total steps is not polynomially bounded** by any known function of `n` |
| Programming focus | Iteration, modular functions, pointers/dynamic arrays to store trajectories, `long`/`unsigned long long` to guard against overflow on the `3n+1` branch |

---

## 📊 Complexity Landscape — Problems 1 to 8

```mermaid
%%{init: {"themeVariables": {"xyChart": {"plotColorPalette": "#4D96FF, #9D4EDD, #06D6A0, #FF9F1C, #F72585, #00C2CB, #FFD93D, #FF6B6B"}}}}%%
xychart-beta
    title "Relative Growth Order Snapshot (DP Problems Only)"
    x-axis ["Q1 Coin-Min", "Q2 Coin-Ways", "Q3 LCS", "Q4 LIS", "Q5 MSIS", "Q6 Edit-Dist", "Q7 Rod-Cut", "Q8 OBST"]
    y-axis "Relative Growth Order" 0 --> 4
    bar [2, 2, 3, 2, 3, 3, 3, 4]
```

| Problem | Complexity | DP Shape |
|---|---|---|
| 1️⃣ Minimum Coin Change | 🟡 `O(n·V)` | 1D table |
| 2️⃣ Coin Change — Ways | 🟡 `O(n·V)` | 1D table, careful loop order |
| 3️⃣ LCS | 🟠 `O(m·n)` | 2D table |
| 4️⃣ LIS | 🟡 `O(n²)` → `O(n log n)` | 1D table (or binary search) |
| 5️⃣ Max Sum IS | 🟠 `O(n²)` | 1D table |
| 6️⃣ Edit Distance | 🟠 `O(m·n)` | 2D table |
| 7️⃣ Rod Cutting | 🟠 `O(n²)` | 1D table |
| 8️⃣ OBST | 🔴 `O(n³)` → `O(n²)` | 2D interval table |

---

## 🛠️ Tech Stack

<div align="center">
<img src="https://skillicons.dev/icons?i=c,git,github,vscode,linux" />
</div>

<div align="center">

![C](https://img.shields.io/badge/Standard-C99-00599C?style=flat-square&logo=c)
![Compiler](https://img.shields.io/badge/Compiler-GCC-A42E2B?style=flat-square&logo=gnu)
![Focus](https://img.shields.io/badge/Focus-Dynamic_Programming-136A8A?style=flat-square)

</div>

---

## ✅ Key Takeaways

- 🪙 **1D vs 2D DP is about how many "things" are changing.** Coin-change and rod-cutting track one shrinking quantity (amount, length) — LCS and Edit Distance track two independent sequences at once, hence the 2D table.
- 🔁 **Loop order can silently change the answer.** Q1 and Q2 use almost identical recurrences, but swapping which loop is outer turns "combinations" into "permutations" — a subtle, easy-to-miss bug worth testing for explicitly.
- 📈 **The same problem can have two correct complexities.** LIS's `O(n²)` DP and `O(n log n)` patience-sorting approach compute the *same answer* — the second just recognizes extra structure (sorted "tails") that the first throws away.
- 🌳 **Interval DP (OBST) generalizes the "try every split point" pattern** seen in Matrix Chain Multiplication from the previous lab — same shape, different cost function.
- 🌀 **Not everything is Dynamic Programming.** The Collatz Conjecture closes the lab on purpose — a reminder that some recurrences have no known optimal substructure, no proof of termination, and no polynomial bound, however simple they look on paper.

---

## 🗂️ Repository Structure

```
Lab-08/
│
├── 📁 Outputs/
│   ├── 🖼️ prog1.png   # Output — Minimum Coin Change
│   ├── 🖼️ prog2.png   # Output — Coin Change: Total Ways
│   ├── 🖼️ prog3.png   # Output — Longest Common Subsequence
│   ├── 🖼️ prog4.png   # Output — Longest Increasing Subsequence
│   ├── 🖼️ prog5.png   # Output — Maximum Sum Increasing Subsequence
│   ├── 🖼️ prog6.png   # Output — Edit Distance with Traceback
│   ├── 🖼️ prog7.png   # Output — Rod Cutting with Reconstruction
│   ├── 🖼️ prog8.png   # Output — Optimal Binary Search Trees
│   └── 🖼️ prog9.png   # Output — Collatz Conjecture
│
├── 🇨 prog1.c           # Q1 · Minimum Coin Change            → O(n·V)
├── 🇨 prog2.c           # Q2 · Coin Change: Total Ways        → O(n·V)
├── 🇨 prog3.c           # Q3 · Longest Common Subsequence     → O(m·n)
├── 🇨 prog4.c           # Q4 · Longest Increasing Subsequence → O(n²) / O(n log n)
├── 🇨 prog5.c           # Q5 · Max Sum Increasing Subsequence → O(n²)
├── 🇨 prog6.c           # Q6 · Edit Distance with Traceback   → O(m·n)
├── 🇨 prog7.c           # Q7 · Rod Cutting with Reconstruction→ O(n²)
├── 🇨 prog8.c           # Q8 · Optimal Binary Search Trees    → O(n³)
├── 🇨 prog9.c           # Q9 · Collatz Conjecture              → Unbounded / unproven
└── 📘 README.md         # You are here
```

| Program File | Problem Solved | Output |
|---|---|---|
| `prog1.c` | Minimum Coin Change | `Outputs/prog1.png` |
| `prog2.c` | Coin Change: Total Number of Ways | `Outputs/prog2.png` |
| `prog3.c` | Longest Common Subsequence (LCS) | `Outputs/prog3.png` |
| `prog4.c` | Longest Increasing Subsequence | `Outputs/prog4.png` |
| `prog5.c` | Maximum Sum Increasing Subsequence | `Outputs/prog5.png` |
| `prog6.c` | Edit Distance with Traceback Information | `Outputs/prog6.png` |
| `prog7.c` | Rod Cutting with Reconstruction | `Outputs/prog7.png` |
| `prog8.c` | Optimal Binary Search Trees (OBST) | `Outputs/prog8.png` |
| `prog9.c` | Collatz Conjecture | `Outputs/prog9.png` |

### ⚡ Build & Run

```bash
# Compile any program (example: prog1.c)
gcc prog1.c -o prog1

# Run it
./prog1        # Linux / macOS
prog1.exe      # Windows
```

> Repeat for `prog2.c` → `prog9.c`. `prog3.c` and `prog6.c` take two input strings; `prog8.c` takes keys with search probabilities; `prog9.c` takes a starting value `n` and an interval `[a, b]` to analyse, per the problem statement.

---

<div align="center">

<img src="https://capsule-render.vercel.app/api?type=waving&color=0:267871,100:136a8a&height=120&section=footer" width="100%"/>

**Made with 🧠 + ☕ for DAA Lab-08 · IIIT Bhubaneswar**

</div>