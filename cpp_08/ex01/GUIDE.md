# 📚 Exercise 01: Span - Calcul d'écarts

## 🎯 Objectif
Créer une classe **Span** qui stocke N entiers et calcule le plus petit et plus grand écart

---

## 🤔 C'est quoi un SPAN ?

### Analogie : Les notes d'examen 📊

Imagine les notes d'une classe :
- **Span** = ensemble de notes (max N notes)
- **shortestSpan** = plus petite différence entre 2 notes (ex: 15 et 16 → 1)
- **longestSpan** = plus grande différence (ex: 5 et 20 → 15)

---

## 📝 Structure

```cpp
class Span {
private:
    unsigned int _maxSize;
    std::vector<int> _numbers;

public:
    Span(unsigned int n);
    void addNumber(int number);
    template<typename Iterator>
    void addNumber(Iterator begin, Iterator end);
    int shortestSpan() const;
    int longestSpan() const;
};
```

---

## 💻 Implémentation

### addNumber()

```cpp
void Span::addNumber(int number) {
    if (_numbers.size() >= _maxSize)
        throw FullException();
    _numbers.push_back(number);
}
```

### shortestSpan()

```cpp
int Span::shortestSpan() const {
    if (_numbers.size() < 2)
        throw NoSpanException();
    
    std::vector<int> sorted = _numbers;
    std::sort(sorted.begin(), sorted.end());
    
    int minSpan = INT_MAX;
    for (size_t i = 1; i < sorted.size(); i++) {
        int span = sorted[i] - sorted[i - 1];
        if (span < minSpan)
            minSpan = span;
    }
    return minSpan;
}
```

### longestSpan()

```cpp
int Span::longestSpan() const {
    if (_numbers.size() < 2)
        throw NoSpanException();
    
    int min = *std::min_element(_numbers.begin(), _numbers.end());
    int max = *std::max_element(_numbers.begin(), _numbers.end());
    return max - min;
}
```

---

## 🧪 Test

```cpp
Span sp(5);
sp.addNumber(6);
sp.addNumber(3);
sp.addNumber(17);
sp.addNumber(9);
sp.addNumber(11);

std::cout << sp.shortestSpan();  // 2
std::cout << sp.longestSpan();   // 14
```

---

## 💡 Points clés

✅ **vector** : conteneur dynamique
✅ **sort** : pour shortestSpan
✅ **min/max_element** : pour longestSpan
✅ **Template** : pour addNumber avec range
