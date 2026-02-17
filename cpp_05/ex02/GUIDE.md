# 📚 Exercise 02: AForm - Classes abstraites et polymorphisme

## 🎯 Objectif
Créer une classe **abstraite** AForm et 3 formulaires concrets qui héritent d'elle

---

## 🤔 C'est quoi une CLASSE ABSTRAITE ?

### Analogie : Le contrat 📜

Imagine un contrat de travail :
- Le **contrat** définit ce que tu DOIS faire (classe abstraite)
- Mais il ne dit PAS COMMENT le faire
- Chaque **employé** fait le travail à sa manière (classes concrètes)

**Classe abstraite = contrat que les classes filles doivent respecter**

### Exemple

```cpp
// Classe abstraite (contrat)
class AForm {
    virtual void executeAction() const = 0;  // ← = 0 rend abstraite
    //                                 ^^^^
    //                                 Fonction virtuelle pure
};

// Classes concrètes (implémentations)
class ShrubberyCreationForm : public AForm {
    void executeAction() const { /* crée un fichier */ }
};

class RobotomyRequestForm : public AForm {
    void executeAction() const { /* fait du bruit */ }
};
```

---

## 📝 Ce qu'il faut faire

### Fichiers requis
- `AForm.hpp` / `AForm.cpp` : classe abstraite
- `ShrubberyCreationForm.hpp` / `.cpp` : crée un fichier avec un arbre ASCII
- `RobotomyRequestForm.hpp` / `.cpp` : robotomise (50% de chance)
- `PresidentialPardonForm.hpp` / `.cpp` : pardonne
- `Bureaucrat.hpp` / `.cpp` : classe Bureaucrat
- `main.cpp` : tests
- `Makefile`

### Structure d'AForm

```cpp
class AForm {
private:
    const std::string _name;
    bool _signed;
    const int _gradeToSign;
    const int _gradeToExecute;

public:
    AForm(const std::string& name, int gradeToSign, int gradeToExecute);
    virtual ~AForm();  // Destructeur virtuel !
    
    void beSigned(const Bureaucrat& bureaucrat);
    void execute(const Bureaucrat& executor) const;
    virtual void executeAction() const = 0;  // Fonction pure
    //                                 ^^^^
    //                                 Rend la classe abstraite
};
```

---

## 💻 Implémentation détaillée

### 1. Fonction virtuelle pure

```cpp
virtual void executeAction() const = 0;
```

**Ce que ça fait :**
- `virtual` = peut être redéfinie dans les classes filles
- `= 0` = fonction **pure** = **DOIT** être implémentée par les classes filles
- Rend la classe **abstraite** = **impossible à instancier**

**Conséquence :**
```cpp
AForm form("test", 1, 1);  // ❌ ERREUR DE COMPILATION !
// "cannot instantiate abstract class"
```

### 2. execute() - Méthode template

```cpp
void AForm::execute(const Bureaucrat& executor) const {
    if (!_signed)
        throw FormNotSignedException();
    if (executor.getGrade() > _gradeToExecute)
        throw GradeTooLowException();
    executeAction();  // ← Appelle la version de la classe fille
}
```

**Flux d'exécution :**
```
1. Vérifie que le formulaire est signé
2. Vérifie que le bureaucrate a le bon grade
3. Appelle executeAction() → polymorphisme !
```

### 3. ShrubberyCreationForm

**Grades :** sign: 145, exec: 137

```cpp
void ShrubberyCreationForm::executeAction() const {
    std::ofstream file((_target + "_shrubbery").c_str());
    if (!file.is_open())
        throw std::runtime_error("Failed to create file");
    file << "       ###\\n";
    file << "      #o###\\n";
    file << "    #####o###\\n";
    // ... arbre ASCII
    file.close();
}
```

**Ce qu'elle fait :**
- Crée un fichier `<target>_shrubbery`
- Écrit un arbre ASCII dedans

### 4. RobotomyRequestForm

**Grades :** sign: 72, exec: 45

```cpp
void RobotomyRequestForm::executeAction() const {
    std::cout << "* drilling noises *" << std::endl;
    if (std::rand() % 2 == 0)
        std::cout << _target << " has been robotomized!" << std::endl;
    else
        std::cout << "Robotomy failed!" << std::endl;
}
```

**Ce qu'elle fait :**
- Fait du bruit
- 50% de chance de réussir la robotomisation

### 5. PresidentialPardonForm

**Grades :** sign: 25, exec: 5

```cpp
void PresidentialPardonForm::executeAction() const {
    std::cout << _target << " has been pardoned by Zaphod Beeblebrox." << std::endl;
}
```

**Ce qu'elle fait :**
- Affiche un message de pardon

---

## 🎓 Concepts clés

### Classe abstraite

**Comment la rendre abstraite :**
```cpp
virtual void fonction() const = 0;  // ← = 0 suffit !
```

**Conséquences :**
- ❌ Impossible de créer un objet de cette classe
- ✅ Peut être utilisée comme pointeur/référence
- ✅ Les classes filles DOIVENT implémenter la fonction pure

### Polymorphisme

```cpp
AForm* forms[3];
forms[0] = new ShrubberyCreationForm("home");
forms[1] = new RobotomyRequestForm("Bender");
forms[2] = new PresidentialPardonForm("Arthur");

for (int i = 0; i < 3; i++) {
    forms[i]->execute(bureaucrat);  // Appelle la bonne version !
    delete forms[i];
}
```

### Destructeur virtuel

```cpp
virtual ~AForm();  // IMPORTANT !
```

**Pourquoi virtuel ?**
```cpp
AForm* form = new ShrubberyCreationForm("test");
delete form;  // Sans virtual → fuite mémoire !
              // Avec virtual → appelle le bon destructeur ✅
```

---

## 🧪 Tests importants

### Test 1: Polymorphisme

```cpp
Bureaucrat boss("Boss", 1);
AForm* forms[3];
forms[0] = new ShrubberyCreationForm("garden");
forms[1] = new RobotomyRequestForm("Target");
forms[2] = new PresidentialPardonForm("Criminal");

for (int i = 0; i < 3; i++) {
    boss.signForm(*forms[i]);
    boss.executeForm(*forms[i]);
    delete forms[i];
}
```

### Test 2: Execute sans signer

```cpp
Bureaucrat bob("Bob", 1);
ShrubberyCreationForm shrub("garden");

try {
    bob.executeForm(shrub);  // ❌ Exception !
} catch (std::exception& e) {
    std::cout << e.what();  // "Form is not signed!"
}
```

### Test 3: Grade trop bas

```cpp
Bureaucrat intern("Intern", 150);
PresidentialPardonForm pardon("Zaphod");

try {
    intern.signForm(pardon);  // ❌ Exception !
} catch (std::exception& e) {
    std::cout << e.what();  // "Grade is too low!"
}
```

---

## ⚠️ Pièges à éviter

### 1. Oublier virtual dans le destructeur

```cpp
// ❌ MAUVAIS
~AForm();  // Pas virtual !

// ✅ BON
virtual ~AForm();  // Virtual !
```

### 2. Oublier d'implémenter executeAction()

```cpp
// ❌ MAUVAIS
class MyForm : public AForm {
    // Oublie d'implémenter executeAction()
};
// → Erreur de compilation !

// ✅ BON
class MyForm : public AForm {
    void executeAction() const {
        // Implémentation
    }
};
```

### 3. Appeler executeAction() directement

```cpp
// ❌ MAUVAIS
form.executeAction();  // Pas de vérifications !

// ✅ BON
form.execute(bureaucrat);  // Vérifie tout avant
```

---

## 💡 Résumé

### Checklist

- [ ] AForm avec fonction virtuelle pure
- [ ] Destructeur virtuel dans AForm
- [ ] 3 classes concrètes qui héritent d'AForm
- [ ] Chaque classe implémente executeAction()
- [ ] execute() vérifie signature et grade
- [ ] executeForm() dans Bureaucrat
- [ ] Tests avec polymorphisme
- [ ] Pas de memory leaks

### Syntaxe clé

```cpp
virtual void func() const = 0;   // Fonction virtuelle pure
virtual ~Class();                // Destructeur virtuel
class Child : public Parent      // Héritage
void func() const override       // Implémentation (C++11, optionnel en C++98)
```

### Points importants

✅ **= 0** : rend la classe abstraite
✅ **virtual ~** : destructeur virtuel obligatoire
✅ **Polymorphisme** : une interface, plusieurs implémentations
✅ **execute()** : vérifie tout avant d'appeler executeAction()
