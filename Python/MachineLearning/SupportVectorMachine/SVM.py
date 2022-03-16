import numpy as np


class SVMTrainer:

    def __init__(
        self,
        num_examples: int,
        num_features: int = 2,
        learning_rate: float = 1e-2,
        num_epochs: int = 500,
        c: float = 0.1,
        penalty: float = 100,
    ) -> None:
        """Initialize a support vector machine trainer."""
        self.c = c
        self.learning_rate = learning_rate
        self.num_epochs = num_epochs
        self.num_examples = num_examples
        self.num_features = num_features

        self.train_loss_history = []
        self.val_loss_history = []
        self.train_acc_history = []
        self.val_acc_history = []
        self.test_loss = None
        self.test_acc = None

        # Initialize weights and bias. Depenending on your approach, you can either
        # initialize w and b separately or theta as a single vector.

        self.w = np.zeros(self.num_features)
        self.b = 0

    def gradient_descent_step(self, x, y) -> None:
        """
        Perform a single step of gradient update.

        Args:
            x: A matrix of features.
            y: A vector of labels.
        """

        alpha = self.learning_rate
        weight, bias = self.hinge_loss_derivative(x, y)
        self.w = self.w - alpha * weight
        self.b = self.b - alpha * bias

    def hinge_loss(self, pred, target) -> float:
        """
        Calculates the hinge loss given predictions and targets.

        Args:
            pred: Predicted labels.
            target: Ground-truth labels.

        Returns:
            A scalar of loss.
        """

        #print(pred)
        #print(target)
        n = np.size(pred)
        answer = 0
        for i in range(n):
            a = 1 / (2 * n)
            b = np.dot(self.w, self.w.T)
            answer += a * b + self.c * max(0, 1 - target[i] *
                                           (pred[i] + self.b))
        #print("answer")
        #print(answer)
        return answer

    def hinge_loss_derivative(self, x, y) -> np.ndarray:
        """
        Calculate the derivative of the loss function w.r.t. theta.

        Args:
            x: Feature vectors.
            y: Ground-truth labels.

        Returns:
            A vector with the same dimension as theta, or w and b if you choose to
            separate them.
        """

        #print(x)
        #print(self.w)
        derivW = np.zeros(self.num_features)
        derivB = 0
        n = self.num_examples
        for j in range(self.num_features):
            for i in range(n):
                condition = 1 - y[i] * (np.dot(x[i], self.w.T) + self.b)
                if (condition > 0):
                    derivW[j] += 1 / n * self.w[j] - self.c * y[i] * x[i][j]
                else:
                    derivW[j] += 1 / n * self.w[j]

        for i in range(n):
            condition = 1 - y[i] * (np.dot(x[i], self.w.T) + self.b)
            if (condition > 0):
                derivB += -1 * self.c * y[i]
            else:
                derivB += 0

        #print(derivW)
        #print(derivB)

        return derivW, derivB

    def accuracy(self, pred, target) -> float:
        """
        Calculates the percentage of matched labels given predictions and targets.

        Args:
            pred: Predicted labels (rounded probabilities).
            target: Ground-truth labels.

        Return:
            The accuracy score (a float) given the predicted labels and the true labels.
        """

        correct = np.sum(pred == target)
        return correct / np.size(pred)

    def predict(self, x) -> int:
        """
        Predict the label of input examples x.

        Args:
            x: Feature vectors.

        Returns:
            A scalar of either -1 or 1.
        """

        answer = np.zeros(np.size(x))
        for i in range(np.size(x)):
            if (x[i] + self.b > 0):
                answer[i] = 1
            else:
                answer[i] = -1
        return answer

    def train(self, x_train, y_train, x_val, y_val) -> None:
        """
        Run gradient descent for n epochs, where n = self.num_epochs. In every epoch,
            1. Update theta.
            2. Calculate the training loss & accuracy given the current theta, and append 
               then to self.train_loss_history and self.train_acc_history.
            3. Calculate the validation loss & accuracy given the current theta, and 
               append then to self.train_loss_history and self.train_acc_history.

        If you wish to use the bias trick, please remember to use it before the for loop.

        Args:
            x_train: Feature vectors for training.
            y_train: Ground-truth labels for training.
            x_val: Feature vectors for validation.
            y_val: Ground-truth labels for validation.
        """

        #print(x_train)
        for i in range(self.num_epochs):
            #print(self.theta)
            hypo_train = np.dot(x_train, self.w)
            hypo_val = np.dot(x_val, self.w)
            #print(hypo_train)
            #print(hypo_val)
            #print(np.size(x_val))
            #print(np.size(y_val))
            '''
            print("Hypo sizes")
            print(hypo_train.shape)
            print(hypo_val.shape)
            print(y_train.shape)
            print(y_val.shape)
            '''
            #print(self.cross_entropy_loss(hypo_train, y_train))
            self.train_loss_history.append(self.hinge_loss(
                hypo_train, y_train))
            self.val_loss_history.append(self.hinge_loss(hypo_val, y_val))
            hypo_train = self.predict(hypo_train)
            hypo_val = self.predict(hypo_val)
            self.train_acc_history.append(self.accuracy(hypo_train, y_train))
            self.val_acc_history.append(self.accuracy(hypo_val, y_val))
            self.gradient_descent_step(x_train, y_train)
        print(self.w)
        print(self.b)
        '''
        print("Predicted")
        print(hypo_train.astype(int))
        print("Target")
        print(y_train)
        '''

    def evaluate(self, x_test, y_test) -> None:
        """
        Evaluate the model on test set and store the test loss int self.test_loss and 
        test accuracy in self.test_acc.

        Args:
            x_test: Feature vectors for testing.
            y_test: Ground-truth labels for testing.
        """

        hypo_test = np.dot(x_test, self.w)
        self.test_loss = self.hinge_loss(hypo_test, y_test)
        hypo_test = self.predict(hypo_test)
        self.test_acc = self.accuracy(hypo_test, y_test)

    def compute_support_vectors(self, x, y) -> np.ndarray:
        """
        Compute support vectors given training data x and y.

        Args:
            x_test: Feature vectors.
            y_test: Ground-truth labels.

        Returns:
            A NumPy array of support vectors.
        """

        sv_idx = []
        sv = []
        offset = 0.05
        for idx, (x_, y_) in enumerate(zip(x, y)):
            if (y_ * (x_ @ self.w + self.b) <= 1 + offset
                    and y_ * (x_ @ self.w + self.b) >= 1 - offset):
                sv_idx.append(idx)
                sv.append(x_)

        print(sv)
        return (np.array(sv_idx), np.array(sv))
