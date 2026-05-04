import tensorflow as tf
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Conv2D, MaxPooling2D, Flatten, Dense, Dropout
from tensorflow.keras.preprocessing.image import ImageDataGenerator

# -------------------------------------------------
# 1. Image Preprocessing
# -------------------------------------------------

train_datagen = ImageDataGenerator(
    rescale=1./255,
    shear_range=0.2,
    zoom_range=0.2,
    horizontal_flip=True
)

test_datagen = ImageDataGenerator(rescale=1./255)

# -------------------------------------------------
# 2. Load Dataset (YOUR PATH)
# -------------------------------------------------

train_data = train_datagen.flow_from_directory(
    r'C:\Users\Swanand\OneDrive\Desktop\DL PROGRAM\dataset\train',
    target_size=(128, 128),
    batch_size=32,
    class_mode='categorical'
)

test_data = test_datagen.flow_from_directory(
    r'C:\Users\Swanand\OneDrive\Desktop\DL PROGRAM\dataset\validation',
    target_size=(128, 128),
    batch_size=32,
    class_mode='categorical'
)

# -------------------------------------------------
# 3. Build CNN Model
# -------------------------------------------------

model = Sequential()

# Layer 1
model.add(Conv2D(32, (3,3), activation='relu', input_shape=(128,128,3)))
model.add(MaxPooling2D(pool_size=(2,2)))

# Layer 2
model.add(Conv2D(64, (3,3), activation='relu'))
model.add(MaxPooling2D(pool_size=(2,2)))

# Layer 3
model.add(Conv2D(128, (3,3), activation='relu'))
model.add(MaxPooling2D(pool_size=(2,2)))

# Flatten
model.add(Flatten())

# Fully Connected
model.add(Dense(128, activation='relu'))
model.add(Dropout(0.5))   # Prevent overfitting

# Output Layer
model.add(Dense(train_data.num_classes, activation='softmax'))

# -------------------------------------------------
# 4. Compile Model
# -------------------------------------------------

model.compile(
    optimizer='adam',
    loss='categorical_crossentropy',
    metrics=['accuracy']
)

# -------------------------------------------------
# 5. Train Model
# -------------------------------------------------

history = model.fit(
    train_data,
    epochs=10,
    validation_data=test_data
)

# -------------------------------------------------
# 6. Evaluate Model
# -------------------------------------------------

loss, accuracy = model.evaluate(test_data)
print("\nFinal Accuracy:", accuracy)

# -------------------------------------------------
# 7. Save Model (Optional but useful)
# -------------------------------------------------

model.save("plant_disease_model.h5")





# Reviewing plant.py contents so I can explain each line precisely.

# Read [](file:///c%3A/Users/ADMIN/OneDrive/Desktop/dl/plant.py)

# ## Line-by-Line Explanation of plant.py

# ### Imports
# 1. `import tensorflow as tf`  
#    - Imports TensorFlow as `tf`, which provides the core deep learning framework.

# 2. `from tensorflow.keras.models import Sequential`  
#    - Imports the `Sequential` model class for building a linear stack of layers.

# 3. `from tensorflow.keras.layers import Conv2D, MaxPooling2D, Flatten, Dense, Dropout`  
#    - Imports common CNN layers:
#      - `Conv2D` for convolution,
#      - `MaxPooling2D` for downsampling,
#      - `Flatten` to convert feature maps to a vector,
#      - `Dense` for fully connected layers,
#      - `Dropout` to reduce overfitting.

# 4. `from tensorflow.keras.preprocessing.image import ImageDataGenerator`  
#    - Imports `ImageDataGenerator`, which generates augmented image batches for training and testing.

# ---

# ### 1. Image Preprocessing
# 5. `train_datagen = ImageDataGenerator(`  
#    - Creates a data generator for training images with preprocessing and augmentation.

# 6. `    rescale=1./255,`  
#    - Scales pixel values from `[0,255]` to `[0,1]`, which helps the model train faster and more stably.

# 7. `    shear_range=0.2,`  
#    - Applies random shear transformations to augment images and improve robustness.

# 8. `    zoom_range=0.2,`  
#    - Applies random zoom changes to training images for augmentation.

# 9. `    horizontal_flip=True`  
#    - Randomly flips images horizontally to increase variation.

# 10. `)`  
#     - Ends the training data generator configuration.

# 11. `test_datagen = ImageDataGenerator(rescale=1./255)`  
#     - Creates a generator for validation/test images that only rescales pixels; no augmentation is applied to test data.

# ---

# ### 2. Load Dataset
# 12. `train_data = train_datagen.flow_from_directory(`  
#     - Loads training images from a directory structure where subfolders represent classes.

# 13. `    r'C:\Users\Swanand\OneDrive\Desktop\DL PROGRAM\dataset\train',`  
#     - Specifies the training data folder path.

# 14. `    target_size=(128, 128),`  
#     - Resizes every image to 128x128 pixels.

# 15. `    batch_size=32,`  
#     - Loads data in batches of 32 images.

# 16. `    class_mode='categorical'`  
#     - Uses categorical labels, which means the target is one-hot encoded for multiclass classification.

# 17. `)`  
#     - Ends the training data loader configuration.

# 18. `test_data = test_datagen.flow_from_directory(`  
#     - Loads validation/test images from a directory structure.

# 19. `    r'C:\Users\Swanand\OneDrive\Desktop\DL PROGRAM\dataset\validation',`  
#     - Specifies the validation folder path.

# 20. `    target_size=(128, 128),`  
#     - Resizes validation images to 128x128 pixels as well.

# 21. `    batch_size=32,`  
#     - Loads test images in batches of 32.

# 22. `    class_mode='categorical'`  
#     - Uses one-hot encoding for validation labels too.

# 23. `)`  
#     - Ends the test data loader configuration.

# ---

# ### 3. Build CNN Model
# 24. `model = Sequential()`  
#     - Creates an empty sequential model.

# 25. `model.add(Conv2D(32, (3,3), activation='relu', input_shape=(128,128,3)))`  
#     - Adds the first convolutional layer:
#       - 32 filters,
#       - kernel size 3x3,
#       - ReLU activation,
#       - input shape 128x128 with 3 color channels.

# 26. `model.add(MaxPooling2D(pool_size=(2,2)))`  
#     - Adds max pooling to reduce spatial dimensions by half.

# 27. `model.add(Conv2D(64, (3,3), activation='relu'))`  
#     - Adds a second convolutional layer with 64 filters.

# 28. `model.add(MaxPooling2D(pool_size=(2,2)))`  
#     - Adds second pooling to further reduce spatial size.

# 29. `model.add(Conv2D(128, (3,3), activation='relu'))`  
#     - Adds a third convolutional layer with 128 filters for deeper feature extraction.

# 30. `model.add(MaxPooling2D(pool_size=(2,2)))`  
#     - Adds a third pooling layer.

# 31. `model.add(Flatten())`  
#     - Flattens the final feature maps into a 1D vector for the dense layers.

# 32. `model.add(Dense(128, activation='relu'))`  
#     - Adds a dense hidden layer with 128 neurons and ReLU activation.

# 33. `model.add(Dropout(0.5))   # Prevent overfitting`  
#     - Adds dropout that randomly drops 50% of neurons during training to reduce overfitting.

# 34. `model.add(Dense(train_data.num_classes, activation='softmax'))`  
#     - Adds the output layer with one neuron per class, using softmax to produce class probabilities.

# ---

# ### 4. Compile Model
# 35. `model.compile(`  
#     - Begins model compilation.

# 36. `    optimizer='adam',`  
#     - Uses the Adam optimizer.

# 37. `    loss='categorical_crossentropy',`  
#     - Uses categorical crossentropy loss for multiclass classification.

# 38. `    metrics=['accuracy']`  
#     - Tracks accuracy during training.

# 39. `)`  
#     - Completes compilation.

# ---

# ### 5. Train Model
# 40. `history = model.fit(`  
#     - Begins training and stores training history.

# 41. `    train_data,`  
#     - Uses the training data generator.

# 42. `    epochs=10,`  
#     - Trains for 10 epochs.

# 43. `    validation_data=test_data`  
#     - Evaluates performance on the validation/test data after each epoch.

# 44. `)`  
#     - Ends training.

# ---

# ### 6. Evaluate Model
# 45. `loss, accuracy = model.evaluate(test_data)`  
#     - Computes loss and accuracy on the validation/test dataset.

# 46. `print("\nFinal Accuracy:", accuracy)`  
#     - Prints the final accuracy result.

# ---

# ### 7. Save Model
# 47. `model.save("plant_disease_model.h5")`  
#     - Saves the trained model to a file named `plant_disease_model.h5` for later use.

# If you want, I can also explain how each model component affects performance or suggest improvements.