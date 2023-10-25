# Use the official Alpine Linux image as the base image
FROM alpine:3.14

# Install essential packages and upgrade the system
RUN apk --no-cache update && \
	apk --no-cache upgrade && \
	apk --no-cache add \
		bash \
		openssl \
	&& rm -rf /var/cache/apk/*

# Install Nginx and its dependencies
RUN apk --no-cache add \
		nginx

# Secure the directory which I'll interac with
RUN mkdir -p /etc/nginx/ssl/

# Setup configuration files
COPY conf/nginx.conf /etc/nginx/nginx.conf
COPY conf/inception.conf /etc/nginx/http.d/inception.conf
COPY tools/configure.sh /etc/configuration
# All other RUN below command could also be included in the script 'configure.sh'
RUN chmod +x /etc/configuration && ./etc/configuration

# Generate a self-signed SSL/TLS certificate and key for the domain "ecoli.42.fr"
RUN openssl req -newkey rsa:2048 -x509 -sha256 -days 365 -nodes \
	-out /etc/nginx/ssl/inception.crt \
	-keyout /etc/nginx/ssl/inception.key \
	-subj "/C=IT/ST=Lazio(State)/L=Rome(Location)/O=42Ecole(Organization)/OU=ecoli(OrganizationalUnit)/CN=ecoli.42.fr/" \
	-addext "subjectAltName = DNS:www.ecoli.42.fr"

# Expose port 443 on which thr container will listen at runtime. Need to use 'docker run -p <port>' to publish the port, accessible from the host
EXPOSE 443

# Start Nginx in the foreground when the container is run. Syntax: CMD["exec", "par1", "par2", ...]
CMD ["nginx", "-g", "daemon off;"]
