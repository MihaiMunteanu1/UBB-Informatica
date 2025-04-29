import numpy as np

class MyANN:
    def __init__(self, hidden_layer_sizes=(5,), learning_rate=0.001, max_iter=400, random_state=None, verbose=10):
        self.hidden_layer_sizes = hidden_layer_sizes
        self.learning_rate = learning_rate
        self.max_iter = max_iter
        self.random_state = random_state
        self.verbose = verbose
        self.weights = []
        self.biases = []

    def _initialize_parameters(self, input_dim, output_dim):
        layer_dims = [input_dim] + list(self.hidden_layer_sizes) + [output_dim]
        for i in range(1, len(layer_dims)):
            weight = np.random.randn(layer_dims[i - 1], layer_dims[i]) * np.sqrt(2 / layer_dims[i - 1])
            bias = np.zeros((1, layer_dims[i]))
            self.weights.append(weight)
            self.biases.append(bias)

    def _relu(self, Z):
        return np.maximum(0, Z)

    def _relu_derivative(self, Z):
        return (Z > 0).astype(float)

    def _sigmoid(self, Z):
        return 1 / (1 + np.exp(-Z))

    def _sigmoid_derivative(self, Z):
        sig = self._sigmoid(Z)
        return sig * (1 - sig)

    def fit(self, X, y):
        X = np.array(X)
        num_samples, num_features = X.shape
        output_dim = 1

        self._initialize_parameters(num_features, output_dim)
        y = np.array(y).reshape(-1, 1)

        for i in range(self.max_iter):
            # Forward pass
            a = [X]
            for weight, bias in zip(self.weights[:-1], self.biases[:-1]):
                z = np.dot(a[-1], weight) + bias
                a.append(self._relu(z))
            z = np.dot(a[-1], self.weights[-1]) + self.biases[-1]
            a.append(self._sigmoid(z))

            # loss
            loss = -np.mean(y * np.log(a[-1] + 1e-8) + (1 - y) * np.log(1 - a[-1] + 1e-8))

            # Backward pass
            dz = a[-1] - y
            for j in range(len(self.weights) - 1, -1, -1):
                dw = (1 / X.shape[0]) * np.dot(a[j].T, dz)
                db = (1 / X.shape[0]) * np.sum(dz, axis=0, keepdims=True)
                if j > 0:
                    dz = np.dot(dz, self.weights[j].T) * self._relu_derivative(a[j])
                self.weights[j] -= self.learning_rate * dw
                self.biases[j] -= self.learning_rate * db

            if self.verbose and i % 10 == 0:
                print(f"Iteration {i}, loss = {loss:.4f}")

    def predict(self, X):
        a = X
        for weight, bias in zip(self.weights[:-1], self.biases[:-1]):
            z = np.dot(a, weight) + bias
            a = self._relu(z)
        z = np.dot(a, self.weights[-1]) + self.biases[-1]
        a = self._sigmoid(z)
        return (a >= 0.5).astype(int)