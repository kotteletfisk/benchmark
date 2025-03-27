use std::time::Instant;

struct Node {
    data: i32,
    next: Option<Box<Node>>,
}

fn test_box_allocations(num_allocations: usize) {
    let start = Instant::now();

    for i in 0..num_allocations {
        let _n = Box::new(Node { data: i as i32, next: None });
    }

    let duration = start.elapsed();
    println!("Box<T> Allocation Time: {:?} ms", duration.as_millis());
}

fn test_vec_allocations(num_allocations: usize) {
    let start = Instant::now();

    let mut vec = Vec::with_capacity(num_allocations);
    for i in 0..num_allocations {
        vec.push(Node { data: i as i32, next: None });
    }

    let duration = start.elapsed();
    println!("Vec<T> Allocation Time: {:?} ms", duration.as_millis());
}

fn main() {
    let num_allocations = 1_000_000;

    test_box_allocations(num_allocations);
    test_vec_allocations(num_allocations);
}
