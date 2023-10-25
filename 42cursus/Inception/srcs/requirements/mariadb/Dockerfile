# Use the official Alpine Linux image as the base image
FROM alpine:3.14

# Install essential packages and upgrade the system
RUN apk --no-cache update && \
	apk --no-cache upgrade && \
	apk --no-cache add \
		bash \
	&& rm -rf /var/cache/apk/*

# Install MARIADB and its dependencies
RUN apk --no-cache add \
		mariadb \
		mariadb-client

# Secure the directory which I'll interac with
RUN mkdir -p /var/run/mysqld \
	mkdir -p /var/MariaDB \
	&& chown -R mysql:mysql /var/run/mysqld \
	&& chown -R mysql:mysql /var/MariaDB

# Setup configuration files
RUN mysql_install_db --user=mysql --datadir=/var/MariaDB --basedir=/usr
COPY conf/mariadb-server.cnf /etc/my.cnf.d/mariadb-server.cnf

# Expose port 3306 on which the container will listen at runtime. Need to use 'docker run -p <port>' to publish the port, accessible from the host
EXPOSE 3306

COPY tools/conf_start.sh /etc/conf_start
RUN chmod +x /etc/conf_start

# Run the script and start MariaDB server. Syntax: CMD["exec", "par1", "par2", ...]
CMD ["./etc/conf_start"]
