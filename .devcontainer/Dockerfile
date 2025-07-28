# Use Debian 12 as base
FROM debian:12

# Install dependencies
RUN apt-get update && \
    apt-get install -y \
        build-essential \
        gcc \
        g++ \
        cmake \
        git \
        wget \
        curl \
        pkg-config \
        libgl1-mesa-dev \
        libx11-dev \
        libxcursor-dev \
        libxrandr-dev \
        libxi-dev \
        libxinerama-dev \
        libxxf86vm-dev \
        libxext-dev \
        libasound2-dev \
        libpulse-dev \
        libopenal-dev \
        libvorbis-dev \
        libssl-dev \
        python3 \
        python3-pip

# Install Node.js (LTS) and npm
RUN curl -fsSL https://deb.nodesource.com/setup_lts.x | bash - && \
    apt-get install -y nodejs

# Install raylib (from source for latest version)
RUN git clone https://github.com/raysan5/raylib.git /tmp/raylib && \
    cd /tmp/raylib && \
    mkdir build && cd build && \
    cmake -DBUILD_SHARED_LIBS=ON .. && \
    make && make install && \
    ldconfig && \
    cd / && rm -rf /tmp/raylib

# Install Claude Code globally
RUN npm install -g @anthropic-ai/claude-code

# Set default user (VS Code devcontainers)
ARG USERNAME=vscode
ARG USER_UID=1000
ARG USER_GID=$USER_UID

RUN groupadd --gid $USER_GID $USERNAME \
    && useradd --uid $USER_UID --gid $USER_GID -m $USERNAME

USER $USERNAME

WORKDIR /workspace