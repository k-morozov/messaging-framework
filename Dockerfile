FROM ubuntu:focal
MAINTAINER Konstantin Morozov <morozov-kst@yandex.ru>
ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && \
    apt-get install -y \
        build-essential make autoconf cmake git pkg-config \
        automake libtool curl g++ unzip \
        gcc g++ \
        python3-pip && \
        apt-get clean && \
        pip3 install conan
