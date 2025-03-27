# First stage: Build the Rust program using the official Rust image
FROM rust:latest AS builder

WORKDIR /app

# Install musl tools
RUN rustup target add x86_64-unknown-linux-musl

# Copy cargo files first to optimize Docker layer caching
COPY Cargo.toml Cargo.lock ./
RUN mkdir src && echo "fn main() {}" > src/main.rs
RUN cargo fetch

# Copy the actual source code and build it statically
COPY . .
RUN cargo build --release --target=x86_64-unknown-linux-musl

# Second stage: Minimal Alpine container for final deployment
FROM alpine:latest

# No need for libgcc/libstdc++ since it's statically linked
COPY --from=builder /app/target/x86_64-unknown-linux-musl/release/soe_stat_rs /usr/local/bin/soe_stat_rs

# Ensure binary is executable
RUN chmod +x /usr/local/bin/soe_stat_rs

CMD ["/usr/local/bin/soe_stat_rs"]