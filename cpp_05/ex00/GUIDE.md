# CPP Module 05 - Exercise 00: Bureaucrat
## Guide de Compréhension

---

## 📋 Objectif
Créer une classe `Bureaucrat` avec un système de grades (1 à 150) et des exceptions personnalisées.

---

## 🏗️ Structure de la Classe

### Attributs Privés
```cpp
const std::string _name;  // Nom constant (ne peut pas changer)
int _grade;               // Grade (1 = meilleur, 150 = pire)
```

---

## 🔧 Orthodox Canonical Form (OCF)

### 1. Default Constructor
```cpp
Bureaucrat();
```
- Crée un bureaucrate avec des valeurs par défaut
- Exemple: nom = "Default", grade = 150

### 2. Parametrized Constructor
```cpp
Bureaucrat(const std::string& name, int grade);
```
- Crée un bureaucrate avec nom et grade spécifiques
- **DOIT** vérifier que le grade est entre 1 et 150
- Lance une exception si invalide

### 3. Copy Constructor
```cpp
Bureaucrat(const Bureaucrat& other);
```
- Crée une copie d'un bureaucrate existant
- Copie le nom (const) et le grade

### 4. Copy Assignment Operator
```cpp
Bureaucrat& operator=(const Bureaucrat& other);
```
- Assigne les valeurs d'un bureaucrate à un autre
- **NE PEUT PAS** copier `_name` (const)
- Copie seulement `_grade`
- Retourne `*this` pour permettre les chaînages

### 5. Destructor
```cpp
~Bureaucrat();
```
- Nettoie les ressources (rien à faire ici)

---

## 📖 Getters

### getName()
```cpp
const std::string& getName() const;
```
- Retourne une référence constante au nom
- `const` à la fin = ne modifie pas l'objet

### getGrade()
```cpp
int getGrade() const;
```
- Retourne le grade actuel
- `const` = ne modifie pas l'objet

---

## 🎯 Member Functions

### incrementGrade()
```cpp
void incrementGrade();
```
- **ATTENTION**: Incrémenter = diminuer le nombre (3 → 2)
- Grade 1 est le MEILLEUR
- Si grade = 1, lance `GradeTooHighException`

### decrementGrade()
```cpp
void decrementGrade();
```
- **ATTENTION**: Décrémenter = augmenter le nombre (3 → 4)
- Grade 150 est le PIRE
- Si grade = 150, lance `GradeTooLowException`

---

## ⚠️ Exceptions Personnalisées

### GradeTooHighException
```cpp
class GradeTooHighException : public std::exception {
public:
    virtual const char* what() const throw();
};
```
- Lancée quand grade < 1
- Hérite de `std::exception`
- `what()` retourne un message d'erreur

### GradeTooLowException
```cpp
class GradeTooLowException : public std::exception {
public:
    virtual const char* what() const throw();
};
```
- Lancée quand grade > 150
- Hérite de `std::exception`
- `what()` retourne un message d'erreur

---

## 🖨️ Overload de l'Opérateur <<

```cpp
std::ostream& operator<<(std::ostream& os, const Bureaucrat& b);
```

### Format de sortie:
```
<name>, bureaucrat grade <grade>
```

### Exemple:
```cpp
Bureaucrat bob("Bob", 75);
std::cout << bob << std::endl;
// Affiche: Bob, bureaucrat grade 75
```

### Pourquoi en dehors de la classe?
- L'opérateur << doit avoir `std::ostream` comme premier paramètre
- Ne peut pas être une méthode membre

---

## 🧪 Utilisation et Tests

### Création valide
```cpp
Bureaucrat bob("Bob", 75);
std::cout << bob << std::endl;
// Bob, bureaucrat grade 75
```

### Création invalide (grade trop haut)
```cpp
try {
    Bureaucrat invalid("Invalid", 0);
} catch (std::exception& e) {
    std::cout << e.what() << std::endl;
    // Grade is too high!
}
```

### Création invalide (grade trop bas)
```cpp
try {
    Bureaucrat invalid("Invalid", 151);
} catch (std::exception& e) {
    std::cout << e.what() << std::endl;
    // Grade is too low!
}
```

### Incrémenter le grade
```cpp
Bureaucrat alice("Alice", 3);
std::cout << alice << std::endl;  // Alice, bureaucrat grade 3
alice.incrementGrade();
std::cout << alice << std::endl;  // Alice, bureaucrat grade 2
alice.incrementGrade();
std::cout << alice << std::endl;  // Alice, bureaucrat grade 1
alice.incrementGrade();           // Exception!
```

### Décrémenter le grade
```cpp
Bureaucrat charlie("Charlie", 148);
std::cout << charlie << std::endl;  // Charlie, bureaucrat grade 148
charlie.decrementGrade();
std::cout << charlie << std::endl;  // Charlie, bureaucrat grade 149
charlie.decrementGrade();
std::cout << charlie << std::endl;  // Charlie, bureaucrat grade 150
charlie.decrementGrade();           // Exception!
```

---

## 🎓 Concepts Clés à Comprendre

### 1. Grades inversés
- Grade 1 = MEILLEUR (président)
- Grade 150 = PIRE (stagiaire)
- Incrémenter = améliorer = diminuer le nombre
- Décrémenter = empirer = augmenter le nombre

### 2. Attributs const
- `const std::string _name` ne peut JAMAIS changer
- Initialisé dans la liste d'initialisation du constructeur
- Ne peut pas être réassigné dans l'opérateur d'assignation

### 3. Exceptions
- Utilisées pour gérer les erreurs
- `throw` lance une exception
- `try/catch` attrape les exceptions
- Héritent de `std::exception`

### 4. const correctness
- Méthodes `const` = ne modifient pas l'objet
- Getters doivent être `const`
- Permet d'utiliser avec des objets constants

### 5. Références
- `const std::string&` = référence constante (pas de copie)
- Plus efficace que passer par valeur
- Empêche la modification

---

## 📝 Checklist de Validation

✅ Classe Bureaucrat avec nom constant et grade  
✅ Orthodox Canonical Form complet (4 fonctions + destructeur)  
✅ Getters getName() et getGrade()  
✅ incrementGrade() et decrementGrade()  
✅ Exceptions GradeTooHighException et GradeTooLowException  
✅ Validation des grades dans le constructeur  
✅ Validation des grades dans increment/decrement  
✅ Overload de l'opérateur <<  
✅ Tests complets dans main.cpp  
✅ Compilation avec -Wall -Wextra -Werror -std=c++98  
✅ Pas de fuites mémoire  

---

## 🚨 Erreurs Courantes à Éviter

1. **Confondre increment/decrement**
   - ❌ incrementGrade() fait `_grade++`
   - ✅ incrementGrade() fait `_grade--`

2. **Oublier de valider dans le constructeur**
   - ❌ Créer un bureaucrate avec grade 200
   - ✅ Lancer une exception

3. **Modifier _name dans operator=**
   - ❌ `_name = other._name;` (erreur de compilation)
   - ✅ Ne copier que `_grade`

4. **Oublier const dans les getters**
   - ❌ `int getGrade();`
   - ✅ `int getGrade() const;`

5. **Mauvais format d'affichage**
   - ❌ "Bob grade 75"
   - ✅ "Bob, bureaucrat grade 75"

---

## 💡 Points Bonus

- Les exceptions sont des classes imbriquées (nested classes)
- `throw()` dans `what()` indique qu'elle ne lance pas d'exception
- `virtual` permet le polymorphisme avec std::exception
- L'opérateur << retourne `std::ostream&` pour permettre le chaînage
