# Guide Pédagogique - RPN Calculator (ex01)

## Concepts Clés

### 1. RPN (Reverse Polish Notation)

**Qu'est-ce que c'est ?**
- Notation polonaise inverse
- Les opérateurs viennent APRÈS les opérandes
- Pas besoin de parenthèses

**Exemples :**
```
Notation normale : 3 + 4
RPN              : 3 4 +

Notation normale : (3 + 4) * 5
RPN              : 3 4 + 5 *

Notation normale : 8 * 9 - 9
RPN              : 8 9 * 9 -
```

### 2. std::stack - La Pile LIFO

**Qu'est-ce que c'est ?**
- Last In, First Out (dernier entré, premier sorti)
- Comme une pile d'assiettes

**Opérations principales :**
```cpp
std::stack<int> stack;
stack.push(5);      // Empiler
int x = stack.top(); // Voir le sommet
stack.pop();        // Dépiler
stack.size();       // Taille
```

**Pourquoi std::stack pour RPN ?**
- RPN utilise naturellement une pile
- On empile les nombres
- On dépile pour calculer

### 3. Algorithme RPN

**Principe :**
1. Lire un token (nombre ou opérateur)
2. Si c'est un nombre → empiler
3. Si c'est un opérateur → dépiler 2 nombres, calculer, empiler le résultat
4. À la fin, il reste 1 seul nombre dans la pile = résultat

**Exemple : "3 4 + 5 *"**
```
Token | Action           | Stack
------|------------------|-------
3     | push(3)          | [3]
4     | push(4)          | [3, 4]
+     | pop 4, pop 3     | []
      | push(3+4)        | [7]
5     | push(5)          | [7, 5]
*     | pop 5, pop 7     | []
      | push(7*5)        | [35]
------|------------------|-------
Résultat : 35
```

### 4. Parsing avec istringstream

**Pourquoi istringstream ?**
- Sépare automatiquement par espaces
- Simplifie le parsing

```cpp
std::istringstream iss("3 4 +");
std::string token;
while (iss >> token) {
    // token = "3", puis "4", puis "+"
}
```

### 5. Validation

**Erreurs possibles :**
```
"(1 + 1)"        → Parenthèses interdites
"1 2 + +"        → Pas assez d'opérandes
"1 2"            → Trop d'opérandes (pas d'opérateur)
"1 0 /"          → Division par zéro
"abc"            → Token invalide
"12 3 +"         → Nombre > 9
```

**Vérifications :**
```cpp
// Token valide ?
if (token.length() == 1 && token[0] >= '0' && token[0] <= '9')
    // C'est un chiffre 0-9

// Assez d'opérandes ?
if (stack.size() < 2)
    throw std::runtime_error("Error");

// Résultat unique ?
if (stack.size() != 1)
    throw std::runtime_error("Error");
```

## Exemple Détaillé : "8 9 * 9 - 9 - 9 - 4 - 1 +"

```
Token | Opération        | Stack
------|------------------|------------------
8     | push(8)          | [8]
9     | push(9)          | [8, 9]
*     | 8 * 9 = 72       | [72]
9     | push(9)          | [72, 9]
-     | 72 - 9 = 63      | [63]
9     | push(9)          | [63, 9]
-     | 63 - 9 = 54      | [54]
9     | push(9)          | [54, 9]
-     | 54 - 9 = 45      | [45]
4     | push(4)          | [45, 4]
-     | 45 - 4 = 41      | [41]
1     | push(1)          | [41, 1]
+     | 41 + 1 = 42      | [42]
------|------------------|------------------
Résultat : 42
```

## Architecture du Code

```cpp
int RPN::calculate(const std::string& expression) {
    std::stack<int> stack;
    
    // Pour chaque token
    while (iss >> token) {
        if (est_operateur(token)) {
            // Dépiler 2 nombres
            int b = stack.top(); stack.pop();
            int a = stack.top(); stack.pop();
            // Calculer et empiler
            stack.push(a op b);
        }
        else if (est_nombre(token)) {
            // Empiler le nombre
            stack.push(nombre);
        }
        else {
            // Erreur
        }
    }
    
    // Vérifier qu'il reste 1 seul résultat
    return stack.top();
}
```

## Points Importants

1. **Ordre des opérandes** - `a op b` pas `b op a` !
   ```cpp
   int b = stack.top(); stack.pop();  // Deuxième opérande
   int a = stack.top(); stack.pop();  // Premier opérande
   stack.push(a - b);  // Pas b - a !
   ```

2. **Division par zéro**
   ```cpp
   if (b == 0)
       throw std::runtime_error("Error");
   ```

3. **Validation finale**
   ```cpp
   if (stack.size() != 1)  // Trop ou pas assez de résultats
       throw std::runtime_error("Error");
   ```

## Différence avec ex00

| ex00 (Bitcoin)     | ex01 (RPN)        |
|--------------------|-------------------|
| std::map           | std::stack        |
| Recherche/tri      | LIFO              |
| lower_bound()      | push/pop/top      |
| Paires clé-valeur  | Pile simple       |

## Tests

```bash
make
./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"  # 42
./RPN "7 7 * 7 -"                   # 42
./RPN "1 2 * 2 / 2 * 2 4 - +"      # 0
./RPN "(1 + 1)"                     # Error
./RPN "1 2"                         # Error (pas d'opérateur)
./RPN "1 2 + +"                     # Error (pas assez d'opérandes)
```

## Ressources

- Notation polonaise inverse (Wikipedia)
- std::stack documentation
- cppreference.com/w/cpp/container/stack
