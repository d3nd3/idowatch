import http.client
import argparse
from urllib.parse import urlencode
import json

APP_KEY="9190d251859c44e5be1dced03f0a556a" # key hard coded in the app

parser = argparse.ArgumentParser(
                    prog='Ryze Data dumper',
                    )

parser.add_argument('-u', '--username', required=True) 
parser.add_argument('-p', '--password', required=True)
args = parser.parse_args()


userapi = http.client.HTTPSConnection("user.idoocloud.com")
headers = {
  'appKey': APP_KEY
}
parms = urlencode({
    "username": args.username,
    "password": args.password
})
userapi.request("POST", f"/userapi/public/account/login?{parms}", headers=headers)
res = userapi.getresponse()
bearer = json.loads(res.read())['result']

healthapi = http.client.HTTPSConnection("health.idoocloud.com")
headers = {
  'appKey': APP_KEY,
  'Authorization': bearer,
  'Content-Type': 'application/json'
}
print("-- Authorized")

healthapi.request("POST", "/api/sports/sync/data", headers=headers)
res = healthapi.getresponse()
sync_data = json.loads(res.read())["result"]
day_data = [x for x in sync_data if type(x) == list]
activities = [activity for data in day_data for activity in data]
sids = [activity[0] for activity in activities]

print("-- Got SIDs")
print(sids)

for sid in sids:
    print(f"-- Getting {sid}")
    payload = json.dumps({
        "sid": sid
    })
    healthapi.request("POST", "/api/sports/find", payload, headers=headers)
    
    res = healthapi.getresponse()
    activity_data = json.loads(res.read())
    print(activity_data)




