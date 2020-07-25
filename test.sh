for i in 2000000 5000000 8000000 10000000
do
    echo Testing $i Continuous Insertion
    ./build/test_R $i;
    ./build/test $i;
done

