#!/bin/sh

while ! mariadb -h$MYSQL_HOSTNAME -u$MYSQL_USER -p$MYSQL_PASSWORD $MYSQL_DATABASE &>/dev/null; do
	echo 'Waiting for MariaDB to become available...'
    sleep 3
done

if [ ! -f "/var/www/html/index.html" ]; then

    # static website
    mv /tmp/unofficialWebsite/* /var/www/html/

    wp core download --allow-root
    wp config create --dbname=$MYSQL_DATABASE --dbuser=$MYSQL_USER --dbpass=$MYSQL_PASSWORD --dbhost=$MYSQL_HOSTNAME --dbcharset="utf8" --dbcollate="utf8_general_ci" --allow-root
    wp core install --url=$DOMAIN_NAME/wordpress --title=unofficialWebsite --admin_user=$WP_USER_ADMIN --admin_password=$WP_PWD_ADMIN --admin_email=$WP_EMAIL_ADMIN --skip-email --allow-root
    wp user create $WP_USER_ADMIN $WP_EMAIL_ADMIN --role=author --user_pass=$WP_PWD_ADMIN --allow-root
    wp theme install bizboost --activate --allow-root
fi

exec /usr/sbin/php-fpm7 -F -R