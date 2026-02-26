# 📚 Exercise 00: Easy start - Templates de fonctions

## 🎯 Objectif
Créer 3 templates de fonctions : **swap**, **min**, **max**

---

## 🤔 C'est quoi un TEMPLATE ?

### Analogie : Le moule à gâteau 🍰

Imagine que tu veux faire des gâteaux de différentes formes :
- Sans template : tu dois créer un moule pour chaque forme (rond, carré, étoile...)
- Avec template : tu as UN SEUL moule magique qui s'adapte à la forme que tu veux

**Le template = moule magique**
**Le type (int, float, string) = la forme**

### Sans template (répétitif 😫)

```cpp
// Pour int
void swap_int(int& a, int& b) {
    int tmp = a;
    a = b;
    b = tmp;
}

// Pour float
void swap_float(float& a, float& b) {
    float tmp = a;
    a = b;
    b = tmp;
}

// Pour string
void swap_string(std::string& a, std::string& b) {
    std::string tmp = a;
    a = b;
    b = tmp;
}

// 😫 Même code 3 fois ! Répétitif !
```

### Avec template (générique 😊)

```cpp
template<typename T>  // T = type magique
void swap(T& a, T& b) {
    T tmp = a;
    a = b;
    b = tmp;
}

// 😊 UNE SEULE fonction pour TOUS les types !
```

---

## 📝 Ce qu'il faut faire

### Fichiers requis
- `whatever.hpp` : contient les 3 templates
- `main.cpp` : tests
- `Makefile`

### ⚠️ IMPORTANT : Pas de whatever.cpp !

**Les templates DOIVENT être dans le .hpp !**

**Pourquoi ?**

Le compilateur a besoin de VOIR le code complet pour générer les fonctions.

```cpp
// main.cpp
int a = 2, b = 3;
swap(a, b);  // Le compilateur voit : "swap avec int"

// Le compilateur génère automatiquement :
void swap(int& a, int& b) {  // T remplacé par int
    int tmp = a;
    a = b;
    b = tmp;
}
```

Si le code était dans .cpp, le compilateur ne pourrait pas le voir → ❌ Erreur !

---

## 💻 Code détaillé

### 1. swap - Échange deux valeurs

```cpp
template<typename T>
void swap(T& a, T& b) {
    T tmp = a;
    a = b;
    b = tmp;
}
```

**Décortiquons ligne par ligne :**

```cpp
template<typename T>
// "Je suis un template, T est un type générique"
// T peut être int, float, string, ou n'importe quoi
```

```cpp
void swap(T& a, T& b) {
// "Fonction swap qui prend 2 références de type T"
// & = référence (pas de copie, modification directe)
```

```cpp
T tmp = a;
// "Crée une variable temporaire de type T"
// Si T=int → int tmp = a;
// Si T=string → string tmp = a;
```

**Exemple concret :**

```cpp
int x = 5, y = 10;
swap(x, y);

// Le compilateur génère :
void swap(int& a, int& b) {
    int tmp = a;    // tmp = 5
    a = b;          // a = 10
    b = tmp;        // b = 5
}
// Résultat : x=10, y=5
```

### 2. min - Retourne le minimum

```cpp
template<typename T>
T const & min(T const & a, T const & b) {
    return (a < b) ? a : b;
}
```

**Décortiquons :**

```cpp
T const &
// "Retourne une référence constante de type T"
// const = ne peut pas être modifié
// & = référence (pas de copie)
```

```cpp
T const & a, T const & b
// "Prend 2 références constantes de type T"
// On ne copie pas, on ne modifie pas
```

```cpp
return (a < b) ? a : b;
// "Si a < b, retourne a, sinon retourne b"
// Opérateur ternaire : condition ? si_vrai : si_faux
```

**Pourquoi `const &` ?**

```cpp
// ❌ Sans référence (copie)
T min(T a, T b) {
    return (a < b) ? a : b;
}
// Si T = std::string → copie coûteuse !
// "Hello World" copié 2 fois !

// ✅ Avec référence (pas de copie)
T const & min(T const & a, T const & b) {
    return (a < b) ? a : b;
}
// Pas de copie, juste une référence → rapide !
```

**Exemple concret :**

```cpp
int x = 5, y = 10;
std::cout << min(x, y);  // 5

std::string s1 = "apple", s2 = "banana";
std::cout << min(s1, s2);  // "apple" (ordre alphabétique)
```

### 3. max - Retourne le maximum

```cpp
template<typename T>
T const & max(T const & a, T const & b) {
    return (a > b) ? a : b;
}
```

Même principe que min, mais avec `>` au lieu de `<`.

---

## 🧪 Tests et utilisation

### Test avec int

```cpp
int a = 2, b = 3;

::swap(a, b);  // :: pour éviter std::swap
std::cout << "a=" << a << ", b=" << b;  // a=3, b=2

std::cout << ::min(a, b);  // 2
std::cout << ::max(a, b);  // 3
```

### Test avec string

```cpp
std::string s1 = "hello", s2 = "world";

::swap(s1, s2);
std::cout << s1 << " " << s2;  // world hello

std::cout << ::min(s1, s2);  // hello (ordre alphabétique)
std::cout << ::max(s1, s2);  // world
```

### Test avec float

```cpp
float f1 = 3.14f, f2 = 2.71f;

::swap(f1, f2);
std::cout << ::min(f1, f2);  // 2.71
std::cout << ::max(f1, f2);  // 3.14
```

---

## ⚠️ Erreurs courantes

### 1. Oublier `::` devant les fonctions

```cpp
// ❌ MAUVAIS
swap(a, b);  // Conflit avec std::swap
min(a, b);   // Conflit avec std::min

// ✅ BON
::swap(a, b);  // Utilise NOTRE swap
::min(a, b);   // Utilise NOTRE min
```

### 2. Mettre le code dans .cpp

```cpp
// ❌ MAUVAIS
// whatever.hpp
template<typename T>
void swap(T& a, T& b);  // Déclaration

// whatever.cpp
template<typename T>
void swap(T& a, T& b) {  // ❌ NE COMPILE PAS !
    // ...
}

// ✅ BON
// whatever.hpp
template<typename T>
void swap(T& a, T& b) {  // Tout dans le .hpp
    // ...
}
```

### 3. Oublier `const &`

```cpp
// ❌ MAUVAIS (copie)
template<typename T>
T min(T a, T b) {  // Copie a et b !
    return (a < b) ? a : b;
}

// ✅ BON (référence)
template<typename T>
T const & min(T const & a, T const & b) {  // Pas de copie
    return (a < b) ? a : b;
}
```

---

## 🎓 Concepts clés

### Template
```cpp
template<typename T>  // Déclare un template
```
- **T** = type générique (peut être n'importe quoi)
- Le compilateur génère une fonction pour chaque type utilisé

### Référence `&`
```cpp
void swap(T& a, T& b)  // & = référence
```
- Pas de copie
- Modification directe de la variable originale

### Référence constante `const &`
```cpp
T const & min(T const & a, T const & b)
```
- Pas de copie (grâce à `&`)
- Pas de modification (grâce à `const`)
- Optimal pour la lecture

### Opérateur ternaire
```cpp
return (a < b) ? a : b;
// condition ? si_vrai : si_faux
```

---

## 💡 Résumé

### Avantages des templates

✅ **Réutilisable** : une fonction pour tous les types
✅ **Type-safe** : le compilateur vérifie les types
✅ **Pas de copie** : avec `const &`
✅ **Généré à la compilation** : pas de coût à l'exécution

### Syntaxe à retenir

```cpp
template<typename T>     // Déclare un template
T                        // Type générique
T&                       // Référence (modifiable)
T const &                // Référence constante (lecture seule)
::fonction()             // Évite les conflits avec std::
```

### Checklist

- [ ] Tout le code dans .hpp (pas de .cpp)
- [ ] Utiliser `template<typename T>`
- [ ] Utiliser `const &` pour min/max
- [ ] Utiliser `::` devant les fonctions
- [ ] Tester avec int, float, string
- [ ] Vérifier que ça compile avec -std=c++98
