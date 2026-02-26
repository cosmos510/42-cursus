# 📚 Exercise 03: Intern - Factory Pattern

## 🎯 Objectif
Créer une classe **Intern** qui peut créer des formulaires dynamiquement

---

## 🤔 C'est quoi un INTERN (Factory) ?

### Analogie : L'usine à formulaires 🏭

```
Tu dis : "Je veux un shrubbery creation"
L'intern : *crée le formulaire*
Tu reçois : Un pointeur vers le formulaire créé
```

**Intern = fabrique de formulaires**

---

## 📝 Structure

```cpp
class Intern {
public:
    Intern();
    Intern(const Intern& other);
    Intern& operator=(const Intern& other);
    ~Intern();
    
    AForm* makeForm(const std::string& formName, const std::string& target);
};
```

---

## 💻 Implémentation

### makeForm() - La fabrique

```cpp
AForm* Intern::makeForm(const std::string& formName, const std::string& target) {
    std::string forms[] = {
        "shrubbery creation",
        "robotomy request",
        "presidential pardon"
    };
    
    for (int i = 0; i < 3; i++) {
        if (formName == forms[i]) {
            std::cout << "Intern creates " << formName << std::endl;
            switch (i) {
                case 0: return new ShrubberyCreationForm(target);
                case 1: return new RobotomyRequestForm(target);
                case 2: return new PresidentialPardonForm(target);
            }
        }
    }
    
    std::cout << "Form " << formName << " doesn't exist" << std::endl;
    return NULL;
}
```

---

## 🧪 Utilisation

```cpp
Intern intern;
Bureaucrat boss("Boss", 1);

AForm* form = intern.makeForm("shrubbery creation", "garden");
if (form) {
    boss.signForm(*form);
    boss.executeForm(*form);
    delete form;  // ⚠️ Ne pas oublier !
}
```

---

## 🎓 Concepts : Factory Pattern

**Avantages :**
- Centralise la création d'objets
- Simplifie le code client
- Facile d'ajouter de nouveaux types

**Exemple :**
```cpp
// Sans factory
if (type == "shrub")
    form = new ShrubberyCreationForm(target);
else if (type == "robot")
    form = new RobotomyRequestForm(target);
// ... répété partout dans le code

// Avec factory
form = intern.makeForm(type, target);  // Simple !
```

---

## ⚠️ Pièges

### 1. Memory leak

```cpp
// ❌ MAUVAIS
AForm* form = intern.makeForm("shrub", "test");
// Oublie de delete !

// ✅ BON
AForm* form = intern.makeForm("shrub", "test");
// ... utilisation ...
delete form;  // Libère !
```

### 2. Nom invalide

```cpp
AForm* form = intern.makeForm("invalid", "test");
if (form == NULL) {  // Vérifie !
    std::cout << "Form creation failed" << std::endl;
}
```

---

## 💡 Résumé

### Checklist
- [ ] makeForm() retourne AForm*
- [ ] Gère 3 types de formulaires
- [ ] Affiche message de création
- [ ] Retourne NULL si nom invalide
- [ ] Tests avec delete

### Points clés
✅ **Factory** : crée des objets dynamiquement
✅ **Retourne NULL** : si nom invalide
✅ **delete** : l'appelant doit libérer la mémoire
