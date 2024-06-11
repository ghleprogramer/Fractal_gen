## program calculates fractals in parallel and creates fractal images
### the program can generate:
#### the Mandelbrot Burning ship Tricorn and Julia fractals


The program's usage is: ./fractal_gen \<option-s\>\
#when no options are given the program runs on the defaults


options are:\
-F M(mandelbrot) B(burningship) | fractal type, default M\
-J num,num | quad julia fractal (num,num) is the seed, default not\
-T pos num | number of threads to be used, default 1\
-P pos num | fractal equation power, default 2\
-R pos num | range of fractal, default 4\
-C num,num | farctal center, default -0.6,0\
-M pos num | fractal equation max number of iterations, default 100\
-L pos num | steps in image color gradiant, default 75\
-Q SD(480p) ED(720p) HD(1080p) 4K 8K | image quality, default HD\
-G nosubopt | conjugate fractal equation(neg power), default not\
-H nosubopt | help
