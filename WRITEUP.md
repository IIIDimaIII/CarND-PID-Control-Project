# Project: PID Controller
## Project Introduction.
In this project, students were required to complete the C++ implementation of PID controller for the self-driving car simulator.
Describe the effect each of the P, I, D components had in your implementation.
* P: how aggressively the car is steering towards the target path. High P helped to get through hard turns at higher speeds. However, it also leads to significant oscillations around the center of the road, which in worst case end up in the car making 90 degrees turn on a straight line.
* D: smooths overshooting introduced by the P component. If chosen properly it makes oscillations barely noticeable on a straight road.
* I: compensates for biases. When I checked the cumulative CTE while running the simulator, I have noticed that at different segments of the road, the CTE was building up towards one direction (left or right). The I component reduced this issue, although I did not notice the significant effect on the driving.

## Describe how the final hyper parameters were chosen.

After testing the code, I started looking for hyperparameters by establishing a base case – a car moving very slow that aggressively steers towards the center of the road. The base case that worked was (P:3, I:0, D:0) and throttle at 0.05. After that, I was trying to use twiddle algorithm to finetune the parameters however I stopped after few iterations. The problem was that the process was too time-consuming: to assess various combinations I had to monitor the performance of the car manually. And since the most difficult sections of the road happen only in the second half of the lap, one iteration would take several minutes.

I switched to manual tuning. First, I found the combination of lowest P and fixed throttle to pass the lap. Then I found I value to counteract car going from side to side. After few trials, I had a car finishing the course rather gracefully but slowly (4-5 miles/hour).

I started working on increasing the car’s speed increasing throttle value, followed by P and then D values. After few gradual increases, the car was not able to clear hard turns properly – it was moving too fast. I decided to add a parameter to control throttle based on CTE value. I wanted the car to slow down when close to the edges of the road. I experimented with different acceleration controlling functions trying to achieve acceleration in the middle of the course and negative throttle at CTE values of appr. +- 2. I also added logic to prevent moving backward.

I have settled with P I D of 0.75, 0, 40.0 and dynamically calculated throttle:

0.7 – 0.7 * (|p_error|)<sup>2</sup>

As the final step, I monitored i_error and tried different values of I such that the error’s value reduced after completing a lap. Thus, my final hyper-parameters became:

PID: 0.75, 0.0005, 0.40
Throttle = 0.7 – 0.7 * (|p_error|)<sup>2</sup>
