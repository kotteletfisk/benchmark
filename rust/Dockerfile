# Use Alpine Linux as base image
FROM alpine:latest

# Install necessary tools: curl, bash, gcc, musl-dev
RUN apk add --no-cache curl bash gcc musl-dev

# Install Rust (using rustup to install the toolchain)
RUN curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | bash -s -- -y

# Set environment variables for Rust
ENV PATH="/root/.cargo/bin:${PATH}"

# Set the working directory inside the container to the project folder
WORKDIR /soe_stat_rs

# Copy the content of the `soe_stat_rs` folder (where Cargo.toml is located) into the container
COPY soe_stat_rs /soe_stat_rs

# Build the Rust project using cargo
RUN cargo build --release

# List the files to verify the build output
RUN ls -l ./target/release/

# Set the default command to run the compiled binary
CMD ["./target/release/soe_stat_rs"]
