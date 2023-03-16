# !/bin/sh

if [ ! -e ccache ]; then
	mkdir ccache
fi

if [ ! -e k510_buildroot ]; then
	mkdir k510_buildroot
fi

docker run --name k510build --rm -it \
	-v "$(pwd)/k510_buildroot:/opt/k510_buildroot" \
	-v "$(pwd)/ccache:/opt/build-cache" \
	ghcr.io/kendryte/k510_env:latest bash
