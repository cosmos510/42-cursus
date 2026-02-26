# 📚 Exercise 01: Iter - Itération sur tableaux

## 🎯 Objectif
Créer une fonction template **iter** qui applique une fonction sur chaque élément d'un tableau

---

## 🤔 C'est quoi ITER ?

### Analogie : La chaîne de production 🏭

Imagine une chaîne de production :
- Des objets arrivent sur un tapis roulant (le tableau)
- Chaque objet passe par une machine (la fonction)
- La machine fait quelque chose sur chaque objet

**iter = applique une opération sur chaque élément**

### Exemple visuel

```
Tableau : [1, 2, 3, 4, 5]
Fonction : print (affiche)

iter(array, 5, print)
    ↓
print(1) → affiche 1
print(2) → affiche 2
print(3) → affiche 3
print(4) → affiche 4
print(5) → affiche 5
```

---

## 📝 Ce qu'il faut faire

### Fichiers requis
- `iter.hpp` : contient le template iter
- `main.cpp` : tests
- `Makefile`

### Code à écrire

```cpp
#include <cstddef>

template<typename T, typename F>
void iter(T* array, size_t length, F func) {
    for (size_t i = 0; i < length; i++)
        func(array[i]);
}
```

---

## 💻 Décortiquons le code

### 1. Les paramètres template

```cpp
template<typename T, typename F>
```

**Deux types génériques :**
- **T** = type des éléments du tableau (int, float, string, etc.)
- **F** = type de la fonction (fonction ou functor)

### 2. Les paramètres de la fonction

```cpp
void iter(T* array, size_t length, F func)
```

**Décortiquons :**

```cpp
T* array
// Pointeur sur le premier élément du tableau
// T* = "tableau de T"
```

```cpp
size_t length
// Nombre d'éléments dans le tableau
// size_t = type pour les tailles (toujours positif)
```

```cpp
F func
// Fonction à appliquer sur chaque élément
// Peut être n'importe quelle fonction
```

### 3. La boucle

```cpp
for (size_t i = 0; i < length; i++)
    func(array[i]);
```

**Ce qui se passe :**
1. Parcourt chaque élément du tableau
2. Appelle `func` sur chaque élément
3. `array[i]` = élément à l'index i

---

## 🧪 Exemples d'utilisation

### Exemple 1: Afficher des nombres

```cpp
// Fonction d'affichage
template<typename T>
void print(T& x) {
    std::cout << x << " ";
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    
    iter(arr, 5, print<int>);
    // Affiche : 1 2 3 4 5
}
```

**Ce qui se passe :**

```cpp
iter(arr, 5, print<int>)
    ↓
print(arr[0])  // print(1)
print(arr[1])  // print(2)
print(arr[2])  // print(3)
print(arr[3])  // print(4)
print(arr[4])  // print(5)
```

### Exemple 2: Incrémenter des nombres

```cpp
// Fonction d'incrémentation
template<typename T>
void increment(T& x) {
    x++;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    
    std::cout << "Avant : ";
    iter(arr, 5, print<int>);  // 1 2 3 4 5
    
    iter(arr, 5, increment<int>);  // Incrémente chaque élément
    
    std::cout << "\nAprès : ";
    iter(arr, 5, print<int>);  // 2 3 4 5 6
}
```

### Exemple 3: Avec des strings

```cpp
template<typename T>
void print(T& x) {
    std::cout << x << " ";
}

int main() {
    std::string arr[] = {"Hello", "World", "42"};
    
    iter(arr, 3, print<std::string>);
    // Affiche : Hello World 42
}
```

### Exemple 4: Mettre au carré

```cpp
template<typename T>
void square(T& x) {
    x = x * x;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    
    iter(arr, 5, square<int>);
    iter(arr, 5, print<int>);
    // Affiche : 1 4 9 16 25
}
```

---

## 🎓 Concepts clés

### 1. Pointeur de tableau

```cpp
int arr[] = {1, 2, 3};
int* ptr = arr;  // arr est automatiquement un pointeur
```

**Équivalent :**
```cpp
iter(arr, 3, func)
// arr = pointeur sur le premier élément
// arr[0] = 1, arr[1] = 2, arr[2] = 3
```

### 2. Callback (fonction passée en paramètre)

```cpp
void iter(T* array, size_t length, F func)
//                                  ^^^^
//                                  Fonction callback
```

**La fonction est un paramètre !**

```cpp
iter(arr, 5, print);      // Passe la fonction print
iter(arr, 5, increment);  // Passe la fonction increment
```

### 3. Template avec 2 paramètres

```cpp
template<typename T, typename F>
//               ^           ^
//               |           |
//          Type tableau  Type fonction
```

**Exemple concret :**

```cpp
int arr[] = {1, 2, 3};
iter(arr, 3, print<int>);

// Le compilateur génère :
void iter(int* array, size_t length, void(*func)(int&)) {
    for (size_t i = 0; i < length; i++)
        func(array[i]);
}
```

### 4. Référence dans la fonction callback

```cpp
template<typename T>
void increment(T& x) {  // & = référence
    x++;
}
```

**Pourquoi `&` ?**

```cpp
// ❌ Sans référence (copie)
void increment(T x) {
    x++;  // Modifie la COPIE, pas l'original !
}

// ✅ Avec référence
void increment(T& x) {
    x++;  // Modifie l'ORIGINAL !
}
```

---

## ⚠️ Erreurs courantes

### 1. Oublier `<cstddef>` pour size_t

```cpp
// ❌ MAUVAIS
template<typename T, typename F>
void iter(T* array, int length, F func)  // int au lieu de size_t

// ✅ BON
#include <cstddef>
template<typename T, typename F>
void iter(T* array, size_t length, F func)
```

### 2. Oublier `&` dans la fonction callback

```cpp
// ❌ MAUVAIS (copie)
template<typename T>
void increment(T x) {  // Pas de &
    x++;  // Modifie la copie !
}

// ✅ BON (référence)
template<typename T>
void increment(T& x) {  // Avec &
    x++;  // Modifie l'original !
}
```

### 3. Mauvaise taille du tableau

```cpp
int arr[] = {1, 2, 3, 4, 5};

// ❌ MAUVAIS
iter(arr, 3, print<int>);  // N'affiche que 1 2 3

// ✅ BON
iter(arr, 5, print<int>);  // Affiche 1 2 3 4 5
```

---

## 🧪 Tests complets

```cpp
#include "iter.hpp"
#include <iostream>
#include <string>

template<typename T>
void print(T& x) {
    std::cout << x << " ";
}

template<typename T>
void increment(T& x) {
    x++;
}

template<typename T>
void square(T& x) {
    x = x * x;
}

int main() {
    // Test 1: Int avec print
    std::cout << "Test 1: ";
    int arr1[] = {1, 2, 3, 4, 5};
    iter(arr1, 5, print<int>);
    std::cout << std::endl;
    
    // Test 2: Int avec increment
    std::cout << "Test 2 avant: ";
    int arr2[] = {1, 2, 3};
    iter(arr2, 3, print<int>);
    std::cout << std::endl;
    
    iter(arr2, 3, increment<int>);
    std::cout << "Test 2 après: ";
    iter(arr2, 3, print<int>);
    std::cout << std::endl;
    
    // Test 3: String
    std::cout << "Test 3: ";
    std::string arr3[] = {"Hello", "World", "42"};
    iter(arr3, 3, print<std::string>);
    std::cout << std::endl;
    
    // Test 4: Float
    std::cout << "Test 4: ";
    float arr4[] = {1.1f, 2.2f, 3.3f};
    iter(arr4, 3, print<float>);
    std::cout << std::endl;
    
    // Test 5: Square
    std::cout << "Test 5: ";
    int arr5[] = {1, 2, 3, 4, 5};
    iter(arr5, 5, square<int>);
    iter(arr5, 5, print<int>);
    std::cout << std::endl;
    
    return 0;
}
```

---

## 💡 Résumé

### Checklist

- [ ] Template avec 2 paramètres (T et F)
- [ ] Paramètre `T* array` (pointeur)
- [ ] Paramètre `size_t length`
- [ ] Paramètre `F func` (fonction)
- [ ] Boucle for sur tous les éléments
- [ ] Appel de func sur chaque élément
- [ ] Include `<cstddef>` pour size_t
- [ ] Tout dans le .hpp

### Syntaxe clé

```cpp
template<typename T, typename F>     // 2 paramètres template
T* array                             // Pointeur sur tableau
size_t length                        // Taille (toujours positif)
F func                               // Fonction callback
func(array[i])                       // Appel de la fonction
T& x                                 // Référence (modifiable)
```

### Points importants

✅ **2 templates** : T pour le type, F pour la fonction
✅ **size_t** : type standard pour les tailles
✅ **Référence &** : pour modifier l'original
✅ **Callback** : fonction passée en paramètre
✅ **Générique** : fonctionne avec tous les types
