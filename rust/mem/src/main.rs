use libc::{getrusage, rusage, RUSAGE_SELF};
use std::time::Instant;
use rand::seq::SliceRandom;

fn main() {

    const NUM_OBJECTS: usize = 1_000_000;
    let mut objects: Vec<Box<LargeObject>> = Vec::with_capacity(NUM_OBJECTS);

    let start_alloc = Instant::now();
    for _ in 0..NUM_OBJECTS {
        objects.push(Box::new(LargeObject { data: [0; 1024] }));
    }
    let end_alloc = Instant::now();
    
    objects.shuffle(&mut rand::rng()); // shuffle
    
    let start_dealloc = Instant::now();
    drop(objects); // Deallocate all objects
    let end_dealloc = Instant::now();
    
    println!("Total test time: {} seconds", (end_dealloc - start_alloc).as_secs_f64());
    println!("Allocation Time: {:.6} seconds", (end_alloc - start_alloc).as_secs_f64());
    println!("Deallocation Time: {:.6} seconds", (end_dealloc - start_dealloc).as_secs_f64());
    println!("Memory usage: {} Kb ({} mb)", get_mem_usage(), get_mem_usage() / 1024);
}

// struct representing a large data object
#[derive(Clone)]
struct LargeObject {
    data: [u8; 1024], // 1KB of data
}

// get memory usage in bytes
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
