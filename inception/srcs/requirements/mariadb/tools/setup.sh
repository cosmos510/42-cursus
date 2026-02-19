#!/bin/bash

MYSQL_ROOT_PASSWORD=$(cat $MYSQL_ROOT_PASSWORD_FILE)
MYSQL_PASSWORD=$(cat $MYSQL_PASSWORD_FILE)

if [ ! -d "/var/lib/mysql/$MYSQL_DATABASE" ]; then
    mysql_install_db --user=mysql --datadir=/var/lib/mysql

    mysqld_safe --datadir=/var/lib/mysql &
    sleep 10

    mysql -e "CREATE DATABASE IF NOT EXISTS $MYSQL_DATABASE;"
    mysql -e "CREATE USER IF NOT EXISTS '$MYSQL_USER'@'%' IDENTIFIED BY '$MYSQL_PASSWORD';"
    mysql -e "GRANT ALL PRIVILEGES ON $MYSQL_DATABASE.* TO '$MYSQL_USER'@'%';"
    mysql -e "ALTER USER 'root'@'localhost' IDENTIFIED BY '$MYSQL_ROOT_PASSWORD';"
    mysql -e "FLUSH PRIVILEGES;"

    mysqladmin -u root -p$MYSQL_ROOT_PASSWORD shutdown
fi

mysqld_safe --datadir=/var/lib/mysql