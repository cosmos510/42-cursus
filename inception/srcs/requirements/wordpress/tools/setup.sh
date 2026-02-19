#!/bin/bash

WORDPRESS_DB_PASSWORD=$(cat $WORDPRESS_DB_PASSWORD_FILE)
WORDPRESS_ADMIN_PASSWORD=$(cat $WORDPRESS_ADMIN_PASSWORD_FILE)
WORDPRESS_USER_PASSWORD=$(cat $WORDPRESS_USER_PASSWORD_FILE)

mkdir -p /run/php
sleep 15

while ! mysql -h mariadb -u $WORDPRESS_DB_USER -p$WORDPRESS_DB_PASSWORD -e "SELECT 1" >/dev/null 2>&1; do
    echo "Waiting for MariaDB..."
    sleep 2
done

if [ ! -f /var/www/html/wp-config.php ]; then
    wp config create --dbname=$WORDPRESS_DB_NAME --dbuser=$WORDPRESS_DB_USER --dbpass=$WORDPRESS_DB_PASSWORD --dbhost=$WORDPRESS_DB_HOST --allow-root

    wp core install --url=$DOMAIN_NAME --title="Inception" --admin_user=$WORDPRESS_ADMIN_USER --admin_password=$WORDPRESS_ADMIN_PASSWORD --admin_email=$WORDPRESS_ADMIN_EMAIL --allow-root

    wp user create $WORDPRESS_USER $WORDPRESS_USER_EMAIL --user_pass=$WORDPRESS_USER_PASSWORD --allow-root
fi

chown -R www-data:www-data /var/www/html

php-fpm7.4 -F