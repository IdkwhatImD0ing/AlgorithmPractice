import tensorflow as tf
import matplotlib.pyplot as plt
from tensorflow.keras import regularizers
from tensorflow.keras.optimizers import SGD
from sklearn.model_selection import train_test_split
from tensorflow import keras
from keras.layers.advanced_activations import PReLU
tf.test.gpu_device_name()

###### Loading training, testing, and validation data ######
(x_train, y_train), (x_test, y_test) = tf.keras.datasets.cifar10.load_data()
x_train, x_val, y_train, y_val = train_test_split(x_train, y_train, test_size = 0.1)

###### Normalizing. ######
x_train = x_train/255
x_val = x_val/255
x_test = x_test/255

###### Optimized Neural Network. ######
model = keras.models.Sequential()
model.add(keras.layers.Conv2D(filters = 32, kernel_size = (3, 3), activation = PReLU(), input_shape = (32, 32, 3)))
model.add(keras.layers.MaxPooling2D((2, 2)))
model.add(keras.layers.Conv2D(filters = 64, kernel_size = (3, 3), activation = PReLU()))
model.add(keras.layers.MaxPooling2D((2, 2)))
model.add(keras.layers.Conv2D(filters = 128, kernel_size = (3, 3), activation = PReLU()))
model.add(keras.layers.MaxPooling2D((2, 2)))
model.add(keras.layers.Conv2D(filters = 128, kernel_size = (3, 3), activation = PReLU()))
model.add(keras.layers.MaxPooling2D((2, 2)))
model.add(keras.layers.Flatten())
model.add(keras.layers.Dense(1024, activation = PReLU()))
model.add(keras.layers.Dropout(0.5))
model.add(keras.layers.Dense(10, activation = 'softmax'))

model.summary()
model.compile(optimizer = SGD(learning_rate = 0.01, momentum = 0.9), loss = keras.losses.sparse_categorical_crossentropy, metrics = ['accuracy'])
model.fit(x_train, y_train, epochs = 10, validation_data = (x_val, y_val))

# Evaluation
test_loss, test_acc = model.evaluate(x_test, y_test)
print(test_loss, test_acc)