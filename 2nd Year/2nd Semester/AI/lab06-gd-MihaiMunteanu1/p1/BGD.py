import numpy as np


class MyBGDRegression:
    def __init__(self, alpha=0.001, max_iter=1000, random_state=None):
        self.intercept_ = 0.0
        self.coef_ = []
        self.alpha = alpha
        self.max_iter = max_iter
        self.random_state = random_state

    def fit(self, X, y):
        if self.random_state is not None:
            np.random.seed(self.random_state)

        X = np.array(X)
        y = np.array(y)

        n_samples = X.shape[0]
        n_features = X.shape[1]
        self.coef_ = np.zeros(n_features)

        for _ in range(self.max_iter):
            y_pred = self.predict(X)
            errors = y - y_pred

            self.coef_ += self.alpha * (2 / n_samples) * np.dot(X.T, errors)
            self.intercept_ += self.alpha * (2 / n_samples) * np.sum(errors)

        return self

    def predict(self, X):
        X = np.array(X)
        return np.dot(X, self.coef_) + self.intercept_