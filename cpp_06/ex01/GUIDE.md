# CPP Module 06 - Exercise 01: Serializer

## Objectif
Sérialiser/désérialiser un pointeur (pointeur ↔ entier).

## Structures

### Data
```cpp
struct Data {
    int value;
    std::string name;
};
```

### Serializer
```cpp
class Serializer {
private:
    Serializer();  // Privé - non-instantiable
public:
    static uintptr_t serialize(Data* ptr);
    static Data* deserialize(uintptr_t raw);
};
```

## Implémentation
```cpp
uintptr_t Serializer::serialize(Data* ptr) {
    return reinterpret_cast<uintptr_t>(ptr);
}

Data* Serializer::deserialize(uintptr_t raw) {
    return reinterpret_cast<Data*>(raw);
}
```

## Test
```cpp
Data original;
original.value = 42;

uintptr_t serialized = Serializer::serialize(&original);
Data* deserialized = Serializer::deserialize(serialized);

if (deserialized == &original)
    std::cout << "SUCCESS" << std::endl;
```

## Concepts
- uintptr_t: entier pour stocker un pointeur
- reinterpret_cast: conversion bas niveau
- Sérialisation: pointeur → entier
- Désérialisation: entier → pointeur

## Checklist
- Non-instantiable
- Méthodes statiques
- Data avec membres
- reinterpret_cast
- Test égalité pointeurs
