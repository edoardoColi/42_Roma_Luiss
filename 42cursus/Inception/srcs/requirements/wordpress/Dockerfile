# Use the official Alpine Linux image as the base image
FROM alpine:3.14

# Install essential packages and upgrade the system
RUN apk --no-cache update && \
	apk --no-cache upgrade && \
	apk --no-cache add \
		bash \
		wget \
		tar \
		curl \
		mysql-client \
	&& rm -rf /var/cache/apk/*

# ENV PHP_VERSION 7.4.33  ## Version pinning not working

# Install PHP-FPM and its dependencies
RUN apk --no-cache add \
		php7 \
		php7-fpm \
		php7-ctype \
		php7-curl \
		php7-dom \
		php7-exif \
		php7-fileinfo \
		php7-gd \
		php7-iconv \
		php7-intl \
		php7-json \
		php7-ldap \
		php7-mbstring \
		php7-mysqli \
		php7-opcache \
		php7-openssl \
		php7-phar \
		php7-session \
		php7-simplexml \
		php7-sockets \
		php7-tokenizer \
		php7-xml \
		php7-xmlreader \
		php7-xmlwriter \
		php7-zlib

# Secure the directory which I'll interac with
RUN mkdir -p /var/WordPress
RUN mkdir -p /var/MySite
RUN mkdir -p /usr/local/bin
RUN mkdir -p /etc/php7/php-fpm.d

# Setup configuration files
COPY conf/php-fpm.conf /etc/php7/php-fpm.conf
RUN adduser -S nginx &&	addgroup -S nginx
COPY conf/www.conf /etc/php7/php-fpm.d/www.conf


# Inject mysite homepage
COPY conf/mysite /var/MySite

# Expose port 9000 on which the container will listen at runtime. Need to use 'docker run -p <port>' to publish the port, accessible from the host
EXPOSE 9000

# Install WORDPRESS and its dependencies directly
RUN apk --no-cache add \
		less \
		mariadb-client
WORKDIR /var/WordPress
RUN wget -q https://wordpress.org/latest.tar.gz && \
	tar -xzf latest.tar.gz && \
	mv ./wordpress/* . && \
	rm latest.tar.gz && rmdir wordpress/
COPY conf/wp-config.php wp-config.php
WORKDIR /
# Run the script and start Php-fpm in the foreground, here allow pool to run as root. Syntax: CMD["exec", "par1", "par2", ...]
CMD ["php-fpm7", "-F", "-R"]

# Install WORDPRESS using 'wp' CLI tool
# RUN curl -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar && \
#     chmod +x wp-cli.phar && \
#     mv wp-cli.phar /usr/local/bin/wp
# COPY tools/conf_start.sh /etc/conf_start
# RUN chmod +x /etc/conf_start
# # Run the script and start Php-fpm in the foreground, here allow pool to run as root. Syntax: CMD["exec", "par1", "par2", ...]
# CMD ["./etc/conf_start"]
