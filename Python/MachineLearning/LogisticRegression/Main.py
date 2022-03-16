import wget
#urltrain = 'https://storage.googleapis.com/cse144/train.csv'
#urltest = 'https://storage.googleapis.com/cse144/test.csv'

#train = wget.download(urltrain)
#test = wget.download(urltest)

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from sklearn.linear_model import LogisticRegression
from sklearn.model_selection import train_test_split
from LogisticRegressionTrainer import LogisticRegressionTrainer


def plot_data(x: np.ndarray, y: np.ndarray) -> None:
    """
    Plot a dataset with 2-d feature vectors and binary labels. 

    Args:
        x: 2-d feature vectors
        y: 1-d binary labels.
    """
    class0_idx = np.where(y == 0)[0]
    class1_idx = np.where(y == 1)[0]
    feature0 = x[:, 0]
    feature1 = x[:, 1]
    plt.scatter(feature0[class0_idx], feature1[class0_idx], label="0")
    plt.scatter(feature0[class1_idx], feature1[class1_idx], label="1")
    plt.legend()
    plt.show()


def plot_decision_boundary(theta, x) -> None:
    """
    Plot the decision boundary using theta. Use this function with plot_data().

    Args:
        theta: a 3-d weight vector.
        x: 2-d feature vectors, which is used to decide the span of the decision
           boundary.
    """
    xx = np.linspace(min(x[:, 0]), max(x[:, 0]))
    yy = (-theta[1] / theta[2]) * xx - (theta[0]) / theta[2]
    plt.plot(xx, yy, color="red", label="boundary")
    plt.ylim(min(x[:, 1]), max(x[:, 1]))


# Read datasts and split your training data into train & validation sets. Split
# features from labels after that.

column_names = ["feature1", "feature2", "label"]
dataset = pd.read_csv("train.csv")
train, val = train_test_split(dataset, test_size=0.3, shuffle=True)
y_train = train["label"]
x_train = train.drop("label", axis=1)

y_val = val["label"]
x_val = val.drop("label", axis=1)

testDataset = pd.read_csv("test.csv")
y_test = dataset["label"]
x_test = dataset.drop("label", axis=1)

y_train = y_train.to_numpy()
x_train = x_train.to_numpy()

y_val = y_val.to_numpy()
x_val = x_val.to_numpy()

y_test = y_test.to_numpy()
x_test = x_test.to_numpy()

print(x_train.shape, y_train.shape)
print(x_val.shape, y_val.shape)
print(x_test.shape, y_test.shape)

plot_data(x_train, y_train)
plot_data(x_val, y_val)

# Train a logistic regression classifier
trainer = LogisticRegressionTrainer(dataset.columns.size - 1,
                                    learning_rate=0.01,
                                    num_epochs=5000,
                                    lambd=0)
trainer.train(x_train, y_train, x_val, y_val)

print(f"Final train loss: {trainer.train_loss_history[-1]}")
print(f"Final validation loss: {trainer.val_loss_history[-1]}")
print(f"Final train acc: {trainer.train_acc_history[-1]}")
print(f"Final validation acc: {trainer.val_acc_history[-1]}")

plt.plot(np.arange(trainer.num_epochs),
         trainer.train_loss_history,
         label="Train loss")
plt.plot(np.arange(trainer.num_epochs),
         trainer.val_loss_history,
         label="Val loss")
plt.title("Train & validation loss")
plt.xlabel("Epoch")
plt.ylabel("Loss")
plt.legend()
plt.show()

plt.plot(np.arange(trainer.num_epochs),
         trainer.train_acc_history,
         label="Train acc")
plt.plot(np.arange(trainer.num_epochs),
         trainer.val_acc_history,
         label="Val acc")
plt.title("Train & validation acc")
plt.xlabel("Epoch")
plt.ylabel("Accuracy")
plt.legend()
plt.show()

print(f"My logistic regression weights: {trainer.theta}")
plot_decision_boundary(trainer.theta, x_val)
plot_data(x_val, y_val)

model = LogisticRegression(penalty="l2", n_jobs=-19).fit(x_train, y_train)
print(
    f"Sklearn logisitic regression weights: {np.append(model.intercept_, model.coef_)}"
)
plot_decision_boundary(np.append(model.intercept_, model.coef_), x_val)
plot_data(x_val, y_val)

# Evaluate your model on the test set
trainer.evaluate(x_test, y_test)
print(f"Test loss: {trainer.test_loss}")
print(f"Test acc: {trainer.test_acc}")