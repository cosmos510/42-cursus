# 📚 Exercise 00: Bureaucrat - Exceptions

## 🎯 Objectif
Créer une classe **Bureaucrat** avec gestion des grades et **exceptions personnalisées**

---

## 🤔 C'est quoi une EXCEPTION ?

### Analogie : Le feu rouge 🚦

Imagine que tu conduis une voiture :
- **Sans exception** : tu fonces dans le mur et le programme crash 💥
- **Avec exception** : tu vois le feu rouge, tu freines, tu gères le problème ✅

**Exception = signal d'alarme qui dit "STOP, il y a un problème !"**

### Sans exception (crash 💥)

```cpp
void setGrade(int grade) {
    _grade = grade;  // Et si grade = 0 ou 200 ? 💥 Comportement indéfini
}
```

### Avec exception (gestion ✅)

```cpp
void setGrade(int grade) {
    if (grade < 1)
        throw GradeTooHighException();  // 🚨 Alarme !
    if (grade > 150)
        throw GradeTooLowException();   // 🚨 Alarme !
    _grade = grade;
}
```

---

## 📝 Ce qu'il faut faire

### Fichiers requis
- `Bureaucrat.hpp` : déclaration de la classe
- `Bureaucrat.cpp` : implémentation
- `main.cpp` : tests
- `Makefile`

### Structure de la classe

```cpp
class Bureaucrat {
private:
    const std::string _name;  // Nom (constant)
    int _grade;               // Grade (1 = meilleur, 150 = pire)

public:
    Bureaucrat(const std::string& name, int grade);
    // ... constructeurs, destructeur, etc.
    
    void incrementGrade();  // Grade-- (devient meilleur)
    void decrementGrade();  // Grade++ (devient pire)
    
    // Exceptions personnalisées
    class GradeTooHighException : public std::exception {};
    class GradeTooLowException : public std::exception {};
};
```

---

## 💻 Implémentation détaillée

### 1. Attributs

```cpp
private:
    const std::string _name;  // const = ne peut pas changer
    int _grade;               // 1 à 150
```

**Pourquoi const ?**
- Un bureaucrate ne change pas de nom !
- Mais son grade peut changer (promotion/rétrogradation)

### 2. Constructeur avec validation

```cpp
Bureaucrat::Bureaucrat(const std::string& name, int grade) 
    : _name(name), _grade(grade) {
    if (grade < 1)
        throw GradeTooHighException();
    if (grade > 150)
        throw GradeTooLowException();
}
```

**Décortiquons :**

```cpp
: _name(name), _grade(grade)
// Liste d'initialisation (obligatoire pour const)
```

```cpp
if (grade < 1)
    throw GradeTooHighException();
// Si grade trop bon (< 1), lance une exception
```

**Exemple concret :**

```cpp
try {
    Bureaucrat bob("Bob", 0);  // Grade invalide !
} catch (std::exception& e) {
    std::cout << "Erreur : " << e.what();  // "Grade is too high!"
}
```

### 3. incrementGrade() - Promotion

```cpp
void Bureaucrat::incrementGrade() {
    if (_grade - 1 < 1)
        throw GradeTooHighException();
    _grade--;  // Grade diminue = devient meilleur
}
```

**⚠️ ATTENTION : Incrémenter = diminuer le nombre !**

```
Grade 2 → incrementGrade() → Grade 1 (meilleur)
Grade 1 → incrementGrade() → Exception ! (déjà au max)
```

**Exemple :**

```cpp
Bureaucrat alice("Alice", 2);
alice.incrementGrade();  // Grade = 1 ✅
alice.incrementGrade();  // Exception ! ❌
```

### 4. decrementGrade() - Rétrogradation

```cpp
void Bureaucrat::decrementGrade() {
    if (_grade + 1 > 150)
        throw GradeTooLowException();
    _grade++;  // Grade augmente = devient pire
}
```

**Exemple :**

```cpp
Bureaucrat charlie("Charlie", 149);
charlie.decrementGrade();  // Grade = 150 ✅
charlie.decrementGrade();  // Exception ! ❌
```

### 5. Exceptions personnalisées

```cpp
class GradeTooHighException : public std::exception {
public:
    virtual const char* what() const throw() {
        return "Grade is too high!";
    }
};

class GradeTooLowException : public std::exception {
public:
    virtual const char* what() const throw() {
        return "Grade is too low!";
    }
};
```

**Décortiquons :**

```cpp
: public std::exception
// Hérite de std::exception (classe de base)
```

```cpp
virtual const char* what() const throw()
// Fonction qui retourne le message d'erreur
// throw() = ne lance pas d'exception (C++98)
```

### 6. Opérateur << (affichage)

```cpp
std::ostream& operator<<(std::ostream& os, const Bureaucrat& b) {
    os << b.getName() << ", bureaucrat grade " << b.getGrade();
    return os;
}
```

**Utilisation :**

```cpp
Bureaucrat bob("Bob", 75);
std::cout << bob << std::endl;
// Affiche : "Bob, bureaucrat grade 75"
```

---

## 🧪 Tests importants

### Test 1: Création valide

```cpp
try {
    Bureaucrat bob("Bob", 75);
    std::cout << bob << std::endl;  // OK
} catch (std::exception& e) {
    std::cout << e.what() << std::endl;
}
```

### Test 2: Grade trop haut (0)

```cpp
try {
    Bureaucrat invalid("Invalid", 0);  // ❌ Exception
} catch (std::exception& e) {
    std::cout << e.what();  // "Grade is too high!"
}
```

### Test 3: Grade trop bas (151)

```cpp
try {
    Bureaucrat invalid("Invalid", 151);  // ❌ Exception
} catch (std::exception& e) {
    std::cout << e.what();  // "Grade is too low!"
}
```

### Test 4: Incrémenter au maximum

```cpp
try {
    Bureaucrat alice("Alice", 2);
    alice.incrementGrade();  // Grade = 1 ✅
    alice.incrementGrade();  // ❌ Exception
} catch (std::exception& e) {
    std::cout << e.what();
}
```

### Test 5: Décrémenter au minimum

```cpp
try {
    Bureaucrat charlie("Charlie", 149);
    charlie.decrementGrade();  // Grade = 150 ✅
    charlie.decrementGrade();  // ❌ Exception
} catch (std::exception& e) {
    std::cout << e.what();
}
```

---

## ⚠️ Pièges à éviter

### 1. Confondre increment et decrement

```cpp
// ❌ MAUVAIS
void incrementGrade() {
    _grade++;  // Grade augmente = devient PIRE !
}

// ✅ BON
void incrementGrade() {
    _grade--;  // Grade diminue = devient MEILLEUR !
}
```

### 2. Oublier de vérifier AVANT de modifier

```cpp
// ❌ MAUVAIS
void incrementGrade() {
    _grade--;
    if (_grade < 1)  // Trop tard ! Déjà modifié !
        throw GradeTooHighException();
}

// ✅ BON
void incrementGrade() {
    if (_grade - 1 < 1)  // Vérifie AVANT
        throw GradeTooHighException();
    _grade--;
}
```

### 3. Oublier throw() dans what()

```cpp
// ❌ MAUVAIS (C++98)
virtual const char* what() const {
    return "Error";
}

// ✅ BON (C++98)
virtual const char* what() const throw() {
    return "Error";
}
```

---

## 🎓 Concepts clés

### Exception

**Lancer une exception :**
```cpp
throw GradeTooHighException();
```

**Attraper une exception :**
```cpp
try {
    // Code qui peut lancer une exception
} catch (std::exception& e) {
    // Gestion de l'erreur
    std::cout << e.what();
}
```

### Hiérarchie des exceptions

```
std::exception (classe de base)
    ↑
    |
GradeTooHighException (notre classe)
```

### const dans les attributs

```cpp
const std::string _name;  // Ne peut pas changer
```

**Conséquence :** doit être initialisé dans la liste d'initialisation :

```cpp
Bureaucrat::Bureaucrat(const std::string& name, int grade)
    : _name(name), _grade(grade) {  // ← Liste d'initialisation
}
```

### Grades : logique inversée

```
1   = Meilleur grade (PDG)
75  = Grade moyen
150 = Pire grade (stagiaire)

incrementGrade() → grade--  (devient meilleur)
decrementGrade() → grade++  (devient pire)
```

---

## 💡 Résumé

### Checklist

- [ ] Attribut `_name` const
- [ ] Attribut `_grade` (1-150)
- [ ] Constructeur avec validation
- [ ] incrementGrade() avec vérification
- [ ] decrementGrade() avec vérification
- [ ] 2 exceptions personnalisées
- [ ] Fonction what() avec throw()
- [ ] Opérateur << pour affichage
- [ ] Forme canonique orthodoxe

### Syntaxe clé

```cpp
throw Exception();              // Lance une exception
try { } catch (Type& e) { }    // Attrape une exception
: public std::exception         // Hérite de std::exception
virtual const char* what() const throw()  // Message d'erreur
const std::string _name         // Attribut constant
```

### Points importants

✅ **Valider dans le constructeur** : empêche la création d'objets invalides
✅ **Vérifier AVANT de modifier** : évite les états incohérents
✅ **increment = grade--** : logique inversée !
✅ **Hériter de std::exception** : standard C++
