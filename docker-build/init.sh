set -x

echo "Install necessary packages"
sudo apt install podman

echo "Building docker image"
podman build -f ./docker-build/Dockerfile -t "xr-driver:amd64"
