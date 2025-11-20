FROM debian:bullseye

RUN apt-get update && apt-get install -y \
    php8.1-fpm \
    php8.1-mysql \
    php8.1-curl \
    php8.1-gd \
    php8.1-xml \
    php8.1-mbstring \
    php8.1-zip \
    wget \
    mariadb-client \
    && rm -rf /var/lib/apt/lists/*

RUN mkdir -p /var/www/html && \
    wget https://wordpress.org/latest.tar.gz && \
    tar -xzf latest.tar.gz && \
    mv wordpress/* /var/www/html/ && \
    rm -rf wordpress latest.tar.gz

RUN wget https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar && \
    chmod +x wp-cli.phar && \
    mv wp-cli.phar /usr/local/bin/wp

COPY conf/www.conf /etc/php/8.1/fpm/pool.d/www.conf
COPY tools/setup.sh /setup.sh

RUN chmod +x /setup.sh

WORKDIR /var/www/html

EXPOSE 9000

CMD ["/setup.sh"]