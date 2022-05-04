# Born2beroot CentOS Stream

## Table of Contents
1. [Operating System](#operating-system)
2. [Installation](#installation)
3. [Packages Installed During Setup](#packages-installed-during-setup)
4. [Logical Volume Manager (LVM)](#logical-volume-manager-lvm)
5. [SELinux](#selinux)
6. [Secure SHell (SSH)](#secure-shell-ssh)
 	- [Connect from Outside](#connect-from-outside)
7. [Uncomplicated FireWall (UFW)](#uncomplicated-firewall-ufw)
8. [Password Policy and Sudo Configuration](#password-policy-and-sudo-configuration)
9. [Setup Groups and Users](#setup-groups-and-users)
10. [Timer Script](#timer-script)
11. [Bonus Project Part](#bonus-project-part)
	- [WordPress Service](#wordpress-service)
	- [FTP Service](#ftp-service)
	- [Use Services](#use-services)
12. [Documentation Sources](#documentation-sources)

## Operating System
In questo progetto utilizziamo [CentOS](https://www.centos.org/) basata su Red Hat Enterprise Linux. Attualmente la versione consigliata è CentOS Stream 8 che disporrà di aggiornamenti (EOL) fino al 31 Maggio 2024.  
L'immagine di sistema puó essere utilizzata sia all'interno di una macchina virtuale oppourtunamente configurata sia in un sistema dedicato (a seguito non si tratterá la configurazione della MV).  
É consigliato verificare la *sha-sum* del file scaricato prima di usare l'iso.  

## Installation
Nel caso si presentasse l'errore `FATAL: No bootable medium found! System halted` l'immagine di sistama non è stata caricata correttamente.  
Nella schermata iniziale installare CentOs selezionando la voce `Install CentOS Stream 8-stream`, partirà l'installazione e chiederà di inserire alcuni parametri di setup.  
<img src=https://github.com/edoardoColi/42_Roma_Luiss/blob/edoardoColi/42cursus/Born2beroot/Installer.png width="60%" height="60%">
```
USER SETTINGS > impostare la password per root
SYSTEM 	      > Network & Host Name      > selezionare e attivare una rete
	      > Installation Destination > selezionare la partizione sulla quale installare il sistema, se si desidera partizionare in modo specifico il disco si può scegliere l'operazione customizzata di partizione invece di quella automatica.
SOFTWERE      > Installation Source      > scegliere come opzione Closest Mirror come sorgente per l'installazione
	      > Softwere Selection       > Base Environment    > opzione Minimal Install
	   				 > Additional Softwere > ciò che ci serve verrà installato in seguito da terminale
(le scelte sono basate sulle specifiche del subject del progetto)

	Begin Installation >> Reboot System
```
Se l'installazione non fa a buon fine ritenta.  
Se volessimo cambiare l'hostname del sistema possiamo farlo con il comando `hostnamectl set-hostname <NOME>`.  
Per verificare le informazioni usiamo `hostnamectl`.

## Packages Installed During Setup
```
dnf install nano
dnf install openssh-server
dnf install /usr/sbin/semanage
dnf whatprovides /usr/sbin/semanage
dnf install -y epel-release
dnf install --enablerepo="epel" -y ufw
dnf install vsftpd
```
DNF è un nuovo packet manager disponibile su _fedora_ dalla versione 18. Ha l'obiettivo di rimpiazzare `yum` nel lungo periodo. Essendo `dnf` un fork di _dnf_ vengono mantenuti tutti i vecchi comandi avendo però prestazioni migliori.  
I vari comandi lanciati durante la guida vengono interpretati come eseguiti dall'utente root.

## Logical Volume Manager (LVM)
É un gestore logico dei volumi che ci permette di gestire le partizioni all'interno del disco. Per visualizzare le partizioni possiamo usare `lsblk`.  
Tuttavia non possiamo partizionare il disco dopo aver avviato la macchina virtuale perchè non possiamo agire sullo spazio di memoria che è attulmente montato e in uso; perciò dobbiamo creare il partizionamento durante l'installazione tramite l'opzione _'partizionamento manuale'_ messo a disposizione dall'installer.

## SELinux
É un architettura di sicurezza che dà la possibilità agli amministratori di sistema di gestire permessi e autorizzazioni degli utenti nel sistema.  
- Configuration  
Per determinare le applicazioni che il sistema è autorizzato a eseguire vediamo il file di configurazione con  
`cat /etc/sysconfig/selinux` per modificarlo possiamo usare  
```
nano /etc/sysconfig/selinux
```
Per controllare lo stato di SELinux possiamo usare `getenforce`, oppure `sestatus` per un output piu verboso.  

## Secure SHell (SSH)
Per verificare che il Secure Shell protocoll sia attivo possiamo verificare lo stato del servizio tramite `systemctl status sshd` e verifichiamo ci sia scritto _"active(running)"_. Nel caso non sia installato possiamo rimediare lanciando `dnf install openssh-server`.  
Ora che il servizio é presente impostiamo i vari parametri nel file di configuraazione `/etc/ssh/sshd_config` :
- Evitiamo che si possa accedere da remoto come root settando il parametro `PermitRootLogin` da **yes** a **no** oppure levando il commento alla riga
```
#PermitRootLogin no
```
- Imponiamo la porta ssh settando il parametro `Port` da 22(default) a quello che preferiamo, levando il commento alla riga
```
#Port 22
```
Affinche SELinux permetta di utilizzare la nuova porta utilizziamo il comando `semanage port -a -t ssh_port_t -p tcp NUMPORT` specificado la porta impostata nel file di configurazione. Facendo ció aggiungiamo la porta a quelle utilizzabili per ssh, per controllare tale lista possiamo usare `semanage port -l | grep ssh_port_t`.  
Per maggiori informazioni controllare il manuale `man semanage`.  
Per riavviare il servisio possiamo utilizzare `systemctl restart sshd.service` oppure direttamente `reboot`.
### Connect from Outside
Nel caso ci trovassimo su una macchina virtuale dovremo abilitare all'interno di Settings > Network > Advanced > PortForwarding il mapping della porta \<PORT\> in quella su cui è attivo il server ssh.  
Verificato l'indirizzo e la porta su cui si trova il server ssh tramite `systemctl status sshd`  
ci possiamo collegare da un terminale esterno con `ssh <username>@<ip> -p <port>`. Prima di utilizzare il servizio dobbiamo adattare il firewall ai cambiamenti. Dobbiamo abilitare la porta per il collegamento SSH.

## Uncomplicated FireWall (UFW)
Utilizziamo il Uncomplicated FireWall per controllare il traffico in entrata e in uscita del dispositivo, per farlo dobbiamo impostare delle regole di firewall.  
Dopo averlo installato con `dnf install -y epel-release` e `dnf install --enablerepo="epel" -y ufw` dobbiamo attivarlo con `ufw enable` poi controllare con `ufw status`, inoltre dobbiamo abilitare l'esecuzione durante l'accensione con `systemctl enable ufw`.  
Il file di configurazione é `/etc/default/ufw`, all'interno del quale possiamo specificare alla voce IPV6 se supportarlo `IPV6=yes` oppure no `IPV6=no`.  
Dato che vogliamo avere solo la regola relativa alla porta 4242 cancelliamo tutte le altre con `ufw delete NUM` dove NUM corrisponde alla riga della regola come descritto dal comando `ufw status numbered`.  
Inizziamo ad aggiungere delle restrizioni bloccando tutto il traffico in ingresso `ufw default deny incoming` e consentendo tutto quello in uscita `ufw default allow outgoing`. Possiamo aggiungere una regola che consente/blocchi il traffico per uno specifico servizio come `ufw allow/deny ssh` oppure `ufw allow/deny https`; possiamo aggiungere anche regole per porte specifiche come `ufw allow/deny 4242`; possiamo utilizzare [diverse conbinazioni](https://www.digitalocean.com/community/tutorials/ufw-essentials-common-firewall-rules-and-commands) in base alle nostre esigenze.  

## Password Policy and Sudo Configuration
Per questo aspetto utilizzeremo il PAM pwquality molude.  
- Il file di configurazione relativo alle restrizioni della password per gli utenti è `/etc/security/pwquality.conf`. Andiamo quindi a modificare i parametri al suo interno levando il commento e settando valori specifici.  
La password:
	- deve essere lunga almeno 10 caratteri
	```
	minlen = 10
	```
	- deve contenere una maiuscola e un numero
	```
	dcredit = -1
	ucredit = -1
	```
	- non deve contenere lo stesso carattere piú di 3 volte di seguito
	```
	maxrepeat = 3
	```
	- non deve includere il nome utente
	```
	usersubstr = 1
	```
	- deve avere almeno 7 caratteri che non fanno parte della precedente password (non si applica per Root)
	```
	difok = 7
	```
	- Anche root deve rispettare la stessa policy quindi leviamo il commento a
	```
	#enforce_for_root
	```

- Per le restrizioni riguardanti il rinnovo della password modifichiamo `/etc/login.defs`. Andiamo quindi a modificare i parametri al suo interno levando il commento e settando valori specifici.
	- deve scadere ogni 30 giorni
	```
	PASS_MAX_DAYS 30
	```
	- puó essere modificata non prima di 2 giorni dall'ultima modifica
	```
	PASS_MIN_DAYS 2
	```
	- l'utente deve ricevere un messaggio 7 giorni prima che scada la password
	```
	PASS_WARN_AGE 7
	```
	_dato che questi cambimenti influenzano solo i nuovi utenti per riportare gli stessi parametri anche sui vecchi possiamo usare `chage -M 30 <USER>`, `chage -m 2 <USER>` e `chage -W 7 <USER>`._
	- deve essere lunga minimo 10 caratteri
	```
	PASS_MIN_LEN 10
	```

- Configurazione per il gruppo sudo:  
possiamo abilitare le seguenti opzioni aggiungendo alla fine del file di configurazione `/etc/sudoers`
	- l'autenticazione sudo é limitata a 3 tentativi
	```
	Defaults	passwd_tries=3
	```
	- messaggio personalizzato \<ERROR-MESSAGE\> quando si sbaglia la password per l'autenticazione sudo
	```
	Defaults	badpass_message="<ERROR-MESSAGE>"
	```
	- ogni azione da sudoer deve essere salvata in un log file all'interno della cartella /var/log/sudo.  
	Poichè non possiamo assumere che la cartella sia presente utilizzare il comando `mkdir /var/log/sudo` e definiamo all'interno il nome del file designato \<FILENAME\>.  
	```
	Defaults	logfile="/var/log/sudo/<FILENAME>"
	Defaults	log_input,log_output
	Defaults	iolog_dir="/var/log/sudo"
	```
	- Attivare la modalitá TTY per sicurezza
	```
	Defaults	requiretty
	```
	- I percorsi utilizzabili da sudo devono essere ristretti a `/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/snap/bin`
	```
	Defaults	secure_path="/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/snap/bin"
	```

Ora dobbiamo verificare e cambiare le password di tutti gli utenti, root compreso.  
Possiamo utilizzare `chage -l username` per controllare alcuni attributi.  

## Setup Groups and Users
- Gruppi  
Per poter aggiungere un nuovo gruppo \<NEW_GROUP\> possiamo utilizzare il comando `groupadd <NEW_GROUP>`. In questo modo verrà aggiunta la voce \<NEW_GROUP\> ai file `/etc/group` e `/etc/gshadow`, nel caso un gruppo con lo stesso nome sia già presente verrà stampato un messaggio di errore.  
Per cancellare un gruppo \<OLD_GROUP\> possiamo utilizzare il comando `groupdel <OLD_GROUP>`. In questo modo verrà rimossa la voce \<OLD_GROUP\> ai file `/etc/group` e `/etc/gshadow`, nel caso un gruppo con lo stesso nome non sia presente verrà stampato un messaggio di errore.  
Per verificare la stato dei gruppi degli utenti si può utilizzare `groups`. Per maggiori dettagli consultare il manuale.  
- Utenti  
Per aggiungere un Utente utilizziamo `adduser username`  
in questo modo verrà creata la directory del nuovo utente(/home/username) e inizializzata come `/etc/skel`.  
Successivamente dovrà essere impostata una password utente tramite `passwd username`.  
Per rimuovere un Utente utilizziamo `userdel username` e nel caso volessimo cancellare anche la directory dell'utente  `userdel -r username`  
la rimozione dell'utente comprende anche la rimozione da tutti i gruppi in cui l'utente era membro.  
  
Possiamo aggiungere i nuovi utenti ai gruppi, per farlo utilizziamo  
`usermod -aG wheel username`  
Possiamo ache rimuovere un utente da un gruppo con `gpasswd -d username wheel`  
All'interno dei comandi utilizziamo il gruppo `wheel` che corrisponde al gruppo di utenti che può utilizzare il comando sudo, come specificato nel file `/etc/sudoers`.  

## Timer Script
Per impostare un azione ripetuta all'interno del server possiamo utilizzare il comando `crontab`, ogni utente può avere il proprio cron tab.  
Dobbiamo specificare dove si trova lo script da far eseguire. Creiamo il file `cronscript.sh` secondo cio che vogliamo mostrare e utilizzaimo `crontab -u username -e` (come username possiamo mettere _root_).  
L'opzione `-e` permette di editare il file relativo al crontab, troviamo le informazioni dettagliate sulla sintassi del comando nel file `/etc/crontab`.  
Scriviamo quindi 
```
SHELL=/bin/sh

#run the script every 10 minutes
# /path/to deve essere modificato in base a dove si trova il file contenente lo script
*/10 * * * * /path/to/cronscript.sh
```
Se lo script necessita di alcuni comandi specifici relativi alle reti possiamo installarli con l'aiuto di dnf.  
Per maggiorni dettagli consultare il manuale `man crontab`.  

## Bonus Project Part
### WordPress Service
```
Jumped
```
### FTP Service
Il File Transfer Protocol è un protocollo che permette di caricare e scaricare file in modo facile.  
Per instalare queesto servizio utilizziamo il comando `dnf install vsftpd`, installiamo cosi il Very Secure FTP Daemon. Per avviare il servizio usiamo `systemctl start vsftpd` e affinche sia abilitata l'esecuzione durante l'accensione lanciamo `systemctl enable vsftpd`.  
Per verificare lo stato del servizio usiamo `systemctl status vsftpd`.  
Impostiamo i vari parametri si ricurezza del servizio modificando `/etc/vsftpd/vsftp.conf`  
Consentiamo di usare il servizio solo agli utenti locali impostando
```
anonymous_enable=NO
local_enable=YES
```
Per consentire di caricare e modificare i file impostiamo
```
write_enable=YES
```
Per bloccare l'accesso all'esterno della propria cartella utente e garantire l'accesso alla propria impostiamo
```
chroot_local_user=YES
allow_writeable_chroot=YES
```
Specifichiamo un range di porte per consentire connessioni FTP passive. Ricordiamoci che tali porte dovranno essere aperte nel firewall. 
```
pasv_min_port=30000
pasv_max_port=31000
```
Specifichiamo la lista degli utenti che possono usare il servizio in `/etc/vsftpd/user_list`.
```
userlist_file=/etc/vsftpd/user_list
userlist_deny=NO
```
È anche possibile configurare Secure Sockets Layer (SSL) con FTP e per farlo dobbiamo generare un certificato e impostare dove questo si trova con
```
rsa_cert_file=/etc/vsftpd/vsftpd.pem
rsa_private_key_file=/etc/vsftpd.pem
ssl_enable=YES
```
per generare  il certificato possiamo usare il comando `openssl req -x509 -nodes -days 3650 -newkey rsa:2048 -keyout /etc/vsftpd.pem -out /etc/vsftpd/vsftpd.pem`.  
Prima di utilizzare il servizio dobbiamo adattare il firewall ai cambiamenti. Dobbiamo abilitare la porta **21** per il collegamento FTP, la porta **20** e l'intervallo **30000-31000** per lo scambio dati Attivo e Pasivo con il server. Utilizziamo allora i comandi  
`ufw allow 20`  
`ufw allow 21`  
`ufw allow 30000:31000/tcp`  
`ufw allow 30000:31000/udp`  
per abilitare le porte e in fine riavviamo entrambi i sevizi con `systemctl restart ufw` e `systemctl restart vsftpd`.
### Use Services
Per utilizzare FTP da terminale abbiamo bisogno di indirizzo e porta del server, possiamo trovare queste informazioni tramite `systemctl status vsftpd`.  
A questo punto possiamo lanciare `ftp <ip>` e in seguito ci verrà chiesto di inserire username e password. Non avendo specificato una porta userà quella di default (21).

## Documentation Sources
- https://www.extraordy.com/linux-struttura-di-partizioni-e-partizionamentro-tramite-lvm/
- https://www.fosslinux.com/43884/apt-vs-aptitude.htm?amp=1
- https://www.redhat.com/it/topics/linux/what-is-selinux
- https://apparmor.net/
- https://docs.centos.org/en-US/centos/install-guide/CustomSpoke-ppc64/
- [ecc...](https://askubuntu.com/questions/950307/why-guided-partitioning-create-a-sda2-of-1-kb)
