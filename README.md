## program calculates fractals in parallel and creates fractal images

The program usage is: ./fractal_gen \<option-s\>\
#when no options are given the program runs on the defaults


options are:\
-F M(mandelbrot) B(burningship) | fractal type, default M\
-P pos num | fractal equation power, default 2\
-R pos num | range of fractal, default 4\
-C num,num | farctal center, default -0.6,0\
-M pos num | fractal equation max number of iterations, default 100\
-T pos num | number of threads to be used, default 1\
-J nosubopt | conjugate fractal equation(neg power), default not\
-Q SD(480p) ED(720p) HD(1080p) 4K 8K | image quality, default HD\
-H nosubopt | help
