from netmiko import ConnectHandler

myserver = {
    'device_type': 'linux',
    'host':   '192.168.6.4',  #Your Server IP
    'username': 'bbx', #your Server Username
    'password': 'Nurfarisya07', #your server password
    'port' : 22,
    'secret': '',
}

net_connect = ConnectHandler(**myserver)
output = net_connect.send_command('uname -a')
print(output)
