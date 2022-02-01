from DataModule import DataModule
from LinearRegressionTrainer import LinearRegressionTrainer
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# Create data module
datamodule = DataModule()
datamodule.load_data()
feature_to_bin = "model_year"
features_to_encode = ["cylinders", "origin"]
features_to_cross = ["displacement", "acceleration"]
intervals = pd.IntervalIndex.from_tuples([(69, 74), (74, 79), (79, 84)])


#print(datamodule.dataset)
datamodule.bin_feature(feature_to_bin, intervals)
#print(datamodule.dataset)
datamodule.one_hot_encode(features_to_encode)
#print(datamodule.dataset)
datamodule.cross_feature(features_to_cross[0], features_to_cross[1])
#print(datamodule.dataset)
datamodule.normalize()
#print(datamodule.dataset)
train, val, test = datamodule.train_val_test_split()
x_train, y_train = train
x_val, y_val = val
x_test, y_test = test

# Train a linear regression trainer
trainer = LinearRegressionTrainer(datamodule.dataset.columns.size - 1, learning_rate = 0.01, num_epochs = 5000)
trainer.train(x_train, y_train, x_val, y_val)


print(f"Final train loss: {trainer.train_loss_history[-1]}")
print(f"Final validation loss: {trainer.val_loss_history[-1]}")

plt.plot(np.arange(trainer.num_epochs), trainer.train_loss_history, label="Train loss")
plt.plot(np.arange(trainer.num_epochs), trainer.val_loss_history, label="Val loss")
plt.title("Train + validation loss")
plt.xlabel("Epoch")
plt.ylabel("Loss")
plt.legend()
plt.show()

# Use the below lines only after tuning hyperparameters

trainer.evaluate(x_test, y_test)
x_test = np.hstack((x_test, np.ones((len(x_test),1))))
hypotheses = np.dot(x_test,trainer.theta)
print(trainer.theta)
print(f"Test loss: {trainer.test_loss}")

myHypo = open("myHypotheses.txt", "w")
actual = open("actualValue.txt", "w")

np.savetxt(myHypo, hypotheses)
np.savetxt(actual, y_test)

myHypo.close()
actual.close()

