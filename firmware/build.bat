cmake -DCMAKE_BUILD_TYPE=Debug -G "Ninja" .

ninja -j 8 %*
