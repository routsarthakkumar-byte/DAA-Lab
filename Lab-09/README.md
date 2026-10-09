<div align="center">

<img src="https://capsule-render.vercel.app/api?type=waving&color=0:ff416c,100:ff4b2b&height=180&section=header&text=DAA%20Lab-09&fontSize=55&fontColor=ffffff&animation=fadeIn&fontAlignY=38&desc=The%20Greedy%20Design%20Paradigm%20%7C%20Design%20%26%20Analysis%20of%20Algorithms&descAlignY=58&descSize=18" width="100%"/>

<img src="https://readme-typing-svg.demolab.com?font=Fira+Code&size=22&duration=2500&pause=800&color=FF416C&center=true&vCenter=true&multiline=true&repeat=true&width=900&height=60&lines=Take+the+best+choice+right+now...+and+never+look+back;Huffman+%7C+Heaps+%7C+Intervals+%7C+Candies+%7C+Superstrings" alt="Typing SVG" />

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
| 🧪 **Lab No.** | 09 |
| 📘 **Course** | Design and Analysis of Algorithm (DAA) |
| 🎓 **Program** | BTech (CS-B and CE), 3rd Semester |
| 📅 **Date** | October 6, 2026 |
| 👨‍🏫 **Instructor** | Dr. Ajaya Kumar Dash |
| 🎯 **Theme** | Greedy design paradigm — 9 medium-to-hard problems plus one open research question |

---

## 🧠 Core Idea Behind This Lab

> A greedy algorithm commits to the **locally best choice at every step** and never revisits it. It only works when two properties hold: the **greedy-choice property** (a locally optimal pick can be extended to a globally optimal solution) and **optimal substructure**. Proving those properties — usually with an *exchange argument* — is the real work; the code is often just a sort or a heap.

```mermaid
flowchart LR
    A["Problem"] --> B{"Greedy-choice property holds?"}
    B -->|"Yes - exchange argument works"| C["Greedy is optimal"]
    B -->|"No"| D["Need DP or search"]
    C --> E["Sort once"]
    C --> F["Use a heap"]
    C --> G["Scan in one or two passes"]
    style A fill:#FF416C,color:#fff,stroke:#b52a4a,stroke-width:2px
    style B fill:#9D4EDD,color:#fff,stroke:#6a2ca0,stroke-width:2px
    style C fill:#06D6A0,color:#000,stroke:#049270,stroke-width:2px
    style D fill:#FF6B6B,color:#fff,stroke:#c94242,stroke-width:2px
    style E fill:#4D96FF,color:#fff,stroke:#2c5fb8,stroke-width:2px
    style F fill:#FF9F1C,color:#000,stroke:#c97900,stroke-width:2px
    style G fill:#FFD93D,color:#000,stroke:#d9ad00,stroke-width:2px
```

---

## 📂 Problem Index

| # | Problem | Greedy Tool | Complexity |
|---|---------|-------------|------------|
| 1 | [Fractional Knapsack with Deterioration](#1--fractional-knapsack-with-deterioration-rate) | Best current value density | `O(n log n)` – `O(n²)`* |
| 2 | [Huffman Coding](#2--huffman-coding-canonical-codebook) | Min-heap merge of two rarest | `O(n log n)` |
| 3 | [Minimum Refuelling Stops](#3--minimum-initial-fuel-reverse-greedy) | Max-heap of passed stations | `O(n log n)` |
| 4 | [Connect Sticks](#4--minimum-cost-to-connect-sticks) | Min-heap, merge two smallest | `O(n log n)` |
| 5 | [Candy Distribution](#5--candy-distribution-bi-directional-slope-greedy) | Left pass + right pass | `O(n)` |
| 6 | [Reorganise String, K Apart](#6--reorganise-string-with-k-distance-apart) | Max-heap + cooldown queue | `O(N log A)` |
| 7 | [Minimise Deviation](#7--minimise-deviation-in-array) | Max-heap, shrink the largest | `O(n log n · log M)` |
| 8 | [Minimum Meeting Rooms](#8--minimum-number-of-meeting-rooms) | Sort + min-heap of end times | `O(n log n)` |
| 9 | [Hu-Tucker Simulation](#9--hu-tucker-greedy-simulation) | Merge cheapest compatible pair | `O(n log n)` – `O(n²)`* |
| 10 | [Greedy Superstring Conjecture](#10--greedy-superstring-conjecture-open-problem) | Merge max-overlap pair | NP-hard exact · polynomial heuristic |

<sub>* Depends on implementation — see the individual sections.</sub>

---

<div align="center">
<img src="https://capsule-render.vercel.app/api?type=rect&color=0:ff416c,100:ff4b2b&height=4&width=100%25" width="100%"/>
</div>

## 1. 🎒 Fractional Knapsack with Deterioration Rate

**Problem:** `n` items with value `vᵢ`, weight `wᵢ`, and decay rate `λᵢ > 0`. An item consumed at time `t` has effective density `(vᵢ/wᵢ) − λᵢ·t`. Choose the consumption order and fractions to maximise total value within capacity `W`.

**Approach:** The classic fractional knapsack is greedy by density. Here density *drifts with time*, so the greedy rule becomes **"always take the item whose current effective density is highest"**, re-evaluated as time advances, taking fractions until the knapsack is full or densities turn non-positive (those items add no value and are skipped).

```mermaid
flowchart TD
    A["Compute effective density of every item at current time t"] --> B["Pick item with highest positive density"]
    B --> C{"Whole item fits in remaining capacity?"}
    C -->|"Yes"| D["Take it fully, advance time t"]
    C -->|"No"| E["Take the fitting fraction, knapsack full"]
    D --> F{"Capacity left and items remain?"}
    F -->|"Yes"| A
    F -->|"No"| G["Report total value"]
    E --> G
    style A fill:#4D96FF,color:#fff,stroke:#2c5fb8,stroke-width:2px
    style B fill:#9D4EDD,color:#fff,stroke:#6a2ca0,stroke-width:2px
    style C fill:#F72585,color:#fff,stroke:#b81b64,stroke-width:2px
    style D fill:#06D6A0,color:#000,stroke:#049270,stroke-width:2px
    style E fill:#FF9F1C,color:#000,stroke:#c97900,stroke-width:2px
    style F fill:#00C2CB,color:#000,stroke:#008c93,stroke-width:2px
    style G fill:#FFD93D,color:#000,stroke:#d9ad00,stroke-width:2px
```

| Strategy | Time | Space |
|---|---|---|
| Re-scan all items for the best density each step | `O(n²)` | `O(1)` extra |
| Sort by a fixed key when the order is static | `O(n log n)` | `O(1)` extra |

> 🔎 Because decay is linear in `t`, two items' density lines can cross, so a single up-front sort is only valid when the ordering cannot change — the re-evaluating version is the safe general form.

---

## 2. 🌲 Huffman Coding (Canonical Codebook)

**Problem:** Build a prefix-free binary code of minimum expected length from symbol frequencies, then output the **canonical** codebook (codes ordered by length, then lexicographically).

**Approach:** Repeatedly extract the two lowest-frequency nodes from a min-heap, merge them under a new parent whose frequency is their sum, and push it back. Code *lengths* come from node depths; the *canonical* codes are then assigned by sorting symbols by (length, symbol) and counting upward in binary.

```mermaid
flowchart TD
    A["Push all symbols into a min-heap"] --> B{"More than one node left?"}
    B -->|"Yes"| C["Extract two smallest nodes"]
    C --> D["Merge into parent with summed frequency"]
    D --> E["Push parent back into heap"]
    E --> B
    B -->|"No"| F["Read code length of each symbol from tree depth"]
    F --> G["Sort by length then symbol, assign canonical codes"]
    style A fill:#4D96FF,color:#fff,stroke:#2c5fb8,stroke-width:2px
    style B fill:#9D4EDD,color:#fff,stroke:#6a2ca0,stroke-width:2px
    style C fill:#FF9F1C,color:#000,stroke:#c97900,stroke-width:2px
    style D fill:#06D6A0,color:#000,stroke:#049270,stroke-width:2px
    style E fill:#00C2CB,color:#000,stroke:#008c93,stroke-width:2px
    style F fill:#F72585,color:#fff,stroke:#b81b64,stroke-width:2px
    style G fill:#FFD93D,color:#000,stroke:#d9ad00,stroke-width:2px
```

**Worked example** (frequencies `a:5, b:9, c:12, d:13, e:16, f:45`):

| Symbol | Frequency | Code length | Canonical code |
|---|---|---|---|
| f | 45 | 1 | `0` |
| c | 12 | 3 | `100` |
| d | 13 | 3 | `101` |
| e | 16 | 3 | `110` |
| a | 5 | 4 | `1110` |
| b | 9 | 4 | `1111` |

Expected length = `224 / 100 = 2.24` bits per symbol, versus `3` bits for a fixed-length code.

| Metric | Complexity |
|---|---|
| Heap-based tree construction | `O(n log n)` — `n−1` merges, each `O(log n)` |
| Canonical code assignment | `O(n log n)` — dominated by the sort |
| Space | `O(n)` |

---

## 3. ⛽ Minimum Initial Fuel (Reverse Greedy)

**Problem:** Reach target distance `D` starting with fuel `F`; stations `(dᵢ, fᵢ)` refuel the vehicle. Find the **minimum number of refuelling stops**.

**Approach — "Decide later" greedy:** Drive as far as the current fuel allows, *remembering* every station passed in a **max-heap of refuel amounts**. When fuel runs out before the target, retroactively "stop" at the passed station with the largest refuel. If the heap is empty and the target is still out of range, it is unreachable.

```mermaid
flowchart TD
    A["Fuel = F, stops = 0"] --> B["Push every station within current range into max-heap"]
    B --> C{"Can reach target D?"}
    C -->|"Yes"| D["Return stops"]
    C -->|"No"| E{"Heap empty?"}
    E -->|"Yes"| F["Unreachable - report -1"]
    E -->|"No"| G["Pop largest refuel, add to fuel, stops + 1"]
    G --> B
    style A fill:#4D96FF,color:#fff,stroke:#2c5fb8,stroke-width:2px
    style B fill:#9D4EDD,color:#fff,stroke:#6a2ca0,stroke-width:2px
    style C fill:#F72585,color:#fff,stroke:#b81b64,stroke-width:2px
    style D fill:#06D6A0,color:#000,stroke:#049270,stroke-width:2px
    style E fill:#FF9F1C,color:#000,stroke:#c97900,stroke-width:2px
    style F fill:#FF6B6B,color:#fff,stroke:#c94242,stroke-width:2px
    style G fill:#00C2CB,color:#000,stroke:#008c93,stroke-width:2px
```

| Metric | Complexity |
|---|---|
| Time | `O(n log n)` — each station is pushed and popped at most once |
| Space | `O(n)` for the heap |

---

<div align="center">
<img src="https://capsule-render.vercel.app/api?type=rect&color=0:ff4b2b,100:ff416c&height=4&width=100%25" width="100%"/>
</div>

## 4. 🪢 Minimum Cost to Connect Sticks

**Problem:** Joining sticks of length `x` and `y` costs `x + y`. Minimise the total cost of joining all `n` sticks into one.

**Approach:** Always join the **two shortest** sticks — short sticks get re-added into later joins, so they should be paid for as few times as possible. This is structurally identical to Huffman's merge step.

**Worked example:** sticks `{2, 3, 4}` → join `2+3 = 5` (cost 5), then `5+4 = 9` (cost 9) → **total 14**.

```mermaid
flowchart LR
    A["Min-heap of stick lengths"] --> B["Pop two smallest x, y"]
    B --> C["cost += x + y"]
    C --> D["Push x + y back"]
    D --> E{"One stick left?"}
    E -->|"No"| B
    E -->|"Yes"| F["Return total cost"]
    style A fill:#4D96FF,color:#fff,stroke:#2c5fb8,stroke-width:2px
    style B fill:#9D4EDD,color:#fff,stroke:#6a2ca0,stroke-width:2px
    style C fill:#FF9F1C,color:#000,stroke:#c97900,stroke-width:2px
    style D fill:#00C2CB,color:#000,stroke:#008c93,stroke-width:2px
    style E fill:#F72585,color:#fff,stroke:#b81b64,stroke-width:2px
    style F fill:#06D6A0,color:#000,stroke:#049270,stroke-width:2px
```

```mermaid
%%{init: {"themeVariables": {"xyChart": {"plotColorPalette": "#FF6B6B, #06D6A0"}}}}%%
xychart-beta
    title "Q4: Re-sorting Every Round vs Min-Heap"
    x-axis ["n=100", "n=1000", "n=10000", "n=100000"]
    y-axis "Relative Operation Count" 0 --> 100
    line [1, 12, 60, 100]
    line [1, 3, 5, 7]
```

| Approach | Time |
|---|---|
| Re-sort after every merge | `O(n² log n)` |
| Min-heap | `O(n log n)` |
| Space | `O(n)` |

---

## 5. 🍬 Candy Distribution (Bi-directional Slope Greedy)

**Problem:** Children in a line each have a rating. Everyone gets at least 1 candy, and a child with a higher rating than a neighbour must get more candies than that neighbour. Minimise total candies.

**Approach:** The constraint has a *left* part and a *right* part, and trying to satisfy both at once is messy. Satisfy them **independently**: a left-to-right pass (higher than left neighbour → left + 1), then a right-to-left pass (higher than right neighbour → take the max of the current value and right + 1).

**Worked example:** ratings `{1, 0, 2}` → candies `{2, 1, 2}` → **total 5**.

```mermaid
flowchart TD
    A["Give every child 1 candy"] --> B["Left-to-right pass"]
    B --> C["If rating > left neighbour: candy = left + 1"]
    C --> D["Right-to-left pass"]
    D --> E["If rating > right neighbour: candy = max of current and right + 1"]
    E --> F["Sum all candies"]
    style A fill:#4D96FF,color:#fff,stroke:#2c5fb8,stroke-width:2px
    style B fill:#9D4EDD,color:#fff,stroke:#6a2ca0,stroke-width:2px
    style C fill:#FF9F1C,color:#000,stroke:#c97900,stroke-width:2px
    style D fill:#F72585,color:#fff,stroke:#b81b64,stroke-width:2px
    style E fill:#00C2CB,color:#000,stroke:#008c93,stroke-width:2px
    style F fill:#06D6A0,color:#000,stroke:#049270,stroke-width:2px
```

| Metric | Complexity |
|---|---|
| Time | `O(n)` — two linear passes |
| Space | `O(n)` for the candy array (an `O(1)` slope-counting variant exists) |

---

## 6. 🔤 Reorganise String with K-Distance Apart

**Problem:** Rearrange string `S` so equal characters are at least `K` positions apart, or report impossible.

**Approach:** Count character frequencies, keep a **max-heap by remaining frequency**, and at each position place the most frequent character that is *not* on cooldown. A placed character waits in a queue for `K` positions before it may re-enter the heap. If the heap is empty while characters remain, no valid arrangement exists.

**Worked example:** `aabbcc`, `K = 3` → `abcabc`.

```mermaid
flowchart TD
    A["Count frequencies, build max-heap"] --> B["Pop most frequent available character"]
    B --> C["Append to output, decrement its count"]
    C --> D["Place in cooldown queue"]
    D --> E{"Queue length reached K?"}
    E -->|"Yes"| F["Release oldest character back into heap"]
    E -->|"No"| G{"Heap empty but characters remain?"}
    F --> G
    G -->|"Yes"| H["Impossible - return empty string"]
    G -->|"No"| B
    style A fill:#4D96FF,color:#fff,stroke:#2c5fb8,stroke-width:2px
    style B fill:#9D4EDD,color:#fff,stroke:#6a2ca0,stroke-width:2px
    style C fill:#FF9F1C,color:#000,stroke:#c97900,stroke-width:2px
    style D fill:#00C2CB,color:#000,stroke:#008c93,stroke-width:2px
    style E fill:#F72585,color:#fff,stroke:#b81b64,stroke-width:2px
    style F fill:#06D6A0,color:#000,stroke:#049270,stroke-width:2px
    style G fill:#FFD93D,color:#000,stroke:#d9ad00,stroke-width:2px
    style H fill:#FF6B6B,color:#fff,stroke:#c94242,stroke-width:2px
```

| Metric | Complexity |
|---|---|
| Time | `O(N log A)` — `N` = string length, `A` = alphabet size (effectively `O(N)` for a fixed alphabet) |
| Space | `O(A + K)` |

---

<div align="center">
<img src="https://capsule-render.vercel.app/api?type=rect&color=0:ff416c,100:ff4b2b&height=4&width=100%25" width="100%"/>
</div>

## 7. 📉 Minimise Deviation in Array

**Problem:** You may multiply an odd element by 2 or halve an even element, any number of times. Minimise `max(A) − min(A)`.

**Approach — turn a two-way problem into a one-way one:** Multiplying odds by 2 is a one-time move (the result is even and can only then be halved). So first **double every odd element** — now every element sits at its maximum possible value and the only remaining move is *halving*. Then greedily halve the current maximum (max-heap) while it is even, tracking the smallest deviation seen; stop when the maximum is odd.

**Worked example:** `{1, 2, 3, 4}` → deviation **1**.

```mermaid
flowchart TD
    A["Double every odd element"] --> B["Build max-heap, track current minimum"]
    B --> C["Record deviation = max - min"]
    C --> D{"Is the maximum even?"}
    D -->|"No"| E["Stop - return best deviation"]
    D -->|"Yes"| F["Pop max, halve it, push back, update min"]
    F --> C
    style A fill:#4D96FF,color:#fff,stroke:#2c5fb8,stroke-width:2px
    style B fill:#9D4EDD,color:#fff,stroke:#6a2ca0,stroke-width:2px
    style C fill:#FF9F1C,color:#000,stroke:#c97900,stroke-width:2px
    style D fill:#F72585,color:#fff,stroke:#b81b64,stroke-width:2px
    style E fill:#06D6A0,color:#000,stroke:#049270,stroke-width:2px
    style F fill:#00C2CB,color:#000,stroke:#008c93,stroke-width:2px
```

| Metric | Complexity |
|---|---|
| Time | `O(n log n · log M)` — each element can be halved at most `log M` times (`M` = max value), each heap operation `O(log n)` |
| Space | `O(n)` |

---

## 8. 🏢 Minimum Number of Meeting Rooms

**Problem:** Given meeting intervals `[sᵢ, eᵢ]`, find the minimum number of rooms so no two overlapping meetings share one.

**Approach:** Sort meetings by start time and keep a **min-heap of end times** (one entry per room in use). For each meeting, if the earliest-ending room is already free, reuse it; otherwise open a new room. The heap size at the end is the answer.

**Worked example:** `[0,30], [5,10], [15,20]` → **2 rooms**.

```mermaid
flowchart TD
    A["Sort meetings by start time"] --> B["For each meeting"]
    B --> C{"Earliest end time <= this start?"}
    C -->|"Yes"| D["Reuse that room - pop and push new end time"]
    C -->|"No"| E["Open a new room - push end time"]
    D --> F{"More meetings?"}
    E --> F
    F -->|"Yes"| B
    F -->|"No"| G["Answer = heap size"]
    style A fill:#4D96FF,color:#fff,stroke:#2c5fb8,stroke-width:2px
    style B fill:#9D4EDD,color:#fff,stroke:#6a2ca0,stroke-width:2px
    style C fill:#F72585,color:#fff,stroke:#b81b64,stroke-width:2px
    style D fill:#06D6A0,color:#000,stroke:#049270,stroke-width:2px
    style E fill:#FF9F1C,color:#000,stroke:#c97900,stroke-width:2px
    style F fill:#00C2CB,color:#000,stroke:#008c93,stroke-width:2px
    style G fill:#FFD93D,color:#000,stroke:#d9ad00,stroke-width:2px
```

| Approach | Time | Space |
|---|---|---|
| Sort + min-heap of end times | `O(n log n)` | `O(n)` |
| Sort starts and ends separately, two pointers | `O(n log n)` | `O(n)` |
| Check every pair for overlap (naive) | `O(n²)` | `O(1)` |

> 🔁 Same sweep idea as the party-attendance and interval-overlap problems from earlier labs — the minimum rooms equals the **maximum number of simultaneously active meetings**.

---

## 9. 🔗 Hu-Tucker Greedy Simulation

**Problem:** Given weights `w₁ … wₙ` in a fixed order, build an optimal **alphabetic** binary tree — leaves must stay in the original left-to-right order — minimising `Σ wᵢ · depth(i)`.

**Why it is harder than Huffman:** Huffman may merge *any* two smallest nodes. Here, merging two nodes with another leaf stuck between them would break the in-order sequence. Hu-Tucker handles this by merging the cheapest **compatible pair** (no leaf between them), then rebuilding the tree in the correct order.

```mermaid
flowchart TD
    A["Weights in fixed order"] --> B["Phase 1: repeatedly merge the cheapest compatible pair"]
    B --> C["Record the level of each original leaf"]
    C --> D["Phase 2: rebuild a tree with those leaf levels"]
    D --> E["Leaves keep original order, cost is minimal"]
    style A fill:#4D96FF,color:#fff,stroke:#2c5fb8,stroke-width:2px
    style B fill:#9D4EDD,color:#fff,stroke:#6a2ca0,stroke-width:2px
    style C fill:#FF9F1C,color:#000,stroke:#c97900,stroke-width:2px
    style D fill:#00C2CB,color:#000,stroke:#008c93,stroke-width:2px
    style E fill:#06D6A0,color:#000,stroke:#049270,stroke-width:2px
```

| Implementation | Time |
|---|---|
| Straightforward simulation (scan for the best compatible pair each round) | `O(n²)` |
| Full Hu-Tucker with an efficient data structure | `O(n log n)` |
| Space | `O(n)` |

---

<div align="center">
<img src="https://capsule-render.vercel.app/api?type=rect&color=0:ff4b2b,100:ff416c&height=4&width=100%25" width="100%"/>
</div>

## 10. 🧵 Greedy Superstring Conjecture (Open Problem)

**Problem:** Given `n` strings, find the **shortest string containing every one of them as a substring**. This is NP-hard, so the classic approach is a *greedy heuristic*: repeatedly merge the pair of strings with the **maximum overlap**.

```mermaid
flowchart TD
    A["Set of strings S"] --> B["Find the pair with maximum overlap"]
    B --> C["Merge them into one string"]
    C --> D{"One string left?"}
    D -->|"No"| B
    D -->|"Yes"| E["Greedy superstring"]
    style A fill:#4D96FF,color:#fff,stroke:#2c5fb8,stroke-width:2px
    style B fill:#9D4EDD,color:#fff,stroke:#6a2ca0,stroke-width:2px
    style C fill:#FF9F1C,color:#000,stroke:#c97900,stroke-width:2px
    style D fill:#F72585,color:#fff,stroke:#b81b64,stroke-width:2px
    style E fill:#06D6A0,color:#000,stroke:#049270,stroke-width:2px
```

### 📜 Status of the conjecture (as described in the lab sheet)

| Item | Detail |
|---|---|
| **Conjecture** | Greedy always returns a superstring at most **2×** the optimal length (a 2-approximation) |
| **Age** | Formulated nearly four decades ago |
| **Reported September 2026 result** | An arXiv paper, *"Disproving the Greedy Superstring Conjecture"*, reports that for inputs with even string length `k ≥ 10` the ratio is at least `(9k + 2) / (4k + 4)`, approaching `9/4 = 2.25` as `k → ∞` |
| **Validation status** | ⚠️ **Not yet officially validated**, per the lab sheet |
| **Note** | The counterexample was reportedly found with AI assistance |

The reported lower bound, plotted against the conjectured ratio of 2:

```mermaid
%%{init: {"themeVariables": {"xyChart": {"plotColorPalette": "#FF416C, #4D96FF"}}}}%%
xychart-beta
    title "Q10: Reported Ratio (9k+2)/(4k+4) vs Conjectured Bound of 2"
    x-axis ["k=10", "k=20", "k=50", "k=100", "k=1000"]
    y-axis "Approximation Ratio" 1.9 --> 2.3
    line [2.0909, 2.1667, 2.2157, 2.2327, 2.2483]
    line [2, 2, 2, 2, 2]
```

> 📈 Upper curve: the reported lower bound on greedy's ratio. Lower line: the conjectured bound of 2. If the result holds up, the curve sitting **above** the line is exactly what "disproved" means — but this is a very recent claim, so treat it as *reported*, not settled.

| Metric | Status |
|---|---|
| Exact shortest superstring | NP-hard |
| Greedy heuristic | Polynomial — the pairwise-overlap computation dominates (roughly quadratic in the number of strings, times string length) |
| Approximation guarantee of greedy | ❓ **Open** — the 2-approximation conjecture is under challenge |

---

## 📊 Complexity Landscape — Problems 1 to 9

```mermaid
%%{init: {"themeVariables": {"xyChart": {"plotColorPalette": "#4D96FF, #9D4EDD, #06D6A0, #FF9F1C, #F72585, #00C2CB, #FFD93D, #FF6B6B, #FF416C"}}}}%%
xychart-beta
    title "Relative Growth Order Snapshot (Problems 1-9)"
    x-axis ["Q1 FracKnap", "Q2 Huffman", "Q3 Fuel", "Q4 Sticks", "Q5 Candy", "Q6 Reorg", "Q7 Deviation", "Q8 Rooms", "Q9 Hu-Tucker"]
    y-axis "Relative Growth Order" 0 --> 4
    bar [2, 2, 2, 2, 1, 2, 3, 2, 2]
```

| Problem | Technique | Complexity |
|---|---|---|
| 1️⃣ Fractional Knapsack (decay) | Best current density | 🟡 `O(n log n)` – `O(n²)` |
| 2️⃣ Huffman | Min-heap merge | 🟡 `O(n log n)` |
| 3️⃣ Refuelling stops | Max-heap, retroactive choice | 🟡 `O(n log n)` |
| 4️⃣ Connect sticks | Min-heap merge | 🟡 `O(n log n)` |
| 5️⃣ Candy | Two linear passes | 🟢 `O(n)` |
| 6️⃣ Reorganise string | Max-heap + cooldown | 🟡 `O(N log A)` |
| 7️⃣ Minimise deviation | Max-heap, halving | 🟠 `O(n log n · log M)` |
| 8️⃣ Meeting rooms | Sort + min-heap | 🟡 `O(n log n)` |
| 9️⃣ Hu-Tucker | Compatible-pair merge | 🟡 `O(n log n)` – `O(n²)` |

<sub>Problem 10 is omitted from the chart: it has no single running time to compare — the exact problem is NP-hard and the open question is about approximation quality, not speed.</sub>

---

## 🛠️ Tech Stack

<div align="center">
<img src="https://skillicons.dev/icons?i=c,git,github,vscode,linux" />
</div>

<div align="center">

![C](https://img.shields.io/badge/Standard-C99-00599C?style=flat-square&logo=c)
![Compiler](https://img.shields.io/badge/Compiler-GCC-A42E2B?style=flat-square&logo=gnu)
![Focus](https://img.shields.io/badge/Focus-Greedy_Algorithms-FF416C?style=flat-square)

</div>

---

## ✅ Key Takeaways

- 🧮 **Heaps are the greedy workhorse.** Seven of the ten problems (Q2, Q3, Q4, Q6, Q7, Q8, Q9) reduce to "repeatedly grab the best available element" — exactly what a priority queue provides in `O(log n)`.
- 🪢 **Huffman, connect-sticks and Hu-Tucker are one family.** All merge items bottom-up; the only difference is *which* pairs are allowed to merge (any two, any two, or only compatible neighbours).
- ⏪ **Greedy can decide *later*.** The refuelling problem never commits to a stop in advance — it keeps the options in a heap and picks retroactively only when forced. Delaying the decision is what makes the greedy choice safe.
- ↔️ **Two simple passes beat one clever one.** Candy distribution splits a two-sided constraint into two one-sided passes, each trivially correct.
- 🔀 **Reformulate before you optimise.** Minimise-deviation becomes easy only after doubling every odd number turns a two-way operation into a one-way one.
- 🧵 **Greedy is not always provably good.** The superstring conjecture is the cautionary tale: a heuristic believed to be within 2× of optimal for decades is now reportedly challenged — a reminder that "works on every example" is not a proof.

---

## 🗂️ Repository Structure

```
Lab-09/
│
├── 📁 outputs/
│   └── 🖼️ Screenshot 20….png   # Output screenshots, one per program
│
├── 🇨 prog1.c              # Q1  · Fractional Knapsack with Deterioration
├── 🇨 prog2.c              # Q2  · Huffman Coding (canonical)          → O(n log n)
├── 🇨 prog3.c              # Q3  · Minimum Refuelling Stops            → O(n log n)
├── 🇨 prog4.c              # Q4  · Connect Sticks                      → O(n log n)
├── 🇨 prog5.c              # Q5  · Candy Distribution                  → O(n)
├── 🇨 prog6.c              # Q6  · Reorganise String, K Apart          → O(N log A)
├── 🇨 prog7.c              # Q7  · Minimise Deviation                  → O(n log n · log M)
├── 🇨 prog8.c              # Q8  · Minimum Meeting Rooms               → O(n log n)
├── 🇨 prog9.c              # Q9  · Hu-Tucker Simulation
├── 🇨 prog10.c             # Q10 · Greedy Superstring
└── 📘 README.md            # You are here
```

| Program File | Problem Solved |
|---|---|
| `prog1.c` | Fractional Knapsack with Deterioration Rate |
| `prog2.c` | Huffman Coding (Canonical Codebook) |
| `prog3.c` | Minimum Initial Fuel (Reverse Greedy) |
| `prog4.c` | Minimum Cost to Connect Sticks |
| `prog5.c` | Candy Distribution Problem |
| `prog6.c` | Reorganise String with K-Distance Apart |
| `prog7.c` | Minimise Deviation in Array |
| `prog8.c` | Minimum Number of Meeting Rooms |
| `prog9.c` | Hu-Tucker Greedy Simulation |
| `prog10.c` | Greedy Superstring Conjecture |

### ⚡ Build & Run

```bash
# Compile any program (example: prog1.c)
gcc prog1.c -o prog1

# Run it
./prog1        # Linux / macOS
prog1.exe      # Windows
```

> Repeat for `prog2.c` → `prog10.c`. Programs that use a heap (`prog2`–`prog4`, `prog6`–`prog9`) implement their own priority queue in C, since the standard library has none.

---

<div align="center">

<img src="https://capsule-render.vercel.app/api?type=waving&color=0:ff4b2b,100:ff416c&height=120&section=footer" width="100%"/>

**Made with 🧠 + ☕ for DAA Lab-09 · IIIT Bhubaneswar**

</div>