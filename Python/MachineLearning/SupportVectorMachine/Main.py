from tqdm.notebook import trange
import matplotlib.pyplot as plt
import numpy as np
from sklearn.datasets import make_blobs
from sklearn.model_selection import train_test_split
from SVM import SVMTrainer
from DualSVM import DualSVMTrainer


def plot_data(x: np.ndarray, y: np.ndarray) -> None:
    class0_idx = np.where(y == -1)[0]
    class1_idx = np.where(y == 1)[0]
    feature0 = x[:, 0]
    feature1 = x[:, 1]
    plt.scatter(feature0[class0_idx], feature1[class0_idx], label="-1")
    plt.scatter(feature0[class1_idx], feature1[class1_idx], label="1")


def modify_label(label):
    return np.array([-1 if i == 0 else 1 for i in label])


x, y = make_blobs(
    n_samples=200,
    n_features=2,
    centers=2,
    cluster_std=1,
    center_box=(-9, 9),
    random_state=1234,
)

x_train_val, x_test, y_train_val, y_test = train_test_split(x,
                                                            y,
                                                            test_size=0.2,
                                                            random_state=288)
x_train, x_val, y_train, y_val = train_test_split(x_train_val,
                                                  y_train_val,
                                                  test_size=0.2,
                                                  random_state=288)

print(x_train.shape, y_train.shape)
print(x_val.shape, y_val.shape)
print(x_test.shape, y_test.shape)

y_train, y_val, y_test = map(modify_label, [y_train, y_val, y_test])

plot_data(x_train, y_train)
plt.title("Training data")
plt.show()
plot_data(x_val, y_val)
plt.title("Validation data")
plt.show()

svm_trainer = SVMTrainer(num_examples=x_train.shape[0],
                         num_epochs=20,
                         learning_rate=0.01,
                         c=0.1)
svm_trainer.train(x_train, y_train, x_val, y_val)

print(f"Final train loss: {svm_trainer.train_loss_history[-1]}")
print(f"Final validation loss: {svm_trainer.val_loss_history[-1]}")
print(f"Final train acc: {svm_trainer.train_acc_history[-1]}")
print(f"Final validation acc: {svm_trainer.val_acc_history[-1]}")

fig, ax = plt.subplots(1, 2, figsize=(12, 4))
ax[0].plot(np.arange(len(svm_trainer.train_loss_history)),
           svm_trainer.train_loss_history,
           label="Train loss")
ax[0].plot(np.arange(len(svm_trainer.val_loss_history)),
           svm_trainer.val_loss_history,
           label="Val loss")
ax[0].set_title("Train & validation loss")
ax[0].set_xlabel("Epoch")
ax[0].set_ylabel("Loss")
ax[0].legend()

ax[1].plot(np.arange(len(svm_trainer.train_loss_history)),
           svm_trainer.train_acc_history,
           label="Train acc")
ax[1].plot(np.arange(len(svm_trainer.val_loss_history)),
           svm_trainer.val_acc_history,
           label="Val acc")
ax[1].set_title("Train & validation acc")
ax[1].set_xlabel("Epoch")
ax[1].set_ylabel("Accuracy")
ax[1].legend()

plt.show()


def plot_decision_boundary(w, b, x) -> None:
    """
    Plot the decision boundary and margin using w and b. Use this function with 
    plot_data().

    Args:
        w: weights, a vector of length 2.
        b: bias, a scalar.
        x: 2-d feature vectors.
    """
    xx = np.linspace(min(x[:, 0]), max(x[:, 0]))
    yy = (-w[0] / w[1]) * xx - (b) / w[1]

    plt.plot(xx, yy, color="red", label="boundary")
    plt.ylim(min(x[:, 1]), max(x[:, 1]))

    decision_boundary_points = np.array(list(zip(xx, yy)))
    w_hat = w / np.sqrt(np.sum(w**2))
    margin = 1 / np.sqrt(np.sum(w**2))
    new_points_up = decision_boundary_points + w_hat * margin
    new_points_down = decision_boundary_points - w_hat * margin

    plt.plot(new_points_up[:, 0],
             new_points_up[:, 1],
             'r--',
             label="margin",
             linewidth=2)
    plt.plot(new_points_down[:, 0],
             new_points_down[:, 1],
             'r--',
             label="margin",
             linewidth=2)


# Plot the training data along with decision boundary and margin and support vectors

theta = np.append(svm_trainer.b, svm_trainer.w)
plot_decision_boundary(svm_trainer.w, svm_trainer.b, x_train)
plot_data(x_train, y_train)

support_vector_idx, support_vectors = svm_trainer.compute_support_vectors(
    x_train, y_train)
if len(support_vectors > 0):
    plt.scatter(support_vectors[:, 0],
                support_vectors[:, 1],
                facecolors="none",
                edgecolors="k",
                label="sv")

plt.legend()
plt.show()

# Dual SVM Trainer
dualsvm_trainer = DualSVMTrainer(num_examples=x_train.shape[0],
                                 num_epochs=20,
                                 learning_rate=10e-5,
                                 c=0.1)
dualsvm_trainer.train(x_train, y_train, x_val, y_val)

print(f"Final train loss: {dualsvm_trainer.train_loss_history[-1]}")
print(f"Final validation loss: {dualsvm_trainer.val_loss_history[-1]}")
print(f"Final train acc: {dualsvm_trainer.train_acc_history[-1]}")
print(f"Final validation acc: {dualsvm_trainer.val_acc_history[-1]}")

fig, ax = plt.subplots(1, 2, figsize=(12, 4))
ax[0].plot(np.arange(len(dualsvm_trainer.train_loss_history)),
           dualsvm_trainer.train_loss_history,
           label="Train loss")
ax[0].plot(np.arange(len(dualsvm_trainer.val_loss_history)),
           dualsvm_trainer.val_loss_history,
           label="Val loss")
ax[0].set_title("Train & validation loss")
ax[0].set_xlabel("Epoch")
ax[0].set_ylabel("Loss")
ax[0].legend()

ax[1].plot(np.arange(len(dualsvm_trainer.train_loss_history)),
           dualsvm_trainer.train_acc_history,
           label="Train acc")
ax[1].plot(np.arange(len(dualsvm_trainer.val_loss_history)),
           dualsvm_trainer.val_acc_history,
           label="Val acc")
ax[1].set_title("Train & validation acc")
ax[1].set_xlabel("Epoch")
ax[1].set_ylabel("Accuracy")
ax[1].legend()

plt.show()

theta = np.append(dualsvm_trainer.b, dualsvm_trainer.w)
plot_decision_boundary(dualsvm_trainer.w, dualsvm_trainer.b, x_train)
plot_data(x_train, y_train)

support_vector_idx, support_vectors = dualsvm_trainer.compute_support_vectors(
    x_train, y_train)
if len(support_vectors > 0):
    plt.scatter(support_vectors[:, 0],
                support_vectors[:, 1],
                facecolors="none",
                edgecolors="k",
                label="sv")

plt.legend()
plt.show()

# Evaluating Trainers
svm_trainer.evaluate(x_test, y_test)
print(f"Test loss: {svm_trainer.test_loss}")
print(f"Test acc: {svm_trainer.test_acc}")

dualsvm_trainer.evaluate(x_test, y_test)
print(f"Test loss: {dualsvm_trainer.test_loss}")
print(f"Test acc: {dualsvm_trainer.test_acc}")