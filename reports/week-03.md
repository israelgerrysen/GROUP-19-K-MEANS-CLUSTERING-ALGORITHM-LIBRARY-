# Project Report: Object-Oriented K-Means Cluster Evaluator

## Overview & Class Structure

This project implements a C++ tool for evaluating K-Means clustering using the **Inertia (Within-Cluster Sum of Squares)** metric. The program is organized using Object-Oriented Programming (OOP) principles to structure data points, evaluation metrics, and cluster managers.

---

## Core Classes & Implementation Details

### Base Evaluator Class (`ClusterEvaluator`)
* **What class was created?** `ClusterEvaluator` (Abstract Base Class).
* **Why?** To define a common interface for all clustering evaluation metrics, enabling **polymorphism**.
* **Data Members:** None (pure interface).
* **Member Functions:**
  * `public: virtual double evaluate(...) = 0` — Pure virtual function to evaluate cluster quality.
  * `public: virtual ~ClusterEvaluator() = default` — Virtual destructor for safe cleanup.

### Derived Class (`InertiaEvaluator`)
* **What class was created?** `InertiaEvaluator` (Inherits from `ClusterEvaluator`).
* **Why?** To implement the specific math for calculating Within-Cluster Sum of Squares (Inertia).
* **Data Members:**
  * `private: bool useSquaredDistance` — Flag to control distance calculation mode.
* **Member Functions:**
  * `public: double evaluate(points, labels, centroids)` — Overridden method executing the inertia calculation loop.
  * `private: double calculateSquaredDistance(p1, p2)` — Helper function for distance math.

### Data Container (`Point` & `ClusterData`)
* **What class was created?** `Point` struct / class.
* **Why?** To represent geometric coordinates in feature space.
* **Data Members:**
  * `public: double x, y` — Coordinates of the data point.
* **Member Functions:**
  * `public: Point(double x, double y)` — Constructor.

---

## OOP Principles Implementation

### Encapsulation
* **How it is used:** Internal mathematical logic (e.g., `calculateSquaredDistance`) and configuration flags (`useSquaredDistance`) are kept `private`.
* **Why:** External caller code only needs the public interface (`evaluate()`). Hiding implementation details prevents accidental state modification and simplifies client code interaction.

### Inheritance
* **How it is used:** `InertiaEvaluator` inherits publicly from `ClusterEvaluator` (`class InertiaEvaluator : public ClusterEvaluator`).
* **Why:** Establishes an "is-a" relationship, allowing future metrics (e.g., `SilhouetteEvaluator`, `DaviesBouldinEvaluator`) to derive from the same base class without breaking downstream code.

### Polymorphism
* **How it is used:** Main functions take a pointer or reference to the base class (`ClusterEvaluator* evaluator`).
* **Why:** Allows dynamically swapping different evaluation metrics at runtime using a unified interface (`evaluator->evaluate(...)`), keeping the code extensible.

---

## Deconstruction & Program Flow

1. **Instantiation:** The program creates data collections (`Point` vectors) representing dataset clusters and computed centroids.
2. **Execution:** The application passes datasets to a `ClusterEvaluator*` instance pointed at `InertiaEvaluator`.
3. **Calculation:** The evaluator iterates through each assigned point, computes the distance to its assigned centroid, aggregates the sum of squares, and returns a scalar score.
4. **Interpretation:** Lower returned values indicate tighter, higher-quality cluster assignments.
