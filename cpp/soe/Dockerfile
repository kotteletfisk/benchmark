# Use Alpine Linux as base
FROM alpine:latest

# Install g++ and necessary build tools
RUN apk add --no-cache g++ make

# Set working directory
WORKDIR /app

# Copy the C++ source file into the container
COPY soe_stats.cpp .

# Compile the C++ program
RUN g++ -o soe_stats soe_stats.cpp

# Set the default command to run the compiled binary
CMD ["./soe_stats"]