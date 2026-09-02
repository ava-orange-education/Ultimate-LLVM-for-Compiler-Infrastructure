# Ultimate-LLVM-for-Compiler-Infrastructure
Ultimate LLVM for Compiler Infrastructure, published by Orange, AVA™

## Repository layout

Code and diagrams for each chapter live in `chNN/`, matching the `chNN/listing-N-M.ext`
paths printed in every listing caption in the book — so a path in the book is the exact
path in this repo, nothing to translate.

| Folder | Chapter |
|---|---|
| `ch01` | Introduction to LLVM |
| `ch02` | LLVM Build and Installation |
| `ch03` | LLVM Frontend — Clang |
| `ch04` | Clang's LibTooling |
| `ch05` | LLVM IR |
| `ch06` | LLVM Assembly Language |
| `ch07` | Optimizer |
| `ch08` | Analysis Passes |
| `ch09` | Transformation Passes |
| `ch10` | Creating an LLVM Pass (Analysis and Transformation) |
| `ch11` | LLVM JIT and Interpreter |
| `ch12` | LLVM Code Generation |
| `ch13` | Multi-Level Intermediate Representation (MLIR) |
| `ch14` | The Awesome LLVM |
| `ch15` | Essential Tools, Best Practices, and Notable Projects |

Each `chNN/` folder holds that chapter's listing files (`listing-N-M.ext`) plus any
supporting headers/sources a listing depends on. Where a chapter has figures, they're
under `chNN/diagrams/` as `Figure_N.M.png`.

`ch14` has no listings (it's a narrative chapter) and so has only a `diagrams/` folder.
