for i in 2000000 4000000 8000000 10000000
do
    echo Testing $i Continuous Insertion
    ./build/test $i;
    ./build/test_R $i;
done

