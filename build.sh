g++ get.cpp log.cpp -o get -lssl -lcrypto
g++ submit.cpp log.cpp -o submit -lssl -lcrypto
cd ./nonogram_solve
cargo build --release