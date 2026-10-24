# Creational Patterns Cheat Sheet

| Pattern | Factory Method | Abstract Factory | Builder | Prototype | Singleton |
|---|---|---|---|---|---|
| **Intent** | Virtual constructor | Families of products | Complex step-by-step | Clone existing object | Exactly one instance |
| **Participants** | Creator, Product | AbstractFactory, Factory1, Factory2, ProductA, ProductB | Director, Builder, Product | Prototype (clone method) | Singleton (private ctor, static getInstance) |
| **C++ Idiom** | `virtual unique_ptr<T> create()` | Pure virtual factory interface | Fluent methods returning `Builder&` | `virtual unique_ptr<T> clone() const` | Scott Meyers local static |
| **When to Use** | Type known only at runtime | Product families must match | 5+ config parameters | Construction is expensive | Hardware/Config coordination |
