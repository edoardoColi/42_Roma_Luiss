#!/bin/bash

# If you want to add your own commands before the service starts, you can do so below.
# Use '#' as a comment character to add comments. Leave blank lines for clarity.
# (MODIFY OUTSIDE THE DOCKER CONTAINER)

sed -i 's/^/# /' /etc/nginx/http.d/default.conf
