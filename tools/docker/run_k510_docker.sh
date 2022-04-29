# !/bin/sh

if [ ! -e ccache ]; then
	mkdir ccache
fi

if [ ! -e k510_buildroot ]; then
	mkdir k510_buildroot
fi

sudo docker run --name k510build --rm -it \
	--user "$(id -u):$(id -g)" --env "HOME=/root" \
	-v "$(pwd)/k510_buildroot:/opt/k510_buildroot" \
	-v "$(pwd)/ccache:/opt/build-cache" \
	-v "/etc/passwd:/etc/passwd:ro" \
	-v "/etc/group:/etc/group:ro" \
	ghcr.io/kendryte/k510_env:latest bash
