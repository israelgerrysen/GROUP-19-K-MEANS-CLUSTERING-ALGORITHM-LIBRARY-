NAKAWEESA LINDA LUCY 
(25/U/02658/PS)


# Week 3 Report: Encapsulation, Inheritance, and Polymorphism


## Encapsulation

Encapsulation is the main object-oriented idea used in this program. It means keeping a class's data and internal steps hidden, and letting other code interact only through a small public interface.

**Public (the interface other code uses):**

- The `Matrix` type alias and the `Method` enum (`MinMax`, `Standard`).
- The constructor `FeatureScaler(method)`.
- `fit`, `transform`, `fit_transform`, `inverse_transform`, and `is_fitted`.

**Private (hidden inside the class):**

- Member data: `method_`, `offsets_`, `scales_`, and `fitted_`.
- Helper functions: `validate` and `apply`.

**Protected:** none, because the class has no subclasses.

**How encapsulation helps:**

- Outside code cannot edit the learned statistics or mark the scaler as fitted by mistake.
- `fit` builds the new statistics in local variables and stores them only after everything succeeds. If it fails, the previous state is kept.
- `transform` and `inverse_transform` throw an error if called before `fit`, so the object never returns results from unlearned data.
- `transform`, `inverse_transform`, and `is_fitted` are `const` because they do not change the object.
- The helpers can be changed later without breaking any code that uses the class.

## Inheritance

`FeatureScaler` does not use inheritance. It does not inherit from any class, and no class inherits from it. I did not need it because the two scaling methods share almost all of their logic and differ only in how `fit` calculates the offset and scale.

If more scaling methods are added later, a possible design is a base `Scaler` class with `MinMaxScaler` and `StandardScaler` subclasses. That is not implemented. In that design, the shared data would become `protected` so subclasses could use it while outside code still could not.

## Polymorphism

`FeatureScaler` does not use polymorphism. It has no virtual functions, no base class, and no overriding. What it does have is a simple runtime choice: the `Method` value passed to the constructor decides whether `fit` uses the MinMax or Standard calculation. The rest of the program uses one type, `FeatureScaler`, whichever method is chosen.

Polymorphism would appear only in the base-class design above, where `fit` would be a `virtual` function that each subclass overrides, and the program could use any scaler through a `Scaler` pointer or reference.

## conclusion
The report shows that encapsulation is the main idea in the play: learned the private statistics and helper functions are private,and other code uses only a small public interface. it also explains that the class uses neither inheritance nor polymorphm, and why


## 4. Class Layout Drawing

![Class Layout Diagram](./diagrams/featureScaler(week_3_progress).jpg)
