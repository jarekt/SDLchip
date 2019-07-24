#simple script for downloading github repos(zip files) easily
import requests
import zipfile
import os

url = 'https://www.libsdl.org/release/SDL2-2.0.9.zip'
folder = 'SDL'
#zip contents into this ^ folder

r = requests.get(url)
if not r:
    print('download failed, try again or download %s manually' % url)
    exit()
open('temp.zip', 'wb').write(r.content)

zipfile.ZipFile('temp.zip').extractall()
os.rename(zipfile.ZipFile('temp.zip').namelist()[0], folder)
os.remove('temp.zip')
