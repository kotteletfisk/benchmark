
FROM alpine:latest

RUN apk add --no-cache g++ make

WORKDIR /app

COPY memory_allo.cpp .

RUN g++ -o memory_allo memory_allo.cpp

CMD ["./memory_allo"]
