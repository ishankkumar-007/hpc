import random

def is_valid(x, y, n, m):
    """Check if coordinates are within grid bounds"""
    return 0 <= x < n and 0 <= y < m

def get_neighbors(x, y, n, m):
    """Get valid neighboring coordinates"""
    directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]  # right, down, left, up
    neighbors = []
    for dx, dy in directions:
        new_x, new_y = x + dx, y + dy
        if is_valid(new_x, new_y, n, m):
            neighbors.append((new_x, new_y))
    return neighbors

def generate_path(n, m):
    """Generate a random path from (0,0) to (n-1,m-1)"""
    # Initialize grid with all walls
    grid = [[1 for _ in range(m)] for _ in range(n)]
    
    # Start point
    current = (0, 0)
    end = (n-1, m-1)
    path = [current]
    grid[0][0] = 0
    
    while current != end:
        x, y = current
        neighbors = get_neighbors(x, y, n, m)
        # Filter neighbors to prefer moving towards the goal
        valid_neighbors = []
        for next_x, next_y in neighbors:
            if (next_x, next_y) not in path:
                if next_x > x or next_y > y:  # Prefer moving right or down
                    valid_neighbors.append((next_x, next_y))
        
        if not valid_neighbors:  # If no preferred direction, use any unvisited neighbor
            valid_neighbors = [n for n in neighbors if n not in path]
        
        if not valid_neighbors:  # If stuck, backtrack
            path.pop()
            if path:
                current = path[-1]
                continue
            else:
                return None  # Path generation failed
        
        # Choose next step
        next_pos = random.choice(valid_neighbors)
        path.append(next_pos)
        current = next_pos
        grid[next_pos[0]][next_pos[1]] = 0
    
    return grid

def add_random_paths(grid, n, m):
    """Add some random additional paths to make the maze more interesting"""
    for i in range(n):
        for j in range(m):
            if grid[i][j] == 1 and random.random() < 0.3:  # 30% chance to convert wall to path
                grid[i][j] = 0
    return grid

def generate_grid(n, m, filename):
    """Generate a grid with guaranteed path and save to file"""
    while True:
        grid = generate_path(n, m)
        if grid is not None:
            break
    
    # Add some random additional paths
    grid = add_random_paths(grid, n, m)
    
    # Save grid to file
    with open(filename, 'w') as f:
        for row in grid:
            line = ','.join(map(str, row)) + ','
            f.write(line + '\n')
    
    return grid

# Example usage
if __name__ == "__main__":
    # Get input from user
    n = int(input("Enter number of rows: "))
    m = int(input("Enter number of columns: "))
    filename = input("Enter filename to save the grid: ")
    
    # Generate and save the grid
    grid = generate_grid(n, m, filename)
    
    # Print the grid for visualization
    print("\nGenerated Grid:")
    # for row in grid:
    #     print(' '.join(map(str, row)))