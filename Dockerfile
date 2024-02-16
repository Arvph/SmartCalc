FROM ubuntu:latest

RUN apt-get update && apt-get install -y \
    build-essential \
    libgl1-mesa-dev \
    git \
    && rm -rf /var/lib/apt/lists/*

COPY src/ /src/
COPY build/ /build/

RUN cd /src/qt/ && qmake && make && make clean && rm -rf Makefile && mv SmartCalc.app ../../build/

CMD ["bin/bash"]

