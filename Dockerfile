FROM gcc:latest

WORKDIR /app

RUN apt update -y && \
    apt install -y cppcheck clang-tidy python3-pip libc6-dbg cmake libgtest-dev
RUN pip install cpplint

COPY ./src ./src
COPY ./include ./include
COPY ./tests ./tests
COPY CMakeLists.txt .
COPY CPPLINT.cfg .
COPY cpplint.py .

RUN cmake . && \
    make

ENTRYPOINT ["./matrix_calculator_test", "./vector_test"]