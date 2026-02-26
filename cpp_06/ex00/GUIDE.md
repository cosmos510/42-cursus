# 📚 Exercise 00: ScalarConverter - Conversion de types

## 🎯 Objectif
Convertir un literal (string) en char, int, float, double

---

## 🤔 C'est quoi un SCALAR ?

**Scalar = type simple (char, int, float, double)**

### Exemples de conversions

```
"42"    → char: '*', int: 42, float: 42.0f, double: 42.0
"'a'"   → char: 'a', int: 97, float: 97.0f, double: 97.0
"42.5f" → char: '*', int: 42, float: 42.5f, double: 42.5
"nan"   → char: impossible, int: impossible, float: nanf, double: nan
```

---

## 📝 Structure

```cpp
class ScalarConverter {
private:
    ScalarConverter();  // Constructeur privé
    // Classe non-instanciable !

public:
    static void convert(const std::string& literal);
};
```

**Pourquoi static ?**
- Pas besoin d'objet
- Utilisation : `ScalarConverter::convert("42")`

---

## 💻 Implémentation

### 1. Détecter le type

```cpp
// Char : 'a'
if (literal.length() == 3 && literal[0] == '\'' && literal[2] == '\'')
    // C'est un char

// Float : 42.5f
if (literal[literal.length() - 1] == 'f')
    // C'est un float

// Double : 42.5
if (literal.find('.') != std::string::npos)
    // C'est un double

// Int : 42
// Sinon, c'est un int
```

### 2. Convertir

```cpp
void ScalarConverter::convert(const std::string& literal) {
    double value;
    
    // Détecte et convertit en double
    // ...
    
    // Affiche toutes les conversions
    printChar(value);
    printInt(value);
    printFloat(value);
    printDouble(value);
}
```

### 3. Afficher

```cpp
void printChar(double value) {
    if (std::isnan(value) || std::isinf(value))
        std::cout << "char: impossible" << std::endl;
    else if (value < 0 || value > 127)
        std::cout << "char: impossible" << std::endl;
    else if (!std::isprint(static_cast<char>(value)))
        std::cout << "char: Non displayable" << std::endl;
    else
        std::cout << "char: '" << static_cast<char>(value) << "'" << std::endl;
}
```

---

## 🧪 Tests

```cpp
ScalarConverter::convert("0");
// char: Non displayable
// int: 0
// float: 0.0f
// double: 0.0

ScalarConverter::convert("42");
// char: '*'
// int: 42
// float: 42.0f
// double: 42.0

ScalarConverter::convert("'a'");
// char: 'a'
// int: 97
// float: 97.0f
// double: 97.0

ScalarConverter::convert("nan");
// char: impossible
// int: impossible
// float: nanf
// double: nan
```

---

## 🎓 Concepts : Casts

### static_cast

```cpp
double d = 42.7;
int i = static_cast<int>(d);  // i = 42
char c = static_cast<char>(d);  // c = '*' (ASCII 42)
```

### Valeurs spéciales

```cpp
std::isnan(value)   // Not a Number
std::isinf(value)   // Infinity
std::isprint(c)     // Caractère affichable
```

---

## ⚠️ Pièges

### 1. Oublier les cas spéciaux

```cpp
// nan, +inf, -inf, nanf, +inff, -inff
```

### 2. Caractères non-affichables

```cpp
// ASCII 0-31 et 127 : Non displayable
```

### 3. Overflow

```cpp
// 999999999999 → int: impossible
```

---

## 💡 Résumé

### Checklist
- [ ] Classe non-instanciable (constructeur privé)
- [ ] Méthode static convert()
- [ ] Détecte char, int, float, double
- [ ] Gère nan, inf
- [ ] Gère caractères non-affichables
- [ ] Gère overflow

### Points clés
✅ **static** : pas besoin d'objet
✅ **static_cast** : conversion explicite
✅ **Cas spéciaux** : nan, inf, non-displayable
