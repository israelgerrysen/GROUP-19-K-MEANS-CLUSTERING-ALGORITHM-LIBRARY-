# BUSULWA GERRYSON ISRAEL 25/U/0826 BELE

# Week 3 Report: Centroid Initialization

This report explains inheritance, polymorphism and encapsulation in my `CentroidInitializer` class. The class layout drawing is in the attached photo.

## 1. Class Layout


| Part | Name | Access |
|---|---|---|
| Member data | `k_`, `gen_` | private |
| Member functions | two constructors, `getK()`, `setK()`, `initialize()` | public |
| Type names | `Point`, `Dataset` | public |
| Protected members | none | - |

## 2. Encapsulation
Encapsulation means keeping data and the functions that use it together in one class, and hiding the data from outside code.

In my class:
- The data (`k_` and `gen_`) is **private**. Other code cannot read or change it directly.
- Other code can only use the **public** functions.
- `getK()` lets other code read `k_`, and `setK()` lets it change `k_`.
- `initialize()` uses `gen_` internally, so the outside code never touches the random number generator.

This protects the data. For example, `k_` can only be changed through `setK()`, and `initialize()` checks that `k` is valid before it does any work. If the inside of the class changes later, the rest of the program does not need to change.

## 3. Inheritance
Inheritance means one class takes the members of another class (a base class).

`CentroidInitializer` does **not** use inheritance. It is a stand-alone class with no base class and no child classes. I did not need it, because the class has one simple job: pick the starting centroids. So there is no inheritance arrow in my drawing.

This is also why there are no `protected` members. `protected` is only useful when a child class needs to use its parent's data, and my class has no child classes.

## 4. Polymorphism
Polymorphism means the same name can do different things.

`CentroidInitializer` does not use virtual functions, so it has no runtime polymorphism. It does use **constructor overloading**, which is a type of polymorphism decided when the code is compiled. The class has two constructors with the same name but different parameters:
- `CentroidInitializer(int k)` uses a random seed, so the results are different every time.
- `CentroidInitializer(int k, unsigned int seed)` uses a fixed seed, so the results can be repeated (useful for testing).

The compiler picks the correct constructor depending on the arguments we give.

## 5. Summary

| Concept | Used in my class? | Where |
|---|---|---|
| Encapsulation | Yes | private `k_` and `gen_`, public functions |
| Inheritance | No | The class is stand-alone |
| Polymorphism | Yes (overloading only) | Two constructors |
