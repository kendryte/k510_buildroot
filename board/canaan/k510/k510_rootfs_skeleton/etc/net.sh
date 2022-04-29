hostname localhost.localdomain
ifconfig eth0 hw ether 00:66:99:66:99:00
ifconfig eth0 192.168.52.200
ifconfig lo 127.0.0.1 netmask 255.0.0.0 broadcast 127.255.255.255
route add -net 127.0.0.0 netmask 255.0.0.0 lo
route add default gw 192.168.52.254 dev eth0
