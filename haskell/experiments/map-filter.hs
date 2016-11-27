sumOfAllOddSquaresLessThan1000 = sum(takeWhile (<10000) [m | m <- [n^2 | n <- [1..]], odd m])
