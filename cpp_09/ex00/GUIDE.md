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
- Tri automatique des dates (ordre chronologique)
- Recherche rapide d'une date
- Fonction `lower_bound()` pour trouver la date la plus proche

### 2. lower_bound() - Recherche de Borne Inférieure

**Concept :**
Trouve le premier élément >= à la valeur recherchée

**Exemple :**
```
Database: 2011-01-03, 2011-01-09, 2012-01-11
Recherche: 2011-01-05

lower_bound(2011-01-05) -> pointe sur 2011-01-09
On recule d'un cran (--it) -> 2011-01-03 ✓
```

**Code :**
```cpp
std::map<std::string, float>::iterator it = _data.lower_bound(date);
if (it == _data.end() || it->first != date) {
    if (it != _data.begin())
        --it;  // Date précédente la plus proche
}
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

## Exemple d'Exécution

**input.txt :**
```
date | value
2011-01-03 | 3
2012-01-11 | -1
```

**data.csv :**
```
date,exchange_rate
2011-01-03,0.3
2011-01-09,0.32
```

**Résultat :**
```
2011-01-03 => 3 = 0.9        // 3 × 0.3
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
