# 📚 Exercise 02: MutantStack - Stack itérable

## 🎯 Objectif
Créer **MutantStack** : une stack avec des itérateurs

---

## 🤔 Pourquoi MutantStack ?

**Problème :** `std::stack` n'a PAS d'itérateurs !

```cpp
std::stack<int> s;
s.push(1);
s.push(2);
// Impossible de parcourir ! ❌
```

**Solution :** MutantStack ajoute des itérateurs

```cpp
MutantStack<int> ms;
ms.push(1);
ms.push(2);
for (iterator it = ms.begin(); it != ms.end(); ++it)
    std::cout << *it;  // ✅ Fonctionne !
```

---

## 📝 Structure

```cpp
template<typename T>
class MutantStack : public std::stack<T> {
public:
    typedef typename std::stack<T>::container_type::iterator iterator;
    
    iterator begin() { return this->c.begin(); }
    iterator end() { return this->c.end(); }
};
```

---

## 💻 Explication

### Héritage de std::stack

```cpp
class MutantStack : public std::stack<T>
```

**Hérite de toutes les méthodes :**
- `push()`
- `pop()`
- `top()`
- `size()`
- etc.

### Accès au conteneur sous-jacent

```cpp
this->c
```

**`c` = conteneur protégé de std::stack (deque par défaut)**

### Typedef des itérateurs

```cpp
typedef typename std::stack<T>::container_type::iterator iterator;
```

**Crée un alias pour le type d'itérateur**

### Méthodes begin() et end()

```cpp
iterator begin() { return this->c.begin(); }
iterator end() { return this->c.end(); }
```

**Expose les itérateurs du conteneur sous-jacent**

---

## 🧪 Test

```cpp
MutantStack<int> mstack;
mstack.push(5);
mstack.push(17);

std::cout << mstack.top() << std::endl;  // 17
mstack.pop();
std::cout << mstack.size() << std::endl;  // 1

mstack.push(3);
mstack.push(5);
mstack.push(737);
mstack.push(0);

MutantStack<int>::iterator it = mstack.begin();
MutantStack<int>::iterator ite = mstack.end();

while (it != ite) {
    std::cout << *it << std::endl;
    ++it;
}
```

---

## 🎓 Concepts

### Conteneur sous-jacent

`std::stack` utilise un conteneur (deque par défaut) :

```
std::stack<int>
    ↓
std::deque<int> c  (protégé)
```

MutantStack accède à `c` via `this->c`

### Polymorphisme

```cpp
std::stack<int> s(mstack);  // ✅ Fonctionne !
```

MutantStack EST une stack (héritage)

---

## 💡 Points clés

✅ **Hérite de std::stack**
✅ **Accède à `this->c`** (conteneur protégé)
✅ **Ajoute begin() et end()**
✅ **typedef pour iterator**
✅ **Compatible avec std::stack**
