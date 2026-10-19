# SEBBOWA MASAMBILA ABRAHAM 25/U/04087/PS


# Week 3 Report: Distance Calculation

This report explains inheritance, polymorphism and encapsulation in my `DistanceCalculator` class. The class layout drawing is in the attached photo.

## 1. Class Layout



| Part | Name | Access |
|---|---|---|
| Member data | none | - |
| Member functions | `distance()` (static), `squareddistance()` (static), deleted constructor | public |
| Type name | `Point` | public |
| Private members | none | - |
| Protected members | none | - |

## 2. Encapsulation
Encapsulation means keeping a class's data and functions together and controlling how other code can use them.

`DistanceCalculator` is a utility class. It has **no member data**, so there is no private data to hide. Encapsulation is used in these ways:
- The maths is hidden inside the functions. Other code gives two points and gets back a number, without seeing how it is calculated.
- The constructor is deleted (`DistanceCalculator() = delete`), so nobody can create an object by mistake. The class can only be used through its static functions.
- The points are passed as `const` references, so the functions cannot change the caller's data.
- Both functions check their input and throw `std::invalid_argument` if the points have different dimensions, so wrong data cannot give a wrong answer quietly.

Encapsulation here is weaker than in a class with private data, such as `CentroidInitializer`, because this class does not need to store anything.

## 3. Inheritance
Inheritance means one class takes the members of another class (a base class).

`DistanceCalculator` does **not** use inheritance. It has no base class and no child classes, because it has one simple job: measure the distance between two points. So there is no inheritance arrow in my drawing, and no `protected` members either, because `protected` is only useful when a child class needs to use its parent's data.

## 4. Polymorphism
Polymorphism means the same name can do different things.

`DistanceCalculator` does **not** use polymorphism. It has no virtual functions and no overloaded functions. It has two functions with two different names, and each one always does the same thing:
- `distance()` returns the normal distance (with the square root).
- `squareddistance()` returns the distance without the square root. This is faster and is enough when we only need to compare distances, such as finding the nearest centroid.

## 5. Summary

| Concept | Used in my class? | Where |
|---|---|---|
| Encapsulation | Partly | Maths hidden inside the functions, deleted constructor, `const` inputs |
| Inheritance | No | The class is stand-alone |
| Polymorphism | No | Two separate functions, no overloading or virtual functions |
