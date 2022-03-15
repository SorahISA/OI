import json

###### read 'id_to_name' list ######

f_id_to_name = open("id_to_name.txt")
id_list = [x.split() for x in f_id_to_name.readlines()]
id_dict = {x[0] : x[1] for x in id_list}
f_id_to_name.close()
# print(id_dict)

###### change user 'f_name' ######

f_users = open("ranking/users/index.json")
users = json.load(f_users)
f_users.close()
# f_teams = open("ranking/teams/index.json")
# teams = json.load(f_teams)
# f_teams.close()

# team_dict = {teams[t_id]['name'] : t_id for t_id in teams}
# print(team_dict)

for u_id in users:
    users[u_id]['f_name'] = id_dict[u_id] + " (" + str(u_id) + ")"
    # users[u_id]['team'] = team_dict[users[u_id]['l_name']]
    with open("ranking/users/" + str(u_id), 'w') as f_user:
        json.dump(users[u_id], f_user, indent = 4)
# print(users)

with open("ranking/users/index.json", 'w') as f_users:
    json.dump(users, f_users, indent = 4)
