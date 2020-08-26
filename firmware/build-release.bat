mkdir %~dp0build
cd %~dp0build

cmake -DCMAKE_BUILD_TYPE=Release -G "Ninja" ..

ninja -j 8 %*
