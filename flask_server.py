from flask import Flask, request

app = Flask(__name__)

# store the last accident message
last_message = "No accident message received yet"

@app.route("/", methods=["GET"])
def home():
    # show the latest accident message in browser
    return f"<h2>Latest Accident Message:</h2><p>{last_message}</p>", 200


@app.route("/receive", methods=["POST"])
def receive():
    global last_message
    data = request.form.get("data")
    if data:
        last_message = data  # update message
    print("Received from C++:", data)
    return "OK", 200


if __name__ == "__main__":
    app.run(port=5000)
