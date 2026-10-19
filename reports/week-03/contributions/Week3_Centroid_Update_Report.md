# Week 3 Report: Centroid Update

This report explains inheritance, polymorphism and encapsulation in my `CentroidUpdater` class. The class layout drawing is in the attached photo.

## 1. Class Layout


| Part | Name | Access |
|---|---|---|
| Member data | none | - |
| Member functions | `update()` (static), deleted constructor | public |
| Type names | `Point`, `Dataset` | public |
| Private members | none | - |
| Protected members | none | - |

## 2. Encapsulation
Encapsulation means keeping a class's data and functions together and controlling how other code can use them.

`CentroidUpdater` is a utility class. It has **no member data**, so there is no private data to hide. Encapsulation is used in these ways:
- The update logic (adding up points, counting, and dividing to get the mean) is all inside `update()`. Other code only sees the function's inputs and its result, not the steps.
- The constructor is deleted (`CentroidUpdater() = delete`), so nobody can create an object by mistake. The class can only be used through its static function.
- The inputs are passed as `const` references, so `update()` cannot change the caller's data. It builds and returns a new list of centroids.
- `update()` checks its input and throws `std::invalid_argument` for bad values, so wrong data cannot produce wrong results quietly.

Encapsulation here is weaker than in a class with private data, such as `CentroidInitializer`. The reason is that this class does not need to store anything.

## 3. Inheritance
Inheritance means one class takes the members of another class (a base class).

`CentroidUpdater` does **not** use inheritance. It has no base class and no child classes, because it has one simple job: move each centroid to the average of its points. So there is no inheritance arrow in my drawing, and no `protected` members either, because `protected` is only useful when a child class needs to use its parent's data.

## 4. Polymorphism
Polymorphism means the same name can do different things.

`CentroidUpdater` does **not** use polymorphism. It has no virtual functions and no overloaded functions. It has only one function, `update()`, and it always does the same thing.

## 5. Summary

| Concept | Used in my class? | Where |
|---|---|---|
| Encapsulation | Partly | Logic hidden inside `update()`, deleted constructor, `const` inputs |
| Inheritance | No | The class is stand-alone |
| Polymorphism | No | Only one function |
