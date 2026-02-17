# CPP Module 05 - Exercise 03: Intern
## Guide de Compréhension

---

## 📋 Objectif
Créer une classe `Intern` qui peut créer des formulaires dynamiquement avec la méthode `makeForm()`.

---

## 🔄 Changements par rapport à ex02

**Aucun changement dans:**
- ✅ AForm (reste identique)
- ✅ ShrubberyCreationForm (reste identique)
- ✅ RobotomyRequestForm (reste identique)
- ✅ PresidentialPardonForm (reste identique)
- ✅ Bureaucrat (reste identique)

**Ajout:**
- ➕ Classe Intern avec makeForm()

---

## 🏗️ Structure de la Classe Intern

```cpp
class Intern {
public:
    Intern();                              // Default constructor
    Intern(const Intern& other);           // Copy constructor
    Intern& operator=(const Intern& other); // Assignment operator
    ~Intern();                             // Destructor

    AForm* makeForm(const std::string& formName, const std::string& target);
};
```

### Caractéristiques:
- ❌ Pas de nom
- ❌ Pas de grade
- ❌ Pas d'attributs
- ✅ Juste une méthode: `makeForm()`

---

## 🎯 Méthode makeForm()

### Signature
```cpp
AForm* makeForm(const std::string& formName, const std::string& target);
```

### Paramètres
- `formName`: Nom du formulaire à créer
- `target`: Cible du formulaire

### Retour
- Pointeur vers un `AForm*` (polymorphisme)
- `NULL` si le formulaire n'existe pas

### Noms de formulaires acceptés
```cpp
"shrubbery creation"
"robotomy request"
"presidential pardon"
```

---

## 💡 Implémentation (Sans if/else excessif)

### ❌ Mauvaise approche (if/else chain)
```cpp
AForm* Intern::makeForm(const std::string& formName, const std::string& target) {
    if (formName == "shrubbery creation")
        return new ShrubberyCreationForm(target);
    else if (formName == "robotomy request")
        return new RobotomyRequestForm(target);
    else if (formName == "presidential pardon")
        return new PresidentialPardonForm(target);
    else
        return NULL;
}
```
**Problème:** Trop de if/else, pas élégant, difficile à maintenir.

---

### ✅ Bonne approche (Tableaux + Pointeurs de fonction)

```cpp
// Fonctions statiques pour créer les formulaires
static AForm* createShrubbery(const std::string& target) {
    return new ShrubberyCreationForm(target);
}

static AForm* createRobotomy(const std::string& target) {
    return new RobotomyRequestForm(target);
}

static AForm* createPardon(const std::string& target) {
    return new PresidentialPardonForm(target);
}

AForm* Intern::makeForm(const std::string& formName, const std::string& target) {
    // Tableau des noms de formulaires
    std::string formNames[] = {
        "shrubbery creation",
        "robotomy request",
        "presidential pardon"
    };
    
    // Tableau de pointeurs de fonction
    AForm* (*creators[])(const std::string&) = {
        &createShrubbery,
        &createRobotomy,
        &createPardon
    };

    // Boucle pour trouver le bon formulaire
    for (int i = 0; i < 3; i++) {
        if (formName == formNames[i]) {
            std::cout << "Intern creates " << formName << std::endl;
            return creators[i](target);
        }
    }

    // Formulaire non trouvé
    std::cout << "Intern cannot create " << formName << " form: unknown form type" << std::endl;
    return NULL;
}
```

---

## 🎓 Explication des Pointeurs de Fonction

### Qu'est-ce qu'un pointeur de fonction?
```cpp
AForm* (*creator)(const std::string&);
//      ^^         ^^^^^^^^^^^^^^^^^^^^
//      Pointeur   Signature de la fonction
```

### Déclaration d'un tableau de pointeurs de fonction
```cpp
AForm* (*creators[])(const std::string&) = {
    &createShrubbery,
    &createRobotomy,
    &createPardon
};
```

### Appel via pointeur de fonction
```cpp
creators[0](target);  // Appelle createShrubbery(target)
creators[1](target);  // Appelle createRobotomy(target)
creators[2](target);  // Appelle createPardon(target)
```

---

## 🧪 Utilisation

### Exemple 1: Création réussie
```cpp
Intern intern;
AForm* form;

form = intern.makeForm("robotomy request", "Bender");
// Affiche: Intern creates robotomy request
// Retourne: RobotomyRequestForm*

if (form) {
    std::cout << *form << std::endl;
    delete form;
}
```

### Exemple 2: Formulaire inconnu
```cpp
Intern intern;
AForm* form;

form = intern.makeForm("tax evasion", "target");
// Affiche: Intern cannot create tax evasion form: unknown form type
// Retourne: NULL

if (!form) {
    std::cout << "Form creation failed" << std::endl;
}
```

### Exemple 3: Workflow complet
```cpp
Intern intern;
Bureaucrat boss("Boss", 1);

AForm* form = intern.makeForm("presidential pardon", "Arthur Dent");
if (form) {
    boss.signForm(*form);
    boss.executeForm(*form);
    delete form;
}
```

---

## 🎯 Cas de Test Importants

### Test 1: Créer les 3 types de formulaires
```cpp
Intern intern;

AForm* s = intern.makeForm("shrubbery creation", "home");
AForm* r = intern.makeForm("robotomy request", "Bender");
AForm* p = intern.makeForm("presidential pardon", "Arthur");

delete s;
delete r;
delete p;
```

### Test 2: Formulaire invalide
```cpp
Intern intern;
AForm* invalid = intern.makeForm("invalid form", "target");
// Affiche un message d'erreur
// invalid == NULL
```

### Test 3: Utilisation avec bureaucrate
```cpp
Intern intern;
Bureaucrat executor("Executor", 1);

AForm* forms[3];
forms[0] = intern.makeForm("robotomy request", "Target1");
forms[1] = intern.makeForm("shrubbery creation", "Target2");
forms[2] = intern.makeForm("presidential pardon", "Target3");

for (int i = 0; i < 3; i++) {
    if (forms[i]) {
        executor.signForm(*forms[i]);
        executor.executeForm(*forms[i]);
        delete forms[i];
    }
}
```

### Test 4: Gestion mémoire
```cpp
Intern intern;
AForm* form = intern.makeForm("robotomy request", "Bender");

if (form) {
    // Utiliser le formulaire
    std::cout << *form << std::endl;
    
    // IMPORTANT: Libérer la mémoire
    delete form;
}
```

---

## 🔧 Orthodox Canonical Form

### Intern doit respecter l'OCF
```cpp
class Intern {
public:
    Intern();                              // ✅ Default constructor
    Intern(const Intern& other);           // ✅ Copy constructor
    Intern& operator=(const Intern& other); // ✅ Assignment operator
    ~Intern();                             // ✅ Destructor
};
```

### Implémentation minimale
```cpp
Intern::Intern() {}

Intern::Intern(const Intern& other) {
    (void)other;  // Rien à copier
}

Intern& Intern::operator=(const Intern& other) {
    (void)other;  // Rien à assigner
    return *this;
}

Intern::~Intern() {}
```

**Note:** Intern n'a pas d'attributs, donc les fonctions sont vides.

---

## 💾 Gestion de la Mémoire

### ⚠️ IMPORTANT: makeForm() alloue de la mémoire!

```cpp
AForm* form = intern.makeForm("robotomy request", "Bender");
// ↑ Allocation dynamique avec 'new'

// Utiliser le formulaire...

delete form;  // ✅ OBLIGATOIRE: Libérer la mémoire
```

### Exemple avec vérification
```cpp
Intern intern;
AForm* form = intern.makeForm("shrubbery creation", "garden");

if (form) {
    // Utiliser le formulaire
    Bureaucrat bob("Bob", 1);
    bob.signForm(*form);
    bob.executeForm(*form);
    
    // Libérer la mémoire
    delete form;
} else {
    std::cout << "Form creation failed" << std::endl;
}
```

---

## 🎨 Design Pattern: Factory

### Qu'est-ce que le Factory Pattern?

Le pattern Factory permet de créer des objets sans spécifier leur classe exacte.

```
Client (main)
    ↓
Intern::makeForm()  ← Factory
    ↓
ShrubberyCreationForm
RobotomyRequestForm
PresidentialPardonForm
```

### Avantages:
- ✅ Encapsulation de la création
- ✅ Code client simplifié
- ✅ Facile d'ajouter de nouveaux formulaires
- ✅ Polymorphisme (retourne AForm*)

---

## 📊 Comparaison des Approches

| Approche | Avantages | Inconvénients |
|----------|-----------|---------------|
| if/else chain | Simple | Pas élégant, difficile à maintenir |
| switch/case | Lisible | Nécessite enum, pas extensible |
| Pointeurs de fonction | Élégant, maintenable | Plus complexe |
| Map/Dictionary | Très flexible | Interdit (pas de STL avant module 08) |

**Recommandation:** Pointeurs de fonction (tableaux)

---

## 🚨 Erreurs Courantes

### 1. Oublier de delete
```cpp
// ❌ ERREUR: Fuite mémoire
AForm* form = intern.makeForm("robotomy request", "Bender");
// Utiliser form...
// Oubli de delete form;

// ✅ CORRECT
AForm* form = intern.makeForm("robotomy request", "Bender");
// Utiliser form...
delete form;
```

### 2. Ne pas vérifier NULL
```cpp
// ❌ ERREUR: Crash si form == NULL
AForm* form = intern.makeForm("invalid", "target");
form->execute(bureaucrat);  // CRASH!

// ✅ CORRECT
AForm* form = intern.makeForm("invalid", "target");
if (form) {
    form->execute(bureaucrat);
    delete form;
}
```

### 3. Mauvais noms de formulaires
```cpp
// ❌ ERREUR: Majuscules, espaces différents
intern.makeForm("Robotomy Request", "target");
intern.makeForm("robotomy_request", "target");

// ✅ CORRECT: Tout en minuscules, espaces
intern.makeForm("robotomy request", "target");
```

### 4. If/else excessif
```cpp
// ❌ ERREUR: Trop de if/else (rejeté à l'évaluation)
if (formName == "shrubbery creation")
    return new ShrubberyCreationForm(target);
else if (formName == "robotomy request")
    return new RobotomyRequestForm(target);
else if (formName == "presidential pardon")
    return new PresidentialPardonForm(target);

// ✅ CORRECT: Utiliser tableaux + pointeurs de fonction
```

---

## 📝 Checklist de Validation

✅ Intern respecte l'OCF (4 fonctions)  
✅ makeForm() retourne AForm*  
✅ makeForm() accepte les 3 noms de formulaires  
✅ Message "Intern creates <form>" affiché  
✅ Message d'erreur si formulaire inconnu  
✅ Retourne NULL si formulaire inconnu  
✅ Pas de if/else excessif (utilise tableaux)  
✅ Tests avec les 3 types de formulaires  
✅ Test avec formulaire invalide  
✅ Gestion correcte de la mémoire (delete)  
✅ Compilation avec -Wall -Wextra -Werror -std=c++98  
✅ Pas de fuites mémoire  

---

## 🎓 Concepts C++ Utilisés

1. **Factory Pattern** (création d'objets)
2. **Pointeurs de fonction** (tableaux de fonctions)
3. **Polymorphisme** (retourne AForm*)
4. **Allocation dynamique** (new/delete)
5. **Gestion mémoire** (responsabilité du client)
6. **Orthodox Canonical Form**

---

## 💡 Points Clés

### 1. Intern n'a pas d'attributs
```cpp
class Intern {
    // Pas d'attributs privés!
public:
    AForm* makeForm(...);
};
```

### 2. makeForm() est une méthode, pas static
```cpp
Intern intern;
AForm* form = intern.makeForm("robotomy request", "Bender");
//            ^^^^^^ Appel sur un objet
```

### 3. Le client doit delete
```cpp
AForm* form = intern.makeForm(...);
// L'intern crée le formulaire
// Le client est responsable de le delete
delete form;
```

### 4. Noms exacts requis
```
"shrubbery creation"    ← Tout en minuscules, avec espace
"robotomy request"      ← Tout en minuscules, avec espace
"presidential pardon"   ← Tout en minuscules, avec espace
```

---

## 🔗 Récapitulatif des 4 Exercices

| Ex | Classe | Fonctionnalité |
|----|--------|----------------|
| 00 | Bureaucrat | Grades + exceptions |
| 01 | Form | Signature de formulaires |
| 02 | AForm + 3 concrets | Exécution de formulaires |
| 03 | Intern | Création dynamique de formulaires |

---

## 🎯 Exemple Complet

```cpp
int main() {
    // Créer un intern
    Intern someRandomIntern;
    
    // Créer un bureaucrate
    Bureaucrat boss("Boss", 1);
    
    // L'intern crée un formulaire
    AForm* rrf = someRandomIntern.makeForm("robotomy request", "Bender");
    
    if (rrf) {
        // Le bureaucrate signe et exécute
        boss.signForm(*rrf);
        boss.executeForm(*rrf);
        
        // Libérer la mémoire
        delete rrf;
    }
    
    return 0;
}
```

**Output:**
```
Intern creates robotomy request
Boss signed robotomy request
* drilling noises *
Bender has been robotomized successfully
Boss executed robotomy request
```

---

## 🏆 Conseils pour l'Évaluation

1. **Expliquer le Factory Pattern** - Pourquoi c'est utile
2. **Montrer la gestion mémoire** - delete après chaque new
3. **Justifier l'approche sans if/else** - Tableaux + pointeurs de fonction
4. **Tester les cas limites** - Formulaire invalide, NULL check
5. **Vérifier les fuites** - Utiliser valgrind/leaks

---

## 📚 Ressources

- **Factory Pattern**: Design pattern de création
- **Pointeurs de fonction**: Mécanisme C++ avancé
- **Polymorphisme**: Base de l'héritage en C++
- **Gestion mémoire**: new/delete, ownership
