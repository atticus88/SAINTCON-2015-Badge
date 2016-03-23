from flask import Flask, request
from decorators import json_response
import json
import mse

app = Flask(__name__)

client = mse.Client("cmx.example.edu","username","password", verify=False)

@app.route("/", methods=["GET"])
@json_response
def index():
	ip = request.remote_addr
	data = client.get_location(ip)
	if len(data) >= 1:
		return json.dumps(data[0])
	return '{"error" : "client not found."}', 404
		

if __name__ == "__main__":
    app.run(host="0.0.0.0")
