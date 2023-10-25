#!/bin/bash

# If you want to add your own commands before the service starts, you can do so below.
# Use '#' as a comment character to add comments. Leave blank lines for clarity.
# (MODIFY OUTSIDE THE DOCKER CONTAINER)

#TODO e' davvero necessario questa wait? non mi basta aver detto the questo container si basa su l'altro?
while ! mariadb -hmariadb -u$MYSQL_USER -p$MYSQL_PASSWORD $MYSQL_DATABASE; do
	echo 'Waiting for MariaDB to become available...'
	sleep 3
done

cd /var/WordPress
wp core download --allow-root
wp config create --dbname=$MYSQL_DATABASE --dbuser=$MYSQL_USER --dbpass=$MYSQL_PASSWORD --dbhost=$MYSQL_HOSTNAME:3306 --dbcharset="utf8mb4" --dbcollate="utf8_general_ci" --allow-root
wp core install --url=wordpress/wp-login.php --title=My_Unofficial_Site --admin_user=$WP_USER --admin_password=$WP_PASSWORD --admin_email=$WP_MAIL --skip-email --allow-root

wp plugin install akismet
wp theme install twentynineteen
wp plugin activate akismet
wp theme activate twentynineteen
# wp user create $WP_USER $WP_MAIL --role=author --user_pass=$WP_PASSWORD --allow-root
# wp theme install bizboost --activate --allow-root

# Since the environment variables are loaded after the ENTRYPOINT/CMD the container is here initialized and then executed.
# exec is used to replace PID 1 with the following process, as should be.
exec php-fpm7 -F -R
