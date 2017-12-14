from miladiir/vitasdk:latest

ENV VITASDK /usr/local/vitasdk

# Install SDL2 and other VitaSDK libraries
RUN git clone https://github.com/vitasdk/vdpm;\ 
    cd vdpm;\ 
    ./install-all.sh;

RUN mkdir /app
ADD . /app/
WORKDIR /app

RUN mkdir texture_example/build;\
    mkdir joypad_example/build;

CMD cd /app/texture_example/build; cmake ..; make;\
    cd /app/joypad_example/build;  cmake ..; make;

