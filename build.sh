g++ get.cpp -o get -lssl -lcrypto
g++ submit.cpp -o submit -lssl -lcrypto
cd ./nonogram_solve
cargo build --release