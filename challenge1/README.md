# Challenge 1 #

## Methods for the minimization of a multivariate function ##

Given a function $f$ from $R^n$ to $R$ we want to find the minimum value using different techniques like gradient decent and momentum/heavy-ball. 

### Gradient Decent Method
This program finds the minimum using the gradient decent method. When running the program the user is asked to spesify what step size strategy to use by typing 1, 2 og 3 to the terminal. The options are:

- Exponential decay: $\alpha_k = \alpha^{0} e^{-\mu k}$
- inverse decay: $\alpha_k = \frac{\alpha^{0}}{1+\mu k}$
- Armijo rule: (Explination in [pdf](https://github.com/bangkorkor/PACS-challenges/blob/main/challenge1/Challenge23-24-1.pdf))

note: I am not shure the Armijo strategy is working properly, the step size seems to be constant. 

### Momentum/Heavy Ball Method

The minimization problem is solved by taking the following update rule:
- given $d_0 = -\alpha_0 \nabla f(x_0)\$ 
- $x_{k+1} = x_k + d_k\$
- $d_{k+1} = \eta d_k - \alpha_{k+1} \nabla f(x_{k+1})\$

The problem uses a constant step size $a_0$. 


## Running the code ##


No external libraries are required. To clone the repository on local, go in the folder where you want to store the repo and do 
```bash
git clone https://github.com/bangkorkor/PACS-challenges.git
```
To run the code, navigate to the right folder (gradientDecent or heavyBallMethod) using ```cd challenge1/src/<FOLDER> ```

To compile the code, just do ```make```in the right folder. And to execute do ```./main ```

