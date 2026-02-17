# CPP Module 06 - Exercise 02: Identify
## Guide de Compréhension

---

## 📋 Objectif
Identifier le type réel d'un objet sans utiliser `std::typeinfo`.

---

## 🏗️ Structures

### Base (classe abstraite)
```cpp
class Base {
public:
    virtual ~Base();  // Destructeur virtuel OBLIGATOIRE
};
```

**Caractéristiques:**
- ✅ Destructeur virtuel (obligatoire pour polymorphisme)
- ✅ Pas d'autres membres
- ✅ Classe de base pour A, B, C

### A, B, C (classes dérivées)
```cpp
class A : public Base {};
class B : public Base {};
class C : public Base {};
```

**Caractéristiques:**
- ✅ Classes vides
- ✅ Héritent publiquement de Base
- ❌ Pas besoin d'OCF (sujet le dit explicitement)

---

## 🎯 Fonctions à Implémenter

### 1. generate()
```cpp
Base* generate(void) {
    int random = std::rand() % 3;
    if (random == 0)
        return new A();
    else if (random == 1)
        return new B();
    else
        return new C();
}
```

**Fonction:**
- Crée aléatoirement A, B ou C
- Retourne `Base*` (polymorphisme)
- Utilise `std::rand()`

**Initialisation:**
```cpp
#include <cstdlib>
#include <ctime>

std::srand(std::time(0));  // Dans main()
```

---

### 2. identify(Base* p)
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

**Fonction:**
- Prend un pointeur `Base*`
- Utilise `dynamic_cast` avec pointeurs
- Affiche "A", "B" ou "C"

**Comment ça marche:**
```cpp
A* a = dynamic_cast<A*>(p);
if (a)  // Succès: p pointe vers un A
else    // Échec: p ne pointe pas vers un A (retourne NULL)
```

---

### 3. identify(Base& p)
```cpp
void identify(Base& p) {
    try {
        (void)dynamic_cast<A&>(p);
        std::cout << "A" << std::endl;
        return;
    } catch (...) {}
    
    try {
        (void)dynamic_cast<B&>(p);
        std::cout << "B" << std::endl;
        return;
    } catch (...) {}
    
    try {
        (void)dynamic_cast<C&>(p);
        std::cout << "C" << std::endl;
        return;
    } catch (...) {}
}
```

**Fonction:**
- Prend une référence `Base&`
- Utilise `dynamic_cast` avec références
- **INTERDIT d'utiliser des pointeurs**
- Affiche "A", "B" ou "C"

**Comment ça marche:**
```cpp
try {
    A& a = dynamic_cast<A&>(p);
    // Succès: p référence un A
} catch (std::bad_cast& e) {
    // Échec: p ne référence pas un A (lance exception)
}
```

---

## 🔄 Workflow Complet

```cpp
#include <cstdlib>
#include <ctime>

int main() {
    std::srand(std::time(0));
    
    // Générer un objet aléatoire
    Base* obj = generate();
    
    // Identifier par pointeur
    std::cout << "Identify by pointer: ";
    identify(obj);
    
    // Identifier par référence
    std::cout << "Identify by reference: ";
    identify(*obj);
    
    // Libérer la mémoire
    delete obj;
    
    return 0;
}
```

**Output possible:**
```
Identify by pointer: B
Identify by reference: B
```

---

## 🎓 Concepts Clés

### 1. dynamic_cast avec pointeurs
```cpp
Derived* d = dynamic_cast<Derived*>(base);
if (d)
    // Succès: base pointe vers un Derived
else
    // Échec: retourne NULL
```

**Caractéristiques:**
- Retourne NULL si échec
- Pas d'exception
- Vérification avec `if (ptr)`

### 2. dynamic_cast avec références
```cpp
try {
    Derived& d = dynamic_cast<Derived&>(base);
    // Succès
} catch (std::bad_cast& e) {
    // Échec: lance std::bad_cast
}
```

**Caractéristiques:**
- Lance exception si échec
- Pas de NULL (références ne peuvent pas être NULL)
- Vérification avec `try/catch`

### 3. RTTI (Run-Time Type Information)
**Définition:** Informations de type disponibles à l'exécution.

**Nécessite:**
- Fonctions virtuelles dans la classe de base
- Compilateur avec RTTI activé (par défaut)

**Utilisé par:**
- `dynamic_cast`
- `typeid` (interdit dans cet exercice)

### 4. Destructeur virtuel
```cpp
class Base {
public:
    virtual ~Base();  // OBLIGATOIRE
};
```

**Pourquoi obligatoire?**
```cpp
Base* obj = new Derived();
delete obj;  // Sans destructeur virtuel: fuite mémoire!
```

**Avec destructeur virtuel:**
- Appelle le destructeur de Derived
- Puis le destructeur de Base
- Pas de fuite mémoire

**Sans destructeur virtuel:**
- Appelle seulement le destructeur de Base
- Fuite mémoire si Derived a des ressources

---

## 🧪 Tests Importants

### Test 1: Tous les types
```cpp
for (int i = 0; i < 10; i++) {
    Base* obj = generate();
    identify(obj);
    identify(*obj);
    delete obj;
}
```

### Test 2: Vérifier la cohérence
```cpp
Base* obj = generate();
std::cout << "Pointer: ";
identify(obj);
std::cout << "Reference: ";
identify(*obj);
// Les deux doivent afficher la même chose
delete obj;
```

### Test 3: Chaque type individuellement
```cpp
Base* a = new A();
Base* b = new B();
Base* c = new C();

identify(a);  // A
identify(b);  // B
identify(c);  // C

delete a;
delete b;
delete c;
```

---

## 🚨 Erreurs Courantes

### 1. Oublier le destructeur virtuel
```cpp
// ❌ ERREUR
class Base {
public:
    ~Base();  // Pas virtuel!
};

// ✅ CORRECT
class Base {
public:
    virtual ~Base();
};
```

### 2. Utiliser std::typeinfo
```cpp
// ❌ INTERDIT
#include <typeinfo>
if (typeid(*p) == typeid(A))
    std::cout << "A" << std::endl;

// ✅ CORRECT
if (dynamic_cast<A*>(p))
    std::cout << "A" << std::endl;
```

### 3. Utiliser des pointeurs dans identify(Base&)
```cpp
// ❌ INTERDIT
void identify(Base& p) {
    Base* ptr = &p;
    if (dynamic_cast<A*>(ptr))
        std::cout << "A" << std::endl;
}

// ✅ CORRECT
void identify(Base& p) {
    try {
        (void)dynamic_cast<A&>(p);
        std::cout << "A" << std::endl;
    } catch (...) {}
}
```

### 4. Ne pas gérer les exceptions
```cpp
// ❌ ERREUR: Crash si mauvais type
void identify(Base& p) {
    A& a = dynamic_cast<A&>(p);  // Lance exception si pas A
    std::cout << "A" << std::endl;
}

// ✅ CORRECT
void identify(Base& p) {
    try {
        (void)dynamic_cast<A&>(p);
        std::cout << "A" << std::endl;
    } catch (...) {}
}
```

### 5. Oublier de delete
```cpp
// ❌ ERREUR: Fuite mémoire
Base* obj = generate();
identify(obj);
// Oubli de delete

// ✅ CORRECT
Base* obj = generate();
identify(obj);
delete obj;
```

---

## 📝 Checklist de Validation

✅ Base avec destructeur virtuel  
✅ A, B, C héritent de Base  
✅ A, B, C sont des classes vides  
✅ generate() crée aléatoirement A, B ou C  
✅ generate() retourne Base*  
✅ identify(Base*) utilise dynamic_cast avec pointeurs  
✅ identify(Base&) utilise dynamic_cast avec références  
✅ identify(Base&) utilise try/catch  
✅ identify(Base&) n'utilise PAS de pointeurs  
✅ Pas d'utilisation de std::typeinfo  
✅ Tests avec les 3 types  
✅ Vérification cohérence pointeur/référence  
✅ Gestion correcte de la mémoire (delete)  
✅ Compilation avec -Wall -Wextra -Werror -std=c++98  

---

## 💡 Points Clés à Retenir

1. **Destructeur virtuel**: Obligatoire pour polymorphisme
2. **dynamic_cast pointeur**: Retourne NULL si échec
3. **dynamic_cast référence**: Lance exception si échec
4. **RTTI**: Nécessite fonctions virtuelles
5. **Pas de pointeurs**: Dans identify(Base&)
6. **std::typeinfo interdit**: Utiliser dynamic_cast
7. **Gestion mémoire**: delete après new

---

## 🎯 Différence Pointeur vs Référence

| Aspect | Pointeur | Référence |
|--------|----------|-----------|
| Peut être NULL | ✅ Oui | ❌ Non |
| dynamic_cast échec | Retourne NULL | Lance exception |
| Vérification | `if (ptr)` | `try/catch` |
| Syntaxe | `*ptr` | `ref` |

---

## 🏆 Conseils pour l'Évaluation

1. Expliquer RTTI et pourquoi le destructeur doit être virtuel
2. Montrer la différence entre dynamic_cast avec pointeur et référence
3. Expliquer pourquoi std::typeinfo est interdit
4. Montrer que identify(Base&) n'utilise pas de pointeurs
5. Tester avec les 3 types et vérifier la cohérence
6. Vérifier qu'il n'y a pas de fuites mémoire
