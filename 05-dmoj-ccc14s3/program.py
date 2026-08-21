# Simulates trying to drive the cars down the hill in their required order.
def possible(cars, n):
    # The branch is a last-in-first-out structure,
    # hence we use it as a stack.
    branch = []
    # We test trying to move out every car from `1` to `n` strictly in that order.
    for lake in range(1, n+1):
        # If the car is on the edge of the branch or the original mountain,
        # then it is possible to move this car out in order.
        if branch and branch[-1] == lake:
            branch.pop()
        elif cars and cars[-1] == lake:
            cars.pop()
        else:
            # Otherwise, the only way you can attempt to move out your desired car
            # is to move cars from the mountain into the branch until you find the one you want.
            while cars and cars[-1] != lake:
                branch.append(cars.pop())
            # If you cannot find the car in the process of doing this, then it is impossible.
            if len(cars) == 0:
                return False
            cars.pop()
    return True

t = int(input())
for _ in range(t):
    n = int(input())
    # The cars are inputted as they appear reading from the top down the mountain.
    # No order reversal is needed.
    cars = []
    for _ in range(n):
        cars.append(int(input()))
    print('Y' if possible(cars, n) else 'N')
