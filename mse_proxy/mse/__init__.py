from requests.auth import HTTPBasicAuth
import requests
import json

class Client():
	def __init__(self, hosts, username, password, version="v2", verify=True):
		""" MSE/CMX connection setup
		pass in the list of MSE/CMX hosts to check against 
		with username and password.
		"""
		if isinstance(hosts, basestring):
			self.hosts = hosts.split(',')
		else:
			self.hosts = hosts

		self.version = version
		self.verify = verify
		self.auth = HTTPBasicAuth(username, password)
		if not verify:
			requests.packages.urllib3.disable_warnings()

	def get_location(self, ip):
		""" Queries all MSE/CMX servers 
		for the device and returns the result with the best 
		confidence 
		"""

		clients = []
		for host in self.hosts:
			r = requests.get('https://%s/api/location/%s/clients?ipAddress=%s' % (host, self.version, ip.lower()), verify=self.verify, auth=self.auth, headers={"Accept":"application/json"})
			if r.status_code == 200:
				clients.append(r.json())

		result = {}
		for client in clients:
			if 'WirelessClientLocation' in result:
				if result['WirelessClientLocation']['confidenceFactor'] > i['WirelessClientLocation']['confidenceFactor']:
					result = client
			else:
					result = client

		return result

