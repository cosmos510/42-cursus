# 📚 CPP MODULE 07 - GUIDE COMPLET

## 🎯 Objectif du module
Apprendre les **templates** en C++ : fonctions et classes génériques qui fonctionnent avec n'importe quel type.

---

## 📝 Exercise 00: Easy start (swap, min, max)

### 🎓 Concepts
- **Templates de fonctions** : fonctions génériques
- **Syntaxe** : `template<typename T>`
- **Utilisation** : fonctionne avec int, float, string, etc.

### 💻 Ce qu'il faut faire

**Fichier : `whatever.hpp`**

```cpp
#ifndef WHATEVER_HPP
#define WHATEVER_HPP

// Échange deux valeurs
template<typename T>
void swap(T& a, T& b) {
    T tmp = a;
    a = b;
    b = tmp;
}

// Retourne le minimum
template<typename T>
T const & min(T const & a, T const & b) {
    return (a < b) ? a : b;
}

// Retourne le maximum
template<typename T>
T const & max(T const & a, T const & b) {
    return (a > b) ? a : b;
}

#endif
```

### ✅ Points clés
- ✅ Tout dans le `.hpp` (templates = header-only)
- ✅ Utilise `const &` pour éviter les copies
- ✅ Fonctionne avec tous les types qui ont `<` et `>`
- ✅ Utilise `::` pour éviter les conflits avec std::min/max

### 🧪 Test
```cpp
int a = 2, b = 3;
::swap(a, b);           // a=3, b=2
std::cout << ::min(a, b);  // 2
std::cout << ::max(a, b);  // 3
```

---

## 📝 Exercise 01: Iter

### 🎓 Concepts
- **Template avec pointeur de fonction**
- **Itération sur tableau**
- **Fonction callback générique**

### 💻 Ce qu'il faut faire

**Fichier : `iter.hpp`**

```cpp
#ifndef ITER_HPP
#define ITER_HPP

#include <cstddef>

// Applique une fonction sur chaque élément d'un tableau
template<typename T, typename F>
void iter(T* array, size_t length, F func) {
    for (size_t i = 0; i < length; i++)
        func(array[i]);
}

#endif
```

### ✅ Points clés
- ✅ `T*` = pointeur sur tableau de type T
- ✅ `F` = type de la fonction (peut être fonction ou functor)
- ✅ `func(array[i])` = appelle la fonction sur chaque élément
- ✅ Fonctionne avec n'importe quel type de tableau et fonction

### 🧪 Test
```cpp
template<typename T>
void print(T& x) { std::cout << x << " "; }

int arr[] = {1, 2, 3, 4, 5};
iter(arr, 5, print<int>);  // Affiche: 1 2 3 4 5
```

### 💡 Cas d'usage
```cpp
// Incrémenter tous les éléments
template<typename T>
void increment(T& x) { x++; }

int arr[] = {1, 2, 3};
iter(arr, 3, increment<int>);  // arr = {2, 3, 4}
```

---

## 📝 Exercise 02: Array

### 🎓 Concepts
- **Template de classe**
- **Gestion dynamique de mémoire**
- **Copie profonde (deep copy)**
- **Surcharge d'opérateurs**

### 💻 Ce qu'il faut faire

**Fichier : `Array.hpp`**

```cpp
#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <exception>
#include <cstddef>

template<typename T>
class Array {
private:
    T* _data;
    unsigned int _size;

public:
    // Constructeur par défaut : tableau vide
    Array() : _data(NULL), _size(0) {}

    // Constructeur avec taille : initialise à 0
    Array(unsigned int n) : _data(new T[n]()), _size(n) {}

    // Constructeur de copie : copie profonde
    Array(const Array& other) : _data(NULL), _size(0) {
        *this = other;
    }

    // Opérateur d'assignation : copie profonde
    Array& operator=(const Array& other) {
        if (this != &other) {
            delete[] _data;
            _size = other._size;
            _data = new T[_size];
            for (unsigned int i = 0; i < _size; i++)
                _data[i] = other._data[i];
        }
        return *this;
    }

    // Destructeur : libère la mémoire
    ~Array() {
        delete[] _data;
    }

    // Accès avec vérification des limites
    T& operator[](unsigned int index) {
        if (index >= _size)
            throw std::exception();
        return _data[index];
    }

    // Version const
    const T& operator[](unsigned int index) const {
        if (index >= _size)
            throw std::exception();
        return _data[index];
    }

    // Retourne la taille
    unsigned int size() const {
        return _size;
    }
};

#endif
```

### ✅ Points clés

**1. Constructeurs**
```cpp
Array<int> empty;        // Tableau vide
Array<int> arr(5);       // Tableau de 5 int initialisés à 0
```

**2. Copie profonde**
```cpp
Array<int> a(3);
a[0] = 42;
Array<int> b(a);  // Copie profonde
b[0] = 99;        // N'affecte PAS a[0]
```

**3. Gestion des erreurs**
```cpp
Array<int> arr(5);
arr[10];  // Lance std::exception (out of bounds)
```

**4. Initialisation avec `()`**
```cpp
new T[n]()  // ← Les () initialisent à 0
// int → 0
// float → 0.0
// string → ""
```

### 🧪 Tests importants

```cpp
// Test 1: Copie profonde
Array<int> a(3);
a[0] = 1;
Array<int> b(a);
b[0] = 99;
// a[0] doit rester 1 (pas 99)

// Test 2: Out of bounds
try {
    Array<int> arr(5);
    arr[10];  // Exception
} catch (std::exception& e) {
    // OK
}

// Test 3: Tableau vide
Array<int> empty;
// empty.size() == 0
// empty[0] lance exception
```

### ⚠️ Pièges à éviter

1. **Oublier la copie profonde**
```cpp
// ❌ MAUVAIS
Array& operator=(const Array& other) {
    _data = other._data;  // Copie superficielle !
}

// ✅ BON
Array& operator=(const Array& other) {
    delete[] _data;
    _data = new T[other._size];
    for (...)
        _data[i] = other._data[i];
}
```

2. **Oublier de vérifier les limites**
```cpp
// ❌ MAUVAIS
T& operator[](unsigned int index) {
    return _data[index];  // Pas de vérification !
}

// ✅ BON
T& operator[](unsigned int index) {
    if (index >= _size)
        throw std::exception();
    return _data[index];
}
```

3. **Memory leaks**
```cpp
// ❌ MAUVAIS
Array& operator=(const Array& other) {
    _data = new T[other._size];  // Leak de l'ancien _data !
}

// ✅ BON
Array& operator=(const Array& other) {
    delete[] _data;  // Libère d'abord
    _data = new T[other._size];
}
```

---

## 🎯 Résumé du module

| Exercise | Concept principal | Difficulté |
|----------|------------------|------------|
| ex00 | Templates de fonctions | ⭐ |
| ex01 | Templates + callbacks | ⭐⭐ |
| ex02 | Templates de classes + mémoire | ⭐⭐⭐ |

## 📋 Checklist finale

### Ex00
- [ ] swap, min, max fonctionnent avec int
- [ ] Fonctionnent avec float
- [ ] Fonctionnent avec string
- [ ] Tout dans le .hpp

### Ex01
- [ ] iter fonctionne avec int[]
- [ ] Fonctionne avec string[]
- [ ] Fonctionne avec différentes fonctions
- [ ] Tout dans le .hpp

### Ex02
- [ ] Constructeur par défaut
- [ ] Constructeur avec taille
- [ ] Copie profonde (constructeur + assignation)
- [ ] operator[] avec vérification
- [ ] size() retourne la bonne taille
- [ ] Exception si out of bounds
- [ ] Pas de memory leaks
- [ ] Version const de operator[]

## 🔍 Commandes de test

```bash
# Compiler
make

# Tester
./program

# Vérifier les leaks
leaks -atExit -- ./program

# Tester tout le module
./test.sh
```

## 💡 Conseils

1. **Templates = header-only** : tout le code dans .hpp
2. **Copie profonde** : toujours allouer nouvelle mémoire
3. **delete[]** : pour les tableaux (pas delete)
4. **Vérifier les limites** : toujours dans operator[]
5. **Tester avec plusieurs types** : int, float, string, etc.

## 🚀 Pour aller plus loin

- Comprendre la différence entre copie superficielle et profonde
- Savoir quand utiliser `const &` vs copie
- Maîtriser l'allocation dynamique avec new/delete
- Comprendre le polymorphisme avec templates
