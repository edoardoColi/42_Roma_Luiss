# Use the official Alpine Linux image as the base image
FROM alpine:3.13

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

# Expose port 3306 on which the container will listen at runtime. Need to use 'docker run -p <port>' to publish the port, accessible from the host
EXPOSE 3306

COPY tools/configure.sh /tmp/configure.sh
ENTRYPOINT ["sh", "/tmp/configure.sh"]

# come fare login nel database per testare password di root e personale
# mysql -u username -p
# SHOW DATABASES;
# USE wordpress;
# SHOW TABLES;
