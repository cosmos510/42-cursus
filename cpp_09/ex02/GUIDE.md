# Guide Pédagogique - PmergeMe (ex02)

## Concepts Clés

### 1. Ford-Johnson Algorithm (Vrai Algorithme)

**Qu'est-ce que c'est ?**
- Algorithme de tri par insertion-fusion optimal
- Minimise le nombre de comparaisons
- Utilise des paires, la séquence de Jacobsthal et la recherche binaire

**Les 5 étapes de Ford-Johnson :**

```
1. Créer des PAIRES et trier chaque paire
2. Trier récursivement les paires par leur plus grand élément
3. Créer la chaîne principale (main chain) avec les grands éléments
4. Insérer le premier pendant (petit élément de la première paire)
5. Insérer les autres pendants selon la SÉQUENCE DE JACOBSTHAL
```

### 2. Le Rôle des Paires

**Pourquoi des paires ?**
- Réduit le nombre de comparaisons
- Chaque paire est triée en 1 comparaison
- On trie ensuite les paires par leur plus grand élément

**Exemple :**
```
Input: [5, 2, 8, 1, 9, 3]

Étape 1: Créer des paires
(5, 2) → (5, 2)  // 5 > 2, garder dans cet ordre
(8, 1) → (8, 1)  // 8 > 1
(9, 3) → (9, 3)  // 9 > 3

Format: (grand, petit)
```

### 3. La Séquence de Jacobsthal

**Qu'est-ce que c'est ?**
- Suite mathématique : J(n) = J(n-1) + 2*J(n-2)
- J(0) = 0, J(1) = 1
- Séquence : 0, 1, 1, 3, 5, 11, 21, 43, 85...

**Formule :**
```cpp
J(0) = 0
J(1) = 1
J(n) = J(n-1) + 2*J(n-2)
```

**Pourquoi Jacobsthal ?**
- Ordre optimal d'insertion des pendants
- Minimise le nombre de comparaisons lors de la recherche binaire
- Garantit que chaque insertion nécessite au maximum log₂(k) comparaisons

**Ordre d'insertion :**
```
Pendants: [p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11]

Ordre Jacobsthal:
1. p1  (toujours en premier)
2. p3  (J(3) = 3)
3. p2  (entre J(2) et J(3))
4. p5  (J(4) = 5)
5. p4  (entre J(3) et J(4))
6. p11 (J(5) = 11)
7. p10, p9, p8, p7, p6 (entre J(4) et J(5), ordre décroissant)
```

### 4. Binary Search (Recherche Binaire)

**Pourquoi ?**
- Insertion optimale dans un tableau trié
- O(log n) comparaisons au lieu de O(n)

**Algorithme :**
```cpp
void binaryInsert(vector<int>& arr, int value, size_t end) {
    size_t left = 0, right = end;
    
    // Trouver la position d'insertion
    while (left < right) {
        size_t mid = left + (right - left) / 2;
        if (arr[mid] < value)
            left = mid + 1;
        else
            right = mid;
    }
    
    // Insérer à la position trouvée
    arr.insert(arr.begin() + left, value);
}
```

## Algorithme Ford-Johnson Complet

### Exemple Détaillé : [5, 2, 8, 1, 9, 3, 7]

```
┌─────────────────────────────────────────────────────────────────┐
│ ÉTAPE 1: Créer des paires et trier chaque paire                │
├─────────────────────────────────────────────────────────────────┤
│ Input: [5, 2, 8, 1, 9, 3, 7]                                   │
│                                                                 │
│ Paires:                                                         │
│   (5, 2) → grand=5, petit=2                                    │
│   (8, 1) → grand=8, petit=1                                    │
│   (9, 3) → grand=9, petit=3                                    │
│ Straggler: 7 (élément seul)                                    │
└─────────────────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────────────────┐
│ ÉTAPE 2: Trier les paires par leur grand élément (récursif)    │
├─────────────────────────────────────────────────────────────────┤
│ Grands éléments: [5, 8, 9]                                     │
│ Appel récursif Ford-Johnson sur [5, 8, 9]                     │
│ Résultat: [5, 8, 9] (déjà trié)                               │
└─────────────────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────────────────┐
│ ÉTAPE 3: Créer la chaîne principale (main chain)               │
├─────────────────────────────────────────────────────────────────┤
│ Main chain: [5, 8, 9]                                          │
│ Pendants: [2, 1, 3] (petits éléments correspondants)          │
└─────────────────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────────────────┐
│ ÉTAPE 4: Insérer le premier pendant                            │
├─────────────────────────────────────────────────────────────────┤
│ Insérer p1 = 2 au début                                        │
│ Résultat: [2, 5, 8, 9]                                        │
└─────────────────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────────────────┐
│ ÉTAPE 5: Insérer selon Jacobsthal                              │
├─────────────────────────────────────────────────────────────────┤
│ Jacobsthal(3) = 3                                              │
│ Insérer p3 = 3 avec binary search dans [2, 5, 8, 9]          │
│   → Position: entre 2 et 5                                     │
│ Résultat: [2, 3, 5, 8, 9]                                     │
│                                                                 │
│ Insérer p2 = 1 avec binary search dans [2, 3, 5, 8, 9]       │
│   → Position: au début                                         │
│ Résultat: [1, 2, 3, 5, 8, 9]                                  │
│                                                                 │
│ Insérer straggler = 7 avec binary search                       │
│   → Position: entre 5 et 8                                     │
│ Résultat final: [1, 2, 3, 5, 7, 8, 9]                         │
└─────────────────────────────────────────────────────────────────┘
```

## Visualisation du Code

### Fonction Jacobsthal
```cpp
static size_t jacobsthal(size_t n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    
    size_t a = 0, b = 1;
    for (size_t i = 2; i <= n; i++) {
        size_t tmp = b;
        b = b + 2 * a;  // J(n) = J(n-1) + 2*J(n-2)
        a = tmp;
    }
    return b;
}
```

### Insertion Binaire
```cpp
static void binaryInsert(std::vector<int>& arr, int value, size_t end) {
    size_t left = 0, right = end;
    
    // Recherche binaire de la position
    while (left < right) {
        size_t mid = left + (right - left) / 2;
        if (arr[mid] < value)
            left = mid + 1;  // Chercher à droite
        else
            right = mid;     // Chercher à gauche
    }
    
    // Insérer à la position trouvée
    arr.insert(arr.begin() + left, value);
}
```

## Questions de l'Évaluateur

### Q1: "Expliquez le rôle des paires"
**Réponse :**
- Les paires réduisent le nombre de comparaisons
- Chaque paire est triée en 1 comparaison (grand, petit)
- On trie ensuite les paires par leur grand élément
- Les petits éléments (pendants) sont insérés après selon Jacobsthal

### Q2: "Qu'est-ce que la séquence de Jacobsthal et pourquoi l'utiliser ?"
**Réponse :**
- Suite : 0, 1, 1, 3, 5, 11, 21, 43...
- Formule : J(n) = J(n-1) + 2*J(n-2)
- Ordre optimal d'insertion qui minimise les comparaisons
- Garantit que chaque insertion nécessite au maximum log₂(k) comparaisons

### Q3: "Expliquez la recherche binaire"
**Réponse :**
- Trouve la position d'insertion dans un tableau trié
- Divise l'espace de recherche par 2 à chaque itération
- Complexité O(log n) au lieu de O(n)
- Essentiel pour l'efficacité de Ford-Johnson

## Complexité

**Comparaisons :**
- Ford-Johnson minimise le nombre de comparaisons
- Optimal pour n ≤ 15
- Proche de l'optimal pour n > 15

**Temps :**
- O(n log n) en moyenne
- Meilleur que quicksort en nombre de comparaisons

**Espace :**
- O(n) pour les structures temporaires

## std::vector vs std::deque

**Performance attendue :**
- `vector` : Plus rapide (mémoire contiguë, cache-friendly)
- `deque` : Plus lent (accès indirect, blocs séparés)

**Différence :**
- vector : ~10-30% plus rapide
- deque : Pénalité d'accès indirect

## Tests

```bash
make
./PmergeMe 5 2 8 1 9 3 7
./PmergeMe 3 5 9 7 4
./PmergeMe `seq 1 100 | shuf | tr '\n' ' '`
./PmergeMe `seq 1 3000 | shuf | tr '\n' ' '`
```

## Ressources

- The Art of Computer Programming, Vol. 3 (Knuth)
- Ford-Johnson algorithm (1959)
- Jacobsthal sequence
- Binary insertion sort
