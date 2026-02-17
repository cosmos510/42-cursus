# 📚 Exercise 02: Array - Template de classe

## 🎯 Objectif
Créer une classe template **Array** qui gère un tableau dynamique avec vérification des limites

---

## 🤔 C'est quoi un Array template ?

### Analogie : Le casier à taille variable 🗄️

Imagine un casier de rangement :
- Tu choisis la **taille** (nombre de cases)
- Tu choisis le **type** d'objets (int, string, etc.)
- Tu peux **accéder** aux cases avec un index
- Si tu essaies d'accéder à une case qui n'existe pas → **alarme** ! 🚨

**Array = tableau sécurisé et générique**

### Comparaison

```cpp
// Tableau C (dangereux)
int arr[5];
arr[10] = 42;  // 💥 Crash ! Pas de vérification

// Notre Array (sécurisé)
Array<int> arr(5);
arr[10] = 42;  // 🚨 Exception ! Vérifie les limites
```

---

## 📝 Ce qu'il faut faire

### Fichiers requis
- `Array.hpp` : classe template Array
- `main.cpp` : tests
- `Makefile`

### Structure de la classe

```cpp
template<typename T>
class Array {
private:
    T* _data;              // Pointeur sur les données
    unsigned int _size;    // Taille du tableau

public:
    Array();                              // Tableau vide
    Array(unsigned int n);                // Tableau de taille n
    Array(const Array& other);            // Copie profonde
    Array& operator=(const Array& other); // Copie profonde
    ~Array();                             // Libère la mémoire
    
    T& operator[](unsigned int index);           // Accès
    const T& operator[](unsigned int index) const; // Accès const
    unsigned int size() const;            // Retourne la taille
};
```

---

## 💻 Implémentation détaillée

### 1. Constructeur par défaut

```cpp
Array() : _data(NULL), _size(0) {}
```

**Crée un tableau vide :**
- Pas de données
- Taille = 0

**Utilisation :**
```cpp
Array<int> empty;
std::cout << empty.size();  // 0
```

### 2. Constructeur avec taille

```cpp
Array(unsigned int n) : _data(new T[n]()), _size(n) {}
```

**Décortiquons :**

```cpp
new T[n]()
//       ^^
//       Les () initialisent à 0 !
```

**Initialisation automatique :**
- `int` → 0
- `float` → 0.0
- `std::string` → ""
- `bool` → false

**Exemple :**
```cpp
Array<int> arr(5);
// arr[0] = 0, arr[1] = 0, ..., arr[4] = 0
```

### 3. Constructeur de copie (COPIE PROFONDE)

```cpp
Array(const Array& other) : _data(NULL), _size(0) {
    *this = other;  // Utilise operator=
}
```

**Pourquoi copie profonde ?**

```cpp
// Copie superficielle (MAUVAIS)
Array a(3);
Array b = a;  // Les deux pointent vers la même mémoire !
b[0] = 99;    // Modifie aussi a[0] ! 💥

// Copie profonde (BON)
Array a(3);
Array b = a;  // Nouvelle allocation mémoire
b[0] = 99;    // N'affecte PAS a[0] ✅
```

### 4. Opérateur d'assignation (COPIE PROFONDE)

```cpp
Array& operator=(const Array& other) {
    if (this != &other) {
        delete[] _data;              // 1. Libère l'ancien
        _size = other._size;         // 2. Copie la taille
        _data = new T[_size];        // 3. Alloue nouveau
        for (unsigned int i = 0; i < _size; i++)
            _data[i] = other._data[i];  // 4. Copie élément par élément
    }
    return *this;
}
```

**Étapes importantes :**

```cpp
if (this != &other)
// Vérifie qu'on ne s'assigne pas à soi-même
// a = a; → ne fait rien
```

```cpp
delete[] _data;
// Libère l'ancienne mémoire AVANT d'allouer
// Évite les memory leaks !
```

```cpp
for (unsigned int i = 0; i < _size; i++)
    _data[i] = other._data[i];
// Copie CHAQUE élément (pas juste le pointeur)
```

**Exemple :**
```cpp
Array<int> a(3);
a[0] = 1;
a[1] = 2;
a[2] = 3;

Array<int> b(5);
b = a;  // b devient une copie de a

std::cout << b.size();  // 3 (pas 5 !)
std::cout << b[0];      // 1
```

### 5. Destructeur

```cpp
~Array() {
    delete[] _data;
}
```

**⚠️ IMPORTANT : `delete[]` pour les tableaux !**

```cpp
// ❌ MAUVAIS
delete _data;  // Undefined behavior !

// ✅ BON
delete[] _data;  // Pour les tableaux
```

### 6. Opérateur [] (accès)

```cpp
T& operator[](unsigned int index) {
    if (index >= _size)
        throw std::exception();
    return _data[index];
}
```

**Décortiquons :**

```cpp
if (index >= _size)
// Vérifie que l'index est valide
// index 5 dans un tableau de taille 5 → Exception !
```

```cpp
return _data[index];
// Retourne une RÉFÉRENCE (modifiable)
```

**Version const :**

```cpp
const T& operator[](unsigned int index) const {
    if (index >= _size)
        throw std::exception();
    return _data[index];
}
```

**Pourquoi 2 versions ?**

```cpp
Array<int> arr(5);
arr[0] = 42;  // Utilise la version non-const

const Array<int>& ref = arr;
std::cout << ref[0];  // Utilise la version const
```

### 7. size()

```cpp
unsigned int size() const {
    return _size;
}
```

---

## 🧪 Tests importants

### Test 1: Constructeurs

```cpp
Array<int> empty;           // Tableau vide
std::cout << empty.size();  // 0

Array<int> arr(5);          // 5 éléments
std::cout << arr.size();    // 5
std::cout << arr[0];        // 0 (initialisé)
```

### Test 2: Copie profonde

```cpp
Array<int> a(3);
a[0] = 42;
a[1] = 21;
a[2] = 10;

Array<int> b(a);  // Copie
b[0] = 99;

std::cout << a[0];  // 42 (pas 99 !)
std::cout << b[0];  // 99
```

### Test 3: Out of bounds

```cpp
Array<int> arr(5);

try {
    arr[10] = 42;  // ❌ Exception !
} catch (std::exception& e) {
    std::cout << "Out of bounds" << std::endl;
}
```

### Test 4: Assignation

```cpp
Array<int> a(3);
a[0] = 1;
a[1] = 2;
a[2] = 3;

Array<int> b(5);
b = a;  // Assignation

std::cout << b.size();  // 3 (pas 5 !)
std::cout << b[0];      // 1

b[0] = 99;
std::cout << a[0];  // 1 (pas 99 !)
```

### Test 5: Différents types

```cpp
Array<int> ints(5);
Array<float> floats(3);
Array<std::string> strings(2);

strings[0] = "Hello";
strings[1] = "World";
```

---

## ⚠️ Pièges à éviter

### 1. Copie superficielle (DANGER !)

```cpp
// ❌ MAUVAIS
Array& operator=(const Array& other) {
    _data = other._data;  // Les deux pointent vers la même mémoire !
    _size = other._size;
    return *this;
}
```

**Problème :**
```
a._data → [1][2][3]
          ↑
b._data ──┘  (même adresse !)

delete a;  // Libère la mémoire
// b._data pointe maintenant vers de la mémoire libérée ! 💥
```

### 2. Memory leak

```cpp
// ❌ MAUVAIS
Array& operator=(const Array& other) {
    _data = new T[other._size];  // Leak de l'ancien _data !
    // ...
}

// ✅ BON
Array& operator=(const Array& other) {
    delete[] _data;  // Libère d'abord
    _data = new T[other._size];
    // ...
}
```

### 3. delete au lieu de delete[]

```cpp
// ❌ MAUVAIS
~Array() {
    delete _data;  // Undefined behavior !
}

// ✅ BON
~Array() {
    delete[] _data;  // Pour les tableaux
}
```

### 4. Oublier les ()

```cpp
// ❌ MAUVAIS
Array(unsigned int n) : _data(new T[n]), _size(n) {}
// Pas d'initialisation !

// ✅ BON
Array(unsigned int n) : _data(new T[n]()), _size(n) {}
//                                     ^^
//                                     Initialise à 0
```

---

## 🎓 Concepts clés

### Copie profonde vs superficielle

**Copie superficielle (MAUVAIS) :**
```
a._data → [1][2][3]
          ↑
b._data ──┘  (même adresse)
```

**Copie profonde (BON) :**
```
a._data → [1][2][3]

b._data → [1][2][3]  (nouvelle allocation)
```

### new vs new[]

```cpp
T* ptr = new T;       // Un seul élément
delete ptr;           // Libère un élément

T* arr = new T[n];    // Tableau de n éléments
delete[] arr;         // Libère le tableau
```

### Initialisation avec ()

```cpp
new T[n]     // Pas d'initialisation (valeurs aléatoires)
new T[n]()   // Initialisation à 0
```

**Exemples :**
- `int` → 0
- `float` → 0.0
- `std::string` → ""
- `bool` → false

### operator[] const et non-const

```cpp
T& operator[](unsigned int index);              // Modifiable
const T& operator[](unsigned int index) const;  // Lecture seule
```

**Utilisation :**
```cpp
Array<int> arr(5);
arr[0] = 42;  // Version non-const

const Array<int>& ref = arr;
int x = ref[0];  // Version const
```

---

## 💡 Résumé

### Checklist

- [ ] Constructeur par défaut (tableau vide)
- [ ] Constructeur avec taille (initialise à 0)
- [ ] Constructeur de copie (copie profonde)
- [ ] Opérateur d'assignation (copie profonde)
- [ ] Destructeur (delete[])
- [ ] operator[] avec vérification
- [ ] operator[] const
- [ ] size()
- [ ] Pas de memory leaks
- [ ] Exception si out of bounds

### Syntaxe clé

```cpp
template<typename T>                 // Template de classe
new T[n]()                          // Alloue et initialise
delete[] _data                      // Libère un tableau
if (this != &other)                 // Évite auto-assignation
T& operator[](unsigned int index)   // Accès modifiable
const T& operator[](unsigned int index) const  // Accès const
```

### Points importants

✅ **Copie profonde** : nouvelle allocation + copie élément par élément
✅ **delete[]** : pour les tableaux (pas delete)
✅ **new T[n]()** : les () initialisent à 0
✅ **2 versions de operator[]** : const et non-const
✅ **Vérifier les limites** : throw exception si out of bounds
