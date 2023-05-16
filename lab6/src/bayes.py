# bayes.py
# Author: Michał Nowakowski

import numpy as np
from sklearn.preprocessing import KBinsDiscretizer
from sklearn.model_selection import train_test_split
from sklearn.base import BaseEstimator, ClassifierMixin


# 1. Wczytaj dane z pobranego pliku tekstowego wine.data do macierzy numpy (wykorzystaj funkcję numpy.genfromtxt)
#  i rozdziel tę macierz na dwie macierze X (o wymiarze
# 178 × 13) i y (178 × 1 — etykiety klas).
DATA = np.genfromtxt('wine.data', delimiter=',')
# 2. Dyskretyzację danych „wine” można wykonać wykorzystując gotowy obiekt
# KBinsDiscretizer (z pakietu sklearn.preprocessing) lub samodzielnie na poziomie opracowywanej 
# klasy NBC (liczba przedziałów, na którą dyskretyzujemy cechy
# oryginalnie ciągłe, powinna być parametrem nastawialnym przez użytkownika).

DISCRETIZER = KBinsDiscretizer(n_bins=3, encode='ordinal', strategy='uniform')

# 3. Podziel dane na część uczącą i testową (wykorzystaj funkcję train_test_split z pakietu sklearn.model_selection).
LEARN_DATA, TEST_DATA = train_test_split(DATA, test_size=0.3, random_state=42)

# 4. Napisz klasę reprezentującą naiwny klasyfikator Bayesa w wariancie ze zmiennymi dyskretnymi. 
# Klasę przygotuj zgodnie z ideą biblioteki scikit-learn — m.in.: wykonaj
# dziedziczenie po klasach BaseEstimator i ClassifierMixin, przygotuj metody fit
# (uczenie) i predict (klasyfikowanie - wskazanie identyfikatora klasy)
# oraz pomocniczo predict_proba (podanie wartości obliczonego prawdopodobieństwa). (Szczegóły
# w kolejnych podrozdziałach).

class NBC(BaseEstimator, ClassifierMixin):
    """Naiwny klasyfikator Bayesa w wariancie ze zmiennymi dyskretnymi."""

    def __init__(self, alpha=1):
        self.alpha = alpha

    def fit(self, X, y):
        """Uczenie."""
        self._classes = np.unique(y)
        self._classes_count = self._classes.size
        self._features_count = X.shape[1]
        self._features_values = [np.unique(X[:, i]) for i in range(self._features_count)]
        self._classes_prob = np.array([np.sum(y == c) / y.size for c in self._classes])
        self._features_prob = np.array([
            np.array([
                np.sum((X[:, i] == v) & (y == c)) / np.sum(y == c) for v in self._features_values[i]
            ]) for i in range(self._features_count)
        ])
        return self

    def predict(self, X):
        """Klasyfikowanie."""
        return np.array([self._classes[np.argmax(self.predict_proba(X)[i, :])] for i in range(X.shape[0])])

    def predict_proba(self, X):
        """Prawdopodobieństwo."""
        return np.array([
            np.array([
                self._classes_prob[c] * np.prod(self._features_prob[i, :, c][self._features_values[i] == X[j, i]])
                for c in range(self._classes_count)
            ]) for i in range(self._features_count)
        ])

# 5. Zastanów się i zaplanuj wg własnego uznania wygodne struktury danych do przechowywania:
# • rozkładu a priori klas P(Y = y),
# • rozkładów warunkowych P(Xj = v|Y = y).
# Mogą to być tablice, słowniki, listy lub odpowiednie połączenia / zagnieżdżenia tych
# struktur. Do tego celu potrzebne będzie także ustalenie dyskretnych dziedzin zmiennych,
#  tj. wykrycie, jakie unikalne wartości poszczególne zmienne mogą przyjmować,
# np. z wykorzystaniem funkcji numpy.unique. Przemyśl, czy informacje o dziedzinach
# należy zdobywać na poziomie funkcji fit na podstawie danych uczących, czy też lepiej
# przekazać je klasyfikatorowi już podczas konstrukcji.

# 6. Wyznacz dokładność (Accuracy =
#NP LZ ∗ 100%, gdzie NP — liczba próbek poprawnie
# sklasyfikowanych w zadanym zbiorze, LZ — liczność zbioru) otrzymanego klasyfikatora
# na zbiorach uczącym i testowym.

def accuracy(y_true, y_pred):
    """Dokładność."""
    return np.sum(y_true == y_pred) / y_true.size

# 7. Obliczenia powtórz uwzględniając poprawkę LaPlace’a (możesz do tego celu 
# wprowadzić przełącznik w konstruktorze Twojej klasy). Powtórz obliczenia - uczenie i pomiary
# dokładności. Zwróć uwagę, czy poprawka LaPlace’a podnosi dokładność testową dla
# tego zbioru danych.