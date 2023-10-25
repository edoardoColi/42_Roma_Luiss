#!/bin/bash

# If you want to add your own commands before the service starts, you can do so below.
# Use '#' as a comment character to add comments. Leave blank lines for clarity.
# (MODIFY OUTSIDE THE DOCKER CONTAINER)

## Log in to MariaDB: Access your MariaDB server as a user with administrative privileges (typically the root user):
#   mysql -u root -p
## After successfully logging in, you can list all databases by running the following SQL query
#   SHOW DATABASES;
## To see more detailed information about each database, you can use:
#   SELECT * FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = '<nome>';
## The following SQL query will list all users and their privileges
#   SELECT user, host FROM mysql.user;
## The following SQL query will Show user privileges for a specific user
#   SHOW GRANTS FOR 'your_username'@'your_host';
## This query provides a list of all user privileges in the information_schema database
#   SELECT * FROM information_schema.user_privileges;

tfile=$(mktemp)
if [ ! -f "$tfile" ]; then
	return 1
fi
cat << EOF > $tfile
USE mysql;
FLUSH PRIVILEGES;

DELETE FROM	mysql.user WHERE User='';
DROP DATABASE test;
DELETE FROM mysql.db WHERE Db='test';
DELETE FROM mysql.user WHERE User='root' AND Host NOT IN ('localhost', '127.0.0.1', '::1');

ALTER USER 'root'@'localhost' IDENTIFIED BY '$MYSQL_ROOT_PASSWORD';

CREATE DATABASE $MYSQL_DATABASE CHARACTER SET utf8 COLLATE utf8_general_ci;
CREATE USER '$MYSQL_USER'@'%' IDENTIFIED by '$MYSQL_PASSWORD';
GRANT ALL PRIVILEGES ON $MYSQL_DATABASE.* TO '$MYSQL_USER'@'%';

FLUSH PRIVILEGES;
EOF

/usr/bin/mysqld --bootstrap < $tfile
rm -f $tfile

# Since the environment variables are loaded after the ENTRYPOINT/CMD the container is here initialized and then executed.
# exec is used to replace PID 1 with the following process, as should be.
exec mysqld --user=mysql --console

#??
# CMD ["mysqld", "--user=nginx", "--skip-name-resolve", "--skip-networking=0"]
# CMD ["mysqld", "--user=mysql", "--console"]
#??
