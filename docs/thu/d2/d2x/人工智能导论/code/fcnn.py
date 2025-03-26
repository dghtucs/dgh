import tensorflow as tf
from tensorflow.keras import layers, models
from tensorflow.keras.datasets import mnist
from tensorflow.keras.utils import to_categorical

# Step 1: Load and preprocess the MNIST dataset
(x_train, y_train), (x_test, y_test) = mnist.load_data()

# Flatten the images from 28x28 to a 1D vector of 784 values (28*28 pixels)
x_train = x_train.reshape((x_train.shape[0], 28 * 28))
x_test = x_test.reshape((x_test.shape[0], 28 * 28))

# Normalize pixel values from [0, 255] to [0, 1]
x_train, x_test = x_train / 255.0, x_test / 255.0

# One-hot encode the labels (categorical crossentropy loss requires one-hot encoding)
y_train = to_categorical(y_train, 10)
y_test = to_categorical(y_test, 10)

# Step 2: Define the Fully Connected Neural Network Model
model = models.Sequential()

# Input layer (784 neurons for the flattened image data)
model.add(layers.InputLayer(input_shape=(28 * 28,)))

# First hidden layer: 128 neurons, ReLU activation
model.add(layers.Dense(128, activation='relu'))

# Second hidden layer: 64 neurons, ReLU activation
model.add(layers.Dense(64, activation='relu'))

# Output layer: 10 neurons (for 10 classes), softmax activation for classification
model.add(layers.Dense(10, activation='softmax'))

# Step 3: Compile the model
model.compile(optimizer='adam',
              loss='categorical_crossentropy',  # for multi-class classification
              metrics=['accuracy'])

# Step 4: Train the model
model.fit(x_train, y_train, epochs=5, batch_size=64, validation_split=0.2)

# Step 5: Evaluate the model
test_loss, test_acc = model.evaluate(x_test, y_test)

print(f"Test accuracy: {test_acc}")
