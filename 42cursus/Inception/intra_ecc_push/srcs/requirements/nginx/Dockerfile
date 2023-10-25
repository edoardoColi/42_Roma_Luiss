FROM debian:buster

RUN apt-get update && \
    apt-get install -y \
        build-essential \
        perl \
        nginx \
        bash \
        openssl && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

RUN apt-get install -y \
        nginx

# Crea la directory per i socket di nginx
RUN mkdir -p /run/nginx  

COPY conf/nginx.conf /etc/nginx/conf.d/default.conf

RUN mkdir /etc/nginx/ssl

# Genera un certificato SSL autofirmato per HTTPS
RUN openssl req -newkey rsa:4096 -x509 -sha256 -days 365 -nodes \
       -out /etc/nginx/ssl/ecoli.crt \
       -keyout /etc/nginx/ssl/ecoli.key \
       -subj "/C=IT/ST=Rome/L=Rome/O=42 School/OU=ecoli/CN=ecoli/"

EXPOSE 443

CMD ["nginx", "-g", "daemon off;"]
