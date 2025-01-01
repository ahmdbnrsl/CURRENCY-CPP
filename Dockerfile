FROM ubuntu:20.04

RUN apt update && apt install -y \
build-essential \
zip \
unzip \
curl \
git