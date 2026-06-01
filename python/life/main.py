Position = tuple[int, int]


class World:
    def __init__(self, start_cells=None) -> None:
        self.cells: dict[Position, bool] = start_cells or {}
        self.bounds: tuple[int, int, int, int] | None = None

    def set_cell(self, position: Position, alive: bool = True) -> None:
        self.cells[position] = alive
        self._update_bounds(position)
        self._create_cell_bounds(position)

    def _update_bounds(self, position: Position) -> None:
        i, j = position
        if self.bounds is None:
            self.bounds = (i, j, i, j)
        x, y, w, h = self.bounds
        x = min(x, i)
        y = min(y, j)
        w = max(w, i)
        h = max(h, j)
        self.bounds = x, y, w, h

    def _create_cell_bounds(self, position: Position) -> None:
        for ni, nj in self._get_neighbors(position):
            self.cells[(ni, nj)] = self.cells.get((ni, nj), False)

    def _get_neighbors(self, position: Position) -> list[Position]:
        template = [
            (-1, -1),
            (-1, 0),
            (-1, 1),
            (0, -1),
            (0, 1),
            (1, -1),
            (1, 0),
            (1, 1),
        ]
        i, j = position
        neighbors = []
        for ni, nj in template:
            neighbors.append((i + ni, j + nj))
        return neighbors

    def _count_neighbors(self, position):
        count = 0
        for ni, nj in self._get_neighbors(position):
            if self.cells.get((ni, nj), False):
                count += 1
        return count

    def __next__(self) -> "World":
        new_world = World()
        for position, alive in self.cells.items():
            count = self._count_neighbors(position)
            if alive:
                if count < 2:
                    new_world.set_cell(position, False)
                elif count > 3:
                    new_world.set_cell(position, False)
                else:
                    new_world.set_cell(position, True)
            else:
                if count == 3:
                    new_world.set_cell(position, True)
        return new_world


def main() -> int:
    world = World()
    cells = [
        (-1, -1),
        (-1, 0),
        (-1, 1),
        (0, -1),
        (0, 0),
        (0, 1),
        (1, -1),
        (1, 0),
        (1, 1),
    ]
    for i, j in cells:
        world.set_cell((i, j), True)

    generation = 1
    while True:
        print(f"Generation {generation}")
        generation += 1
        x, y, w, h = world.bounds

        for i in range(x, w + 1):
            for j in range(y, h + 1):
                if world.cells.get((i, j), False):
                    print("#", end="")
                else:
                    print(" ", end="")
            print()
        world = next(world)

        k = input()
        if k.lower().strip() == "q":
            break
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
