#!/bin/bash
# Lo script viene lanciato come root quindi non abbiamo bisogno di usare sudo

arc=$(uname -a)													#prende le informazioni di sistema
pcpu=$(grep "physical id" /proc/cpuinfo | sort | uniq | wc -l)							#prende e conta i processori fisicamente presenti
vcpu=$(grep "^processor" /proc/cpuinfo | wc -l)									#prende e conta i processori virtuali presenti (thread)
fram=$(free -m | awk '$1 == "Mem:" {print $2}')									#prende la memoria ram totale
uram=$(free -m | awk '$1 == "Mem:" {print $3}')									#prende la memoria ram usata
pram=$(free | awk '$1 == "Mem:" {printf("%.2f"), $3/$2*100}')							#prende la percentuale di memoria ram usata/totale
fdisk=$(df -Bg | grep '^/dev/' | grep -v '/boot$' | awk '{ft += $2} END {print ft}')				#prende la memoria disco totale
udisk=$(df -Bm | grep '^/dev/' | grep -v '/boot$' | awk '{ut += $3} END {print ut}')				#prende la memoria disco usata
pdisk=$(df -Bm | grep '^/dev/' | grep -v '/boot$' | awk '{ut += $3} {ft+= $2} END {printf("%d"), ut/ft*100}')	#prende la percentuale di memoria disco usata/totale
cpul=$(top -bn1 | grep '^%Cpu' | cut -c 9- | xargs | awk '{printf("%.1f%%"), $1 + $3}')				#prende la percentuale di carico della CPU
lb=$(who -b | awk '$1 == "system" {print $3 " " $4}')								#prende data e ora dell'ultimo boot
lvmt=$(lsblk | grep "lvm" | wc -l)										#prende e conta le frasi con lvm nella tabella delle partizioni
lvmu=$(if [ $lvmt -eq 0 ]; then echo no; else echo yes; fi)							#dice se c'e una partizione con lvm
ctcp=$(cat /proc/net/sockstat{,6} | awk '$1 == "TCP:" {print $3}')						#prende il numero delle connessioni TCP
ulog=$(users | wc -w)												#prende il numero degli utenti loggati all'host corrente
ip=$(hostname -I)												#prende tutti gli indirizzi ip
mac=$(ip link show | awk '$1 == "link/ether" {print $2}')							#prende i mac delle intarfacce presenti
cmds=$(journalctl _COMM=sudo | grep COMMAND | wc -l)								#prende la conta dei comandi sudo lanciati
# Mostra il messaggio su tutte le console non grafiche
wall "	#Architecture: $arc
	#CPU physical: $pcpu
	#vCPU: $vcpu
	#Memory Usage: $uram/${fram}MB ($pram%)
	#Disk Usage: $udisk/${fdisk}Gb ($pdisk%)
	#CPU load: $cpul
	#Last boot: $lb
	#LVM use: $lvmu
	#Connexions TCP: $ctcp ESTABLISHED
	#User log: $ulog
	#Network: IP $ip ($mac)
	#Sudo: $cmds cmd"
