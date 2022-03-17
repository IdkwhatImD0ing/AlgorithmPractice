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
x_train = x_train
x_val = x_val
x_test = x_test

input_shape = (256, 256, 3)
n_classes = 10

efnb0 = keras.applications.EfficientNetB3(weights='imagenet',
                                          include_top=False,
                                          input_shape=input_shape,
                                          classes=n_classes)

model = keras.models.Sequential()
model.add(keras.layers.UpSampling2D((2, 2)))
model.add(keras.layers.UpSampling2D((2, 2)))
model.add(keras.layers.UpSampling2D((2, 2)))
model.add(efnb0)
model.add(keras.layers.Flatten())
model.add(keras.layers.BatchNormalization())
model.add(keras.layers.Dense(128, activation='relu'))
model.add(keras.layers.Dropout(0.5))
model.add(keras.layers.BatchNormalization())
model.add(keras.layers.Dense(64, activation='relu'))
model.add(keras.layers.Dropout(0.5))
model.add(keras.layers.BatchNormalization())
model.add(keras.layers.Dense(n_classes, activation='softmax'))
model.build(input_shape=(None, 32, 32, 3))
model.summary()

optimizer = keras.optimizers.Adam(lr=0.0001)

#early stopping to monitor the validation loss and avoid overfitting
early_stop = keras.callbacks.EarlyStopping(monitor='val_loss',
                                           mode='min',
                                           verbose=1,
                                           patience=10,
                                           restore_best_weights=True)

#reducing learning rate on plateau
rlrop = keras.callbacks.ReduceLROnPlateau(monitor='val_loss',
                                          mode='min',
                                          patience=5,
                                          factor=0.5,
                                          min_lr=1e-6,
                                          verbose=1)

#model compiling
model.compile(optimizer=optimizer,
              loss=tf.keras.losses.SparseCategoricalCrossentropy(),
              metrics=['accuracy'])

model_history = model.fit(x_train,
                          y_train,
                          validation_data=(x_val, y_val),
                          verbose=1,
                          epochs=10,
                          batch_size=16)
