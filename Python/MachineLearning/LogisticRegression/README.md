# Logistic Regression

## Dataset
There are 1000 synthetic examples in total (800 in train.csv and 200 in test.csv), and each of them is a two-dimension (real-value) feature vector with a binary label (0 or 1). Train.csv is further split into a trainint dataset and a validation dataset

## Functions

### Sigmoid
This function coverts the raw dot product of θ and feature vectors X into probabilities.

### Cross entropy and derivative
Cross-entropy is a loss function for both binary and multi-class classification problems. The equation used for this assignment is a special case of the general cross-entropy loss – the binary cross-entropy
loss. 

### Gradient Descent Step
This function performs a one-step gradient update on θ using the derivative of the cross-entropy loss described above.

### Accuracy
This function is used to calculate prediction accuracy. It accepts two vectors ˆy and y and returns the percentage (a floating number) of correct predictions.

### Regularization
L2 reguluarization is used on the loss function and its derivative.
