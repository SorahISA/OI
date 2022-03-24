#!/usr/bin/env python3
import os
import json
import requests
from urllib.parse import urljoin
import sys

if len(sys.argv)<=1:
    print("Usage: cmsRankingDump.py URL")
    exit(0)
BaseURL = sys.argv[1]
SavePath = "ranking"
if len(sys.argv)>=3:
    SavePath = sys.argv[2]

def dumpdata(path, jsondecode=True, save=True):
    url = urljoin(BaseURL,path)
    try:
        res = requests.get(url, stream=True)
        if res.status_code != 200:
            print("[Warning] Response status is %d instead of 200 while dumping %s"%(res.status_code,path))
            return None
    except:
        print("[Warning] Request error while dumping %s"%path)
        return None
    if save:
        with open(path,"wb") as f:
            f.write(res.content)
    if jsondecode:
        return json.loads(res.text)
    else:
        return res.text

def dumpdata_dir(path,jsondecode=True):
    data = dumpdata(path,jsondecode,False)
    if data == None:
        return None
    try:
        os.mkdir(path)
    except:
        pass
    open(os.path.join(path,"index.json"),"w").write(json.dumps(data))
    open(os.path.join(path,".htaccess"),"w").write("DirectoryIndex index.json")
    return data

try:
    os.mkdir(SavePath)
except:
    pass
os.chdir(SavePath)
try:
    os.mkdir("lib")
    os.mkdir("img")
except:
    pass

dumpdata("img/close.png",False);
dumpdata("img/face.png",False);
dumpdata("img/favicon.ico",False);
dumpdata("img/flag.png",False);
dumpdata("img/logo.png",False);
dumpdata("img/tick_black.png",False);
dumpdata("img/tick_white.png",False);
dumpdata("lib/eventsource.js",False);
dumpdata("lib/explorercanvas.js",False);
dumpdata("lib/jquery.js",False);
dumpdata("lib/raphael.js",False);
dumpdata("Chart.js",False);
dumpdata("Config.js",False);
dumpdata("DataStore.js",False);
dumpdata("HistoryStore.js",False);
dumpdata("Overview.js",False);
dumpdata("Ranking.css",False);
dumpdata("Ranking.html",False);
dumpdata("Ranking.js",False);
dumpdata("Scoreboard.js",False);
dumpdata("TeamSearch.js",False);
dumpdata("TimeView.js",False);
dumpdata("UserDetail.js",False);

contests = dumpdata_dir("contests")
if contests is None:
    exit(0)
for c in contests:
    dumpdata(os.path.join("contests",c))

dumpdata("history");
dumpdata("scores");
# dumpdata("events");
dumpdata("logo",False);

tasks = dumpdata_dir("tasks")
if tasks is None:
    exit(0)
for t in tasks:
    dumpdata(os.path.join("tasks",t))

teams = dumpdata_dir("teams")
if teams is None:
    exit(0)
for t in teams:
    dumpdata(os.path.join("teams",t))
    
users = dumpdata_dir("users")
if users is None:
    exit(0)
for u in users:
    dumpdata(os.path.join("users",u))

try:
    os.mkdir("flags")
except:
    pass
for t in teams:
    dumpdata(os.path.join("flags",t))

try:
    os.mkdir("sublist")
except:
    pass
for u in users:
    dumpdata(os.path.join("sublist",u))

subchanges = dumpdata_dir("subchanges")
if subchanges is None:
    exit(0)
for s in subchanges:
    dumpdata(os.path.join("subchanges",s))

submissions = dumpdata_dir("submissions")
if submissions is None:
    exit(0)
for s in submissions:
    dumpdata(os.path.join("submissions",s))