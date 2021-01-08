import requests
from bs4 import BeautifulSoup

machine_ip = '10.10.83.105'
host = 'http://{machine_ip}'

# Returns the server response (i.e 200, 404, etc)
response = requests.get(host)

# Get and parse the html source code
html = response.text
soup = BeautifulSoup(html, 'html.parser')

# Print all links from webpage
for link in soup.find_all('a'):
    print(link.get('href'))
