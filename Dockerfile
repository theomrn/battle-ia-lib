FROM ubuntu:22.04

RUN apt-get update && apt-get install -y --no-install-recommends ca-certificates && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*


RUN apt-get update && apt-get install -y \
    gcc \
    g++ \
    ninja-build \
    pkg-config \
    libboost-dev \
    libabsl-dev \
    protobuf-compiler \
    libprotobuf-dev \
    wget \
    unzip \
    pkg-config && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# Install system dependencies
RUN apt-get update && apt-get install -y \
    python3 \
    python3-pip \
    python3-setuptools \
    python3-wheel \
    && rm -rf /var/lib/apt/lists/*

# Install the latest version of Meson using pip
RUN pip3 install --upgrade pip \
    && pip3 install meson


WORKDIR /app 

COPY . .


RUN meson setup builddir/

RUN meson compile -C builddir/

CMD ["/app/builddir/battle_c_bot"]
