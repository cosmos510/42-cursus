# 📚 Exercise 01: Form - Signature de formulaires

## 🎯 Objectif
Créer une classe **Form** que les bureaucrates peuvent **signer**

---

## 🤔 C'est quoi un FORM ?

### Analogie : Le document administratif 📄

Imagine un formulaire administratif :
- Il a un **nom** (ex: "Demande de congés")
- Il peut être **signé** ou **non signé**
- Il faut un **grade minimum** pour le signer
- Il faut un **grade minimum** pour l'exécuter

**Form = document avec des permissions**

### Exemple concret

```
Formulaire : "Demande de congés"
Grade pour signer : 50
Grade pour exécuter : 25
État : Non signé

Bob (grade 30) essaie de signer → ❌ Grade trop bas !
Alice (grade 10) essaie de signer → ✅ OK, formulaire signé !
```

---

## 📝 Ce qu'il faut faire

### Fichiers requis
- `Bureaucrat.hpp` / `Bureaucrat.cpp` : classe Bureaucrat (ex00)
- `Form.hpp` / `Form.cpp` : nouvelle classe Form
- `main.cpp` : tests
- `Makefile`

### Structure de la classe Form

```cpp
class Form {
private:
    const std::string _name;        // Nom du formulaire
    bool _signed;                   // Signé ou non
    const int _gradeToSign;         // Grade requis pour signer
    const int _gradeToExecute;      // Grade requis pour exécuter

public:
    Form(const std::string& name, int gradeToSign, int gradeToExecute);
    
    void beSigned(const Bureaucrat& bureaucrat);  // Signer le formulaire
    
    class GradeTooHighException : public std::exception {};
    class GradeTooLowException : public std::exception {};
};
```

---

## 💻 Implémentation détaillée

### 1. Attributs

```cpp
private:
    const std::string _name;        // Nom (constant)
    bool _signed;                   // État de signature
    const int _gradeToSign;         // Grade min pour signer (constant)
    const int _gradeToExecute;      // Grade min pour exécuter (constant)
```

**Pourquoi const ?**
- Le nom ne change pas
- Les grades requis ne changent pas
- Seul `_signed` peut changer (false → true)

### 2. Constructeur avec validation

```cpp
Form::Form(const std::string& name, int gradeToSign, int gradeToExecute)
    : _name(name), _signed(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute) {
    if (gradeToSign < 1 || gradeToExecute < 1)
        throw GradeTooHighException();
    if (gradeToSign > 150 || gradeToExecute > 150)
        throw GradeTooLowException();
}
```

**Décortiquons :**

```cpp
_signed(false)
// Par défaut, le formulaire n'est PAS signé
```

```cpp
if (gradeToSign < 1 || gradeToExecute < 1)
// Vérifie que les grades sont valides (1-150)
```

**Exemple :**

```cpp
Form form("Tax Form", 50, 25);  // ✅ OK
Form invalid("Bad", 0, 50);     // ❌ Exception !
```

### 3. beSigned() - Signer le formulaire

```cpp
void Form::beSigned(const Bureaucrat& bureaucrat) {
    if (bureaucrat.getGrade() > _gradeToSign)
        throw GradeTooLowException();
    _signed = true;
}
```

**Décortiquons :**

```cpp
if (bureaucrat.getGrade() > _gradeToSign)
// Si le grade du bureaucrate est TROP BAS (nombre trop grand)
// Rappel : grade 1 = meilleur, grade 150 = pire
```

**Exemple concret :**

```cpp
Form form("Contract", 50, 25);  // Besoin de grade ≤ 50 pour signer
Bureaucrat bob("Bob", 75);      // Grade 75 (trop bas)
Bureaucrat alice("Alice", 30);  // Grade 30 (OK)

form.beSigned(bob);    // ❌ Exception ! Grade trop bas
form.beSigned(alice);  // ✅ OK, formulaire signé
```

### 4. Méthode signForm() dans Bureaucrat

**À ajouter dans Bureaucrat.cpp :**

```cpp
void Bureaucrat::signForm(Form& form) {
    try {
        form.beSigned(*this);
        std::cout << _name << " signed " << form.getName() << std::endl;
    } catch (std::exception& e) {
        std::cout << _name << " couldn't sign " << form.getName() 
                  << " because " << e.what() << std::endl;
    }
}
```

**Pourquoi ?**
- Encapsule la logique de signature
- Affiche un message de succès ou d'échec
- Gère l'exception automatiquement

**Utilisation :**

```cpp
Bureaucrat bob("Bob", 75);
Form form("Contract", 50, 25);

bob.signForm(form);
// Affiche : "Bob couldn't sign Contract because Grade is too low!"
```

### 5. Opérateur << (affichage)

```cpp
std::ostream& operator<<(std::ostream& os, const Form& f) {
    os << "Form " << f.getName() 
       << ", signed: " << (f.isSigned() ? "yes" : "no")
       << ", grade to sign: " << f.getGradeToSign()
       << ", grade to execute: " << f.getGradeToExecute();
    return os;
}
```

**Utilisation :**

```cpp
Form form("Tax Form", 50, 25);
std::cout << form << std::endl;
// Affiche : "Form Tax Form, signed: no, grade to sign: 50, grade to execute: 25"
```

---

## 🧪 Tests importants

### Test 1: Création valide

```cpp
try {
    Form form("Contract", 50, 25);
    std::cout << form << std::endl;  // OK
} catch (std::exception& e) {
    std::cout << e.what() << std::endl;
}
```

### Test 2: Grade invalide

```cpp
try {
    Form invalid("Bad", 0, 50);  // ❌ Exception
} catch (std::exception& e) {
    std::cout << e.what();  // "Grade is too high!"
}
```

### Test 3: Signature réussie

```cpp
Bureaucrat alice("Alice", 30);
Form form("Contract", 50, 25);

std::cout << form << std::endl;  // signed: no
alice.signForm(form);            // ✅ Signature OK
std::cout << form << std::endl;  // signed: yes
```

### Test 4: Signature échouée (grade trop bas)

```cpp
Bureaucrat intern("Intern", 100);
Form form("Top Secret", 50, 25);

intern.signForm(form);
// Affiche : "Intern couldn't sign Top Secret because Grade is too low!"
```

### Test 5: Signer un formulaire déjà signé

```cpp
Bureaucrat alice("Alice", 1);
Form form("Document", 50, 25);

alice.signForm(form);  // ✅ Signé
alice.signForm(form);  // ✅ Déjà signé (pas d'erreur)
```

---

## ⚠️ Pièges à éviter

### 1. Confondre > et <

```cpp
// ❌ MAUVAIS
if (bureaucrat.getGrade() < _gradeToSign)
    throw GradeTooLowException();
// Grade 1 < 50 → Exception ! Mais grade 1 est MEILLEUR !

// ✅ BON
if (bureaucrat.getGrade() > _gradeToSign)
    throw GradeTooLowException();
// Grade 100 > 50 → Exception ! Grade trop bas
```

### 2. Oublier d'initialiser _signed à false

```cpp
// ❌ MAUVAIS
Form::Form(...) : _name(name), _gradeToSign(...) {
    // _signed non initialisé !
}

// ✅ BON
Form::Form(...) : _name(name), _signed(false), _gradeToSign(...) {
}
```

### 3. Modifier les attributs const

```cpp
// ❌ IMPOSSIBLE
void Form::setName(const std::string& name) {
    _name = name;  // Erreur ! _name est const
}
```

---

## 🎓 Concepts clés

### Forward declaration

**Dans Form.hpp :**

```cpp
class Bureaucrat;  // Forward declaration

class Form {
    void beSigned(const Bureaucrat& bureaucrat);
};
```

**Pourquoi ?**
- Form utilise Bureaucrat
- Bureaucrat utilise Form
- Dépendance circulaire !

**Solution :**
- Forward declaration dans le .hpp
- Include dans le .cpp

### Logique des grades

```
Grade 1   → Peut signer TOUS les formulaires
Grade 50  → Peut signer les formulaires avec gradeToSign ≥ 50
Grade 150 → Peut signer seulement les formulaires avec gradeToSign = 150
```

**Vérification :**

```cpp
if (bureaucrat.getGrade() > _gradeToSign)
    // Grade du bureaucrate TROP BAS (nombre trop grand)
```

### Attributs const multiples

```cpp
const std::string _name;
const int _gradeToSign;
const int _gradeToExecute;
```

**Tous doivent être initialisés dans la liste d'initialisation :**

```cpp
Form::Form(...)
    : _name(name), _signed(false), _gradeToSign(gs), _gradeToExecute(ge) {
}
```

---

## 💡 Résumé

### Checklist

- [ ] Attributs const (_name, _gradeToSign, _gradeToExecute)
- [ ] Attribut _signed (bool)
- [ ] Constructeur avec validation des grades
- [ ] beSigned() avec vérification du grade
- [ ] Getters pour tous les attributs
- [ ] 2 exceptions personnalisées
- [ ] Opérateur << pour affichage
- [ ] signForm() dans Bureaucrat
- [ ] Forward declaration
- [ ] Forme canonique orthodoxe

### Syntaxe clé

```cpp
class Bureaucrat;                    // Forward declaration
const int _grade;                    // Attribut constant
if (grade > required)                // Grade trop bas
form.beSigned(*this);                // Passer this comme référence
(condition ? "yes" : "no")           // Opérateur ternaire
```

### Points importants

✅ **Grade > required = trop bas** : logique inversée !
✅ **Forward declaration** : évite les dépendances circulaires
✅ **_signed = false** : par défaut non signé
✅ **Valider dans le constructeur** : grades entre 1 et 150
