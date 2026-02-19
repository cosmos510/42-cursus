# Guide Pédagogique - Bitcoin Exchange (ex00)

## Concepts Clés

### 1. std::map - Le Conteneur Associatif

**Qu'est-ce que c'est ?**
- Un conteneur qui stocke des paires clé-valeur
- Trié automatiquement par clé
- Recherche en O(log n)

**Dans notre cas :**
```cpp
std::map<std::string, float> _data;
// clé = date (string)    valeur = prix bitcoin (float)
// "2011-01-03" -> 0.3
// "2011-01-09" -> 0.32
```

**Pourquoi std::map ?**

Le problème nécessite 3 choses :

1. **Stocker des paires date/prix**
   - map stocke naturellement des paires
   - Accès rapide : `_data["2011-01-03"]` → 0.3

2. **Dates triées chronologiquement**
   - map trie automatiquement par clé
   - "2011-01-03" < "2011-01-09" < "2012-01-11" ✓

3. **Trouver la date la plus proche (inférieure)**
   - Fonction `lower_bound()` parfaite pour ça
   - Sans map, il faudrait trier + recherche binaire manuelle

**Comparaison avec d'autres conteneurs :**

| Conteneur | Pourquoi PAS adapté ? |
|-----------|----------------------|
| `std::vector<pair>` | Pas trié automatiquement, pas de lower_bound efficace |
| `std::list<pair>` | Pas de recherche rapide, pas de lower_bound |
| `std::set` | Stocke seulement des clés, pas de paires clé-valeur |
| `std::multimap` | Permet des doublons (pas nécessaire ici) |
| **`std::map`** | **Tri auto + paires + lower_bound = parfait !** |

**Exemple concret :**

```cpp
// Chargement de la database
std::map<std::string, float> _data;
_data["2011-01-03"] = 0.3;
_data["2011-01-09"] = 0.32;
_data["2012-01-11"] = 7.1;

// Automatiquement trié :
// "2011-01-03" → 0.3
// "2011-01-09" → 0.32
// "2012-01-11" → 7.1
```

**Pourquoi pas un vector ?**

```cpp
// Avec vector (complexe)
std::vector<std::pair<std::string, float>> v;
v.push_back(make_pair("2011-01-09", 0.32));
v.push_back(make_pair("2011-01-03", 0.3));  // Pas trié!
// Il faut trier manuellement
std::sort(v.begin(), v.end());
// Recherche manuelle avec lower_bound
auto it = std::lower_bound(v.begin(), v.end(), date, comparator);
// Besoin d'un comparateur custom!

// Avec map (simple)
std::map<std::string, float> m;
m["2011-01-09"] = 0.32;
m["2011-01-03"] = 0.3;  // Trié automatiquement!
// Recherche directe
auto it = m.lower_bound(date);  // C'est tout!
```

**Les avantages de map :**
- Tri automatique (pas besoin de std::sort)
- lower_bound intégré (pas besoin de comparateur)
- Syntaxe claire : `map[date] = price`
- Pas de doublons (une date = un prix)

### 2. lower_bound() - Recherche de Borne Inférieure

**Concept :**
Trouve le premier élément >= à la valeur recherchée

**Exemple visuel :**
```
Database (map triée automatiquement):
  "2011-01-03" → 0.3
  "2011-01-09" → 0.32
  "2012-01-11" → 7.1

Recherche: "2011-01-05"

lower_bound("2011-01-05") pointe sur "2011-01-09"
                                      ↑
                                      Premier élément >= "2011-01-05"

Mais on veut la date AVANT (inférieure):
  --it → pointe sur "2011-01-03" ✓
```

**Processus détaillé :**

```cpp
std::map<std::string, float>::iterator it = _data.lower_bound("2011-01-05");

// Cas 1: Date exacte trouvée
if (it != _data.end() && it->first == "2011-01-05") {
    // Utiliser directement it->second
}

// Cas 2: Date pas trouvée, prendre la précédente
else {
    if (it == _data.begin()) {
        // Aucune date avant! Erreur
    } else {
        --it;  // Reculer d'un cran
        // it pointe maintenant sur la date inférieure la plus proche
    }
}
```

**Exemple complet avec toutes les dates :**

```
┌────────────────────────────────────────────────────────────────────────────────┐
│ Date recherchée | lower_bound pointe sur | Après --it      | Prix utilisé | Pourquoi ? │
├────────────────┼────────────────────────┼─────────────────┼──────────────┼────────────────────────────────┤
│ 2011-01-03      | 2011-01-03             | (pas besoin)    | 0.3          | Date exacte  │
│ 2011-01-05      | 2011-01-09             | 2011-01-03      | 0.3          | Date avant   │
│ 2011-01-09      | 2011-01-09             | (pas besoin)    | 0.32         | Date exacte  │
│ 2011-12-31      | 2012-01-11             | 2011-01-09      | 0.32         | Date avant   │
│ 2012-01-11      | 2012-01-11             | (pas besoin)    | 7.1          | Date exacte  │
│ 2020-01-01      | end()                  | 2012-01-11      | 7.1          | Dernière date│
│ 2010-01-01      | 2011-01-03             | begin() = ERROR | -            | Avant tout   │
└────────────────┴────────────────────────┴─────────────────┴──────────────┴────────────────────────────────┘
```

**Code détaillé pour "2011-01-05" :**

```cpp
// Database:
// "2011-01-03" → 0.3
// "2011-01-09" → 0.32
// "2012-01-11" → 7.1

std::string date = "2011-01-05";
float value = 3.0;

// Étape 1: Chercher avec lower_bound
std::map<std::string, float>::iterator it = _data.lower_bound("2011-01-05");
// it pointe sur "2011-01-09" (premier >= "2011-01-05")

// Étape 2: Vérifier si c'est la date exacte
if (it == _data.end() || it->first != "2011-01-05") {
    // Pas la date exacte
    
    // Étape 3: Vérifier qu'on peut reculer
    if (it == _data.begin()) {
        // Erreur: aucune date avant!
        std::cerr << "Error: no data available" << std::endl;
        continue;
    }
    
    // Étape 4: Reculer d'un cran
    --it;
    // it pointe maintenant sur "2011-01-03"
}

// Étape 5: Calculer et afficher
float rate = it->second;  // rate = 0.3
float result = value * rate;  // result = 3.0 * 0.3 = 0.9
std::cout << "2011-01-05 => 3 = 0.9" << std::endl;
```

**Visualisation de l'arbre (map interne) :**

```
         "2011-01-09" (0.32)
         /              \
"2011-01-03" (0.3)    "2012-01-11" (7.1)

Recherche "2011-01-05":
  1. Compare avec racine "2011-01-09"
     "2011-01-05" < "2011-01-09" → aller à gauche
  2. Trouve "2011-01-03"
     "2011-01-05" > "2011-01-03" → pas de fils droit
  3. lower_bound retourne "2011-01-09" (premier >=)
  4. On recule (--it) pour avoir "2011-01-03"
```

**Pourquoi lower_bound et pas find ?**

```cpp
// find() cherche la date EXACTE
auto it = _data.find("2011-01-05");
if (it == _data.end()) {
    // Pas trouvé! Il faut chercher manuellement la date avant
    // Compliqué!
}

// lower_bound() trouve la date >= et on recule
auto it = _data.lower_bound("2011-01-05");
if (it != _data.begin())
    --it;  // Simple!
```

### 3. Parsing de Fichiers CSV

**Format CSV (data.csv) :**
```
date,exchange_rate
2011-01-03,0.3
2011-01-09,0.32
```

**Parsing :**
```cpp
size_t pos = line.find(',');           // Trouve la virgule
string date = line.substr(0, pos);     // Avant la virgule
string value = line.substr(pos + 1);   // Après la virgule
```

### 4. Validation de Dates

**Format attendu : YYYY-MM-DD**

**Vérifications :**
1. Longueur = 10 caractères
2. Tirets aux positions 4 et 7
3. Tous les autres caractères sont des chiffres
4. Mois entre 1-12
5. Jour entre 1-31 (selon le mois)

```cpp
if (date.length() != 10 || date[4] != '-' || date[7] != '-')
    return false;
```

### 5. Validation de Valeurs

**Règles :**
- Doit être un nombre (float ou int)
- Doit être positif (>= 0)
- Doit être <= 1000

**Conversion sécurisée :**
```cpp
char* end;
float value = strtof(str.c_str(), &end);
if (*end != '\0')  // Il reste des caractères non convertis
    valid = false;
```

### 6. Gestion d'Erreurs

**Types d'erreurs :**
```
Error: could not open file.          // Fichier inexistant
Error: bad input => 2001-42-42       // Date invalide
Error: not a positive number.        // Valeur négative
Error: too large a number.           // Valeur > 1000
```

## Architecture du Programme

```
main.cpp
  ↓
BitcoinExchange::loadDatabase("data.csv")
  → Charge toutes les dates/prix dans std::map
  ↓
BitcoinExchange::processInput("input.txt")
  → Pour chaque ligne:
    1. Parse date | valeur
    2. Valide date
    3. Valide valeur
    4. Cherche prix avec lower_bound()
    5. Calcule: valeur × prix
    6. Affiche résultat
```

## Exemple d'Exécution Détaillé

**input.txt :**
```
date | value
2011-01-03 | 3
2011-01-05 | 2
2012-01-11 | -1
```

**data.csv :**
```
date,exchange_rate
2011-01-03,0.3
2011-01-09,0.32
2012-01-11,7.1
```

**Processus complet :**

```
┌──────────────────────────────────────────────────────────────────────────────────────┐
│ ÉTAPE 1: Chargement de la database (loadDatabase)                                   │
├──────────────────────────────────────────────────────────────────────────────────────┤
│ Ligne CSV              | Parsing                    | Map après insertion          │
├────────────────────────┼────────────────────────────┼──────────────────────────────┤
│ 2011-01-03,0.3         | date="2011-01-03", rate=0.3 | ["2011-01-03" → 0.3]         │
│ 2011-01-09,0.32        | date="2011-01-09", rate=0.32| ["2011-01-03" → 0.3]         │
│                        |                            | ["2011-01-09" → 0.32]        │
│ 2012-01-11,7.1         | date="2012-01-11", rate=7.1 | ["2011-01-03" → 0.3]         │
│                        |                            | ["2011-01-09" → 0.32]        │
│                        |                            | ["2012-01-11" → 7.1]         │
└────────────────────────┴────────────────────────────┴──────────────────────────────┘

┌──────────────────────────────────────────────────────────────────────────────────────┐
│ ÉTAPE 2: Traitement de l'input (processInput)                                       │
├──────────────────────────────────────────────────────────────────────────────────────┤
│ Ligne 1: "2011-01-03 | 3"                                                           │
├──────────────────────────────────────────────────────────────────────────────────────┤
│   1. Parsing: date="2011-01-03", value=3                                            │
│   2. Validation date: OK                                                             │
│   3. Validation value: OK (0 <= 3 <= 1000)                                          │
│   4. lower_bound("2011-01-03") → trouve "2011-01-03" (date exacte)                 │
│   5. rate = 0.3                                                                      │
│   6. result = 3 * 0.3 = 0.9                                                         │
│   7. Output: "2011-01-03 => 3 = 0.9"                                                │
├──────────────────────────────────────────────────────────────────────────────────────┤
│ Ligne 2: "2011-01-05 | 2"                                                           │
├──────────────────────────────────────────────────────────────────────────────────────┤
│   1. Parsing: date="2011-01-05", value=2                                            │
│   2. Validation date: OK                                                             │
│   3. Validation value: OK (0 <= 2 <= 1000)                                          │
│   4. lower_bound("2011-01-05") → trouve "2011-01-09" (premier >=)                  │
│   5. "2011-01-09" != "2011-01-05" → pas date exacte                                │
│   6. --it → recule à "2011-01-03"                                                   │
│   7. rate = 0.3                                                                      │
│   8. result = 2 * 0.3 = 0.6                                                         │
│   9. Output: "2011-01-05 => 2 = 0.6"                                                │
├──────────────────────────────────────────────────────────────────────────────────────┤
│ Ligne 3: "2012-01-11 | -1"                                                          │
├──────────────────────────────────────────────────────────────────────────────────────┤
│   1. Parsing: date="2012-01-11", value=-1                                           │
│   2. Validation date: OK                                                             │
│   3. Validation value: ERREUR (value < 0)                                           │
│   4. Output: "Error: not a positive number."                                        │
└──────────────────────────────────────────────────────────────────────────────────────┘

Résultat final:
2011-01-03 => 3 = 0.9
2011-01-05 => 2 = 0.6
Error: not a positive number.
```

## Points Importants

1. **std::map trie automatiquement** - Pas besoin de trier manuellement
2. **lower_bound() est efficace** - O(log n) au lieu de parcourir tout le map
3. **Trim les espaces** - "2011-01-03 " doit devenir "2011-01-03"
4. **Gestion des itérateurs** - Vérifier begin() et end() avant de décrémenter
5. **C++98** - Pas de C++11 features (auto, nullptr, etc.)

## Pièges à Éviter

❌ **Ne pas vérifier les itérateurs**
```cpp
--it;  // DANGER si it == begin()
```

✓ **Toujours vérifier**
```cpp
if (it != _data.begin())
    --it;
```

❌ **Oublier de trim les espaces**
```cpp
"2011-01-03 " != "2011-01-03"  // Différent !
```

✓ **Nettoyer les espaces**
```cpp
while (!date.empty() && date[date.length() - 1] == ' ')
    date.erase(date.length() - 1);
```

## Compilation et Test

```bash
make
./btc input.txt
```

## Ressources

- `man std::map`
- `man std::lower_bound`
- cppreference.com/w/cpp/container/map
