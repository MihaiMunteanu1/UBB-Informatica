import math
import random
import numpy as np


def _sigmoid(z):
    return 1 / (1 + math.exp(-z))


def binary_cross_entropy(y_true, y_pred):
    m = len(y_true)
    epsilon = 1e-15
    y_pred = [max(min(p, 1 - epsilon), epsilon) for p in y_pred]
    loss = -1 / m * sum(y_true[i] * math.log(y_pred[i]) + (1 - y_true[i]) * math.log(1 - y_pred[i]) for i in range(m))
    return loss


class LogisticRegressorBinary:
    def __init__(self, alpha=0.01, max_iter=1000, random_state=None):
        self.alpha = alpha
        self.max_iter = max_iter
        self.random_state = random_state
        self.intercept_ = 0.0
        self.coef_ = []
        self.classes_ = [0, 1]

    def _predict_row(self, row):
        z = self.intercept_ + sum(w * x for w, x in zip(self.coef_, row))
        return _sigmoid(z)

    def fit(self, X, y):
        if self.random_state is not None:
            random.seed(self.random_state)

        m = len(X)
        n = len(X[0])
        self.intercept_ = 0.0
        self.coef_ = [0.0] * n

        for iteration in range(self.max_iter):
            predictions = [self._predict_row(row) for row in X]

            # loss = binary_cross_entropy(y, predictions)

            error = [y[i] - predictions[i] for i in range(m)]
            d_intercept = sum(error) / m
            d_coef = [0.0 for _ in range(n)]

            for j in range(n):
                d_coef[j] = sum(error[i] * X[i][j] for i in range(m)) / m

            self.intercept_ += self.alpha * d_intercept
            for j in range(n):
                self.coef_[j] += self.alpha * d_coef[j]

    def predict_proba(self, X):
        return [self._predict_row(row) for row in X]

    def predict(self, X, threshold=0.5):
        return [1 if p >= threshold else 0 for p in self.predict_proba(X)]

    def plain_function(self):
        return f"f(X) = {self.intercept_} + " + " + ".join([f"{w} * x{index}" for index, w in enumerate(self.coef_)])


class LogisticRegressorMultiClass:
    def __init__(self, alpha=0.01, max_iter=1000, random_state=None):
        self.alpha = alpha
        self.max_iter = max_iter
        self.random_state = random_state
        self.classes_ = []
        self.models = {}

    def fit(self, X, y):
        self.classes_ = sorted(set(y))
        for cls in self.classes_:
            y_binary = [1 if label == cls else 0 for label in y]
            model = LogisticRegressorBinary(self.alpha, self.max_iter, self.random_state)
            model.fit(X, y_binary)
            self.models[cls] = model

    def predict_proba(self, X):
        class_probs = {}
        for cls, model in self.models.items():
            class_probs[cls] = model.predict_proba(X)

        return [[class_probs[cls][i] for cls in self.classes_] for i in range(len(X))]

    def predict(self, X):
        probs = self.predict_proba(X)
        return [self.classes_[np.argmax(row)] for row in probs]

    def plain_function(self):
        equations = {}
        for cls, model in self.models.items():
            equations[cls] = model.plain_function()

        return equations