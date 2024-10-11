use std::io::{self, read_to_string};

use nonogram::{
    problem::Problem, solver::Solver, solver_backtrack_inference::SolverBacktrackInference,
};

fn main() -> io::Result<()> {
    let puzzle = read_to_string(io::stdin())?;
    let mut iter = puzzle.split_ascii_whitespace();
    let width: usize = iter.next().unwrap().parse().unwrap();
    let height: usize = iter.next().unwrap().parse().unwrap();
    let puzzle = iter.next().unwrap();
    let puzzle = puzzle.split('/').collect::<Vec<_>>();
    let puzzle = puzzle
        .iter()
        .map(|line| {
            line.split('.')
                .map(|num| num.parse::<i32>().unwrap())
                .collect::<Vec<_>>()
        })
        .collect::<Vec<_>>();
    let col_info = puzzle[0..width].to_owned();
    let row_info = puzzle[width..(width + height)].to_owned();

    let puzzle = Problem { col_info, row_info };
    let mut solver = SolverBacktrackInference::new(&puzzle);
    let solution = solver.solve();

    // println!("题目: \n\n{}", puzzle);
    // println!("答案: \n\n{}", solution.unwrap());
    for row in solution.unwrap().grid {
        for cell in row {
            if cell {
                print!("y");
            } else {
                print!("n");
            }
        }
    }

    let param = iter.next().unwrap();
    print!(" {}", param);

    Ok(())
}
