# Genetic Algorithm Toolbox & CVRP Solver

## 📌 Project Overview
This repository contains **Assignment 1** for the Soft Computing course. The project is divided into two main parts:
1. **Part 1 (GA Toolbox):** A highly modular, object-oriented Genetic Algorithm toolbox built from scratch in C++ (without using external GA libraries).
2. **Part 2 (CVRP):** An application of the toolbox to solve the Capacitated Vehicle Routing Problem (CVRP) to find high-quality, feasible routes.

## 🏗️ Architecture & Design
The toolbox is designed using modern C++ (C++17) and implements several standard software design patterns:
* **Strategy Pattern:** Selection, Crossover, Mutation, and Replacement algorithms are decoupled from the main GA loop. They are defined as abstract base classes, allowing the user to mix and match them at runtime.
* **Builder Pattern:** The `GeneticAlgorithmBuilder` allows the user to cleanly configure hyperparameters, inject problem-specific fitness/feasibility functions, and select specific operators before building the final `GeneticAlgorithmToolbox`.
* **Dependency Injection:** The GA doesn't know about the specific optimization problem. The user provides `std::function` callbacks for fitness evaluation and feasibility checking.
* **Polymorphism & Smart Pointers:** Chromosomes are handled via `std::unique_ptr<Chromosome>`, ensuring strict memory management and allowing the toolbox to handle Binary, Integer, and Floating-point representations seamlessly.

### UML Class Diagram
![UML Diagram](https://www.plantuml.com/plantuml/svg/xPPTRzis5yVl_Ic85kWZjxPXfq_N5tX6aomkSj7DQ3hiOXWAMZgMYLAaHXx5oR9-zucY9DAKL6VtIm33vlcHEkT_NiJt6gd28kCZ3ZiaA8bYwHv9mXJ4oAGOwQzCv5JHZ70c0Ezp85BXNde6lQU9F32HaXtb6ZnBpAdMvuYARGk4wrYA6_ONaBc729c0XfoSdNcBYeglPl7DF3oCF8m8kP0g0NKfkLJawV-hltBrN2bvE5xyDjgp10XaETwJ3B8jA3qQ_OzCspzoKJ1U7aQeICXdAVbMtddcaNte1n20B3xdgLGCzrcpwUdLJrUlrpzKJatBw7Oi9U_8X_FBwgjPrC2ja6PlQIi4-xE0BpcgvKrZMbMxbTHQteBgWfUDgGAp0cd_WHzhIuKfo3cD8GE1NVAJCrRmZg40hTUYn7Q5gBnQ9hBOSeZAi3IIoxsIcTGoWsTZkmMePbl66TuVRzjAoOSsCS6GKRwHUS6DgsQZ-s68QVdnGWDQ1QFOatDSVg-5VrPJhOGHBMFi0LhfXe16io6xfzGGigx5gmM8Tg8FSd9z7xmE9OfocOVSrdoFniT93OkqhkPLsGL16GV4lopZ_yeu7wvV9Onq6IxUldtvkYdewPwAXCEri4yptfIGVspvyrQonEHM5IBCh2EhP0vDezbiDPZYTsIvZ1LG1BrQ1IFGfhbGDg9m-BLrK9wWKHKnhbPbnRovEgyhvaKhXvtkxmWJI7uaY_dSM3DwPvoof-lM-ifQsthPABcbDX4bOvDMOlFP6uCrrJ98pHT66JyiBp5ck7jowqwCFkk7DcKYORSiAIZN9aKGerJB_ioisl55a-IwtHULH_ZfZJbG5VahkXIjMZ1Vlg1PIW4lGACxnTYz29vRo0Eq8Kuu-Cn8HBSQ5OsHsC2T_IZmftKhjIAtmJqq1tmZQJlxeh4F-enspAvbNFJXUJSTBNmWvbB0zveZUFQ1vgRqT2Hn3-guvIQaklfC2BZyk4bvmGHLzxuuwrVctrP5QWvrSfjHuR8VRerCA1EYH3hkDLU7ZUk46dSZPlmnXvf5tInEo6szxCktuootzcuGrm8X1VN8A5WzHBUo48ctdbDM6IS6S67wX_jnPaoK7_JEHkoJGSWExGRF18QnsrKNkcsIobUxvyXF9yAQIugFbC1Mvx0ArZwfCQT5y8mX9KBkj0xsIQ4KhU646e6_dG5vWueYfEnu80O3mhxUxM2Shy_M2_8Gjbb5c6lAqTkmx31HP1kgGA1kEzgAuNJrPffnq3xpaomu8C9lUm3kEM1JLqEVPQ44DUz-Z_2JYmxmNqilUwPWUpKP339kY2XVb4TrBWOJaf_rhzjuJKA61lDaO9mvGJuM7Db6Ck4kj84QlwW4LDSO1jhShGRZp0pGkPzCI5me1SBKe1MoAbZtoqJf1b0xH77DMTuyC_3uLy5sKcLLJmmWFqiHKjqqRpTKqSo_3IncyzQ7cmFjEX2gujqZ1uLHbebg8JRTQfUxdSuL4-df5t57AdT3ejpp9j3ZYZDa6dk0eBERMryiirng5jxhXYw9pykjJnPFtCt_5EZYFuMwENAATCruacmIUnBq57li9T7Noq7snFbizlo9nuwyRSk_Io9yoOT0zzKS4k5xgtzqtnCczg0OKX4VUTogRG_h7wW1rJTHHsqoBD8pY08ac4IZ9aVM68o4m1esUnS9Hy80vNVzo4k-jGuqMnVizbkGXa_oGAI9budKbxzf83BzVS-I1CGVYJo8AUcHFaHwT0sHJj0XC11KWFdT-nv4KcJy7m00)

## 📂 Project Structure
```text
GeneticAlgorithmToolbox/
│
├── include/                    # Header files (.h)
│   ├── core/                   # GAConfig, Chromosome (Binary, Int, Float), Population
│   ├── algorithms/             # Abstract & Concrete Selection, Crossover, Mutation, Replacement
│   ├── builder/                # The GeneticAlgorithmBuilder
│   └── toolbox/                # The main GeneticAlgorithmToolbox (GA Loop)
│
├── src/                        # Implementation files (.cpp)
│   └── ...                     # Mirrors the include/ structure
│
├── problem_cvrp/               # Part 2: Problem-specific logic
│   ├── CVRP.h / .cpp           # CVRP model, capacity constraints, and decoding logic
│   └── run_cvrp.cpp            # Entry point for the CVRP solver
│
├── main.cpp                    # Entry point for testing the Toolbox
└── README.md
```

## ⚙️ Toolbox Features Implemented

### Chromosome Representations
The toolbox supports three distinct genotype representations:
1. **BinaryChromosome:** Standard bit-strings (0 or 1).
2. **IntegerChromosome:** Permutations or integer values bounded within `[LB, UB]`. (Used for CVRP).
3. **FloatChromosome:** Double-precision floating-point values bounded within `[LB, UB]`. (Used for smooth curve fitting).

### Genetic Operators
**Selection:**
* Roulette Wheel Selection
* Tournament Selection

**Crossover:**
* Multi-point Crossover
* Order Crossover (OX) - *designed for permutations to avoid duplicate genes.*

**Mutation:**
* Bit-Flip Mutation (Binary)
* Uniform Mutation (Floating Point - Lab 2)
* Non-Uniform Mutation (Floating Point - Lab 2)
* Swap Mutation (Integer/Permutation safe)

**Replacement:**
* Generational Replacement
* Elitist Replacement (Preserves the best chromosomes)

## 🛠️ Usage Example: Wiring the Builder & Toolbox

This project uses the **Builder Pattern** to make configuring the Genetic Algorithm incredibly clean. You don't need to memorize complex constructor arguments. You simply chain the configurations and inject your problem-specific functions.

Here is an example of how to solve a simple mathematical optimization problem (maximizing \(f(x) = x^2\)) using the toolbox:

```cpp
#include "builder/GeneticAlgorithmBuilder.h"
#include "core/Chromosome.h"
#include <iostream>
#include <random>

int main() {
    // 1. Configure the GA Hyperparameters
    GAConfig config;
    config.populationSize = 50;
    config.maxGenerations = 100;
    config.crossoverProbability = 0.8;
    config.mutationProbability = 0.1;

    // 2. Create the Initial Population (Float Chromosomes)
    std::mt19937 rng(std::random_device{}());
    Population initialPop;
    for (int i = 0; i < config.populationSize; ++i) {
        // Chromosome of size 1, bounds between [-100, 100]
        initialPop.addIndividual(std::make_unique<FloatChromosome>(1, -100.0, 100.0, rng));
    }

    // 3. Build and Configure the Toolbox using the Builder
    GeneticAlgorithmBuilder builder;
    auto toolbox = builder
        .setConfig(config)
        .setInitialPopulation(std::move(initialPop))
        
        // Choose the algorithms (Strategy Pattern)
        .setSelection(std::make_unique<TournamentSelection>(3))
        .setCrossover(std::make_unique<MultiPointCrossover>())
        .setMutation(std::make_unique<UniformFloatMutation>())
        .setReplacement(std::make_unique<ElitistReplacement>())
        
        // Inject the Problem-Specific Logic (Dependency Injection)
        .setFitnessFunction([](const Chromosome& c) {
            // Objective: Maximize x^2
            auto& floatChromo = dynamic_cast<const FloatChromosome&>(c);
            double x = floatChromo.getGene(0);
            return x * x; // Fitness = x^2
        })
        .setFeasibilityFunction([](const Chromosome& c) {
            // This simple problem has no constraints, so everything is feasible
            return true; 
        })
        .build(); // Finalize and create the Toolbox

    // 4. Run the GA
    std::cout << "Running Genetic Algorithm..." << std::endl;
    auto bestSolution = toolbox->run();

    // 5. Output the result
    auto& bestFloat = dynamic_cast<FloatChromosome&>(*bestSolution);
    std::cout << "Best x found: " << bestFloat.getGene(0) << std::endl;
    std::cout << "Best Fitness (x^2): " << bestSolution->getFitness() << std::endl;

    return 0;
}
```

## 🚀 How to Run (VS Code)

### Prerequisites
Ensure you have the C/C++ toolchain installed (MinGW-w64/MSYS2) and that `g++` and `gdb` are added to your system's `PATH` variable. You will also need the **C/C++ extension** by Microsoft installed in VS Code.

### 1. Building the Project
The project uses a `tasks.json` file to compile all the source files using `g++`.
1. Open the project folder in VS Code.
2. Press `Ctrl + Shift + B` (or go to **Terminal -> Run Build Task**).
3. The compiler will read `tasks.json`, compile all files in `src/`, and generate the executable `build/main.exe`.

### 2. Running and Debugging
The project is configured to run and debug via `launch.json`.
1. Open the file you want to run (e.g., `main.cpp` or `problem_cvrp/run_cvrp.cpp`).
2. Set a breakpoint if desired by clicking to the left of the line number.
3. Press `F5` (or go to **Run -> Start Debugging**).
4. VS Code will compile the code (if not already built) and launch the executable in the integrated terminal/debugger.

> **Important Note**: If you add new `.cpp` files to the project later, you must explicitly add them to the `"args"` list in `.vscode/tasks.json` so the compiler knows to include them in the build!

## 🚚 Part 2: CVRP Implementation Details
*   **Representation:** The CVRP is modeled using an `IntegerChromosome` where the genes represent a permutation of customer IDs.
*   **Decoding:** A problem-specific decoder is used to split the integer permutation into vehicle routes. A new vehicle is dispatched whenever the next customer's demand exceeds the current vehicle's remaining capacity.
*   **Fitness Evaluation:** The fitness is the inverse of the total routing distance. 
*   **Feasibility:** The decoder ensures capacity constraints are generally met, while a `feasibilityFn` acts as a safety net to penalize any rare infeasible solutions (e.g., exceeding total fleet capacity).

## 🧠 Design Justifications
* **Why `std::unique_ptr`?** Used to manage chromosome ownership without the risk of memory leaks. When a population is destroyed, all chromosomes are cleanly deleted. It also explicitly models ownership transfer during `clone()`.
* **Why a Builder?** A GA has many hyperparameters and algorithm combinations. The builder prevents constructor "bloat" and makes the code highly readable and configurable.
* **Why runtime polymorphism for Chromosomes?** Using a template base class would force the population to be homogeneous at compile time. Using an abstract `Chromosome` base class allows the toolbox to evolve a population of any representation dynamically.
