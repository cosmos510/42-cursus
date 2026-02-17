# CPP Module 05 - Exercise 02: Concrete Forms
## Guide de Compréhension

---

## 📋 Objectif
Créer une classe abstraite `AForm` et 3 formulaires concrets qui peuvent être **exécutés**.

---

## 🔄 Changements par rapport à ex01

### Form → AForm (Abstract Form)
```cpp
class AForm {
    // ...
    virtual void executeAction() const = 0;  // Fonction pure virtuelle
};
```
- Renommer `Form` en `AForm`
- Ajouter `execute()` pour exécuter le formulaire
- Ajouter `executeAction()` pure virtuelle (= 0)
- AForm devient **abstraite** (ne peut pas être instanciée)

---

## 🏗️ Structure de AForm

### Attributs (inchangés)
```cpp
private:
    const std::string _name;
    bool _signed;
    const int _gradeToSign;
    const int _gradeToExecute;
```

### Nouvelles méthodes
```cpp
void execute(const Bureaucrat& executor) const;
virtual void executeAction() const = 0;  // Pure virtuelle
```

### Nouvelle exception
```cpp
class FormNotSignedException : public std::exception {
    virtual const char* what() const throw();
};
```

---

## ⚙️ Méthode execute()

```cpp
void AForm::execute(const Bureaucrat& executor) const {
    if (!_signed)
        throw FormNotSignedException();
    if (executor.getGrade() > _gradeToExecute)
        throw GradeTooLowException();
    executeAction();  // Appelle la fonction virtuelle
}
```

### Vérifications:
1. ✅ Le formulaire est signé
2. ✅ Le grade du bureaucrate est suffisant
3. ✅ Appelle `executeAction()` de la classe dérivée

---

## 📝 Les 3 Formulaires Concrets

### 1. ShrubberyCreationForm
```cpp
class ShrubberyCreationForm : public AForm {
private:
    std::string _target;
public:
    ShrubberyCreationForm(const std::string& target);
    virtual void executeAction() const;
};
```

**Grades:**
- Sign: 145
- Execute: 137

**Action:**
- Crée un fichier `<target>_shrubbery`
- Écrit des arbres ASCII dedans

**Exemple:**
```cpp
ShrubberyCreationForm form("home");
// Crée le fichier: home_shrubbery
```

---

### 2. RobotomyRequestForm
```cpp
class RobotomyRequestForm : public AForm {
private:
    std::string _target;
public:
    RobotomyRequestForm(const std::string& target);
    virtual void executeAction() const;
};
```

**Grades:**
- Sign: 72
- Execute: 45

**Action:**
- Affiche "* drilling noises *"
- 50% de chance: "<target> has been robotomized successfully"
- 50% de chance: "Robotomy failed on <target>"

**Implémentation:**
```cpp
void RobotomyRequestForm::executeAction() const {
    std::cout << "* drilling noises *" << std::endl;
    if (std::rand() % 2)
        std::cout << _target << " has been robotomized successfully" << std::endl;
    else
        std::cout << "Robotomy failed on " << _target << std::endl;
}
```

---

### 3. PresidentialPardonForm
```cpp
class PresidentialPardonForm : public AForm {
private:
    std::string _target;
public:
    PresidentialPardonForm(const std::string& target);
    virtual void executeAction() const;
};
```

**Grades:**
- Sign: 25
- Execute: 5

**Action:**
- Affiche: "<target> has been pardoned by Zaphod Beeblebrox"

**Implémentation:**
```cpp
void PresidentialPardonForm::executeAction() const {
    std::cout << _target << " has been pardoned by Zaphod Beeblebrox" << std::endl;
}
```

---

## 👤 Bureaucrat::executeForm()

```cpp
void Bureaucrat::executeForm(const AForm& form) const {
    try {
        form.execute(*this);
        std::cout << _name << " executed " << form.getName() << std::endl;
    } catch (std::exception& e) {
        std::cout << _name << " couldn't execute " << form.getName() 
                  << " because " << e.what() << std::endl;
    }
}
```

---

## 🎯 Workflow Complet

### 1. Créer un formulaire
```cpp
ShrubberyCreationForm form("garden");
```

### 2. Créer un bureaucrate
```cpp
Bureaucrat bob("Bob", 137);
```

### 3. Signer le formulaire
```cpp
bob.signForm(form);
```

### 4. Exécuter le formulaire
```cpp
bob.executeForm(form);
// Crée le fichier garden_shrubbery
```

---

## 🧪 Cas de Test Importants

### Test 1: Exécution réussie
```cpp
Bureaucrat bob("Bob", 137);
ShrubberyCreationForm form("home");
bob.signForm(form);      // ✅ Grade 137 >= 145
bob.executeForm(form);   // ✅ Grade 137 >= 137
// Fichier home_shrubbery créé
```

### Test 2: Formulaire non signé
```cpp
Bureaucrat bob("Bob", 1);
ShrubberyCreationForm form("home");
bob.executeForm(form);   // ❌ FormNotSignedException
```

### Test 3: Grade insuffisant pour exécuter
```cpp
Bureaucrat intern("Intern", 140);
ShrubberyCreationForm form("home");
Bureaucrat boss("Boss", 1);
boss.signForm(form);     // ✅ Boss peut signer
intern.executeForm(form); // ❌ Grade 140 < 137
```

### Test 4: Grade insuffisant pour signer
```cpp
Bureaucrat intern("Intern", 150);
PresidentialPardonForm form("Arthur");
intern.signForm(form);   // ❌ Grade 150 < 25
```

### Test 5: Robotomy (aléatoire)
```cpp
Bureaucrat bob("Bob", 45);
RobotomyRequestForm form("Bender");
bob.signForm(form);
bob.executeForm(form);   // 50% succès, 50% échec
bob.executeForm(form);   // Peut être différent
```

---

## 🏛️ Architecture (Design Pattern)

### Template Method Pattern
```
AForm::execute()           ← Méthode template (validation)
    ↓
executeAction()            ← Implémentation spécifique
    ↓
ShrubberyCreationForm::executeAction()
RobotomyRequestForm::executeAction()
PresidentialPardonForm::executeAction()
```

**Avantages:**
- Validation centralisée dans `execute()`
- Chaque formulaire implémente seulement son action
- Code réutilisable et maintenable

---

## 📊 Tableau Récapitulatif

| Formulaire              | Grade Sign | Grade Exec | Action                    |
|------------------------|------------|------------|---------------------------|
| ShrubberyCreationForm  | 145        | 137        | Crée fichier avec arbres  |
| RobotomyRequestForm    | 72         | 45         | Robotomise (50% chance)   |
| PresidentialPardonForm | 25         | 5          | Pardonne par Zaphod       |

---

## 🔧 Orthodox Canonical Form

### AForm
✅ Default constructor (peut être protégé)
✅ Copy constructor
✅ Assignment operator
✅ Destructor (virtuel!)

### Formulaires concrets
✅ Parametrized constructor (avec target)
✅ Copy constructor
✅ Assignment operator
✅ Destructor

**Note:** Les formulaires concrets héritent de AForm, donc doivent respecter l'OCF.

---

## 💡 Points Clés

### 1. Classe abstraite
```cpp
virtual void executeAction() const = 0;  // = 0 rend la classe abstraite
```
- Ne peut pas être instanciée
- Doit être héritée

### 2. Destructeur virtuel
```cpp
virtual ~AForm();
```
- **OBLIGATOIRE** pour les classes avec fonctions virtuelles
- Permet la destruction correcte des objets dérivés

### 3. Const correctness
```cpp
void execute(const Bureaucrat& executor) const;
virtual void executeAction() const = 0;
```
- `execute()` et `executeAction()` sont `const`
- Ne modifient pas l'état du formulaire

### 4. Polymorphisme
```cpp
AForm* form = new ShrubberyCreationForm("home");
form->execute(bureaucrat);  // Appelle ShrubberyCreationForm::executeAction()
delete form;
```

---

## 🚨 Erreurs Courantes

### 1. Oublier le destructeur virtuel
```cpp
// ❌ ERREUR
class AForm {
    ~AForm();  // Pas virtuel!
};

// ✅ CORRECT
class AForm {
    virtual ~AForm();
};
```

### 2. Implémenter executeAction() dans AForm
```cpp
// ❌ ERREUR - AForm ne doit pas implémenter executeAction()
void AForm::executeAction() const {
    // ...
}

// ✅ CORRECT - Seulement dans les classes dérivées
void ShrubberyCreationForm::executeAction() const {
    // ...
}
```

### 3. Oublier de vérifier si signé
```cpp
// ❌ ERREUR
void AForm::execute(const Bureaucrat& executor) const {
    if (executor.getGrade() > _gradeToExecute)
        throw GradeTooLowException();
    executeAction();  // Oubli de vérifier _signed!
}

// ✅ CORRECT
void AForm::execute(const Bureaucrat& executor) const {
    if (!_signed)
        throw FormNotSignedException();
    if (executor.getGrade() > _gradeToExecute)
        throw GradeTooLowException();
    executeAction();
}
```

### 4. Mauvais grades dans les constructeurs
```cpp
// ❌ ERREUR
ShrubberyCreationForm::ShrubberyCreationForm(const std::string& target)
    : AForm("ShrubberyCreationForm", 137, 145), _target(target) {}
    // Grades inversés!

// ✅ CORRECT
ShrubberyCreationForm::ShrubberyCreationForm(const std::string& target)
    : AForm("ShrubberyCreationForm", 145, 137), _target(target) {}
    // Sign: 145, Exec: 137
```

---

## 📝 Checklist de Validation

✅ AForm est abstraite (executeAction() = 0)  
✅ AForm a un destructeur virtuel  
✅ execute() vérifie: signé + grade suffisant  
✅ ShrubberyCreationForm crée un fichier  
✅ RobotomyRequestForm a 50% de succès  
✅ PresidentialPardonForm affiche le message  
✅ Bureaucrat::executeForm() implémenté  
✅ Tous les formulaires respectent l'OCF  
✅ Tests complets dans main.cpp  
✅ make fclean supprime les fichiers *_shrubbery  
✅ Compilation avec -Wall -Wextra -Werror -std=c++98  
✅ Pas de fuites mémoire  

---

## 🎓 Concepts C++ Utilisés

1. **Classes abstraites** (pure virtual)
2. **Polymorphisme** (virtual functions)
3. **Héritage** (public inheritance)
4. **Template Method Pattern**
5. **Exception handling**
6. **File I/O** (ofstream)
7. **Random numbers** (rand)
8. **Const correctness**

---

## 🔗 Liens avec les autres exercices

**ex01 → ex02:**
- Form devient AForm (abstraite)
- Ajout de execute() et executeAction()
- Ajout de FormNotSignedException

**ex02 → ex03:**
- Ajout de la classe Intern
- Intern::makeForm() crée les formulaires dynamiquement
- Pas de changement dans AForm ou les formulaires concrets
