# Object-Oriented Programming Report: Week 03

## 1. Encapsulation
I implemented encapsulation in the `DataLoader` class by exposing only a clean public interface via the `public:` access specifier:
```cpp
static vector<vector<double>> loadCSV(const string& filename);
```
All parsing variables (such as cell buffers, line strings, and quote tracking flags) are kept out of the class header and strictly confined within the function implementation in `DataLoader.cpp`. This prevents outside code from tampering with intermediate state.

## 2. Inheritance
The `DataLoader` class does not inherit from any base class, nor is it used as a base class. Because it acts as a standalone static service utility for file processing, an inheritance hierarchy (using `public`, `protected`, or `private` base classes) was unnecessary for its design.

## 3. Polymorphism
Polymorphism is not used in `DataLoader`. The `loadCSV` function is defined as a `static` member function:
* It is bound statically at compile-time.
* It does not use `virtual` methods or dynamic vtable dispatch.
* Calling `DataLoader::loadCSV(...)` directly executes the implementation without requiring instance creation or dynamic runtime resolution.

## 4. Class Structure Summary

| Class | Access Specifiers | Member Data | Member Functions | Inheritance / Polymorphism |
| :--- | :--- | :--- | :--- | :--- |
| `DataLoader` | `public:` | None (Stateless) | `static vector<vector<double>> loadCSV(const string& filename)` | None (Static Utility Class) |