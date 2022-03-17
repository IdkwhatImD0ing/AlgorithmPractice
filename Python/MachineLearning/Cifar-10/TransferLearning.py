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
x_train, x_val, y_train, y_val = train_test_split(x_train,
                                                  y_train,
                                                  test_size=0.1)

###### Normalizing. ######
x_train = x_train / 255.0
x_val = x_val / 255.0
x_test = x_test / 255.0

resModel = keras.applications.ResNet50(weights='imagenet',
                                       include_top=False,
                                       input_shape=(256, 256, 3))

model = keras.models.Sequential()
model.add(keras.layers.UpSampling2D((2, 2)))
model.add(keras.layers.UpSampling2D((2, 2)))
model.add(keras.layers.UpSampling2D((2, 2)))
model.add(resModel)
model.add(keras.layers.Flatten())
model.add(keras.layers.BatchNormalization())
model.add(keras.layers.Dense(128, activation='relu'))
model.add(keras.layers.Dropout(0.5))
model.add(keras.layers.BatchNormalization())
model.add(keras.layers.Dense(64, activation='relu'))
model.add(keras.layers.Dropout(0.5))
model.add(keras.layers.BatchNormalization())
model.add(keras.layers.Dense(10, activation='softmax'))

model.compile(optimizer=keras.optimizers.RMSprop(learning_rate=2e-5),
              loss=tf.keras.losses.SparseCategoricalCrossentropy(),
              metrics=['accuracy'])
history = model.fit(x_train,
                    y_train,
                    epochs=5,
                    batch_size=20,
                    validation_data=(x_val, y_val))
