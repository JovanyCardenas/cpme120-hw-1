FROM gcc:13

WORKDIR /app


CMD ["bash", "-c", "gcc -Wall -Wextra -o utf8_analyzer utf8_analyzer.c && ./utf8_analyzer"]
