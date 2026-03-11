import requests
import json

# Base URLs to try (api2 may be blocked or regional). To get the live URL from
# the app on a rooted phone: adb shell, then
#   cd /data/data/com.watch.life/shared_prefs/
#   grep -r "http" .
# Look for network_config.xml or similar for the exact base_url.
BASE_URLS = [
    "https://api2.idoocloud.com",
    "https://life-us-api.idoocloud.com",
    "https://api-life.idoocloud.com",
]
# If DNS fails, try direct IP with Host header (Alibaba Cloud node example):
# BASE_URLS = ["https://47.252.31.214"] and headers["Host"] = "api2.idoocloud.com"

def get_watch_faces(device_id="7733", page=1):
    path = "/watch_face/list"
    
    headers = {
        "Content-Type": "application/json",
        "User-Agent": "VeryFit/3.4.5 (Android; Rooted)",
        "Accept-Language": "en-US"
    }
    
    payload = {
        "device_type": int(device_id),
        "page_index": page,
        "page_size": 20,
        "lang": "en"
    }

    print(f"--- Fetching faces for Device ID: {device_id} (Page {page}) ---")
    
    last_error = None
    for base in BASE_URLS:
        url = base.rstrip("/") + path
        try:
            print(f"Trying {url} ...")
            response = requests.post(url, headers=headers, json=payload, timeout=10)
            response.raise_for_status()
            data = response.json()
            
            if data.get("code") == 0 or "data" in data:
                items = data.get("data", {}).get("items", [])
                if not items:
                    print("No watch faces found for this ID.")
                    return

                print(f"Found {len(items)} faces:\n")
                print(f"{'ID':<10} | {'Name':<20} | {'Download URL'}")
                print("-" * 60)
                
                for face in items:
                    name = face.get("name", "Unknown")
                    f_id = face.get("id", "N/A")
                    dl_url = face.get("file_url")
                    print(f"{f_id:<10} | {name:<20} | {dl_url}")
                return
            else:
                last_error = data.get("msg", "Unknown error")
        except requests.exceptions.RequestException as e:
            last_error = e
            continue
    
    print(f"All endpoints failed. Last error: {last_error}")

if __name__ == "__main__":
    get_watch_faces("7733")