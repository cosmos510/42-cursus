# 📚 Exercise 00: easyfind - Recherche dans conteneurs

## 🎯 Objectif
Créer une fonction template **easyfind** qui cherche un entier dans un conteneur STL

---

## 🤔 C'est quoi easyfind ?

### Analogie : Chercher dans une liste 🔍

Imagine que tu cherches un numéro dans une liste :
- Tu parcours la liste élément par élément
- Quand tu trouves le numéro → tu le montres (retourne l'itérateur)
- Si tu ne trouves pas → tu lèves une alarme (exception)

---

## 📝 Code à écrire

```cpp
#include <algorithm>
#include <exception>

class NotFoundException : public std::exception {
public:
    virtual const char* what() const throw() {
        return "Element not found";
    }
};

template<typename T>
typename T::iterator easyfind(T& container, int value) {
    typename T::iterator it = std::find(container.begin(), container.end(), value);
    if (it == container.end())
        throw NotFoundException();
    return it;
}
```

---

## 💻 Explication

### typename T::iterator

```cpp
typename T::iterator
```

**Pourquoi typename ?**
- `T::iterator` est un type dépendant (dépend de T)
- `typename` dit au compilateur : "c'est un type"

### std::find

```cpp
std::find(container.begin(), container.end(), value)
```

**Algorithme STL qui :**
- Cherche `value` entre `begin()` et `end()`
- Retourne un itérateur vers l'élément trouvé
- Retourne `end()` si non trouvé

### Vérification

```cpp
if (it == container.end())
    throw NotFoundException();
```

**Si `it == end()` → élément non trouvé → exception**

---

## 🧪 Utilisation

```cpp
std::vector<int> vec;
vec.push_back(1);
vec.push_back(2);
vec.push_back(3);

try {
    std::vector<int>::iterator it = easyfind(vec, 2);
    std::cout << "Found: " << *it << std::endl;  // Found: 2
} catch (std::exception& e) {
    std::cout << e.what() << std::endl;
}
```

---

## 🎓 Concepts

### Itérateur

**Pointeur "intelligent" vers un élément**

```cpp
std::vector<int>::iterator it = vec.begin();
std::cout << *it;  // Déréférence
++it;              // Avance
```

### Conteneurs compatibles

✅ `std::vector<int>`
✅ `std::list<int>`
✅ `std::deque<int>`

❌ `std::map` (associatif)
❌ `std::set` (associatif)

---

## ⚠️ Pièges

### 1. Oublier typename

```cpp
// ❌ MAUVAIS
T::iterator easyfind(...)

// ✅ BON
typename T::iterator easyfind(...)
```

### 2. Oublier <algorithm>

```cpp
#include <algorithm>  // Pour std::find
```

### 3. Ne pas vérifier end()

```cpp
// ❌ MAUVAIS
return std::find(...);  // Retourne end() si non trouvé

// ✅ BON
if (it == container.end())
    throw NotFoundException();
```

---

## 💡 Résumé

✅ **std::find** : algorithme STL
✅ **typename** : pour types dépendants
✅ **Itérateur** : pointeur vers élément
✅ **Exception** : si non trouvé
✅ **Tout dans .hpp** : templates
