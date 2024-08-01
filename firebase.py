import pyrebase
import tensorflow as tf
import numpy as np
import time

firebase_config = {
    "apiKey": "api key",
    "authDomain": "myapp-1234",
    "database url": 'url',
    "storageBucket": "myapp",
}


firebase = pyrebase.initialize_app(firebase_config)
db = firebase.database()


model = tf.keras.models.load_model(r"irrigation_model.h5")


crop_type_mapping = {
    'Wheat': 0,
    'Groundnut': 1,
    'Garden Flowers': 2,
    'Maize': 3,
    'Paddy': 4,
    'Potato': 5,
    'Pulse': 6,
    'Sugarcane': 7,
    'Coffee': 8
}

def fetch_real_time_data():
    crop_type = db.child("crop_type").get().val()
    temperature = db.child("temperature").get().val()
    humidity = db.child("humidity").get().val()
    soil_moisture = db.child("soil_moisture").get().val()


    crop_type_numerical = crop_type_mapping.get(crop_type, -1)


    print(f"Fetched data - CropType: {crop_type}, Temperature: {temperature}, Humidity: {humidity}, Soil Moisture: {soil_moisture}")

    data = {
        "crop_type": crop_type_numerical,
        "temperature": temperature,
        "humidity": humidity,
        "soil_moisture": soil_moisture
    }
    return data

def preprocess_data(data):
    crop_type = data.get('crop_type', 0)
    temperature = data.get('temperature', 0)
    humidity = data.get('humidity', 0)
    soil_moisture = data.get('soil_moisture', 0)


    print(f"Preprocessed data - CropType: {crop_type}, Temperature: {temperature}, Humidity: {humidity}, Soil Moisture: {soil_moisture}")


    input_numerical = np.array([temperature, humidity, soil_moisture]).reshape((1, -1))

    input_crop_type = np.array([crop_type]).reshape((1, 1))

    return input_crop_type, input_numerical

def make_prediction(model, data):
    crop_type, preprocessed_data = preprocess_data(data)
    prediction = model.predict([crop_type, preprocessed_data])


    print(f"Prediction: {prediction}")

    return prediction

def store_prediction(prediction):

    prediction_value = prediction[0][0] if isinstance(prediction, np.ndarray) else prediction[0]


    prediction_value = float(prediction_value)


    db.child("latest_prediction").set({"prediction": prediction_value})

if __name__ == "__main__":
    while True:
        try:

            real_time_data = fetch_real_time_data()


            prediction = make_prediction(model, real_time_data)


            store_prediction(prediction)

            time.sleep(60)
        except Exception as e:
            print(f"An error occurred: {e}")
            time.sleep(60)
