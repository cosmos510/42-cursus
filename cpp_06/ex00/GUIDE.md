# CPP Module 06 - Exercise 00: ScalarConverter

## Objectif
Convertir une string vers char, int, float, double.

## Structure
```cpp
class ScalarConverter {
private:
    ScalarConverter();  // Privé - non-instantiable
public:
    static void convert(const std::string& literal);
};
```

## Types de Littéraux
- Char: 'c'
- Int: 42, -42
- Float: 42.0f, nanf, +inff, -inff
- Double: 42.0, nan, +inf, -inf

## Affichage
- char: 'c' ou impossible ou Non displayable
- int: 42 ou impossible
- float: 42.0f (toujours .0)
- double: 42.0 (toujours .0)

## Exemples
```
./convert 42
char: '*'
int: 42
float: 42.0f
double: 42.0

./convert nan
char: impossible
int: impossible
float: nanf
double: nan
```

## Checklist
- Non-instantiable
- Méthode statique
- Gère nan, inf
- Format .0 pour entiers
- Gestion overflows
