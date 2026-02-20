FROM dtcooper/raspberrypi-os:bookworm

WORKDIR /workspace

RUN apt update

RUN apt-get update && apt-get install -y \
    build-essential \
    make \
    cmake \
    libboost-all-dev \
    iputils-ping \
    curl \
    tar

RUN curl -OL https://github.com/WiringPi/WiringPi/releases/download/3.18/wiringpi_3.18_arm64.deb
RUN apt install -y ./wiringpi_3.18_arm64.deb

RUN mkdir src
COPY src/ ./src/
COPY CMakeLists.txt .

RUN cmake -B ./build -S .
RUN cmake --build ./build

EXPOSE 8080/tcp
EXPOSE 8080/udp
# CMD ./build/src/server
# CMD ./build/src/server 0.0.0.0 8080

