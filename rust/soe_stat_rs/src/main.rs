use libc::{getrusage, rusage, RUSAGE_SELF};
fn main() {
    let i: usize = 10000000;
    let mut count: i32 = 0;
    use std::time::Instant;

    let now: Instant = Instant::now();
    let res: Vec<bool> = sieve(i);
    let elapsed: f64 = now.elapsed().as_secs_f64();

    for val in res.iter() {
        if *val {
            count += 1;
        }
    }

    println!("Prime numbers found: {}", count);
    println!("Time in seconds: {:.6?}", elapsed);
    println!("Memory usage in bytes: {}", get_mem_usage());
}

fn get_mem_usage() -> i64 {

    let mut usage: rusage = unsafe { std::mem::zeroed() };
    let result: i32 = unsafe { getrusage(RUSAGE_SELF, &mut usage) };

    if result == 0 {
        return usage.ru_maxrss;
    }
    else {
        eprint!("Failed to call libc getrusage");
    }
    return 0;
}

fn sieve(n: usize) -> Vec<bool>{

    // Initialize Sieve Array with all elements initially set to True
    let mut sieve_array: Vec<bool> = vec![true; n+1];

    // Set arr[0] and arr[1] to false, because 0 and 1 are not prime
    sieve_array[0] =  false;
    sieve_array[1] = false;

    // Traverse from 2 to n
    // If a number is prime, mark all its multiples except number itself as false
    for i in 2..n+1 {
        if sieve_array[i] {

            // Mark all the multiples except number itself as false
            for j in (2*i..n+1).step_by(i) {
                sieve_array[j] = false;
            }
        }
    }

    return sieve_array;
}