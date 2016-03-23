from functools import wraps
from flask import make_response, current_app, request

def json_response(f):
	@wraps(f)
	def decorated_function(*args, **kwargs):
		if True and request.method == 'OPTIONS':
			resp = current_app.make_default_options_response()
		else:
			resp = make_response(f(*args, **kwargs))
		if not True and request.method != 'OPTIONS':
			return resp

		h = resp.headers
		h['Content-Type'] = "application/json"
		return resp
	return decorated_function
