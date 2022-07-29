from urllib.parse import urlencode
from hashlib import sha512
import getpass, json, os, re, requests, time

def login(s, handle, password):
    res = s.get('https://codeforces.com/enter')
    csrf_token = re.findall('<meta name="X-Csrf-Token" content="(.{32})"/>', res.text)[0]
    data = {
        'csrf_token': csrf_token,
        'action': 'enter',
        'ftaa': '',
        'bfaa': '',
        'handleOrEmail': handle,
        'password': password
    }
    res = s.post('https://codeforces.com/enter', data = data)
    assert 'Logout' in res.text

def logout(s):
    res = s.get('https://codeforces.com')
    link = re.findall('<a href="(/.{32}/logout)">Logout</a>', res.text)[0]
    res = s.get('https://codeforces.com' + link)
    assert 'Logout' not in res.text

def get_all_contestants(contestId):
    key = input('Codeforces Key: ')
    secret = input('Codeforces Secret: ')
    data = urlencode({
        'apiKey': key,
        'contestId': contestId,
        # 'handle': '*',
        # 'from': 1,
        # 'count': 10,
        'time': int(time.time())
    })
    methods = 'contest.status'
    apiSig = sha512(f'123456/{methods}?{data}#{secret}'.encode()).hexdigest()
    
    res = requests.get(f'https://codeforces.com/api/{methods}?{data}', params = {'apiSig': '123456' + apiSig})
    # print(res.url)
    all_subs = json.loads(res.text)['result']
    all_subs.reverse()
    
    sub_id = {}
    for i, sub in enumerate(all_subs):
        # print(sub)
        if (sub['author']['participantType'] in ['CONTESTANT']):
            name = sub['author']['members'][0]['handle']
            # for mem in sub['author']['members']:
                # if (len(name) != 0):
                    # name += ", "
                # name += mem['handle'];
            # status = 1 if (sub['author']['participantType'] in ['VIRTUAL']) else status = 0
            sub_id.setdefault(name, [])
            sub_id[name].append([sub['problem']['index'], sub['id'], sub['relativeTimeSeconds'], i])
    
    return sub_id

def get_submission_detail(s, ID):
    time.sleep(2)
    res = s.get('https://codeforces.com')
    csrf_token = re.findall('<meta name="X-Csrf-Token" content="(.{32})"/>', res.text)[0]
    data = {
        'csrf_token': csrf_token,
        'submissionId': ID,
    }
    res = s.post('https://codeforces.com/group/z3GP4YeQl0/data/judgeProtocol', data = data)
    return res.text

def process_subtask(s):
    subtasks = []
    pos = 0
    while pos != -1:
        pos = s.find('Group', pos + 1)
        if pos == -1:
            break
        pos = s.find(':', pos)
        posL = s.find(' ', pos) + 1
        posR = s.find(' ', posL)
        subtasks.append(float(s[posL:posR]))
    return subtasks

def f_contests():
    
    try:
        os.mkdir('ranking/contests')
    except OSError as error:
        print("Directory 'ranking/contests' already created")
    
    with open('files/contests.json') as f_contests:
        contests = json.load(f_contests)
    
    for contest in contests:
        with open('ranking/contests/' + contest, 'w') as f:
            json.dump(contests[contest], f, indent = 4)
    
    with open('ranking/contests/index.json', 'w') as f:
        json.dump(contests, f, indent = 4)
    
    return contests

def f_tasks():
    
    try:
        os.mkdir('ranking/tasks')
    except OSError as error:
        print("Directory 'ranking/tasks' already created")
    
    with open('files/tasks.json') as f_tasks:
        tasks = json.load(f_tasks)
    
    for task in tasks:
        with open('ranking/tasks/' + task, 'w') as f:
            json.dump(tasks[task], f, indent = 4)
    
    with open('ranking/tasks/index.json', 'w') as f:
        json.dump(tasks, f, indent = 4)
    
    return tasks

def f_teams():
    
    try:
        os.mkdir('ranking/teams')
    except OSError as error:
        print("Directory 'ranking/teams' already created")
    
    teams = {}
    
    with open('ranking/teams/index.json', 'w') as f:
        json.dump(teams, f, indent = 4)
    
    return teams

def f_users(contestants):
    
    try:
        os.mkdir('ranking/users')
    except OSError as error:
        print("Directory 'ranking/users' already created")
    
    users = {}
    
    for key in contestants:
        users[key] = {'f_name': key, 'l_name': '', 'team': None}
        
        with open('ranking/users/' + key, 'w') as f:
            json.dump(users[key], f, indent = 4)
    
    with open('ranking/users/index.json', 'w') as f:
        json.dump(users, f, indent = 4)
    
    return users

def f_history(contestants, tasks):
    
    history = []
    for key in contestants:
        score = {}
        for x in contestants[key]:
            if (len(x) != 5):
                continue
            if (tasks[x[0]]['score_mode'] == 'max_subtask'):
                score.setdefault(x[0], [0] * len(x[4]))
                flag_inc = False
                for i, val in enumerate(x[4]):
                    if (val > score[x[0]][i]):
                        score[x[0]][i] = val
                        flag_inc = True
                if (flag_inc):
                    history.append([key, x[0], x[2], sum(score[x[0]])])
            elif (tasks[x[0]]['score_mode'] == 'max'):
                score.setdefault(x[0], 0)
                if (sum(x[4]) > score[x[0]]):
                    score[x[0]] = sum(x[4]);
                    history.append([key, x[0], x[2], score[x[0]]])
    
    history.sort(key = lambda sub : sub[2])
    
    with open('ranking/history', 'w') as f:
        json.dump(history, f, indent = 4)
    
    return history

def f_scores(history):
    
    scores = {}
    for sub in history:
        scores.setdefault(sub[0], {})
        scores[sub[0]].setdefault(sub[1], sub[3])
        scores[sub[0]][sub[1]] = max(scores[sub[0]][sub[1]], sub[3])
    
    with open('ranking/scores', 'w') as f:
        json.dump(scores, f, indent = 4)
    
    return scores

def f_subchanges(contestants, tasks):
    
    try:
        os.mkdir('ranking/subchanges')
    except OSError as error:
        print("Directory 'ranking/subchanges' already created")
    
    subchanges = {}
    for key in contestants:
        for x in contestants[key]:
            subchange = {
                'submission': str(x[3]),
                'time': x[2],
            }
            if (len(x) != 5):
                subchange['score'] = 0
                subchange['extra'] = ['0'] * len(tasks[x[0]]['extra_headers'])
            else:
                subchange['score'] = sum(x[4])
                subchange['extra'] = [str(int(score)) if (score.is_integer()) else str(score) for score in x[4]]
            
            subchanges[str(x[2]) + str(x[3]) + 's'] = subchange
            
            with open('ranking/subchanges/' + str(x[2]) + str(x[3]) + 's', 'w') as f:
                json.dump(subchange, f, indent = 4)
    
    with open('ranking/subchanges/index.json', 'w') as f:
        json.dump(subchanges, f, indent = 4)

def f_sublist(contestants, tasks):
    
    try:
        os.mkdir('ranking/sublist')
    except OSError as error:
        print("Directory 'ranking/sublist' already created")
    
    sublists = {}
    for key in contestants:
        sublist = []
        for x in contestants[key]:
            subsublist = {
                'user': key,
                'task': x[0],
                'time': x[2],
                'key': str(x[3]),
                'token': False,
            }
            if (len(x) != 5):
                subsublist['score'] = 0
                subsublist['extra'] = ['0'] * len(tasks[x[0]]['extra_headers'])
            else:
                subsublist['score'] = sum(x[4])
                subsublist['extra'] = [str(int(score)) if (score.is_integer()) else str(score) for score in x[4]]
            sublist.append(subsublist)
        
        sublists[key] = sublist
        
        with open('ranking/sublist/' + key, 'w') as f:
            json.dump(sublist, f, indent = 4)
    
    return sublists

def f_submissions(contestants):
    
    try:
        os.mkdir('ranking/submissions')
    except OSError as error:
        print("Directory 'ranking/submissions' already created")
    
    submissions = []
    for key in contestants:
        for x in contestants[key]:
            submission = {
                'user': key,
                'task': x[0],
                'time': x[2]
            }
            submissions.append(submission)
            
            with open('ranking/submissions/' + str(x[3]), 'w') as f:
                json.dump(submission, f, indent = 4)
    
    with open('ranking/submissions/index.json', 'w') as f:
        json.dump(submissions, f, indent = 4)
    
    return submissions

def main_func():
    handle      = input('Handle: ')
    password    = getpass.getpass('Password: ')
    contestId   = int(input('Contest ID: '))
    contestants = get_all_contestants(contestId)
    
    s = requests.Session()
    login(s, handle, password)
    for key in contestants:
        for x in contestants[key]:
            detail = get_submission_detail(s, x[1])
            if ('Points' in detail):
                x.append(process_subtask(detail))
    logout(s)
    
    # for key in contestants:
        # print(key)
        # for x in contestants[key]:
            # print(x)
    
    try:
        os.mkdir('ranking')
    except OSError as error:
        print("Directory 'ranking' already created")
    
    contests    = f_contests()
    tasks       = f_tasks()
    teams       = f_teams()
    users       = f_users(contestants)
    history     = f_history(contestants, tasks)
    scores      = f_scores(history)
    subchanges  = f_subchanges(contestants, tasks)
    sublists    = f_sublist(contestants, tasks)
    submissions = f_submissions(contestants)

if __name__ == '__main__':
    main_func()
