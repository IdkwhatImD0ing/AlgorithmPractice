# Predicting Profit of Restraunt given Previous Data

## Background Info

Suppose you run a restaurant franchise and are considering different cities for opening a new outlet. The chain already has trucks in various cities and you have data for profits and populations from the cities. You would like to select which city to expand to next.

Now you will implement linear regression with one variable to predict profits for a food truck.

### Data

The file `ex1data1.txt` contains the dataset. The first column is the population of a city (in 10,000s) and the second column is the profit of a food truck in that city (in $10,000s). A negative value for profit indicates a loss.

## Functions

### Computing Cost

The function `computeCost` computes the cost for a given theta.

### Gradient Descent

Performs gradient descent to learn `theta`. Updates theta by taking `num_iters` gradient steps with learning rate `alpha`.

Also stores the cost for each step in a list.

