FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=Etc/UTC

# Update + basic tools
RUN apt update && apt install -y \
    build-essential \
    cmake \
    pkg-config \
    git \
    vim \
    nano \
    wget \
    curl \
    sudo \
    kmod \
    udev \
    && rm -rf /var/lib/apt/lists/*

# OpenGL / EGL / GLES / DRM / Mesa
RUN apt update && apt install -y \
    libgl1-mesa-dev \
    libegl1-mesa-dev \
    libgles2-mesa-dev \
    libdrm-dev \
    libgbm-dev \
    mesa-utils \
    mesa-utils-extra \
    libdrm-tests \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /workspace

CMD ["/bin/bash"]
