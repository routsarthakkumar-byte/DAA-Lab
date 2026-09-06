<div align="center">

# DAA Laboratory · Lab 06

**Eight implementations. One coherent analysis story.**

![Language](https://img.shields.io/badge/Language-C99-00599C?logo=c&logoColor=white)
![Questions](https://img.shields.io/badge/Questions-8-7c3aed)
![Topics](https://img.shields.io/badge/Topics-D%26C%20%2B%20DP-0ea5e9)
![Outputs](https://img.shields.io/badge/PNG%20runs-8-16a085)

[← Main README](../README.md) · [Programs](#laboratory-dashboard) · [Outputs](#sample-output-gallery) · [Build](#build-everything)

</div>

---

## Source map

Two supplied documents define this lab. Their questions are deliberately kept in order rather than blended together.

| Source | Questions | Content |
| --- | --- | --- |
| Complexity-analysis PDF | Q1-Q4 | 1D arrays, square matrices, FFT convolution, reversal-only sorting |
| Dynamic Programming brief | Q5-Q8 | Fibonacci, 0/1 Knapsack, LCS, Matrix Chain Multiplication |

## Laboratory dashboard

| Q | Required task | Submitted program | Final bound | Evidence |
| :---: | --- | --- | --- | --- |
| 1 | Nine operations on an unsorted array | [`prog1.c`](prog1.c) | `O(n)` to `O(n log n)` | [sample run](Outputs/output-01.png) |
| 2 | Seven square-matrix operations | [`prog2.c`](prog2.c) | `O(n^2)` to `O(n^3)` | [sample run](Outputs/output-02.png) |
| 3 | Convolution in `O(n log n)` | [`prog3.c`](prog3.c) | `O(N log N)` | [sample run](Outputs/output-03.png) |
| 4 | Sort with reversals only | [`prog4.c`](prog4.c) | `O(n log^2 n)` weighted cost | [sample run](Outputs/output-04.png) |
| 5 | nth Fibonacci through DP | [`prog5.c`](prog5.c) | `O(n)` time, `O(n)` table | [sample run](Outputs/output-05.png) |
| 6 | 0/1 Knapsack + chosen items | [`prog6.c`](prog6.c) | `O(nW)` | [sample run](Outputs/output-06.png) |
| 7 | LCS length + subsequence | [`prog7.c`](prog7.c) | `O(mn)` | [sample run](Outputs/output-07.png) |
| 8 | Minimum Matrix Chain cost | [`prog8.c`](prog8.c) | `O(n^3)` | [sample run](Outputs/output-08.png) |

## Algorithm stories

### Q1-Q4 · From direct work to divide-and-conquer

- **Array workbench:** Linear scans solve maximum, mean, standard deviation, reversal, and pivot partitioning. Sorting-based median, mode, and duplicate removal form the `O(n log n)` ceiling.
- **Matrix kernels:** Element-wise operations are quadratic; multiplication and Gaussian-elimination determinant calculation are cubic.
- **FFT convolution:** Zero-pad, transform, multiply pointwise, and invert. This replaces pairwise work with `O(N log N)` butterfly stages.
- **Reversal sorting:** Direct placement needs at most `n-1` reversals. A recursive rotate-merge implementation bounds reversal length cost by `O(n log^2 n)`.

### Q5-Q8 · Dynamic Programming toolkit

| Program | State | Transition | Result reconstructed |
| --- | --- | --- | --- |
| Fibonacci | `F[i]` | `F[i-1] + F[i-2]` | `F(n)` |
| Knapsack | `K[i][w]` | skip or take item `i` | selected item set |
| LCS | `L[i][j]` | match diagonal / best prefix | an actual common subsequence |
| Matrix Chain | `M[i][j]` | choose final split `k` | optimal parenthesization |

```text
Optimal substructure
├── smaller Fibonacci states form the next state
├── smaller capacities decide each Knapsack cell
├── shorter prefix pairs decide LCS cells
└── shorter matrix intervals decide every chain split
```

## Sample-output gallery

Each image below is a captured interactive program run, not a mockup. The dedicated [`Outputs/`](Outputs) folder keeps all eight PNG files together for submission.

| Q1 | Q2 | Q3 | Q4 |
| --- | --- | --- | --- |
| [Open PNG](Outputs/output-01.png) | [Open PNG](Outputs/output-02.png) | [Open PNG](Outputs/output-03.png) | [Open PNG](Outputs/output-04.png) |

| Q5 | Q6 | Q7 | Q8 |
| --- | --- | --- | --- |
| [Open PNG](Outputs/output-05.png) | [Open PNG](Outputs/output-06.png) | [Open PNG](Outputs/output-07.png) | [Open PNG](Outputs/output-08.png) |

## Build everything

```bash
# Q1-Q3 use the math library
gcc -std=c99 -Wall -Wextra -O2 prog1.c -o prog1 -lm
gcc -std=c99 -Wall -Wextra -O2 prog2.c -o prog2 -lm
gcc -std=c99 -Wall -Wextra -O2 prog3.c -o prog3 -lm

gcc -std=c99 -Wall -Wextra -O2 prog4.c -o prog4
gcc -std=c99 -Wall -Wextra -O2 prog5.c -o prog5
gcc -std=c99 -Wall -Wextra -O2 prog6.c -o prog6
gcc -std=c99 -Wall -Wextra -O2 prog7.c -o prog7
gcc -std=c99 -Wall -Wextra -O2 prog8.c -o prog8
```

## Final complexity map

| Growth | Lab 06 examples | Why it appears |
| --- | --- | --- |
| `O(n)` | array scans, Fibonacci | one pass / one transition per state |
| `O(n log n)` | sorted array tasks, FFT | divide-and-merge levels |
| `O(n^2)` | matrix surfaces, LCS | every cell or prefix pair matters |
| `O(nW)` | 0/1 Knapsack | item-capacity state grid |
| `O(n^3)` | matrix multiplication, determinant, Matrix Chain | three indices or a split choice |
| `O(n log^2 n)` | reversal-cost sort | reversal merge work across recursive levels |

---

<div align="center"><sub>Interactive C99 implementations · complexity explained beside the result · eight documented sample runs</sub></div>
