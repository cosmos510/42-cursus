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

Le calcul RPN suit naturellement le principe LIFO :

1. **On lit de gauche à droite** → on empile les nombres au fur et à mesure
2. **Quand on voit un opérateur** → on doit utiliser les 2 derniers nombres
3. **Les 2 derniers = sommet de la pile** → LIFO parfait !
4. **Le résultat remplace les 2 nombres** → on empile le résultat

**Comparaison avec d'autres conteneurs :**

| Conteneur | Pourquoi PAS adapté ? |
|-----------|----------------------|
| `std::vector` | Accès par index pas nécessaire, plus complexe |
| `std::deque` | Accès aux 2 bouts pas nécessaire |
| `std::list` | Pas d'accès direct au dernier élément |
| `std::queue` | FIFO (premier entré, premier sorti) = inverse de ce qu'on veut |
| **`std::stack`** | **LIFO = exactement ce qu'il faut !** |

**Exemple concret : "3 4 +"**
```
Étape 1: Lire "3"
  → Empiler 3
  Stack: [3] ← sommet

Étape 2: Lire "4"
  → Empiler 4
  Stack: [3, 4] ← sommet

Étape 3: Lire "+"
  → Dépiler 4 (dernier entré)
  → Dépiler 3 (avant-dernier entré)
  → Calculer 3 + 4 = 7
  → Empiler 7
  Stack: [7] ← sommet

Résultat: 7
```

**Pourquoi pas un tableau/vector ?**
```cpp
// Avec vector (plus complexe)
std::vector<int> v;
v.push_back(3);           // OK
v.push_back(4);           // OK
int b = v[v.size()-1];    // Compliqué
v.pop_back();
int a = v[v.size()-1];    // Compliqué
v.pop_back();
v.push_back(a + b);

// Avec stack (simple)
std::stack<int> s;
s.push(3);                // OK
s.push(4);                // OK
int b = s.top(); s.pop(); // Simple
int a = s.top(); s.pop(); // Simple
s.push(a + b);
```

**La stack cache la complexité :**
- Pas besoin de gérer les indices
- Pas besoin de calculer `size()-1`
- Interface minimale = moins d'erreurs
- Sémantique claire : push/pop/top

### 3. Algorithme RPN - Processus Détaillé

**Principe :**
1. Lire un token (nombre ou opérateur)
2. Si c'est un nombre → empiler
3. Si c'est un opérateur → dépiler 2 nombres, calculer, empiler le résultat
4. À la fin, il reste 1 seul nombre dans la pile = résultat

**Processus Complet : "3 4 + 5 *"**

```
┌───────────────────────────────────────────────────────┐
│ Token | Type      | Action              | Stack (sommet à droite) │
├───────┼───────────┼─────────────────────┼────────────────────────┤
│   3   | Nombre    | push(3)             | [3]                    │
│   4   | Nombre    | push(4)             | [3, 4]                 │
│   +   | Opérateur | pop 4, pop 3        | []                     │
│       |           | calcul: 3 + 4 = 7   |                        │
│       |           | push(7)             | [7]                    │
│   5   | Nombre    | push(5)             | [7, 5]                 │
│   *   | Opérateur | pop 5, pop 7        | []                     │
│       |           | calcul: 7 * 5 = 35  |                        │
│       |           | push(35)            | [35]                   │
└───────┴───────────┴─────────────────────┴────────────────────────┘
Résultat final: 35
```

**Détail du code pour chaque étape :**

```cpp
// Étape 1: Token = "3"
if (isNumber("3")) {              // true
    stack.push(3);                 // Stack: [3]
}

// Étape 2: Token = "4"
if (isNumber("4")) {              // true
    stack.push(4);                 // Stack: [3, 4]
}

// Étape 3: Token = "+"
if (isOperator("+")) {            // true
    applyOperator(stack, '+');
    // Dans applyOperator:
    int b = stack.top();           // b = 4
    stack.pop();                   // Stack: [3]
    int a = stack.top();           // a = 3
    stack.pop();                   // Stack: []
    stack.push(a + b);             // push(7), Stack: [7]
}

// Étape 4: Token = "5"
if (isNumber("5")) {              // true
    stack.push(5);                 // Stack: [7, 5]
}

// Étape 5: Token = "*"
if (isOperator("*")) {            // true
    applyOperator(stack, '*');
    // Dans applyOperator:
    int b = stack.top();           // b = 5
    stack.pop();                   // Stack: [7]
    int a = stack.top();           // a = 7
    stack.pop();                   // Stack: []
    stack.push(a * b);             // push(35), Stack: [35]
}

// Fin: Vérification
if (stack.size() != 1)             // size = 1, OK!
    throw error;
return stack.top();                // return 35
```

**Pourquoi l'ordre a-b et pas b-a ?**

C'est CRUCIAL pour les opérations non-commutatives (- et /) :

```
Expression: "5 3 -"
On veut: 5 - 3 = 2

Stack après push: [5, 3]
                     ↑  ↑
                     a  b (sommet)

Dépilage:
  int b = stack.top(); // b = 3 (deuxième opérande)
  stack.pop();
  int a = stack.top(); // a = 5 (premier opérande)
  stack.pop();
  
Calcul: a - b = 5 - 3 = 2 ✓

Si on faisait b - a:
  b - a = 3 - 5 = -2 ✗ (FAUX!)
```

**Visualisation de la pile (vue de côté) :**

```
Expression: "5 3 -"

Étape 1: push(5)     Étape 2: push(3)     Étape 3: opérateur "-"

    ┌───┐              ┌───┐
    │ 5 │              │ 3 │ ← top (b=3, deuxième)
    └───┘              ├───┤
                         │ 5 │ ← (a=5, premier)
                         └───┘
                         
    pop b=3, pop a=5
    calcul: a - b = 5 - 3 = 2
    push(2)
    
                         ┌───┐
                         │ 2 │ ← résultat
                         └───┘
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

3. Pourquoi std::stack ?

Réponse à donner :

👉 "J'ai choisi std::stack parce que :

LIFO (Last In, First Out) = parfait pour RPN

Empiler les nombres, dépiler pour calculer

Interface simple : push/pop/top

Pourquoi PAS les autres :

❌ std::vector : Accès par index pas nécessaire

❌ std::queue : FIFO (inverse de ce qu'on veut)

❌ std::map : Déjà utilisé en ex00 (interdit)"