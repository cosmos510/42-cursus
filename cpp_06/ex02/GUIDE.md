# 📚 Exercise 02: Base - Identification de types

## 🎯 Objectif
Identifier le type réel d'un objet (A, B ou C) via pointeur ou référence

---

## 🤔 C'est quoi l'IDENTIFICATION de type ?

### Analogie : Deviner le déguisement 🎭

```
Tu vois : Une personne déguisée (Base*)
Tu dois deviner : C'est A, B ou C ?
```

**Identification = découvrir le type réel derrière un pointeur/référence**

---

## 📝 Structure

```cpp
class Base {
public:
    virtual ~Base() {}  // Destructeur virtuel obligatoire !
};

class A : public Base {};
class B : public Base {};
class C : public Base {};
```

---

## 💻 Implémentation

### generate() - Crée aléatoirement A, B ou C

```cpp
Base* generate(void) {
    std::srand(std::time(NULL));
    int random = std::rand() % 3;
    
    switch (random) {
        case 0: return new A();
        case 1: return new B();
        case 2: return new C();
    }
    return NULL;
}
```

### identify(Base* p) - Identifie par pointeur

```cpp
void identify(Base* p) {
    if (dynamic_cast<A*>(p))
        std::cout << "A" << std::endl;
    else if (dynamic_cast<B*>(p))
        std::cout << "B" << std::endl;
    else if (dynamic_cast<C*>(p))
        std::cout << "C" << std::endl;
}
```

**dynamic_cast avec pointeur :**
- Retourne le pointeur casté si succès
- Retourne NULL si échec

### identify(Base& p) - Identifie par référence

```cpp
void identify(Base& p) {
    try {
        (void)dynamic_cast<A&>(p);
        std::cout << "A" << std::endl;
        return;
    } catch (std::exception&) {}
    
    try {
        (void)dynamic_cast<B&>(p);
        std::cout << "B" << std::endl;
        return;
    } catch (std::exception&) {}
    
    std::cout << "C" << std::endl;
}
```

**dynamic_cast avec référence :**
- Retourne la référence castée si succès
- Lance std::bad_cast si échec

---

## 🧪 Test

```cpp
Base* ptr = generate();

std::cout << "By pointer: ";
identify(ptr);

std::cout << "By reference: ";
identify(*ptr);

delete ptr;
```

---

## 🎓 Concepts : dynamic_cast

### Avec pointeur

```cpp
Base* base = new A();
A* a = dynamic_cast<A*>(base);

if (a != NULL)
    std::cout << "C'est un A !" << std::endl;
```

### Avec référence

```cpp
Base& base = *new A();

try {
    A& a = dynamic_cast<A&>(base);
    std::cout << "C'est un A !" << std::endl;
} catch (std::bad_cast&) {
    std::cout << "Ce n'est pas un A" << std::endl;
}
```

### Différences

| Pointeur | Référence |
|----------|-----------|
| Retourne NULL si échec | Lance exception si échec |
| Facile à tester | Nécessite try/catch |

---

## ⚠️ Pièges

### 1. Oublier le destructeur virtuel

```cpp
// ❌ MAUVAIS
class Base {
    ~Base() {}  // Pas virtual !
};

// ✅ BON
class Base {
    virtual ~Base() {}  // Virtual !
};
```

**Pourquoi ?**
- dynamic_cast nécessite du polymorphisme
- Polymorphisme = au moins une fonction virtuelle

### 2. Confondre pointeur et référence

```cpp
// Pointeur : teste NULL
if (dynamic_cast<A*>(ptr))
    // ...

// Référence : try/catch
try {
    dynamic_cast<A&>(ref);
} catch (std::bad_cast&) {}
```

---

## 💡 Résumé

### Checklist
- [ ] Base avec destructeur virtuel
- [ ] Classes A, B, C héritent de Base
- [ ] generate() crée aléatoirement
- [ ] identify(Base*) avec dynamic_cast
- [ ] identify(Base&) avec try/catch
- [ ] Tests avec les deux versions

### Points clés
✅ **dynamic_cast** : cast sécurisé avec vérification
✅ **Pointeur** : retourne NULL si échec
✅ **Référence** : lance exception si échec
✅ **virtual ~** : obligatoire pour dynamic_cast
