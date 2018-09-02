from flask import Flask
from flask import render_template
from flask import request
from flask import jsonify
import timedelta

app = Flask(__name__)

humidity = []
temperature = []
waterlvl = []
solar_radiation = []

@app.route('/dashboard', methods = ["GET"])

def serve():
    site = render_template("index.html")
    return site 

@app.route('/stream', methods = ["POST"])

def data_stream():
    print(request)
    data = request.get_json()
    humidity.append(data["humidity"])
    temperature.append(data["temperature"])
    waterlvl.append(data["water"])
    solar_radiation.append(data["light"])
    print (humidity, temperature, waterlvl, solar_radiation)
    return "ok"

@app.route('/update', methods = {"GET"})

def update():
    msg = [humidity[len(humidity)-7:],temperature[len(temperature)-7:], waterlvl[len(temperature)-7:], solar_radiation[len(temperature)-7:]]
    return str(msg)
    # msg = "{\"humidity\":" + str(humidity[len(humidity)-7:]) + ,\"temperature\": temperature[len(temperature)-7:], "waterlvl": waterlvl[len(temperature)-7:], "solar_radiation": solar_radiation[len(temperature)-7:]  } "




if __name__ == '__main__':
    app.run(host='0.0.0.0',debug = True)
