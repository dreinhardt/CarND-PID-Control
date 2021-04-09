
# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

> **My Comment:** Dominik's Writeup


## Compilation

### Your code should compile.
Code must compile without errors with cmake and make.
Given that we've made CMakeLists.txt as general as possible, it's recommend that you do not change it unless you can guarantee that your changes will still compile on any platform.
> **My Comment:** As you can see, I use CMake and the code compiles without any errors.

## Implementation
### The PID procedure follows what was taught in the lessons.
It's encouraged to be creative, particularly around hyperparameter tuning/optimization. However, the base algorithm should follow what's presented in the lessons.
> **My Comment:** I imlemented two PIDs. One for steering and one for throttle. Both are kind of unique. As a reflection, the most important step is to reduce the speed in terms the angle is mismatching our wished behavior. Then, the only way to re-adjust the controler is to slow down and get back to the middle of the track.
Furthermore, I limitted the speed to 80mph. Because of several breaking maneuvers, that speed limit can never be reached (see const double MAX_SPEED = 80;).

## Reflection
### Describe the effect each of the P, I, D components had in your implementation.
Student describes the effect of the P, I, D component of the PID algorithm in their implementation. Is it what you expected?
Visual aids are encouraged, i.e. record of a small video of the car in the simulator and describe what each component is set to.

> **My Comment:** Because I cannot record a video on my machine, I describe my setup in text. 
>  - Parameter P is responsible to reduce the error. As bigger the number    is chosen as faster the car os oszilating around that
> optimum.
>  - Parameter I is responsible to avoid the bias and find the middle    lane, specially in straight track parts. For that demo, I skipped   
> that parameter and chose 0. 
>   - Parameter D is responsible to avoid    overshooting the optimum. A greater parameter (at least greater than    P) will avoid high
> frequent oszilations around the optimum (reduced    error to 0).

### Describe how the final hyperparameters were chosen.
Student discusses how they chose the final hyperparameters (P, I, D coefficients). This could be have been done through manual tuning, twiddle, SGD, or something else, or a combination!

> **My Comment:** For my tuning I didn't used twiddle. 
I tested some parameters and used for the first PID for steering the following configuration. **Unfortunately, creating a screen cast video is not possible and allowed with that business notebook.**
> 
>  - P = 1.0 -> I chose 1 as my main parameter. In case it is small, the car is driving more smoothly around the middle of the lane. This even results in faster speeds, because the car will not drive bigger curves on the street. **I expected, that the car is coming closer to a much more stable driving status. Unimportant which variables I tried to chose, there is always some oszilation because auf always changing lane conditions, like curves. Specially in curves, the car is overshooting a lot!**
>  - I = 0.0 -> I skipped that parameter. As shown in the lessons, that parameter could be a very small number. Because of several curves in the track, I skipped that parameter and used 0. **I expected more usage of that parameter for my drive. Because I did not saw a higher use and change of reaction of the car, I skipped it.**
>  - D = 2.0 -> I used a higher D value to reduce the oszilation frequency around the optimum (reduced error). The parameters are not optimized and oszilation is still visible. **I expected a much better and stable driving condition even in straight lane parts. Not even here, the car is coming to a smooth and centered ride.**
> 
> For my second PID for throttle control I chose: 
> - P = 0.5 -> I chose that variable, because the car seems to react better and had a better speedup in straight lane parts. **I expected here a much faster speedup**
> - I = 0.0 -> I skipped that part because the bias seems to be not in focus in terms of speed. **I would expect here much more effect on more straighter tracks.**
> - D = 1.0 -> this was necessary to chose a parameter which is around 1. Otherwise, the start of my demo would be very slow and the car reacts not fast enough. Holding the correct speed is difficult because of several breaking maneuvers. **I would have expected a much better reaction in case the controller is overreacting. Its only solvable for me to break and throttle down.*
>
> **Overall, the PID controller is nice and easy to implement. But for autonomous cars, it can only be used in combination with other sensors, which detect other obstacles. Furthermore, it can be difficult to drive with it in a multilane road (thinking of lane detection). Another problem is, that the PID controller system reflects only the actual state of the car and its steering reaction in time t. There is no prediction to react on upcoming curves and other difficulties on the track. This is propably one reason, that the car is never getting into a complete stable status.**


## Simulation
### The vehicle must successfully drive a lap around the track.
No tire may leave the drivable portion of the track surface. The car may not pop up onto ledges or roll over any surfaces that would otherwise be considered unsafe (if humans were in the vehicle).
> **My Comment:** As you can see, my car is staying on and within the street as required.