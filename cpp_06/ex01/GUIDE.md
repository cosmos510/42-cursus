# 📚 Exercise 01: Serializer - Sérialisation de pointeurs

## 🎯 Objectif
Convertir un pointeur en entier (serialize) et vice-versa (deserialize)

---

## 🤔 C'est quoi la SÉRIALISATION ?

### Analogie : Le code postal 📮

```
Adresse (pointeur) → Code postal (nombre) → Adresse (pointeur)
0x7fff5fbff8ac     → 140734799804588      → 0x7fff5fbff8ac
```

**Sérialisation = convertir un pointeur en nombre**

---

## 📝 Structure

```cpp
struct Data {
    int value;
    std::string name;
};

class Serializer {
private:
    Serializer();  // Non-instanciable

public:
    static uintptr_t serialize(Data* ptr);
    static Data* deserialize(uintptr_t raw);
};
```

---

## 💻 Implémentation

### serialize()

```cpp
uintptr_t Serializer::serialize(Data* ptr) {
    return reinterpret_cast<uintptr_t>(ptr);
}
```

**reinterpret_cast :**
- Convertit un pointeur en entier
- Réinterprète les bits bruts

### deserialize()

```cpp
Data* Serializer::deserialize(uintptr_t raw) {
    return reinterpret_cast<Data*>(raw);
}
```

---

## 🧪 Test

```cpp
Data data;
data.value = 42;
data.name = "Test";

std::cout << "Original: " << &data << std::endl;

uintptr_t raw = Serializer::serialize(&data);
std::cout << "Serialized: " << raw << std::endl;

Data* ptr = Serializer::deserialize(raw);
std::cout << "Deserialized: " << ptr << std::endl;

std::cout << "Match: " << (&data == ptr ? "YES" : "NO") << std::endl;
// Match: YES
```

---

## 🎓 Concepts : reinterpret_cast

### Qu'est-ce que c'est ?

```cpp
reinterpret_cast<Type>(value)
```

**Réinterprète les bits bruts sans conversion**

### Exemple

```cpp
int* ptr = new int(42);
uintptr_t num = reinterpret_cast<uintptr_t>(ptr);
// Convertit le pointeur en nombre

int* back = reinterpret_cast<int*>(num);
// Reconvertit le nombre en pointeur
```

### uintptr_t

```cpp
#include <stdint.h>

uintptr_t  // Type entier assez grand pour stocker un pointeur
```

---

## ⚠️ Pièges

### 1. Utiliser le mauvais cast

```cpp
// ❌ MAUVAIS
uintptr_t num = static_cast<uintptr_t>(ptr);  // Erreur !

// ✅ BON
uintptr_t num = reinterpret_cast<uintptr_t>(ptr);
```

### 2. Oublier <stdint.h>

```cpp
#include <stdint.h>  // Pour uintptr_t
```

---

## 💡 Résumé

### Checklist
- [ ] Classe non-instanciable
- [ ] serialize() : Data* → uintptr_t
- [ ] deserialize() : uintptr_t → Data*
- [ ] Utilise reinterpret_cast
- [ ] Test : adresse originale == adresse désérialisée

### Points clés
✅ **reinterpret_cast** : réinterprète les bits
✅ **uintptr_t** : type pour stocker un pointeur
✅ **Bidirectionnel** : serialize ↔ deserialize
