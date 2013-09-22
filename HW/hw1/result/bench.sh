bench() {
    for i in `seq 5`; do
    ./a.out && gprof -b | grep -A5 cum >> out
    done
    echo "=========================" >> out
}

g++ m.cpp -Dn=1000000 -pg
bench
g++ m.cpp -Dn=10000000 -pg
bench
g++ m.cpp -Dn=1000000 -pg -DR
bench
g++ m.cpp -Dn=10000000 -pg -DR
bench

g++ i.cpp -Dk=10000 -pg
bench
g++ i.cpp -Dk=100000 -pg
bench
g++ i.cpp -Dk=10000 -pg -DR
bench
g++ i.cpp -Dk=100000 -pg -DR
bench

g++ mi.cpp -DN=1000000 -pg
bench
g++ mi.cpp -DN=10000000 -pg
bench
