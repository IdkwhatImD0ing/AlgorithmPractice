import numpy as np
from SVM import SVMTrainer


class DualSVMTrainer(SVMTrainer):

    def __init__(self, penalty=1.0, **kwargs):
        super().__init__(**kwargs)
        self.penalty = penalty

        # Initialize model parameters alpha.
        np.random.seed(144)
        self.alpha = np.random.rand(self.num_examples)

    def gradient_descent_step(self, x, y) -> None:
        """
        Perform a single step of gradient update.

        Args:
            x: A matrix of features.
            y: A vector of labels.
        """

        self.alpha = self.alpha - self.learning_rate * self.hinge_loss_derivative(
            x, y)

        for i in range(np.size(self.alpha)):
            if (self.alpha[i] < 0):
                self.alpha[i] = 0
            if (self.alpha[i] > self.c):
                self.alpha[i] = self.c

    def hinge_loss(self, x, y) -> float:
        """
        Calculates the hinge loss given predictions and targets.

        Args:
            pred: Predicted labels.
            target: Ground-truth labels.

        Returns:
            A scalar of loss.
        """
        n = self.num_examples
        sum = 0
        for i in range(n):
            sum += self.alpha[i]
        part_one = -1 * sum

        part_two = 0

        for i in range(n):
            for j in range(n):
                part_two += self.alpha[i] * self.alpha[j] * y[i] * y[j] * x[
                    i].T * x[j]

        part_two = part_two / 2.0

        part_three = 0
        for k in range(n):
            part_three += self.alpha[k] * y[k]

        part_three = self.penalty * (part_three * part_three)

        answer = part_one + part_two + part_three
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

        n = self.num_examples
        deriv = np.zeros(np.size(self.alpha))
        part_one = 0
        for i in range(n):
            part_one = -1
            temp_one = 0
            temp_two = 0
            for j in range(n):
                temp_one += self.alpha[j] * y[i] * y[j] * x[i].T @ x[j]

            for k in range(n):
                temp_two += self.alpha[k] * y[k]

            temp_two *= 2 * self.penalty * y[i]

            part_one += temp_one + temp_two
            deriv[i] = part_one

        return deriv[i]

    def compute_bw(self, x, y):
        """
        Compute weights and bias given model parameter self.alpha, and training data x
        and y.

        Args:
            x: Feature vectors.
            y: Ground-truth labels.

        Returns:
            A vector with the same dimension as theta, or w and b if you choose to
            separate them.
        """

        n = self.num_examples
        w = np.zeros(self.num_features)
        sum = 0

        for k in range(np.size(w)):
            sum = 0
            for i in range(n):
                sum += self.alpha[i] * y[i] * x[i][k]

            w[k] = sum

        sum = 0
        for i in range(n):
            sum += (1 / y[i]) - np.dot(x[i], self.w.T)

        b = sum / (2 * n)
        return w, b

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

        for i in range(self.num_epochs):
            #print(self.theta)
            self.w, self.b = self.compute_bw(x_train, y_train)
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
            self.val_loss_history.append(
                SVMTrainer.hinge_loss(self, hypo_val, y_val))
            hypo_train = self.predict(hypo_train)
            hypo_val = self.predict(hypo_val)
            self.train_acc_history.append(self.accuracy(hypo_train, y_train))
            self.val_acc_history.append(self.accuracy(hypo_val, y_val))
            self.gradient_descent_step(x_train, y_train)
        '''
        print("Predicted")
        print(hypo_train.astype(int))
        print("Target")
        print(y_train)
        print(self.w)
        print(self.b)
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
        self.test_loss = SVMTrainer.hinge_loss(self, hypo_test, y_test)
        hypo_test = self.predict(hypo_test)
        self.test_acc = self.accuracy(hypo_test, y_test)
