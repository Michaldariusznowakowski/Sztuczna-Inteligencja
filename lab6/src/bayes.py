# bayes.py
# Author: Michał Nowakowski

import numpy as np
from sklearn.preprocessing import KBinsDiscretizer
from sklearn.model_selection import train_test_split
from sklearn.base import BaseEstimator, ClassifierMixin
import matplotlib.pyplot as plt

## Config

LICZBA_PRZEDZIALOW = 20

DEBUG = False

####################

SELFPATH = __file__[:__file__.rfind('\\') + 1]

DATA = np.genfromtxt(SELFPATH+'wine.data', delimiter=',')

LABELS = ['Class', 'Alcohol', 'Malic acid', 'Ash', 'Alcalinity of ash', 'Magnesium', 'Total phenols',
            'Flavanoids', 'Nonflavanoid phenols', 'Proanthocyanins', 'Color intensity', 'Hue',
            'OD280/OD315 of diluted wines', 'Proline']
CLASS = DATA[:, 0]
DATA = DATA[:, 1:]


class Bayes(BaseEstimator, ClassifierMixin):
    def __init__(self):
        self.prior = None
        self.likelihood = None
        self.classes = None

    def fit(self, X, y):
        self.classes = np.unique(y)
        self.prior = np.zeros(len(self.classes))
        self.likelihood = np.zeros((len(self.classes), X.shape[1], LICZBA_PRZEDZIALOW))
        for i, c in enumerate(self.classes):
            self.prior[i] = np.sum(y == c) / len(y)
            for j in range(X.shape[1]):
                for k in range(LICZBA_PRZEDZIALOW):
                    self.likelihood[i, j, k] = np.sum((X[:, j] == k) & (y == c)) / np.sum(y == c)

    def predict(self, X):
        y_pred = np.zeros(X.shape[0])
        for i in range(X.shape[0]):
            p = np.zeros(len(self.classes))
            for j, c in enumerate(self.classes):
                p[j] = self.prior[j]
                for k in range(X.shape[1]):
                    p[j] *= self.likelihood[j, k, int(X[i, k])]
            y_pred[i] = self.classes[np.argmax(p)]
        return y_pred

    def clean(self):
        self.prior = None
        self.likelihood = None
        self.classes = None

    def laplace(self, X, y):
        self.classes = np.unique(y)
        self.prior = np.zeros(len(self.classes))
        self.likelihood = np.zeros((len(self.classes), X.shape[1], LICZBA_PRZEDZIALOW))
        for i, c in enumerate(self.classes):
            self.prior[i] = np.sum(y == c) / len(y)
            for j in range(X.shape[1]):
                for k in range(LICZBA_PRZEDZIALOW):
                    self.likelihood[i, j, k] = (np.sum((X[:, j] == k) & (y == c)) + 1) / (np.sum(y == c) + LICZBA_PRZEDZIALOW)

    def accuracy(self, y_true, y_pred):
        acc = np.sum(y_true == y_pred) / len(y_true) * 100
        return round(acc, 2)
    

if DEBUG:
    # plot data
    plt.figure(figsize=(10, 10))
    for i in range(1, 14):
        plt.subplot(5, 3, i)
        plt.scatter(DATA[:, i - 1], CLASS, s=1)
        plt.title(LABELS[i])
    plt.tight_layout()
    plt.show()

# deskrtyzacja
est = KBinsDiscretizer(n_bins=LICZBA_PRZEDZIALOW, encode='ordinal', strategy='uniform')
DATA_D = est.fit_transform(DATA) 
# plot data
if DEBUG:
    plt.figure(figsize=(10, 10))
    for i in range(1, 14):
        plt.subplot(5, 3, i)
        plt.scatter(DATA_D[:, i - 1], CLASS, s=1)
        plt.title(LABELS[i])
    plt.tight_layout()
    plt.show()

# podział na część uczącą i testową
X_train, X_test, y_train, y_test = train_test_split(DATA_D, CLASS, test_size=0.3, random_state=42)

## Bayes 
bayes = Bayes()
bayes.fit(X_train, y_train)
y_pred = bayes.predict(X_test)
print('Bayes accuracy: ', bayes.accuracy(y_test, y_pred) , '%')

## Bayes z wykorzystaniem estymatora Laplace'a
bayes.clean()
bayes.laplace(X_train, y_train)
y_pred = bayes.predict(X_test)
print('Bayes with Laplace accuracy: ', bayes.accuracy(y_test, y_pred), '%')



##################
## Test na danych z iris.data
DATA = np.genfromtxt(SELFPATH+'iris.data', delimiter=',', dtype=str)
CLASS = DATA[:, 4]
# zmiana etykiet na liczby
CLASS[CLASS == 'Iris-setosa'] = 0
CLASS[CLASS == 'Iris-versicolor'] = 1
CLASS[CLASS == 'Iris-virginica'] = 2
CLASS = CLASS.astype(int)

DATA = DATA[:, 1:]
DATA = DATA.astype(float)

# deskrtyzacja
est = KBinsDiscretizer(n_bins=LICZBA_PRZEDZIALOW, encode='ordinal', strategy='uniform')
DATA_D = est.fit_transform(DATA)

# podział na część uczącą i testową
X_train, X_test, y_train, y_test = train_test_split(DATA_D, CLASS, test_size=0.3, random_state=42)

## Bayes
bayes.clean()
bayes.fit(X_train, y_train)
y_pred = bayes.predict(X_test)
print('Bayes accuracy: ', bayes.accuracy(y_test, y_pred) , '%')

## Bayes z wykorzystaniem estymatora Laplace'a
bayes.clean()
bayes.laplace(X_train, y_train)
y_pred = bayes.predict(X_test)
print('Bayes with Laplace accuracy: ', bayes.accuracy(y_test, y_pred) , '%')

