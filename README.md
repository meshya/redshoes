# redshoes 
Force Redirect your OS data to a socks5 proxy
\
\
\
Redshoes is a CLI application which help you control redsocks and rediredt your packets to redsocks using iptables.

# Build
For build use make \
`$ make` \
For build using gcc: \
`$ make CXX=g++` 

# Installation
Use make  \
`# make install`

# Unstallation
Use make again \
`# make uninstall`\
Or you can do it you self\
`# rm -rf /opt/redshoes`
`# unlink /usr/bin/redshoes`

# How to use ?
first install app :) \
after installing follow this steps:\
1_ run redshoes as superUser\
`# redshoes`\
2_ Use Up and Down and Enter keys for navigate\
3_ Click on configure redsocks\
3.1_ The editore is vim if you know how to work with that follow 4 step
3.2_ In the vim for editting press i key and for exitting press Esc and for exit with save write :wq and press Enter and for without save write :q! and press Enter.
4_ In the redsocks section edit ip, port, login and password how you want\
```
redsocks{
    ....
    ip = .... # Put your proxy interface here
    port = .... # Put your proxy port here
    #login = .... # Uncomment this if needed
    #password = .... # Uncomment this if needed
    ....
}
```
### 5_ Are you using a local proxy server like tor or xray ?
#### Yes 
6_ Run your proxy service on a special user.\
7_ Find UID of PROXY_USERNAME you can run this command: \
` $id -u PROXY_USERNAME `\
8_ Go to Configure iptables\
9_ Edit config file like this: \
before:\
```
#-A {redsocks_chain_name} -m owner --uid-owner /* If you are running a socks proxy on your localhost like tor or xray Enter UID of user which handle socks service here and uncomment this line */ -j RETURN
```
after:\
```
-A {redsocks_chain_name} -m owner --uid-owner PROXY_USER_UID -j RETURN
```
#### No
5_ Drink some water go next section :)

#### At th last
10_ Turn on redsocks and tunnel
11_ take care yourself 
